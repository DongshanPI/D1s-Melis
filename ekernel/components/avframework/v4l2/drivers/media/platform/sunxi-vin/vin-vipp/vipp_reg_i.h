/*
 * ekernel/components/avframework/v4l2/platform/sunxi-vin/vin-vipp/vipp_reg_i.h
 *
 * Copyright (c) 2007-2017 Allwinnertech Co., Ltd.
 *
 * Authors:  Zhao Wei <zhaowei@allwinnertech.com>
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

#ifndef __VIPP__REG__I__H__
#define __VIPP__REG__I__H__

/*
 * Detail information of registers
 */

#define VIPP_TOP_EN_REG_OFF		0X000
#define VIPP_CLK_GATING_EN		0
#define VIPP_CLK_GATING_EN_MASK		(0X1 << VIPP_CLK_GATING_EN)

#define VIPP_EN_REG_OFF			0X004
#define VIPP_EN				0
#define VIPP_EN_MASK			(0X1 << VIPP_EN)
#define VIPP_VER_EN			3
#define VIPP_VER_EN_MASK		(0X1 << VIPP_VER_EN)

#define VIPP_VER_REG_OFF		0X008
#define VIPP_SMALL_VER			0
#define VIPP_SMALL_VER_MASK		(0XFFF << VIPP_SMALL_VER)
#define VIPP_BIG_VER			12
#define VIPP_BIG_VER_MASK		(0XFFF << VIPP_BIG_VER)

#define VIPP_FEATURE_REG_OFF		0X00C
#define VIPP_OSD_EXIST			0
#define VIPP_OSD_EXIST_MASK		(0X1 << VIPP_OSD_EXIST)
#define VIPP_YUV422TO420		1
#define VIPP_YUV422TO420_MASK		(0X1 << VIPP_YUV422TO420)

#define VIPP_CTRL_REG_OFF		0X014
#define VIPP_OSD_OV_UPDATE		0
#define VIPP_OSD_OV_UPDATE_MASK		(0X1 << VIPP_OSD_OV_UPDATE)
#define VIPP_OSD_CV_UPDATE		1
#define VIPP_OSD_CV_UPDATE_MASK		(0X1 << VIPP_OSD_CV_UPDATE)
#define VIPP_PARA_READY			2
#define VIPP_PARA_READY_MASK		(0X1 << VIPP_PARA_READY)

#define VIPP_OSD_LOAD_ADDR_REG_OFF	0X018
#define VIPP_OSD_STAT_ADDR_REG_OFF	0X01C
#define VIPP_OSD_BM_ADDR_REG_OFF	0X020
#define VIPP_REG_LOAD_ADDR_REG_OFF	0X024

#define VIPP_STA_REG_OFF		0X030
#define VIPP_REG_LOAD_PD		0
#define VIPP_REG_LOAD_PD_MASK		(0X01 << VIPP_REG_LOAD_PD)
#define VIPP_MBUS_IDLE_PD		1
#define VIPP_MBUS_IDLE_PD_MASK		(0X01 << VIPP_MBUS_IDLE_PD)
#define VIPP_BM_ERROR_PD		2
#define VIPP_BM_ERROR_PD_MASK		(0X01 << VIPP_BM_ERROR_PD)
#define VIPP_FRAME_LOST_PD		3
#define VIPP_FRAME_LOST_PD_MASK		(0X01 << VIPP_FRAME_LOST_PD)
#define VIPP_HBLANK_SHORT_PD		4
#define VIPP_HBLANK_SHORT_PD_MASK	(0X01 << VIPP_HBLANK_SHORT_PD)
#define VIPP_BM_RDADDR_ERR_PD		5
#define VIPP_BM_RDADDR_ERR_PD_MASK	(0X01 << VIPP_BM_RDADDR_ERR_PD)
#define VIPP_FRMEND_BM_NOTIDLE_PD	6
#define VIPP_FRMEND_BM_NOTIDLE_PD_MASK	(0X01 << VIPP_FRMEND_BM_NOTIDLE_PD)

