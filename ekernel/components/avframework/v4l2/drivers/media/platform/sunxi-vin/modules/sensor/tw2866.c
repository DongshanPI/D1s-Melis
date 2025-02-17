
/*
 * A V4L2 driver for TW2866 YUV cameras.
 *
 * Copyright (c) 2017 by Allwinnertech Co., Ltd.  http://www.allwinnertech.com
 *
 * Authors:  Zhao Wei <zhaowei@allwinnertech.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */


#include <melis/init.h>
#include <linux/videodev2.h>
#include <hal_timer.h>
#include <v4l2-device.h>
#include <v4l2-mediabus.h>

#include "camera.h"
#include "sensor_helper.h"

#define MCLK              (24*1000*1000)
#define CLK_POL           V4L2_MBUS_PCLK_SAMPLE_FALLING
#define V4L2_IDENT_SENSOR 0xc8

/*
 * Our nominal (default) frame rate.
 */
#define SENSOR_FRAME_RATE 30

/*
 * The TW2866 sits on i2c with ID 0x50
 */
#define I2C_ADDR 0x50 /* tw2866 work when CCI in 100k speed */
#define SENSOR_NAME "tw2866"


#if 0
static struct regval_list read_reg[] = {
	{0x00, 0x00},
	{0x01, 0x00},
	{0x02, 0x00},
	{0x03, 0x00},
	{0xFA, 0x00},		/*output clock, base of pclk, 1ch*d1 = 27m */
	{0xFB, 0x00},
	{0xFC, 0x00},
	{0x9C, 0x00},		/*A0 */
	{0x9E, 0x00},
	{0xF9, 0x00},		/*Video misc */
	{0xAA, 0x00},		/*Video AGC */
	{0x6A, 0x00},		/*CLKPO2/CLKNO2 off */
	{0x6B, 0x00},		/*CLKPO3/CLKNO3 off */
	{0x6C, 0x00},		/*CLKPO4/CLKNO4 off */
	{0x60, 0x00},		/*0x15/0x05�� */
	{0x61, 0x00},
	{0xca, 0x00},		/*chmd: 0=1ch 1=2ch 2=4ch */
	{0xcd, 0x00},		/*1st */
	{0x42, 0x00},		/*testpattern 75%color bar */
};

#endif

#if 0
static struct regval_list reg_d1_1ch[] = {
	{0x00, 0x00},
	{0x01, 0x00},
	{0x02, 0x64},
	{0x03, 0x11},
	{0xFA, 0x40},		/*output clock, base of pclk, 1ch*d1 = 27m */
	{0xFB, 0x2F},
	{0xFC, 0xFF},
	{0x9C, 0x20},		/*A0 */
	{0x9E, 0x52},
	{0xF9, 0x11},		/*Video misc */
	{0xAA, 0x00},		/*Video AGC */
	{0x6A, 0x0f},		/*CLKPO2/CLKNO2 off */
	{0x6B, 0x0f},		/*CLKPO3/CLKNO3 off */
	{0x6C, 0x0f},		/*CLKPO4/CLKNO4 off */
	{0x60, 0x15},		/*0x15/0x05*/
	{0x61, 0x03},
	{0xca, 0x00},		/*chmd: 0=1ch 1=2ch 2=4ch */
	{0xcd, 0xe4},		/*1st */
	{0x5b, 0x11},		/*pad drive set */
};
#endif

#if 0
static struct regval_list reg_d1_2ch[] = {
	{0x00, 0x00},
	{0x01, 0x00},
	{0x02, 0x64},
	{0x03, 0x11},
	{0xFA, 0x45},		/*0x45 *//*[7]:v-scale output clock, base of pclk, 2ch*d1 = 54m */
	{0xFB, 0x2F},
	{0xFC, 0xFF},
	{0x9C, 0x20},		/*A0 */
	{0x9E, 0x52},
	{0xF9, 0x11},		/*Video misc */
	{0xAA, 0x00},		/*Video AGC */
	{0xca, 0x01},		/*chmd: 0=1ch 1=2ch 2=4ch */
	{0xcd, 0xe4},		/*1st */
	{0xcc, 0x39},		/*2nd */
	{0xcb, 0x00},		/*4ch cif */
	{0x60, 0x15},		/*0x15/0x05*/
	{0x61, 0x03},
	{0x5b, 0x00},		/*pad drive set */
};
#endif

