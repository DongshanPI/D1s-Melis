/*
 * ekernel/components/avframework/v4l2/platform/sunxi-vin/vin-cci/sunxi_cci.c
 *
 * Copyright (c) 2007-2017 Allwinnertech Co., Ltd.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include "sunxi_cci.h"
#include "../platform/platform_cfg.h"
#include <log.h>
#include <hal_atomic.h>

#if defined(CONFIG_CCI_MODULE) || defined(CONFIG_CCI) || defined(CONFIG_CCI_TO_TWI)
#define USED_TO_CCI_OR_TWI
#endif

#ifdef USED_TO_CCI_OR_TWI
#include "bsp_cci.h"

#define CCI_MODULE_NAME "vin_cci"

extern hal_spinlock_t vin_lock;
static LIST_HEAD(cci_drv_list);

static hal_irqreturn_t cci_irq_handler(void *dev)
{
	unsigned long flags = 0;
	struct cci_dev *cci = (struct cci_dev *)dev;
	uint32_t __cpsr;

	__cpsr = hal_spin_lock_irqsave(&vin_lock);
	bsp_cci_irq_process(cci->id);
	hal_spin_unlock_irqrestore(&vin_lock ,__cpsr);
	return HAL_IRQ_OK;
}


static int __cci_clk_get(struct cci_dev *dev)
{
#ifndef FPGA_VER
	struct device_node *np = dev->pdev->dev.of_node;

	dev->clock = of_clk_get(np, 0);
	if (IS_ERR_OR_NULL(dev->clock))
		vin_warn("cci get clk failed!\n");
#endif
	return 0;
}

static int __cci_clk_enable(struct cci_dev *dev, int enable)
{
#ifndef FPGA_VER
	if (!IS_ERR_OR_NULL(dev->clock)) {
		if (enable) {
			if (clk_prepare_enable(dev->clock)) {
				vin_err("cci clk enable error!\n");
				return -1;
			}
		} else {
			if (__clk_get_enable_count(dev->clock))
				clk_disable_unprepare(dev->clock);
		}
	}
#endif
	return 0;
}

static void __cci_clk_release(struct cci_dev *dev)
{
#ifndef FPGA_VER
	if (dev->clock)
		clk_put(dev->clock);
#endif
}

static int __cci_pin_config(struct cci_dev *dev, int enable)
{
#ifndef FPGA_VER
	char pinctrl_names[10] = "";

	if (!IS_ERR_OR_NULL(dev->pctrl))
		devm_pinctrl_put(dev->pctrl);

	if (enable)
		strcpy(pinctrl_names, "default");
	else
		strcpy(pinctrl_names, "sleep");

	dev->pctrl = devm_pinctrl_get_select(&dev->pdev->dev, pinctrl_names);
	if (IS_ERR_OR_NULL(dev->pctrl)) {
		vin_err("cci%d request pinctrl handle failed!\n", dev->id);
		return -EINVAL;
	}
	usleep_range(1000, 1200);
#endif
	return 0;
}

static int __cci_pin_release(struct cci_dev *dev)
{
#ifndef FPGA_VER
	if (!IS_ERR_OR_NULL(dev->pctrl))
		devm_pinctrl_put(dev->pctrl);
#endif
	return 0;
}

static struct cci_dev *cci_dev_get(int id)
{
	struct cci_dev *cci;

	list_for_each_entry(cci, &cci_drv_list, cci_list) {
		if (cci->id == id)
			return cci;
	}
	return NULL;
}

void cci_s_power(unsigned int sel, int on_off)
{
	struct cci_dev *cci = cci_dev_get(sel);

	if (cci == NULL) {
		vin_err("cci is NULL!\n");
		return;
	}
	vin_log(VIN_LOG_CCI, "%s, %d!\n", __func__, on_off);

	if (on_off && (cci->use_cnt)++ > 0)
		return;
	else if (!on_off && (cci->use_cnt == 0 || --(cci->use_cnt) > 0))
		return;

	__cci_pin_config(cci, on_off);

	if (on_off) {
		__cci_clk_enable(cci, 1);
		bsp_csi_cci_init_helper(sel);
	} else {
		bsp_csi_cci_exit(sel);
		__cci_clk_enable(cci, 0);
	}
}

#if defined(CONFIG_CCI_TO_TWI)
static int
sunxi_i2c_xfer(struct i2c_adapter *adap, struct twi_msg *msgs, int num)
{
	struct cci_dev *cci = (struct cci_dev *)adap->algo_data;
	struct cci_msg cci_msg;
	unsigned char *buf;
	int i;
	if (num == 1) {                          /*write*/
		cci_msg.bus_fmt.saddr_7bit = msgs->addr;
		cci_msg.bus_fmt.wr_flag = 0;
		cci_msg.bus_fmt.rs_start = START_WITH_ID_W;
		cci_msg.bus_fmt.rs_mode = STOP_START;
		if (msgs->len == 0) {
			cci_msg.bus_fmt.addr_len = 0;
			cci_msg.bus_fmt.data_len = 0;
		} else {
			cci_msg.bus_fmt.addr_len = 1;
			cci_msg.bus_fmt.data_len = msgs->len - 1;
		}
		cci_msg.pkt_buf = msgs->buf;
		cci_msg.pkt_num = 1;

		bsp_cci_tx_start_wait_done(cci->id, &cci_msg);
		return 1;
	} else if (num == 2) {			/*read*/
		buf = kzalloc(1 + msgs[1].len, GFP_KERNEL);
		buf[0] = msgs[0].buf[0];
		cci_msg.bus_fmt.saddr_7bit = msgs[0].addr;
		cci_msg.bus_fmt.wr_flag = 1;
		cci_msg.bus_fmt.rs_start = START_WITH_ID_W;
		cci_msg.bus_fmt.rs_mode = STOP_START;
		cci_msg.bus_fmt.addr_len = 1;
		cci_msg.bus_fmt.data_len = msgs[1].len;
		cci_msg.pkt_buf = buf;
		cci_msg.pkt_num = 1;

		bsp_cci_tx_start_wait_done(cci->id, &cci_msg);
		for (i = 0; i < cci_msg.bus_fmt.data_len; i++)
			msgs[1].buf[i] = buf[i+1];
		kfree(buf);
		return i;
	}
}

