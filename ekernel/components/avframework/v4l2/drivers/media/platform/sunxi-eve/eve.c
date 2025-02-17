/*
 * drivers\media\platform\eve.c
 * (C) Copyright 2016-2017
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * xiongyi<xiongyi@allwinnertech.com>
 *
 * Driver for embedded vision engine(EVE).
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 */
#include "eve.h"
#include <linux/signal.h>

#define EVE_INPUT_CLK 24
#define EVE_TIME_DEFAULT 0x80002701
#define EVE_REG_LEN 0x40

#define BIT_HIGH_8 0xff00
#define BIT0 0x1
#define BIT1 0x2
#define BIT2 0x4

/* volatile deleted here*/
static unsigned int *eve_regs_init;
static unsigned int *eve_regs_temp;
static struct fasync_struct *async_queue;
static unsigned long eve_end_flag, eve_int_flag;
static unsigned long eve_sig_sel;
static unsigned char if_error, if_run;
static unsigned long eve_irq_id;
static unsigned int startTime[5] = {0, 0, 0, 0, 0};
static struct dentry *debugfsP;
static struct clk *eve_clk;
static unsigned long time_reg_value = EVE_TIME_DEFAULT;

static void eve_open_clk(struct eve_register *regP, int en)
{
	struct eve_register reg = *regP;
	unsigned long rate;

	if (reg.value == 0x0)
		reg.value = time_reg_value;
	else
		time_reg_value = reg.value;

	rate = EVE_INPUT_CLK * (1 + ((reg.value&BIT_HIGH_8)>>8));
	rate /= 1 + ((reg.value&BIT1)>>1);
	rate /= 1 + (reg.value&BIT0);
	if (clk_set_rate(eve_clk, rate*1000000) < 0)
		printk(KERN_INFO "[EVE]: Set clk failed, use default!\n");
	if (en > 0) {
		if (clk_prepare_enable(eve_clk) < 0) {
			printk(KERN_INFO "[EVE]: Open clk failed!\n");
			return;
		}
		sunxi_periph_reset_assert(eve_clk);
		sunxi_periph_reset_deassert(eve_clk);
		if_error = 1;
		writel(0x0000001f, eve_regs_init);
		writel(0x0000001c, eve_regs_init + 0x01);
		writel(0x00000000, eve_regs_init + 0x01);
		mdelay(5);
		writel(0x00000020, eve_regs_init + 0x01);
		writel(0x00000000, eve_regs_init + 0x01);
	}
}

static void eve_close_clk(void)
{
	sunxi_periph_reset_assert(eve_clk);
	sunxi_periph_reset_deassert(eve_clk);
	if_error = 1;
	writel(0x0000001f, eve_regs_init);
	writel(0x0000001c, eve_regs_init + 0x01);
	writel(0x00000000, eve_regs_init + 0x01);
	mdelay(5);
	writel(0x00000020, eve_regs_init + 0x01);
	writel(0x00000000, eve_regs_init + 0x01);
	clk_disable_unprepare(eve_clk);
}

static void eve_show_regs(void)
{
	int i = 0;
	unsigned long rData = 0;

	for (i = 0; i < EVE_REG_LEN; i++) {
		rData = readl(eve_regs_init + i);
		printk(KERN_INFO "Addr = %#010x, Value = %#010x\n",
		(unsigned int)(eve_regs_init + i), (unsigned int)rData);
	}
}

static void eve_save_regs(void)
{
	int i = 0;
	unsigned long rData = 0;

	printk(KERN_INFO "[EVE]: Save!\n");
	eve_show_regs();
	eve_regs_temp = (unsigned int *)kmalloc(EVE_REG_LEN*sizeof(unsigned int), \
					GFP_KERNEL);
	if (IS_ERR_OR_NULL(eve_regs_temp)) {
		printk(KERN_INFO "[EVE]: Error: malloc failed!\n");
		return;
	}
	for (i = 1; i < EVE_REG_LEN; i++) {
		rData = readl(eve_regs_init + i);
		eve_regs_temp[i] = rData;
	}
}