#if 1
static struct regval_list reg_d1_4ch[] = {
	{0x00, 0x00},
	{0x01, 0x00},
	{0x02, 0x64},
	{0x03, 0x11},
	{0xFA, 0x4a},		/*output clock, base of pclk, 4ch*cif = 54m  4ch*d1 = 108m */
	{0xFB, 0x2F},
	{0xFC, 0xFF},
	{0x9C, 0x20},		/*A0 */
	{0x9E, 0x52},
	{0x6A, 0x05},
	{0x6B, 0x05},
	{0x6C, 0x05},
	{0xF9, 0x11},		/*Video misc */
	{0xAA, 0x00},		/*Video AGC */
	{0xca, 0x02},		/*chmd: 0=1ch 1=2ch 2=4ch */
	{0xcd, 0xe4},		/*1st */
	{0xcc, 0x39},		/*2nd */
	{0xcb, 0x00},		/*4ch cif */
	{0x60, 0x15},		/*0x15/0x05*/
	{0x61, 0x03},
	{REG_DLY, 0x20},
	{0x5b, 0xFF},		/*pad drive set */
};
#endif

#if 0
/*This be used when ddr sample mode enable*/
static struct regval_list reg_cif_4ch[] = {
	/*CSI_MODE==CSI_MODE_TW2866_4CH_CIF */
	{0x00, 0x00},
	{0x01, 0x00},
	{0x02, 0x64},
	{0x03, 0x11},
	{0xFA, 0x45},  /*output clock, base of pclk, 4ch*cif = 54m  4ch*d1 = 108m */
	{0xFB, 0x2F},
	{0xFC, 0xFF},
	{0x9C, 0x20},  /*A0 */
	{0x9E, 0x52},
	{0x6A, 0x0f},
	{0x6B, 0x0f},
	{0x6C, 0x0f},
	{0xF9, 0x11},  /*Video misc*/
	{0xAA, 0x00},  /*Video AGC*/
	{0xca, 0x02},  /*chmd: 0=1ch 1=2ch 2=4ch*/
	{0xcd, 0xe4},  /*1st*/
	{0xcc, 0x39},  /*2nd*/
	{0xcb, 0x00},  /*4ch cif*/
	{0x60, 0x15},  /*0x15/0x05*/
	{0x61, 0x03},
	{0xFF, 0X20},
	{0x5b, 0xff},  /*pad drive set*/
	{0x42, 0x98},  /*testpattern 75%color bar*/

};
#endif

static int sensor_s_sw_stby(struct v4l2_subdev *sd, int on_off)
{
	if (on_off)
		vin_gpio_write(sd, RESET, CSI_GPIO_LOW);
	else
		vin_gpio_write(sd, RESET, CSI_GPIO_HIGH);
	return 0;
}

