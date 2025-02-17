/*
 * ekernel/components/avframework/v4l2/platform/sunxi-vin/vin-vipp/vipp_reg.c
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

#include "vipp_reg_i.h"
#include "vipp_reg.h"

#include "../utility/vin_io.h"
#include "../platform/platform_cfg.h"

/*#define VIPP_SCALER_DIRECTLY_WRITE_REG*/
#define VIPP_ADDR_BIT_R_SHIFT 2

volatile void __iomem *vipp_base[VIN_MAX_SCALER];

struct vipp_reg {
	VIPP_MODULE_EN_REG_t *vipp_module_en;
	VIPP_SCALER_CFG_REG_t *vipp_scaler_cfg;
	VIPP_SCALER_OUTPUT_SIZE_REG_t *vipp_scaler_output_size;
	VIPP_OUTPUT_FMT_REG_t *vipp_output_fmt;
	VIPP_OSD_CFG_REG_t *vipp_osd_cfg;
	VIPP_OSD_RGB2YUV_GAIN0_REG_t *vipp_osd_rgb2yuv_gain0;
	VIPP_OSD_RGB2YUV_GAIN1_REG_t *vipp_osd_rgb2yuv_gain1;
	VIPP_OSD_RGB2YUV_GAIN2_REG_t *vipp_osd_rgb2yuv_gain2;
	VIPP_OSD_RGB2YUV_GAIN3_REG_t *vipp_osd_rgb2yuv_gain3;
	VIPP_OSD_RGB2YUV_GAIN4_REG_t *vipp_osd_rgb2yuv_gain4;
	VIPP_OSD_RGB2YUV_OFFSET_REG_t *vipp_osd_rgb2yuv_offset;
	VIPP_CROP_START_POSITION_REG_t *vipp_crop_start;
	VIPP_CROP_SIZE_REG_t *vipp_crop_size;
#if defined CONFIG_ARCH_SUN8IW16P1 || defined CONFIG_SOC_SUN8IW19P1
	VIPP_OSD_REGION_REG_t *vipp_osd_ov_region;
	VIPP_OSD_OV_ALPHA_CFG0_REG_t *vipp_osd_ov_alpha_cfg0;
	VIPP_OSD_OV_ALPHA_CFG1_REG_t *vipp_osd_ov_alpha_cfg1;
	VIPP_OSD_REGION_REG_t *vipp_osd_cv_region;
	VIPP_OSD_CV_REGION_YUV_REG_t *vipp_osd_cv_region_yuv;
	VIPP_OSD_INV_W_REG_t *vipp_osd_inv_w;
	VIPP_OSD_INV_H_REG_t *vipp_osd_inv_h;
	VIPP_ORL_CONTROL_REG_t *vipp_orl_control;
	VIPP_ORL_START_REG_t *vipp_orl_start;
	VIPP_ORL_END_REG_t *vipp_orl_end;
	VIPP_ORL_YUV_REG_t *vipp_orl_yuv;
#endif
};
struct vipp_reg vipp_reg_load_addr[VIN_MAX_SCALER];

#if defined CONFIG_ARCH_SUN8IW12P1
struct vipp_osd_para {
	VIPP_OSD_OVERLAY_CFG_REG_t *vipp_osd_overlay_cfg;
	VIPP_OSD_COVER_CFG_REG_t *vipp_osd_cover_cfg;
	VIPP_OSD_COVER_DATA_REG_t *vipp_osd_cover_data;
};
struct vipp_osd_para vipp_osd_para_load_addr[VIN_MAX_SCALER];
#endif

int vipp_set_base_addr(unsigned int id, unsigned long addr)
{
	if (id > VIN_MAX_SCALER - 1)
		return -1;
	vipp_base[id] = (volatile void __iomem *)addr;

	return 0;
}

/* open module */

void vipp_top_clk_en(unsigned int id, unsigned int en)
{
	vin_reg_clr_set(vipp_base[id] + VIPP_TOP_EN_REG_OFF,
			VIPP_CLK_GATING_EN_MASK, en << VIPP_CLK_GATING_EN);
}

void vipp_enable(unsigned int id)
{
	vin_reg_clr_set(vipp_base[id] + VIPP_EN_REG_OFF,
			VIPP_EN_MASK, 1 << VIPP_EN);
}