static void eve_recover_regs(void)
{
	int i = 0;

	if (IS_ERR_OR_NULL(eve_regs_temp))
		return;
	for (i = 1; i < EVE_REG_LEN; i++)
		writel(eve_regs_temp[i], eve_regs_init + i);
	kfree(eve_regs_temp);
	eve_regs_temp = NULL;
	printk(KERN_INFO "[EVE]: recover!\n");
	eve_show_regs();
}

static hal_irqreturn_t eve_interrupt(void *data)
{
	unsigned long now_int, int_mask;

	int_mask = readl(eve_regs_init + 0x01);
	int_mask = ((int_mask&0x03)<<3) | ((int_mask&0x1C00)>>10);
	now_int = readl(eve_regs_init);
	writel(now_int, eve_regs_init);
	eve_int_flag |= (now_int & int_mask);
	if (eve_int_flag > 0x07) {
		writel(0x3f, eve_regs_init);
		printk(KERN_INFO "[EVE]: Time out!\n");
		eve_int_flag = 0;
		eve_save_regs();
		sunxi_periph_reset_assert(eve_clk);
		sunxi_periph_reset_deassert(eve_clk);
		eve_recover_regs();
		goto SAFE_RETURN;
	} else
		if_error = 0;

	if ((((eve_int_flag & 0x04) > 0) ||
		(eve_int_flag >= eve_end_flag)) && async_queue) {
		startTime[eve_int_flag&BIT0]++;
		startTime[eve_int_flag&BIT1]++;
		startTime[eve_int_flag&BIT2]++;
		eve_sig_sel = eve_int_flag;
		eve_int_flag &= (~eve_sig_sel);
		eve_end_flag &= (~eve_sig_sel);
SAFE_RETURN:
		kill_fasync(&async_queue, SIGIO, POLL_IN);
	}
	return IRQ_HANDLED;
}

static int eve_fasync(int fd, struct file *filp, int mode)
{
	return fasync_helper(fd, filp, mode, &async_queue);
}

static int evedev_open(struct inode *node, struct file *filp)
{
	if_run = 1;
	return 0;
}

static int evedev_close(struct inode *node, struct file *filp)
{
	if_run = 0;
	return eve_fasync(-1, filp, 0);
}

static int eve_write(struct file *filp,
	const char __user *buf,
	size_t count,
	loff_t *ppos)
{
	if (copy_from_user(&eve_end_flag,
	(void __user *)buf,
	sizeof(unsigned long)))
		return -EFAULT;
	eve_end_flag &= 0x07;
	eve_sig_sel = 0x00;
	return 0;
}

static int eve_read(struct file *filp,
	char __user *buf,
	size_t count,
	loff_t *ppos)
{
	if (copy_to_user((char *)buf, &eve_sig_sel, sizeof(unsigned long)))
		return -EFAULT;
	return 0;
}


static long eve_ioctl(struct file *filp,
	unsigned int cmd,
	unsigned long arg)
{
	struct eve_register reg;

	if (unlikely(copy_from_user(&reg, (void __user *)arg,
			sizeof(struct eve_register)))) {
		return -EFAULT;
	}
BACK_POINT:
		if (likely(cmd == EVE_WRITE_REGISTER)) {
			writel(reg.value, eve_regs_init + (reg.addr>>2));
			return 0;
		} else if (cmd == EVE_READ_RESNUM) {
			return readl(eve_regs_init + (reg.addr>>2));
		}
			switch (cmd) {
			case EVE_READ_REGISTER:
				return readl(eve_regs_init + (reg.addr>>2));
			case EVE_OPEN_CLK:
				eve_open_clk(&reg, 1);
				break;
			case EVE_SYS_RESET:
				sunxi_periph_reset_assert(eve_clk);
				sunxi_periph_reset_deassert(eve_clk);
				break;
			case EVE_MOD_RESET:
				if_error = 1;
				writel(0x0000001f, eve_regs_init);
				writel(0x0000001c, eve_regs_init + 0x01);
				writel(0x00000000, eve_regs_init + 0x01);
				mdelay(5);
				writel(0x00000020, eve_regs_init + 0x01);
				writel(0x00000000, eve_regs_init + 0x01);
				goto BACK_POINT;
			case EVE_CLOSE_CLK:
				eve_close_clk();
				break;
			case EVE_PLL_SET:
				eve_open_clk(&reg, -1);
				break;
			default:
				break;
			}
	return 0;
}