static int sensor_power(struct v4l2_subdev *sd, int on)
{
	switch (on) {
	case STBY_ON:
		sensor_dbg("CSI_SUBDEV_STBY_ON!\n");
		sensor_s_sw_stby(sd, ON);
		break;
	case STBY_OFF:
		sensor_dbg("CSI_SUBDEV_STBY_OFF!\n");
		sensor_s_sw_stby(sd, OFF);
		break;
	case PWR_ON:
		sensor_dbg("CSI_SUBDEV_PWR_ON!\n");
		sensor_print("CSI_SUBDEV_PWR_ON!\n");
		cci_lock(sd);
		vin_gpio_set_status(sd, PWDN, 1);
		vin_gpio_set_status(sd, RESET, 1);
		vin_gpio_write(sd, PWDN, CSI_GPIO_HIGH);
		vin_gpio_write(sd, RESET, CSI_GPIO_LOW);
		usleep(1000);
		vin_set_mclk_freq(sd, MCLK);
		vin_set_mclk(sd, ON);
		usleep(10000);
		vin_gpio_write(sd, POWER_EN, CSI_GPIO_HIGH);
		vin_set_pmu_channel(sd, IOVDD, ON);
		vin_set_pmu_channel(sd, AVDD, ON);
		vin_set_pmu_channel(sd, DVDD, ON);
		vin_set_pmu_channel(sd, AFVDD, ON);
		vin_gpio_write(sd, PWDN, CSI_GPIO_LOW);
		usleep(10000);
		vin_gpio_write(sd, RESET, CSI_GPIO_HIGH);
		usleep(30000);
		cci_unlock(sd);
		break;
	case PWR_OFF:
		sensor_dbg("CSI_SUBDEV_PWR_OFF!\n");
		sensor_print("CSI_SUBDEV_PWR_OFF!\n");
		cci_lock(sd);
		vin_set_mclk(sd, OFF);
		vin_gpio_write(sd, POWER_EN, CSI_GPIO_LOW);
		vin_set_pmu_channel(sd, AFVDD, OFF);
		vin_set_pmu_channel(sd, DVDD, OFF);
		vin_set_pmu_channel(sd, AVDD, OFF);
		vin_set_pmu_channel(sd, IOVDD, OFF);
		usleep(10000);
		vin_gpio_write(sd, PWDN, CSI_GPIO_HIGH);
		vin_gpio_write(sd, RESET, CSI_GPIO_LOW);
		vin_gpio_set_status(sd, RESET, 0);
		vin_gpio_set_status(sd, PWDN, 0);
		cci_unlock(sd);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static int sensor_reset(struct v4l2_subdev *sd, u32 val)
{
	vin_gpio_write(sd, RESET, CSI_GPIO_LOW);
	usleep(5000);
	vin_gpio_write(sd, RESET, CSI_GPIO_HIGH);
	usleep(5000);
	return 0;
}

static int sensor_detect(struct v4l2_subdev *sd)
{
	data_type rdval = 0;
	int cnt = 0;

	sensor_read(sd, 0xff, &rdval);
	sensor_print("V4L2_IDENT_SENSOR = 0x%x\n", rdval);

	while ((rdval != V4L2_IDENT_SENSOR) && (cnt < 5)) {
		sensor_read(sd, 0xff, &rdval);
		sensor_print("retry = %d, V4L2_IDENT_SENSOR = %x\n", cnt, rdval);
		cnt++;
	}

	if (rdval != V4L2_IDENT_SENSOR)
		return -ENODEV;

	return 0;
}

static int sensor_init(struct v4l2_subdev *sd, u32 val)
{
	int ret;
	struct sensor_info *info = to_state(sd);

	sensor_dbg("sensor_init\n");

	/*Make sure it is a target sensor */
	ret = sensor_detect(sd);
	if (ret) {
		sensor_err("chip found is not an target chip.\n");
		return ret;
	}

	info->focus_status = 0;
	info->low_speed = 0;
	info->width = VGA_WIDTH;
	info->height = VGA_HEIGHT;
	info->hflip = 0;
	info->vflip = 0;

	info->tpf.numerator = 1;
	info->tpf.denominator = 30;	/* 30fps */

	info->preview_first_flag = 1;
	return 0;
}

static long sensor_ioctl(struct v4l2_subdev *sd, unsigned int cmd, void *arg)
{
	int ret = 0;
	struct sensor_info *info = to_state(sd);

	switch (cmd) {
	case GET_CURRENT_WIN_CFG:
		if (info->current_wins != NULL) {
			memcpy(arg,
			       info->current_wins,
			       sizeof(struct sensor_win_size));
			ret = 0;
		} else {
			sensor_err("empty wins!\n");
			ret = -1;
		}
		break;
	case SET_FPS:
		break;
	case VIDIOC_VIN_SENSOR_CFG_REQ:
		sensor_cfg_req(sd, (struct sensor_config *)arg);
		break;
	default:
		return -EINVAL;
	}
	return ret;
}

/*
 * Store information about the video data format.
 */
static struct sensor_format_struct sensor_formats[] = {
	{
	.desc = "BT656 4CH",
	.mbus_code = MEDIA_BUS_FMT_UYVY8_2X8,
	.regs = NULL,
	.regs_size = 0,
	.bpp = 2,
	},
};
#define N_FMTS ARRAY_SIZE(sensor_formats)

/*
 * Then there is the issue of window sizes.  Try to capture the info here.
 */

static struct sensor_win_size sensor_win_sizes[] = {
	{
	 .width = 704,
	 .height = 576,
	 .hoffset = 0,
	 .voffset = 0,
	 .regs = reg_d1_4ch,
	 .regs_size = ARRAY_SIZE(reg_d1_4ch),
	 .set_size = NULL,
	 },
};

#define N_WIN_SIZES (ARRAY_SIZE(sensor_win_sizes))

static int sensor_g_mbus_config(struct v4l2_subdev *sd,
				struct v4l2_mbus_config *cfg)
{
	cfg->type = V4L2_MBUS_BT656;
	cfg->flags = CLK_POL | CSI_CH_0 | CSI_CH_1 | CSI_CH_2 | CSI_CH_3;
	//cfg->flags = CLK_POL | CSI_CH_0;
	return 0;
}

static int sensor_g_ctrl(struct v4l2_ctrl *ctrl)
{
	return -EINVAL;
}

static int sensor_s_ctrl(struct v4l2_ctrl *ctrl)
{
	return -EINVAL;
}

static int sensor_reg_init(struct sensor_info *info)
{
	struct v4l2_subdev *sd = &info->sd;
	struct sensor_format_struct *sensor_fmt = info->fmt;
	struct sensor_win_size *wsize = info->current_wins;

	sensor_dbg("sensor_reg_init\n");

	sensor_write_array(sd, sensor_fmt->regs, sensor_fmt->regs_size);

	if (wsize->regs)
		sensor_write_array(sd, wsize->regs, wsize->regs_size);

	if (wsize->set_size)
		wsize->set_size(sd);

	info->fmt = sensor_fmt;
	info->width = wsize->width;
	info->height = wsize->height;

	return 0;
}

static int sensor_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct sensor_info *info = to_state(sd);

	sensor_print("%s on = %d, %d*%d %x\n", __func__, enable,
		  info->current_wins->width,
		  info->current_wins->height, info->fmt->mbus_code);

	if (!enable)
		return 0;
	return sensor_reg_init(info);
}

/* ----------------------------------------------------------------------- */
static const struct v4l2_ctrl_ops sensor_ctrl_ops = {
	.g_volatile_ctrl = sensor_g_ctrl,
	.s_ctrl = sensor_s_ctrl,
};

static const struct v4l2_subdev_core_ops sensor_core_ops = {
	.reset = sensor_reset,
	.init = sensor_init,
	.s_power = sensor_power,
	.ioctl = sensor_ioctl,
};

static const struct v4l2_subdev_video_ops sensor_video_ops = {
	.s_parm = sensor_s_parm,
	.g_parm = sensor_g_parm,
	.s_stream = sensor_s_stream,
	.g_mbus_config = sensor_g_mbus_config,
};

static const struct v4l2_subdev_pad_ops sensor_pad_ops = {
	.enum_mbus_code = sensor_enum_mbus_code,
	.enum_frame_size = sensor_enum_frame_size,
	.get_fmt = sensor_get_fmt,
	.set_fmt = sensor_set_fmt,
};

static const struct v4l2_subdev_ops sensor_ops = {
	.core = &sensor_core_ops,
	.video = &sensor_video_ops,
	.pad = &sensor_pad_ops,
};


/* ----------------------------------------------------------------------- */
static struct cci_driver cci_drv[] = {
	{
		.name = SENSOR_NAME,
		.addr_width = CCI_BITS_8,
		.data_width = CCI_BITS_8,
	}
};

static int sensor_init_controls(struct v4l2_subdev *sd, const struct v4l2_ctrl_ops *ops)
{
	struct sensor_info *info = to_state(sd);
	struct v4l2_ctrl_handler *handler = &info->handler;
	struct v4l2_ctrl *ctrl;
	int ret = 0;

	v4l2_ctrl_handler_init(handler, 2);

	v4l2_ctrl_new_std(handler, ops, V4L2_CID_GAIN, 1 * 1600,
			      256 * 1600, 1, 1 * 1600);
	ctrl = v4l2_ctrl_new_std(handler, ops, V4L2_CID_EXPOSURE, 0,
			      65536 * 16, 1, 0);
	if (ctrl != NULL)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;

	if (handler->error) {
		ret = handler->error;
		v4l2_ctrl_handler_free(handler);
	}

	sd->ctrl_handler = handler;

	return ret;
}


static int sensor_probe(int id)
{
	struct v4l2_subdev *sd;
	struct sensor_info *info;

	info = rt_calloc(1, sizeof(struct sensor_info));
	if (info == NULL)
		return -ENOMEM;
	sd = &info->sd;
	cci_dev_probe_helper(sd, &sensor_ops, &cci_drv[id]);

	sensor_init_controls(sd, &sensor_ctrl_ops);

	rt_mutex_init(&info->lock, "sinfomtx", RT_IPC_FLAG_FIFO);

	info->fmt = &sensor_formats[0];
	info->fmt_pt = &sensor_formats[0];
	info->win_pt = &sensor_win_sizes[0];
	info->fmt_num = N_FMTS;
	info->win_size_num = N_WIN_SIZES;
	info->sensor_field = V4L2_FIELD_INTERLACED;
	return 0;
}

static int sensor_remove(int id)
{
	struct v4l2_subdev *sd;

	sd = cci_dev_remove_helper(&cci_drv[id]);

	rt_free(to_state(sd));
	return 0;
}

int tw2866_init(void)
{
	sensor_probe(0);

	return 0;
}

int tw2866_remove(void)
{
	sensor_remove(0);

	return 0;
}

device_initcall(tw2866_init);