static unsigned int sunxi_i2c_functionality(struct i2c_adapter *adap)
{
	return I2C_FUNC_I2C|I2C_FUNC_10BIT_ADDR|I2C_FUNC_SMBUS_EMUL;
};

static const struct i2c_algorithm sunxi_i2c_algorithm = {
	.master_xfer	  = sunxi_i2c_xfer,
	.functionality	  = sunxi_i2c_functionality,
};
#endif

static int cci_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct cci_dev *cci = NULL;
	int ret, irq = 0;

	if (np == NULL) {
		vin_err("CCI failed to get of node\n");
		return -ENODEV;
	}
	cci = kzalloc(sizeof(struct cci_dev), GFP_KERNEL);
	if (!cci) {
		ret = -ENOMEM;
		goto ekzalloc;
	}

	of_property_read_u32(np, "device_id", &pdev->id);
	if (pdev->id < 0) {
		vin_err("CCI failed to get device id\n");
		ret = -EINVAL;
		goto freedev;
	}
	cci->id = pdev->id;
	cci->pdev = pdev;

	irq = irq_of_parse_and_map(np, 0);
	if (irq <= 0) {
		vin_err("[CCI%d] failed to get irq\n", pdev->id);
		ret = -EINVAL;
		goto freedev;
	}
	cci->base = of_iomap(np, 0);
	if (!cci->base) {
		ret = -EIO;
		goto freedev;
	}
	cci->irq = irq;

	list_add_tail(&cci->cci_list, &cci_drv_list);
	init_waitqueue_head(&cci->wait);

#if defined(CONFIG_CCI_TO_TWI)
	cci->adap.owner   = THIS_MODULE;
	cci->adap.nr      = cci->id + 4;
	cci->adap.retries = 3;
	cci->adap.timeout = 5*HZ;
	cci->adap.class   = I2C_CLASS_HWMON | I2C_CLASS_SPD;
	snprintf(cci->adap.name, sizeof(cci->adap.name),
				"twi""%u", cci->adap.nr);
	pdev->dev.init_name = cci->adap.name;

	cci->adap.algo = &sunxi_i2c_algorithm;
#endif
	ret = hal_request_irq(irq, cci_irq_handler, CCI_MODULE_NAME, cci);
	if (ret) {
		vin_err("[CCI%d] requeset irq failed!\n", cci->id);
		goto unmap;
	}
#if defined(CONFIG_CCI_TO_TWI)
	cci->adap.algo_data  = cci;
	cci->adap.dev.parent = &pdev->dev;
	cci->adap.dev.of_node = pdev->dev.of_node;

	ret = i2c_add_numbered_adapter(&cci->adap);
	if (ret < 0) {
		vin_err("[i2c%d] failed to add adapter\n", cci->id);
	}
#endif

	ret = bsp_csi_cci_set_base_addr(cci->id, (unsigned long)cci->base);
	if (ret < 0)
		goto freeirq;

	if (__cci_clk_get(cci)) {
		vin_err("cci clock get failed!\n");
		goto freeirq;
	}
#if defined(CONFIG_CCI_TO_TWI)
	cci_s_power(cci->id, 1);
#endif
	platform_set_drvdata(pdev, cci);
	vin_log(VIN_LOG_CCI, "cci probe end cci_sel = %d!\n", cci->id);

	return 0;
freeirq:
	hal_free_irq(irq, cci);
unmap:
	iounmap(cci->base);
freedev:
	kfree(cci);
ekzalloc:
	vin_err("cci probe err!\n");
	return ret;
}

static int cci_remove(struct platform_device *pdev)
{
	struct cci_dev *cci = platform_get_drvdata(pdev);

	platform_set_drvdata(pdev, NULL);

	__cci_pin_release(cci);
	__cci_clk_release(cci);
	hal_free_irq(cci->irq, cci);
	if (cci->base)
		iounmap(cci->base);
	list_del(&cci->cci_list);
	kfree(cci);
	return 0;
}

static const struct of_device_id sunxi_cci_match[] = {
	{.compatible = "allwinner,sunxi-csi_cci",},
	{},
};

MODULE_DEVICE_TABLE(of, sunxi_cci_match);

static struct platform_driver cci_platform_driver = {
	.probe = cci_probe,
	.remove = cci_remove,
	.driver = {
		   .name = CCI_MODULE_NAME,
		   .owner = THIS_MODULE,
		   .of_match_table = sunxi_cci_match,
		   },
};

#endif

int sunxi_cci_platform_register(void)
{
#ifdef USED_TO_CCI_OR_TWI
	int ret;

	ret = platform_driver_register(&cci_platform_driver);
	if (ret) {
		vin_err("platform driver register failed\n");
		return ret;
	}
	vin_log(VIN_LOG_CCI, "cci_init end\n");
#endif
	return 0;
}

void sunxi_cci_platform_unregister(void)
{
#ifdef USED_TO_CCI_OR_TWI
	platform_driver_unregister(&cci_platform_driver);
	vin_log(VIN_LOG_CCI, "cci_exit end\n");
#endif
}