#define VIPP_INTER_STATUS_REG_OFF	0X034
#define VIPP_TOP_CTL_ST			0
#define VIPP_TOP_CTL_ST_MASK		(0X3FF << VIPP_TOP_CTL_ST)
#define VIPP_BM_CORE_CTL_ST		10
#define VIPP_BM_CORE_CTL_ST_MASK	(0XFF << VIPP_BM_CORE_CTL_ST)

#define VIPP_FIFO_RW_POINTER_REG_OFF	0X038
#define VIPP_FIFO_RPT			0
#define VIPP_FIFO_RPT_MASK		(0X7FF << VIPP_FIFO_RPT)
#define VIPP_FIFO_WPT			16
#define VIPP_FIFO_WPT_MASK		(0X7FF << VIPP_FIFO_WPT)

#define VIPP_BMAP_STATUS_REG_OFF	0X03C
#define VIPP_BMAP_CNT_Y			0
#define VIPP_BMAP_CNT_Y_MASK		(0XFFF << VIPP_BMAP_CNT_Y)
#define VIPP_BMAP_CNT_X			12
#define VIPP_BMAP_CNT_X_MASK		(0X1FF << VIPP_BMAP_CNT_X)
#define VIPP_RXO_CMD_WPT		21
#define VIPP_RXO_CMD_WPT_MASK		(0X7FF << VIPP_RXO_CMD_WPT)

#define VIPP_MODULE_EN_REG_OFF		0X040
#define VIPP_SC_CFG_REG_OFF		0X044
#define VIPP_SC_SIZE_REG_OFF		0X048
#define VIPP_MODE_REG_OFF		0X04C

#define VIPP_OSD_CFG_REG_OFF		0X050

#if defined CONFIG_ARCH_SUN8IW12P1 || defined CONFIG_ARCH_SUN8IW15P1 || defined CONFIG_ARCH_SUN8IW17P1
#define VIPP_OSD_GAIN0_REG_OFF		0X054
#define VIPP_OSD_GAIN1_REG_OFF		0X058
#define VIPP_OSD_GAIN2_REG_OFF		0X05C
#define VIPP_OSD_GAIN3_REG_OFF		0X060
#define VIPP_OSD_GAIN4_REG_OFF		0X064
#define VIPP_OSD_OFFSET_REG_OFF		0X068
#define VIPP_CROP_START_REG_OFF		0X070
#define VIPP_CROP_SIZE_REG_OFF		0X074

#else

#define VIPP_OSD_OV0_ST_REG_OFF		0X054
#define VIPP_OSD_OV0_ED_REG_OFF		0X058
#define VIPP_OSD_OV1_ST_REG_OFF		0X05C
#define VIPP_OSD_OV1_ED_REG_OFF		0X060
#define VIPP_OSD_OV2_ST_REG_OFF		0X064
#define VIPP_OSD_OV2_ED_REG_OFF		0X068
#define VIPP_OSD_OV3_ST_REG_OFF		0X06C
#define VIPP_OSD_OV3_ED_REG_OFF		0X070
#define VIPP_OSD_OV4_ST_REG_OFF		0X074
#define VIPP_OSD_OV4_ED_REG_OFF		0X078
#define VIPP_OSD_OV5_ST_REG_OFF		0X07C
#define VIPP_OSD_OV5_ED_REG_OFF		0X080
#define VIPP_OSD_OV6_ST_REG_OFF		0X084
#define VIPP_OSD_OV6_ED_REG_OFF		0X088
#define VIPP_OSD_OV7_ST_REG_OFF		0X08C
#define VIPP_OSD_OV7_ED_REG_OFF		0X090

#define VIPP_OSD_OV_ALPHA_CFG0_REG_OFF	0X094
#define VIPP_OSD_OV_ALPHA_CFG1_REG_OFF	0X098