static int sunxi_eve_show(struct seq_file *m, void *v)
{
	unsigned long rdata1, rdata2, rdata3, rdata4;

	seq_printf(m, "[sunxi-eve] IP Version: %#010x\n",
						readl(eve_regs_init + (0x0c>>2)));
	seq_printf(m, "----------------MODULE STATUS---------------\n");
/*
	seq_printf(m, "      DMA     SF      BOOST    Time out IRQ\n");
	seq_printf(m, "      %ld       %ld       %ld        %d          %ld\n\n",
			-1*((eve_int_flag&0x10)>>4) + 1*((eve_int_flag&0x4)>>2),
			-1*((eve_int_flag&0x8)>>3) + 1*((eve_int_flag&0x2)>>1),
			-1*((eve_int_flag&0x8)>>3) + 1*(eve_int_flag&0x1),
			(if_error == 2)?1 : 0,
			eve_sig_sel);
*/
	seq_printf(m, "----------------MODULE PARAM---------------\n");
	seq_printf(m, "      eve_end_flag     \n");
	seq_printf(m, "      %#010lx\n\n", eve_end_flag);
	seq_printf(m, "-------------MODULE INT TIMEs-------------\n");
	seq_printf(m, "      DMA          SF         BOOST\n");
	seq_printf(m, "    %d          %d          %d\n\n",
			startTime[4], startTime[2], startTime[1]);
	seq_printf(m, "---------------TASK SIZE INFO--------------\n");
	seq_printf(m, "  Module Name    Input     ROI    Output  Channel Layels\n");
	rdata1 = readl(eve_regs_init + (0x10>>2));
	rdata2 = readl(eve_regs_init + (0x14>>2));
	rdata3 = readl(eve_regs_init + (0x18>>2));
	seq_printf(m, "     <DMA>    %ld x %ld  %ld x %ld  %ld x %ld   %d   %d\n",
			((rdata1&0xffff0000)>>16), rdata1&0xffff,
			((rdata2&0xffff0000)>>16), rdata2&0xffff,
			((rdata3&0xffff0000)>>16), rdata3&0xffff,
			2, 1);
	rdata1 = readl(eve_regs_init + (0x38>>2));
	rdata2 = readl(eve_regs_init + (0x3c>>2));
	rdata3 = readl(eve_regs_init + (0x40>>2));
	rdata4 = readl(eve_regs_init + (0x80>>2));
	seq_printf(m, "     <SF>     %ld x %ld  %ld x %ld  %ld x %ld   %ld  %ld\n",
			((rdata1&0xffff0000)>>16), rdata1&0xffff,
			((rdata2&0xffff0000)>>16), rdata2&0xffff,
			((rdata3&0xffff0000)>>16), rdata3&0xffff,
			rdata4&0x7, ((rdata4&0x3f00)>>8));
	rdata1 = readl(eve_regs_init + (0x88>>2));
	rdata4 = readl(eve_regs_init + (0xa4>>2));
	seq_printf(m, "   <BOOST>    %ld x %ld      -               %ld      %ld\n",
			((rdata1&0xffff0000)>>16), rdata1&0xffff,
			((rdata4&0x1c)>>2), ((rdata4&0x3f0000)>>16)+1);
	return 0;
}

static int sunxi_eve_open(struct inode *inode,
	struct file *file)
{
	return single_open(file, sunxi_eve_show, NULL);
}

static int eve_suspend(struct platform_device *pdev,
	pm_message_t state){
	printk(KERN_INFO "[EVE]: Time for sleep!\n");
	if (if_run > 0) {
		eve_save_regs();
		eve_close_clk();
	}
	return 0;
}