void vipp_disable(unsigned int id)
{
	vin_reg_clr_set(vipp_base[id] + VIPP_EN_REG_OFF,
			VIPP_EN_MASK, 0 << VIPP_EN);
}

void vipp_ver_en(unsigned int id, unsigned int en)
{
	vin_reg_clr_set(vipp_base[id] + VIPP_EN_REG_OFF,
			VIPP_VER_EN_MASK, en << VIPP_VER_EN);
}

void vipp_version_get(unsigned int id, struct vipp_version *v)
{
	unsigned int reg_val = vin_reg_readl(vipp_base[id] + VIPP_VER_REG_OFF);

	v->ver_small = (reg_val & VIPP_SMALL_VER_MASK) >> VIPP_SMALL_VER;
	v->ver_big = (reg_val & VIPP_BIG_VER_MASK) >> VIPP_BIG_VER;
}

void vipp_feature_list_get(unsigned int id, struct vipp_feature_list *fl)
{
	unsigned int reg_val = vin_reg_readl(vipp_base[id] + VIPP_FEATURE_REG_OFF);

	fl->osd_exit = (reg_val & VIPP_OSD_EXIST_MASK) >> VIPP_OSD_EXIST;
	fl->yuv422to420 = (reg_val & VIPP_YUV422TO420_MASK) >> VIPP_YUV422TO420;
}

void vipp_set_para_ready(unsigned int id, enum vipp_ready_flag flag)
{
#ifndef VIPP_SCALER_DIRECTLY_WRITE_REG
	vin_reg_clr_set(vipp_base[id] + VIPP_CTRL_REG_OFF,
			VIPP_PARA_READY_MASK, flag << VIPP_PARA_READY);
#endif
}

void vipp_set_osd_ov_update(unsigned int id, enum vipp_update_flag flag)
{
	if (id > MAX_OSD_NUM - 1)
		return;

	vin_reg_clr_set(vipp_base[id] + VIPP_CTRL_REG_OFF,
			VIPP_OSD_OV_UPDATE_MASK, flag << VIPP_OSD_OV_UPDATE);
}

void vipp_set_osd_cv_update(unsigned int id, enum vipp_update_flag flag)
{
#if defined CONFIG_ARCH_SUN8IW12P1
	vin_reg_clr_set(vipp_base[id] + VIPP_CTRL_REG_OFF,
			VIPP_OSD_CV_UPDATE_MASK, flag << VIPP_OSD_CV_UPDATE);
#endif
}

void vipp_set_osd_para_load_addr(unsigned int id, unsigned long dma_addr)
{
#if defined CONFIG_ARCH_SUN8IW12P1
	vin_reg_writel(vipp_base[id] + VIPP_OSD_LOAD_ADDR_REG_OFF, dma_addr >> VIPP_ADDR_BIT_R_SHIFT);
#endif
}

int vipp_map_osd_para_load_addr(unsigned int id, unsigned long vaddr)
{
#if defined CONFIG_ARCH_SUN8IW12P1
	if (id > VIN_MAX_SCALER - 1)
		return -1;

	vipp_osd_para_load_addr[id].vipp_osd_overlay_cfg = (VIPP_OSD_OVERLAY_CFG_REG_t *)vaddr;
	vipp_osd_para_load_addr[id].vipp_osd_cover_cfg = (VIPP_OSD_COVER_CFG_REG_t *)(vaddr + MAX_OVERLAY_NUM * 8);
	vipp_osd_para_load_addr[id].vipp_osd_cover_data = (VIPP_OSD_COVER_DATA_REG_t *)(vaddr + MAX_OVERLAY_NUM * 8 + MAX_COVER_NUM * 8);
#endif
	return 0;
}

void vipp_set_osd_stat_load_addr(unsigned int id, unsigned long dma_addr)
{
	vin_reg_writel(vipp_base[id] + VIPP_OSD_STAT_ADDR_REG_OFF, dma_addr >> VIPP_ADDR_BIT_R_SHIFT);
}

void vipp_set_osd_bm_load_addr(unsigned int id, unsigned long dma_addr)
{
	vin_reg_writel(vipp_base[id] + VIPP_OSD_BM_ADDR_REG_OFF, dma_addr >> VIPP_ADDR_BIT_R_SHIFT);
}