#define VIPP_OSD_CV0_ST_REG_OFF		0X09C
#define VIPP_OSD_CV0_ED_REG_OFF		0X0A0
#define VIPP_OSD_CV1_ST_REG_OFF		0X0A4
#define VIPP_OSD_CV1_ED_REG_OFF		0X0A8
#define VIPP_OSD_CV2_ST_REG_OFF		0X0AC
#define VIPP_OSD_CV2_ED_REG_OFF		0X0B0
#define VIPP_OSD_CV3_ST_REG_OFF		0X0B4
#define VIPP_OSD_CV3_ED_REG_OFF		0X0B8
#define VIPP_OSD_CV4_ST_REG_OFF		0X0BC
#define VIPP_OSD_CV4_ED_REG_OFF		0X0C0
#define VIPP_OSD_CV5_ST_REG_OFF		0X0C4
#define VIPP_OSD_CV5_ED_REG_OFF		0X0C8
#define VIPP_OSD_CV6_ST_REG_OFF		0X0CC
#define VIPP_OSD_CV6_ED_REG_OFF		0X0D0
#define VIPP_OSD_CV7_ST_REG_OFF		0X0D4
#define VIPP_OSD_CV7_ED_REG_OFF		0X0D8

#define VIPP_OSD_CV0_YUV_REG_OFF	0X0DC
#define VIPP_OSD_CV1_YUV_REG_OFF	0X0E0
#define VIPP_OSD_CV2_YUV_REG_OFF	0X0E4
#define VIPP_OSD_CV3_YUV_REG_OFF	0X0E8
#define VIPP_OSD_CV4_YUV_REG_OFF	0X0EC
#define VIPP_OSD_CV5_YUV_REG_OFF	0X0F0
#define VIPP_OSD_CV6_YUV_REG_OFF	0X0F4
#define VIPP_OSD_CV7_YUV_REG_OFF	0X0F8

#define VIPP_OSD_INV_WIDTH_REG_OFF	0X0FC
#define VIPP_OSD_INV_HEIGHT_REG_OFF	0X100

#define VIPP_OSD_GAIN0_REG_OFF		0X104
#define VIPP_OSD_GAIN1_REG_OFF		0X108
#define VIPP_OSD_GAIN2_REG_OFF		0X10C
#define VIPP_OSD_GAIN3_REG_OFF		0X110
#define VIPP_OSD_GAIN4_REG_OFF		0X114
#define VIPP_OSD_OFFSET_REG_OFF		0X118
#define VIPP_CROP_START_REG_OFF		0X11C
#define VIPP_CROP_SIZE_REG_OFF		0X120
#define VIPP_ORL_CONTROL_REG_OFF	0X130
#define VIPP_ORL_START0_REG_OFF  	0X140
#define VIPP_ORL_END0_REG_OFF		0X180
#define VIPP_ORL_YUV0_REG_OFF		0X1C0

#endif

typedef union {
	unsigned int dwval;
	struct {
		unsigned int sc_en:1;
		unsigned int osd_en:1;
		unsigned int chroma_ds_en:1;
		unsigned int res0:29;
	} bits;
} VIPP_MODULE_EN_REG_t;

typedef union {
	unsigned int dwval;
	struct {
#if !defined CONFIG_SOC_SUN8IW19P1 && !defined CONFIG_ARCH_SUN50IW10P1
		unsigned int sc_out_fmt:1;
		unsigned int res0:3;
		unsigned int sc_xratio:12;
		unsigned int sc_yratio:12;
		unsigned int sc_weight_shift:4;
#else
		unsigned int sc_xratio:13;
		unsigned int res0:1;
		unsigned int sc_yratio:13;
		unsigned int sc_weight_shift:5;
#endif
	} bits;
} VIPP_SCALER_CFG_REG_t;

typedef union {
	unsigned int dwval;
	struct {
		unsigned int sc_width:13;
		unsigned int res0:3;
		unsigned int sc_height:13;
		unsigned int res1:3;
	} bits;
} VIPP_SCALER_OUTPUT_SIZE_REG_t;