static int eve_resume(struct platform_device *pdev)
{
	struct eve_register reg;

	printk(KERN_INFO "[EVE]: Weak up!\n");
	if (if_run > 0) {
		reg.addr = 0x030010c0;
		reg.value = 0x0;
		eve_open_clk(&reg, 1);
		eve_recover_regs();
		kill_fasync(&async_queue, SIGIO, POLL_IN);
	}
	return 0;
}

static const struct file_operations eve_fops = {
	.owner	=	THIS_MODULE,
	.unlocked_ioctl	=	eve_ioctl,
	.fasync	=	eve_fasync,
	.read	=	eve_read,
	.write	=	eve_write,
	.open	=	evedev_open,
	.release	=	evedev_close
};

static const struct file_operations eve_proc_fops = {
	.owner	=	THIS_MODULE,
	.open	=	sunxi_eve_open,
	.read	=	seq_read,
	.llseek =	seq_lseek,
	.release =	single_release,
};

static struct miscdevice eve_dev = {
	.minor	=	MISC_DYNAMIC_MINOR,
	.name	=	DEVICE_NAME,
	.fops	=	&eve_fops
};

static struct of_device_id eve_of_match[] = {
	{ .compatible = "allwinner,sunxi-aie-eve", },
	{}
};
MODULE_DEVICE_TABLE(of, eve_of_match);

static struct platform_driver eve_pm_driver = {
	.driver		= {
		.name	= "EVE_PM",
		.owner	= THIS_MODULE,
		.of_match_table = eve_of_match,
	},
	.suspend	= eve_suspend,
	.resume		= eve_resume,
};

static int __init eve_init(void)
{
	struct device_node *node;
	int r = misc_register(&eve_dev);

	if (r >= 0)
		printk(KERN_INFO "EVE device had been registered! %d\n", r);
	else
		printk(KERN_INFO "EVE device register failed! %d\n", r);

	r = platform_driver_probe(&eve_pm_driver, NULL);
	if (r >= 0)
		printk(KERN_INFO "EVE pm driver had been registered! %d\n", r);
	else
		printk(KERN_INFO "EVE pm driver register failed! %d\n", r);


	node = of_find_compatible_node(NULL, NULL,
	"allwinner,sunxi-aie-eve");
	eve_irq_id = irq_of_parse_and_map(node, 0);
	eve_clk = of_clk_get(node, 1);
	if ((!eve_clk) || IS_ERR(eve_clk)) {
		printk(KERN_INFO "[EVE]: Error, can't find clk!\n");
		return -EFAULT;
	}
	r = hal_request_irq(eve_irq_id, eve_interrupt, DEVICE_NAME, NULL);
	if (r < 0) {
		printk(KERN_INFO "Request EVE Irq error! return %d\n", r);
		return -EFAULT;
	}
	printk(KERN_INFO "Request EVE Irq success! return %d, irq_id = %ld\n",
				r,  eve_irq_id);
	eve_regs_init = (unsigned int *)of_iomap(node, 0);
	printk(KERN_INFO "[EVE] remap from %#010x to %#010lx\n", 0x01500000,
				(unsigned long)eve_regs_init);
	startTime[0] = 0; startTime[1] = 0;
	startTime[2] = 0; startTime[3] = 0; startTime[4] = 0;
	debugfsP = debugfs_create_file("sunxi-eve", 0444, NULL, NULL,
									&eve_proc_fops);
	if (IS_ERR_OR_NULL(debugfsP))
		printk(KERN_INFO "Warning: Fail to create debugfs node!\n");
	eve_end_flag = 0;
	if_run = 0;
	return 0;
}

static void __exit eve_exit(void)
{
	hal_free_irq(eve_irq_id, NULL);
	iounmap(eve_regs_init);
	clk_put(eve_clk);
	platform_driver_unregister(&eve_pm_driver);
	misc_deregister(&eve_dev);
	printk(KERN_INFO "EVE device has been removed!\n");
	if (!IS_ERR_OR_NULL(debugfsP))
		debugfs_remove(debugfsP);
};

module_init(eve_init);
module_exit(eve_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("XiongYi<xiongyi@allwinnertech.com>");
MODULE_DESCRIPTION("EVE device driver");
MODULE_VERSION("1.0");
MODULE_ALIAS("platform:EVE(AW1721)");