void vipp_set_reg_load_addr(unsigned int id, unsigned long dma_addr)
{
	vin_reg_writel(vipp_base[id] + VIPP_REG_LOAD_ADDR_REG_OFF, dma_addr >> VIPP_ADDR_BIT_R_SHIFT);
}

int vipp_map_reg_load_addr(unsigned int id, unsigned long vaddr)
{
	if (id > VIN_MAX_SCALER - 1)
		return -1;

	vipp_reg_load_addr[id].vipp_module_en = (VIPP_MODULE_EN_REG_t *)(vaddr + VIPP_MODULE_EN_REG_OFF);
	vipp_reg_load_addr[id].vipp_scaler_cfg = (VIPP_SCALER_CFG_REG_t *)(vaddr + VIPP_SC_CFG_REG_OFF);
	vipp_reg_load_addr[id].vipp_scaler_output_size = (VIPP_SCALER_OUTPUT_SIZE_REG_t *)(vaddr + VIPP_SC_SIZE_REG_OFF);
	vipp_reg_load_addr[id].vipp_output_fmt = (VIPP_OUTPUT_FMT_REG_t *)(vaddr + VIPP_MODE_REG_OFF);
	vipp_reg_load_addr[id].vipp_osd_cfg = (VIPP_OSD_CFG_REG_t *)(vaddr + VIPP_OSD_CFG_REG_OFF);
	vipp_reg_load_addr[id].vipp_osd_rgb2yuv_gain0 = (VIPP_OSD_RGB2YUV_GAIN0_REG_t *)(vaddr + VIPP_OSD_GAIN0_REG_OFF);
	vipp_reg_load_addr[id].vipp_osd_rgb2yuv_gain1 = (VIPP_OSD_RGB2YUV_GAIN1_REG_t *)(vaddr + VIPP_OSD_GAIN1_REG_OFF);
	vipp_reg_load_addr[id].vipp_osd_rgb2yuv_gain2 = (VIPP_OSD_RGB2YUV_GAIN2_REG_t *)(vaddr + VIPP_OSD_GAIN2_REG_OFF);
	vipp_reg_load_addr[id].vipp_osd_rgb2yuv_gain3 = (VIPP_OSD_RGB2YUV_GAIN3_REG_t *)(vaddr + VIPP_OSD_GAIN3_REG_OFF);
	vipp_reg_load_addr[id].vipp_osd_rgb2yuv_gain4 = (VIPP_OSD_RGB2YUV_GAIN4_REG_t *)(vaddr + VIPP_OSD_GAIN4_REG_OFF);
	vipp_reg_load_addr[id].vipp_osd_rgb2yuv_offset = (VIPP_OSD_RGB2YUV_OFFSET_REG_t *)(vaddr + VIPP_OSD_OFFSET_REG_OFF);
	vipp_reg_load_addr[id].vipp_crop_start = (VIPP_CROP_START_POSITION_REG_t *)(vaddr + VIPP_CROP_START_REG_OFF);
	vipp_reg_load_addr[id].vipp_crop_size = (VIPP_CROP_SIZE_REG_t *)(vaddr + VIPP_CROP_SIZE_REG_OFF);
#if defined CONFIG_ARCH_SUN8IW16P1 || defined CONFIG_SOC_SUN8IW19P1
	vipp_reg_load_addr[id].vipp_osd_ov_region = (VIPP_OSD_REGION_REG_t *)(vaddr + VIPP_OSD_OV0_ST_REG_OFF);
	vipp_reg_load_addr[id].vipp_osd_ov_alpha_cfg0 = (VIPP_OSD_OV_ALPHA_CFG0_REG_t *)(vaddr + VIPP_OSD_OV_ALPHA_CFG0_REG_OFF);
	vipp_reg_load_addr[id].vipp_osd_ov_alpha_cfg1 = (VIPP_OSD_OV_ALPHA_CFG1_REG_t *)(vaddr + VIPP_OSD_OV_ALPHA_CFG1_REG_OFF);
	vipp_reg_load_addr[id].vipp_osd_cv_region = (VIPP_OSD_REGION_REG_t *)(vaddr + VIPP_OSD_CV0_ST_REG_OFF);
	vipp_reg_load_addr[id].vipp_osd_cv_region_yuv = (VIPP_OSD_CV_REGION_YUV_REG_t *)(vaddr + VIPP_OSD_CV0_YUV_REG_OFF);
	vipp_reg_load_addr[id].vipp_osd_inv_w = (VIPP_OSD_INV_W_REG_t *)(vaddr + VIPP_OSD_INV_WIDTH_REG_OFF);
	vipp_reg_load_addr[id].vipp_osd_inv_h = (VIPP_OSD_INV_H_REG_t *)(vaddr + VIPP_OSD_INV_HEIGHT_REG_OFF);
	vipp_reg_load_addr[id].vipp_orl_control = (VIPP_ORL_CONTROL_REG_t *)(vaddr + VIPP_ORL_CONTROL_REG_OFF);
	vipp_reg_load_addr[id].vipp_orl_start = (VIPP_ORL_START_REG_t *)(vaddr + VIPP_ORL_START0_REG_OFF);
	vipp_reg_load_addr[id].vipp_orl_end = (VIPP_ORL_END_REG_t *)(vaddr + VIPP_ORL_END0_REG_OFF);
	vipp_reg_load_addr[id].vipp_orl_yuv = (VIPP_ORL_YUV_REG_t *)(vaddr + VIPP_ORL_YUV0_REG_OFF);
#endif
	return 0;
}