typedef union {
	unsigned int dwval;
	struct {
		unsigned int vipp_out_fmt:1;
		unsigned int vipp_in_fmt:1;
		unsigned int sc_out_fmt:1;
		unsigned int res0:29;
	} bits;
} VIPP_OUTPUT_FMT_REG_t;

#if defined CONFIG_ARCH_SUN8IW12P1
typedef union {
	unsigned int dwval;
	struct {
		unsigned int osd_ov_en:1;
		unsigned int osd_cv_en:1;
		unsigned int osd_argb_mode:2;
		unsigned int osd_stat_en:1;
		unsigned int res0:3;
		unsigned int osd_ov_num:6;
		unsigned int res1:2;
		unsigned int osd_cv_num:3;
		unsigned int res2:13;
	} bits;
} VIPP_OSD_CFG_REG_t;

#else

typedef union {
	unsigned int dwval;
	struct {
		unsigned int inv_en0:1;
		unsigned int inv_en1:1;
		unsigned int inv_en2:1;
		unsigned int inv_en3:1;
		unsigned int inv_en4:1;
		unsigned int inv_en5:1;
		unsigned int inv_en6:1;
		unsigned int inv_en7:1;
		unsigned int inv_th:8;
		unsigned int stat_en:1;
		unsigned int hflip:1;
		unsigned int vflip:1;
		unsigned int argb_mode:2;
		unsigned int ov_num:4;
		unsigned int cv_num:4;
		unsigned int res0:3;
	} bits;
} VIPP_OSD_CFG_REG_t;

typedef union {
	unsigned long long ddwval;
	struct {
		unsigned int h_start:12;
		unsigned int res0:4;
		unsigned int v_start:12;
		unsigned int res1:4;
		unsigned int h_end:12;
		unsigned int res2:4;
		unsigned int v_end:12;
		unsigned int res3:4;
	} bits;
} VIPP_OSD_REGION_REG_t;

typedef union {
	unsigned int dwval;
	struct {
		unsigned int ov_alpha_rgn0:5;
		unsigned int ov_alpha_rgn1:5;
		unsigned int ov_alpha_rgn2:5;
		unsigned int ov_alpha_rgn3:5;
		unsigned int res0:12;
	} bits;
} VIPP_OSD_OV_ALPHA_CFG0_REG_t;

typedef union {
	unsigned int dwval;
	struct {
		unsigned int ov_alpha_rgn4:5;
		unsigned int ov_alpha_rgn5:5;
		unsigned int ov_alpha_rgn6:5;
		unsigned int ov_alpha_rgn7:5;
		unsigned int res0:12;
	} bits;
} VIPP_OSD_OV_ALPHA_CFG1_REG_t;

typedef union {
	unsigned int dwval;
	struct {
		unsigned int cv_y:8;
		unsigned int cv_u:8;
		unsigned int cv_v:8;
		unsigned int res0:8;
	} bits;
} VIPP_OSD_CV_REGION_YUV_REG_t;

typedef union {
	unsigned int dwval;
	struct {
		unsigned int inv_w_rgn0:4;
		unsigned int inv_w_rgn1:4;
		unsigned int inv_w_rgn2:4;
		unsigned int inv_w_rgn3:4;
		unsigned int inv_w_rgn4:4;
		unsigned int inv_w_rgn5:4;
		unsigned int inv_w_rgn6:4;
		unsigned int inv_w_rgn7:4;
	} bits;
} VIPP_OSD_INV_W_REG_t;

typedef union {
	unsigned int dwval;
	struct {
		unsigned int inv_h_rgn0:4;
		unsigned int inv_h_rgn1:4;
		unsigned int inv_h_rgn2:4;
		unsigned int inv_h_rgn3:4;
		unsigned int inv_h_rgn4:4;
		unsigned int inv_h_rgn5:4;
		unsigned int inv_h_rgn6:4;
		unsigned int inv_h_rgn7:4;
	} bits;
} VIPP_OSD_INV_H_REG_t;

typedef union {
	unsigned int dwval;
	struct {
		unsigned int orl_num:5;
		unsigned int res0:3;
		unsigned int orl_width:3;
		unsigned int res1:5;
	} bits;
} VIPP_ORL_CONTROL_REG_t;

typedef union {
	unsigned int dwval;
	struct {
		unsigned int orl_xs:13;
		unsigned int res0:3;
		unsigned int orl_ys:13;
		unsigned int res1:3;
	} bits;
} VIPP_ORL_START_REG_t;

typedef union {
	unsigned int dwval;
	struct {
		unsigned int orl_xe:13;
		unsigned int res0:3;
		unsigned int orl_ye:13;
		unsigned int res1:3;
	} bits;
} VIPP_ORL_END_REG_t;

typedef union {
	unsigned int dwval;
	struct {
		unsigned int orl_y:8;
		unsigned int orl_u:8;
		unsigned int orl_v:8;
		unsigned int res0:8;
	} bits;
} VIPP_ORL_YUV_REG_t;

#endif

typedef union {
	unsigned int dwval;
	struct {
		unsigned int jc0:11;
		unsigned int res0:5;
		unsigned int jc1:11;
		unsigned int res1:5;
	} bits;
} VIPP_OSD_RGB2YUV_GAIN0_REG_t;

typedef union {
	unsigned int dwval;
	struct {
		unsigned int jc2:11;
		unsigned int res0:5;
		unsigned int jc3:11;
		unsigned int res1:5;
	} bits;
} VIPP_OSD_RGB2YUV_GAIN1_REG_t;

typedef union {
	unsigned int dwval;
	struct {
		unsigned int jc4:11;
		unsigned int res0:5;
		unsigned int jc5:11;
		unsigned int res1:5;
	} bits;
} VIPP_OSD_RGB2YUV_GAIN2_REG_t;

typedef union {
	unsigned int dwval;
	struct {
		unsigned int jc6:11;
		unsigned int res0:5;
		unsigned int jc7:11;
		unsigned int res1:5;
	} bits;
} VIPP_OSD_RGB2YUV_GAIN3_REG_t;

typedef union {
	unsigned int dwval;
	struct {
		unsigned int jc8:11;
		unsigned int res0:21;
	} bits;
} VIPP_OSD_RGB2YUV_GAIN4_REG_t;

typedef union {
	unsigned int dwval;
	struct {
		unsigned int jc9:9;
		unsigned int jc10:9;
		unsigned int jc11:9;
		unsigned int res0:5;
	} bits;
} VIPP_OSD_RGB2YUV_OFFSET_REG_t;

typedef union {
	unsigned int dwval;
	struct {
		unsigned int crop_hor_st:13;
		unsigned int res0:3;
		unsigned int crop_ver_st:13;
		unsigned int res1:5;
	} bits;
} VIPP_CROP_START_POSITION_REG_t;

typedef union {
	unsigned int dwval;
	struct {
		unsigned int crop_width:13;
		unsigned int res0:3;
		unsigned int crop_height:13;
		unsigned int res1:5;
	} bits;
} VIPP_CROP_SIZE_REG_t;

typedef union {
	unsigned long long ddwval;
	struct {
		unsigned long long h_start:13;
		unsigned long long h_end:13;
		unsigned long long res0:6;
		unsigned long long v_start:13;
		unsigned long long v_end:13;
		unsigned long long alpha:5;
		unsigned long long inverse_en:1;
	} bits;
} VIPP_OSD_OVERLAY_CFG_REG_t;

typedef union {
	unsigned long long ddwval;
	struct {
		unsigned long long h_start:13;
		unsigned long long h_end:13;
		unsigned long long res0:6;
		unsigned long long v_start:13;
		unsigned long long v_end:13;
		unsigned long long res1:6;
	} bits;
} VIPP_OSD_COVER_CFG_REG_t;

typedef union {
	unsigned long long ddwval;
	struct {
		unsigned long long y:8;
		unsigned long long u:8;
		unsigned long long v:8;
		unsigned long long res0:40;
	} bits;
} VIPP_OSD_COVER_DATA_REG_t;

#endif /*__VIPP__REG__I__H__*/