void vipp_get_status(unsigned int id, struct vipp_status *status)
{
	unsigned int reg_val = vin_reg_readl(vipp_base[id] + VIPP_STA_REG_OFF);

	status->reg_load_pd = (reg_val & VIPP_REG_LOAD_PD_MASK) >> VIPP_REG_LOAD_PD;
	status->bm_error_pd = (reg_val & VIPP_BM_ERROR_PD_MASK) >> VIPP_BM_ERROR_PD;
}

void vipp_clr_status(unsigned int id, enum vipp_status_sel sel)
{
	vin_reg_writel(vipp_base[id] + VIPP_STA_REG_OFF, sel);
}

void vipp_scaler_en(unsigned int id, unsigned int en)
{
#ifndef	VIPP_SCALER_DIRECTLY_WRITE_REG
	vipp_reg_load_addr[id].vipp_module_en->bits.sc_en = en;
#else
	VIPP_MODULE_EN_REG_t vipp_module_en;

	vipp_module_en.dwval = 0;
	vipp_module_en.bits.sc_en = en;
	vin_reg_writel(vipp_base[id] + VIPP_MODULE_EN_REG_OFF, vipp_module_en.dwval);
#endif
}

void vipp_osd_en(unsigned int id, unsigned int en)
{
	if (id > MAX_OSD_NUM - 1)
		return;

	vipp_reg_load_addr[id].vipp_module_en->bits.osd_en = en;
}

void vipp_chroma_ds_en(unsigned int id, unsigned int en)
{
	if (id > MAX_OSD_NUM - 1)
		return;

	vipp_reg_load_addr[id].vipp_module_en->bits.chroma_ds_en = en;
}

void vipp_scaler_cfg(unsigned int id, struct vipp_scaler_config *cfg)
{
#ifndef	VIPP_SCALER_DIRECTLY_WRITE_REG
#if !defined CONFIG_SOC_SUN8IW19P1 && !defined CONFIG_ARCH_SUN50IW10P1
	vipp_reg_load_addr[id].vipp_scaler_cfg->bits.sc_out_fmt = cfg->sc_out_fmt;
#else
	vipp_reg_load_addr[id].vipp_output_fmt->bits.sc_out_fmt = cfg->sc_out_fmt;
#endif
	vipp_reg_load_addr[id].vipp_scaler_cfg->bits.sc_xratio = cfg->sc_x_ratio;
	vipp_reg_load_addr[id].vipp_scaler_cfg->bits.sc_yratio = cfg->sc_y_ratio;
	vipp_reg_load_addr[id].vipp_scaler_cfg->bits.sc_weight_shift = cfg->sc_w_shift;
#else
	VIPP_SCALER_CFG_REG_t vipp_scaler_cfg;

	vipp_scaler_cfg.dwval = 0;
	vipp_scaler_cfg.bits.sc_out_fmt = cfg->sc_out_fmt;
	vipp_scaler_cfg.bits.sc_xratio = cfg->sc_x_ratio;
	vipp_scaler_cfg.bits.sc_yratio = cfg->sc_y_ratio;
	vipp_scaler_cfg.bits.sc_weight_shift = cfg->sc_w_shift;
	vin_reg_writel(vipp_base[id] + VIPP_SC_CFG_REG_OFF, vipp_scaler_cfg.dwval);

#endif
}

void vipp_scaler_output_fmt(unsigned int id, enum vipp_format fmt)
{
#ifndef	VIPP_SCALER_DIRECTLY_WRITE_REG
#if !defined CONFIG_SOC_SUN8IW19P1 && !defined CONFIG_ARCH_SUN50IW10P1
	vipp_reg_load_addr[id].vipp_scaler_cfg->bits.sc_out_fmt = fmt;
#else
	vipp_reg_load_addr[id].vipp_output_fmt->bits.sc_out_fmt = fmt;
#endif
#else
	vin_reg_clr_set(vipp_base[id] + VIPP_SC_CFG_REG_OFF, 0x1, fmt);
#endif
}

void vipp_scaler_output_size(unsigned int id, struct vipp_scaler_size *size)
{
#ifndef	VIPP_SCALER_DIRECTLY_WRITE_REG
	vipp_reg_load_addr[id].vipp_scaler_output_size->bits.sc_width = size->sc_width;
	vipp_reg_load_addr[id].vipp_scaler_output_size->bits.sc_height = size->sc_height;
#else
	VIPP_SCALER_OUTPUT_SIZE_REG_t vipp_scaler_output_size;

	vipp_scaler_output_size.dwval = 0;
	vipp_scaler_output_size.bits.sc_width = size->sc_width;
	vipp_scaler_output_size.bits.sc_height = size->sc_height;
	vin_reg_writel(vipp_base[id] + VIPP_SC_SIZE_REG_OFF, vipp_scaler_output_size.dwval);
#endif
}

void vipp_output_fmt_cfg(unsigned int id, enum vipp_format fmt)
{
#ifndef	VIPP_SCALER_DIRECTLY_WRITE_REG
	vipp_reg_load_addr[id].vipp_output_fmt->bits.vipp_out_fmt = fmt;
	vipp_reg_load_addr[id].vipp_output_fmt->bits.vipp_in_fmt = 1;

#else
	VIPP_OUTPUT_FMT_REG_t vipp_output_fmt;

	vipp_output_fmt.dwval = 0;
	vipp_output_fmt.bits.vipp_out_fmt = fmt;
	vipp_output_fmt.bits.vipp_in_fmt = 1;
	vin_reg_writel(vipp_base[id] + VIPP_MODE_REG_OFF, vipp_output_fmt.dwval);
#endif
}

void vipp_osd_cfg(unsigned int id, struct vipp_osd_config *cfg)
{
#if defined CONFIG_ARCH_SUN8IW12P1
	vipp_reg_load_addr[id].vipp_osd_cfg->bits.osd_ov_en = cfg->osd_ov_en;
	vipp_reg_load_addr[id].vipp_osd_cfg->bits.osd_cv_en = cfg->osd_cv_en;
	vipp_reg_load_addr[id].vipp_osd_cfg->bits.osd_argb_mode = cfg->osd_argb_mode;
	vipp_reg_load_addr[id].vipp_osd_cfg->bits.osd_stat_en = cfg->osd_stat_en;
	vipp_reg_load_addr[id].vipp_osd_cfg->bits.osd_ov_num = cfg->osd_ov_num;
	vipp_reg_load_addr[id].vipp_osd_cfg->bits.osd_cv_num = cfg->osd_cv_num;
#elif defined CONFIG_ARCH_SUN8IW16P1 || defined CONFIG_SOC_SUN8IW19P1
	vipp_reg_load_addr[id].vipp_osd_cfg->bits.argb_mode = cfg->osd_argb_mode;
	vipp_reg_load_addr[id].vipp_osd_cfg->bits.stat_en = 1;
	vipp_reg_load_addr[id].vipp_osd_cfg->bits.ov_num = cfg->osd_ov_num + 1;
	vipp_reg_load_addr[id].vipp_osd_cfg->bits.cv_num = cfg->osd_cv_num + 1;
	vipp_reg_load_addr[id].vipp_orl_control->bits.orl_num = cfg->osd_orl_num + 1;
	vipp_reg_load_addr[id].vipp_orl_control->bits.orl_width = cfg->osd_orl_width;
#endif
}

void vipp_osd_rgb2yuv(unsigned int id, struct vipp_rgb2yuv_factor *factor)
{
	vipp_reg_load_addr[id].vipp_osd_rgb2yuv_gain0->bits.jc0 = factor->jc0;
	vipp_reg_load_addr[id].vipp_osd_rgb2yuv_gain0->bits.jc1 = factor->jc1;
	vipp_reg_load_addr[id].vipp_osd_rgb2yuv_gain1->bits.jc2 = factor->jc2;
	vipp_reg_load_addr[id].vipp_osd_rgb2yuv_gain1->bits.jc3 = factor->jc3;
	vipp_reg_load_addr[id].vipp_osd_rgb2yuv_gain2->bits.jc4 = factor->jc4;
	vipp_reg_load_addr[id].vipp_osd_rgb2yuv_gain2->bits.jc5 = factor->jc5;
	vipp_reg_load_addr[id].vipp_osd_rgb2yuv_gain3->bits.jc6 = factor->jc6;
	vipp_reg_load_addr[id].vipp_osd_rgb2yuv_gain3->bits.jc7 = factor->jc7;
	vipp_reg_load_addr[id].vipp_osd_rgb2yuv_gain4->bits.jc8 = factor->jc8;
	vipp_reg_load_addr[id].vipp_osd_rgb2yuv_offset->bits.jc9 = factor->jc9;
	vipp_reg_load_addr[id].vipp_osd_rgb2yuv_offset->bits.jc10 = factor->jc10;
	vipp_reg_load_addr[id].vipp_osd_rgb2yuv_offset->bits.jc11 = factor->jc11;
}

void vipp_set_crop(unsigned int id, struct vipp_crop *crop)
{
	vipp_reg_load_addr[id].vipp_crop_start->bits.crop_hor_st = crop->hor;
	vipp_reg_load_addr[id].vipp_crop_start->bits.crop_ver_st = crop->ver;
	vipp_reg_load_addr[id].vipp_crop_size->bits.crop_width = crop->width;
	vipp_reg_load_addr[id].vipp_crop_size->bits.crop_height = crop->height;
}

void vipp_osd_hvflip(unsigned int id, int hflip, int vflip)
{
#if defined CONFIG_ARCH_SUN8IW16P1 || defined CONFIG_SOC_SUN8IW19P1
	vipp_reg_load_addr[id].vipp_osd_cfg->bits.hflip = hflip;
	vipp_reg_load_addr[id].vipp_osd_cfg->bits.vflip = vflip;
#endif
}

void vipp_osd_inverse(unsigned int id, int *inverse, int cnt)
{
#if defined CONFIG_ARCH_SUN8IW12P1
	int i;

	for (i = 0; i < cnt; i++)
		vipp_osd_para_load_addr[id].vipp_osd_overlay_cfg[i].bits.inverse_en = inverse[i];
#endif
}

void vipp_osd_para_cfg(unsigned int id, struct vipp_osd_para_config *para,
				struct vipp_osd_config *cfg)
{
#if defined CONFIG_ARCH_SUN8IW12P1
	int i;

	for (i = 0; i < cfg->osd_ov_num + 1; i++) {
		vipp_osd_para_load_addr[id].vipp_osd_overlay_cfg[i].bits.h_start = para->overlay_cfg[i].h_start;
		vipp_osd_para_load_addr[id].vipp_osd_overlay_cfg[i].bits.h_end = para->overlay_cfg[i].h_end;
		vipp_osd_para_load_addr[id].vipp_osd_overlay_cfg[i].bits.v_start = para->overlay_cfg[i].v_start;
		vipp_osd_para_load_addr[id].vipp_osd_overlay_cfg[i].bits.v_end = para->overlay_cfg[i].v_end;
		vipp_osd_para_load_addr[id].vipp_osd_overlay_cfg[i].bits.alpha = para->overlay_cfg[i].alpha;
	}

	for (i = 0; i < cfg->osd_cv_num + 1; i++) {
		vipp_osd_para_load_addr[id].vipp_osd_cover_cfg[i].bits.h_start = para->cover_cfg[i].h_start;
		vipp_osd_para_load_addr[id].vipp_osd_cover_cfg[i].bits.h_end = para->cover_cfg[i].h_end;
		vipp_osd_para_load_addr[id].vipp_osd_cover_cfg[i].bits.v_start = para->cover_cfg[i].v_start;
		vipp_osd_para_load_addr[id].vipp_osd_cover_cfg[i].bits.v_end = para->cover_cfg[i].v_end;
		vipp_osd_para_load_addr[id].vipp_osd_cover_data[i].bits.y = para->cover_data[i].y;
		vipp_osd_para_load_addr[id].vipp_osd_cover_data[i].bits.u = para->cover_data[i].u;
		vipp_osd_para_load_addr[id].vipp_osd_cover_data[i].bits.v = para->cover_data[i].v;
	}
#elif defined CONFIG_ARCH_SUN8IW16P1
	int i;

	for (i = 0; i < cfg->osd_ov_num + 1; i++) {
		vipp_reg_load_addr[id].vipp_osd_ov_region[i].bits.h_start = para->overlay_cfg[i].h_start;
		vipp_reg_load_addr[id].vipp_osd_ov_region[i].bits.h_end = para->overlay_cfg[i].h_end;
		vipp_reg_load_addr[id].vipp_osd_ov_region[i].bits.v_start = para->overlay_cfg[i].v_start;
		vipp_reg_load_addr[id].vipp_osd_ov_region[i].bits.v_end = para->overlay_cfg[i].v_end;
	}
	vipp_reg_load_addr[id].vipp_osd_ov_alpha_cfg0->bits.ov_alpha_rgn0 = para->overlay_cfg[0].alpha;
	vipp_reg_load_addr[id].vipp_osd_ov_alpha_cfg0->bits.ov_alpha_rgn1 = para->overlay_cfg[1].alpha;
	vipp_reg_load_addr[id].vipp_osd_ov_alpha_cfg0->bits.ov_alpha_rgn2 = para->overlay_cfg[2].alpha;
	vipp_reg_load_addr[id].vipp_osd_ov_alpha_cfg0->bits.ov_alpha_rgn3 = para->overlay_cfg[3].alpha;
	vipp_reg_load_addr[id].vipp_osd_ov_alpha_cfg1->bits.ov_alpha_rgn4 = para->overlay_cfg[4].alpha;
	vipp_reg_load_addr[id].vipp_osd_ov_alpha_cfg1->bits.ov_alpha_rgn5 = para->overlay_cfg[5].alpha;
	vipp_reg_load_addr[id].vipp_osd_ov_alpha_cfg1->bits.ov_alpha_rgn6 = para->overlay_cfg[6].alpha;
	vipp_reg_load_addr[id].vipp_osd_ov_alpha_cfg1->bits.ov_alpha_rgn7 = para->overlay_cfg[7].alpha;

	for (i = 0; i < cfg->osd_cv_num + 1; i++) {
		vipp_reg_load_addr[id].vipp_osd_cv_region[i].bits.h_start = para->cover_cfg[i].h_start;
		vipp_reg_load_addr[id].vipp_osd_cv_region[i].bits.h_end = para->cover_cfg[i].h_end;
		vipp_reg_load_addr[id].vipp_osd_cv_region[i].bits.v_start = para->cover_cfg[i].v_start;
		vipp_reg_load_addr[id].vipp_osd_cv_region[i].bits.v_end = para->cover_cfg[i].v_end;
		vipp_reg_load_addr[id].vipp_osd_cv_region_yuv[i].bits.cv_y = para->cover_data[i].y;
		vipp_reg_load_addr[id].vipp_osd_cv_region_yuv[i].bits.cv_u = para->cover_data[i].u;
		vipp_reg_load_addr[id].vipp_osd_cv_region_yuv[i].bits.cv_v = para->cover_data[i].v;
	}

	vipp_reg_load_addr[id].vipp_osd_inv_w->bits.inv_w_rgn0 = para->overlay_cfg[0].inv_w_rgn;
	vipp_reg_load_addr[id].vipp_osd_inv_w->bits.inv_w_rgn1 = para->overlay_cfg[1].inv_w_rgn;
	vipp_reg_load_addr[id].vipp_osd_inv_w->bits.inv_w_rgn2 = para->overlay_cfg[2].inv_w_rgn;
	vipp_reg_load_addr[id].vipp_osd_inv_w->bits.inv_w_rgn3 = para->overlay_cfg[3].inv_w_rgn;
	vipp_reg_load_addr[id].vipp_osd_inv_w->bits.inv_w_rgn4 = para->overlay_cfg[4].inv_w_rgn;
	vipp_reg_load_addr[id].vipp_osd_inv_w->bits.inv_w_rgn5 = para->overlay_cfg[5].inv_w_rgn;
	vipp_reg_load_addr[id].vipp_osd_inv_w->bits.inv_w_rgn6 = para->overlay_cfg[6].inv_w_rgn;
	vipp_reg_load_addr[id].vipp_osd_inv_w->bits.inv_w_rgn7 = para->overlay_cfg[7].inv_w_rgn;

	vipp_reg_load_addr[id].vipp_osd_inv_h->bits.inv_h_rgn0 = para->overlay_cfg[0].inv_h_rgn;
	vipp_reg_load_addr[id].vipp_osd_inv_h->bits.inv_h_rgn1 = para->overlay_cfg[1].inv_h_rgn;
	vipp_reg_load_addr[id].vipp_osd_inv_h->bits.inv_h_rgn2 = para->overlay_cfg[2].inv_h_rgn;
	vipp_reg_load_addr[id].vipp_osd_inv_h->bits.inv_h_rgn3 = para->overlay_cfg[3].inv_h_rgn;
	vipp_reg_load_addr[id].vipp_osd_inv_h->bits.inv_h_rgn4 = para->overlay_cfg[4].inv_h_rgn;
	vipp_reg_load_addr[id].vipp_osd_inv_h->bits.inv_h_rgn5 = para->overlay_cfg[5].inv_h_rgn;
	vipp_reg_load_addr[id].vipp_osd_inv_h->bits.inv_h_rgn6 = para->overlay_cfg[6].inv_h_rgn;
	vipp_reg_load_addr[id].vipp_osd_inv_h->bits.inv_h_rgn7 = para->overlay_cfg[7].inv_h_rgn;

	vipp_reg_load_addr[id].vipp_osd_cfg->bits.inv_en0 = para->overlay_cfg[0].inv_en;
	vipp_reg_load_addr[id].vipp_osd_cfg->bits.inv_en1 = para->overlay_cfg[1].inv_en;
	vipp_reg_load_addr[id].vipp_osd_cfg->bits.inv_en2 = para->overlay_cfg[2].inv_en;
	vipp_reg_load_addr[id].vipp_osd_cfg->bits.inv_en3 = para->overlay_cfg[3].inv_en;
	vipp_reg_load_addr[id].vipp_osd_cfg->bits.inv_en4 = para->overlay_cfg[4].inv_en;
	vipp_reg_load_addr[id].vipp_osd_cfg->bits.inv_en5 = para->overlay_cfg[5].inv_en;
	vipp_reg_load_addr[id].vipp_osd_cfg->bits.inv_en6 = para->overlay_cfg[6].inv_en;
	vipp_reg_load_addr[id].vipp_osd_cfg->bits.inv_en7 = para->overlay_cfg[7].inv_en;

	vipp_reg_load_addr[id].vipp_osd_cfg->bits.inv_th = para->overlay_cfg[0].inv_th;

#elif defined CONFIG_SOC_SUN8IW19P1
	int i;

	for (i = 0; i < cfg->osd_orl_num + 1; i++) {
		vipp_reg_load_addr[id].vipp_orl_start[i].bits.orl_ys = para->orl_cfg[i].v_start;
		vipp_reg_load_addr[id].vipp_orl_start[i].bits.orl_xs = para->orl_cfg[i].h_start;
		vipp_reg_load_addr[id].vipp_orl_end[i].bits.orl_ye = para->orl_cfg[i].v_end;
		vipp_reg_load_addr[id].vipp_orl_end[i].bits.orl_xe = para->orl_cfg[i].h_end;
		vipp_reg_load_addr[id].vipp_orl_yuv[i].bits.orl_y = para->orl_data[i].y;
		vipp_reg_load_addr[id].vipp_orl_yuv[i].bits.orl_u = para->orl_data[i].u;
		vipp_reg_load_addr[id].vipp_orl_yuv[i].bits.orl_v = para->orl_data[i].v;
	}
#endif
}
