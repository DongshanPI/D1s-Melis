/*
 * drivers/media/platform/sunxi-tvd/bsp_tvd/bsp_tvd.h
 *
 * Copyright (c) 2007-2018 Allwinnertech Co., Ltd.
 * Author: zhengxiaobin <zhengxiaobin@allwinnertech.com>
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

#ifndef BSP_TVD_H_
#define BSP_TVD_H_

#include <melis/init.h>
#include <interrupt.h>
#include <linux/videodev2.h>
#include <hal_sem.h>
#include <hal_gpio.h>
#include <hal_clk.h>
#include <hal_mem.h>
#include <hal_queue.h>
#include <hal_log.h>
#include <hal_timer.h>


#define FLITER_NUM 1
#define TVD_3D_COMP_BUFFER_SIZE (0x400000)
#define CVBS_INTERFACE 0
#define YPBPRI_INTERFACE 1
#define YPBPRP_INTERFACE 2
#define NTSC 0
#define PAL 1
#define NONE 2


//
// detail information of registers
//

typedef union {
	u32 dwval;
	struct {
		u32 tvd_adc_map                                              :  2 ;    // default: 0x0;
		u32 res0                                                     : 2 ;
		u32 tvin_sel                                                 : 1 ;
		u32 res1                                                     : 27 ;
	} bits;
} tvd_top_map_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 tvd_en_3d_dma                                            :  1 ;    // default: 0x0;
		u32 comb_3d_en                                               :  1 ;    // default: 0x1;
		u32 res0                                                     :  2 ;    // default: ;
		u32 comb_3d_sel                                              :  2 ;    // default: 0x1;
		u32 res1                                                     : 26 ;    // default: ;
	} bits;
} tvd_3d_ctl1_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 dram_trig                                                     ;    // default: 0x0;
	} bits;
} tvd_3d_ctl2_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 comb_3d_addr0                                                 ;    // default: 0x0;
	} bits;
} tvd_3d_ctl3_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 comb_3d_addr1                                                 ;    // default: 0x0;
	} bits;
} tvd_3d_ctl4_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 comb_3d_size                                                  ;    // default: 0x0;
	} bits;
} tvd_3d_ctl5_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 res0:4;
		u32 lpf_dig_en:1;
		u32 res1:19;
		u32 lpf_dig_sel:1;
		u32 res2:7;
	} bits;
} tvd_adc_dig_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 adc_en                                                   :  1 ;    // default: 0x0;
		u32 afe_en                                                   :  1 ;    // default: 0x0;
		u32 lpf_en                                                   :  1 ;    // default: 0x0;
		u32 lpf_sel                                                  :  2 ;    // default: 0x0;
		u32 res0                                                     : 27 ;    // default: ;
	} bits;
} tvd_adc_ctl_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 stage1_ibias                                             :  2 ;    // default: 0x0;
		u32 stage2_ibias                                             :  2 ;    // default: 0x0;
		u32 stage3_ibias                                             :  2 ;    // default: 0x0;
		u32 stage4_ibias                                             :  2 ;    // default: 0x0;
		u32 stage5_ibias                                             :  2 ;    // default: 0x0;
		u32 stage6_ibias                                             :  2 ;    // default: 0x0;
		u32 stage7_ibias                                             :  2 ;    // default: 0x0;
		u32 stage8_ibias                                             :  2 ;    // default: 0x0;
		u32 clp_step                                                 :  3 ;    // default: 0x0;
		u32 res0                                                     :  9 ;    // default: ;
		u32 data_dly                                                 :  1 ;    // default: 0x0;
		u32 res1                                                     :  2 ;    // default: ;
		u32 adc_test                                                 :  1 ;    // default: 0x0;
	} bits;
} tvd_adc_cfg_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 adc_wb_length                                            : 23 ;    // default: 0x10000;
		u32 res0                                                     :  1 ;    // default: ;
		u32 adc_wb_start                                             :  1 ;    // default: 0x0;
		u32 res1                                                     :  3 ;    // default: ;
		u32 adc_wb_buffer_reset                                      :  1 ;    // default: 0x0;
		u32 adc_dump_mode                                            :  1 ;    // default: ;
		u32 adc_test_mode                                            :  1 ;    // default: 0x0;
		u32 fifo_err                                                 :  1 ;    // default: 0x0;
	} bits;
} tvd_adc_dump_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 tvd_en_ch                                                :  1 ;    // default: 0x0;
		u32 res0                                                     : 14 ;    // default: ;
		u32 clr_rsmp_fifo                                            :  1 ;    // default: 0x0;
		u32 res1                                                     :  9 ;    // default: ;
		u32 en_lock_disable_write_back1only_start_wb_when_locked     :  1 ;    // default: 0x0;
		u32 en_lock_disable_write_back2when_unlocked                 :  1 ;    // default: 0x0;
		u32 res2                                                     :  5 ;    // default: ;
	} bits;
} tvd_en_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 ypbpr_mode                                               :  1 ;    // default: 0x0;
		u32 svideo_mode                                              :  1 ;    // default: 0x0;
		u32 progressive_mode                                         :  1 ;    // default: 0x0;
		u32 res0                                                     :  1 ;    // default: ;
		u32 blue_display_mode                                        :  2 ;    // default: 0x2;
		u32 res1                                                     :  2 ;    // default: ;
		u32 blue_color                                               :  1 ;	   // default: 0x0
		u32 res2                                                     : 23 ;    // default: ;
	} bits;
} tvd_mode_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 agc_en                                                   :  1 ;    // default: 0x1;
		u32 agc_frequence                                            :  1 ;    // default: 0x0;
		u32 res0                                                     :  6 ;    // default: ;
		u32 agc_target                                               :  8 ;    // default: 0xdd;
		u32 cagc_en                                                  :  1 ;    // default: 0x0;
		u32 res1                                                     :  7 ;    // default: ;
		u32 cagc_target                                              :  8 ;    // default: 0x8a;
	} bits;
} tvd_clamp_agc1_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 agc_gate_width                                           :  7 ;    // default: 0x40;
		u32 res0                                                     :  1 ;    // default: ;
		u32 agc_backporch_delay                                      :  8 ;    // default: 0x64;
		u32 agc_gate_begin                                           : 13 ;    // default: 0x0;
		u32 res1                                                     :  2 ;    // default: ;
		u32 black_level_clamp                                        :  1 ;    // default: 0x1;
	} bits;
} tvd_clamp_agc2_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 h_sample_step                                                 ;    // default: 0x20000000;
	} bits;
} tvd_hlock1_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 htol                                                     :  4 ;    // default: 0x0;
		u32 res0                                                     : 12 ;    // default: ;
		u32 hsync_filter_gate_start_time                             :  8 ;    // default: 0xd6;
		u32 hsync_filter_gate_end_time                               :  8 ;    // default: 0x4e;
	} bits;
} tvd_hlock2_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 hsync_rising_detect_window_start_time                    :  8 ;    // default: 0x0;
		u32 hsync_rising_detect_window_end_time                      :  8 ;    // default: 0x0;
		u32 hsync_tip_detect_window_start_time                       :  8 ;    // default: 0x0;
		u32 hsync_tip_detect_window_end_time                         :  8 ;    // default: 0x0;
	} bits;
} tvd_hlock3_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 hsync_detect_window_start_time_for_coarse_detection      :  8 ;    // default: 0x00;
		u32 hsync_detect_window_end_time_for_corase_detect           :  8 ;    // default: 0x0;
		u32 hsync_rising_time_for_fine_detect                        :  8 ;    // default: 0x0;
		u32 hsync_fine_to_coarse_offset                              :  8 ;    // default: 0x0;
	} bits;
} tvd_hlock4_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 hactive_start                                            :  8 ;    // default: 0x0;
		u32 hactive_width                                            :  8 ;    // default: 0x0;
		u32 backporch_detect_window_start_time                       :  8 ;    // default: 0x0;
		u32 backporch_detect_window_end_time                         :  8 ;    // default: 0x0;
	} bits;
} tvd_hlock5_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 vtol                                                     :  3 ;    // default: 0x0;
		u32 res0                                                     :  1 ;    // default: ;
		u32 vactive_start                                            : 11 ;    // default: 0x22;
		u32 res1                                                     :  1 ;    // default: ;
		u32 vactive_height                                           : 11 ;    // default: 0;
		u32 res2                                                     :  5 ;    // default: ;
	} bits;
} tvd_vlock1_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 hsync_dectector_disable_start_line                       :  7 ;    // default: 0x0;
		u32 res0                                                     :  9 ;    // default: ;
		u32 hsync_detector_disable_end_line                          :  5 ;    // default: 0x0;
		u32 res1                                                     : 11 ;    // default: ;
	} bits;
} tvd_vlock2_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 color_kill_en                                            :  1 ;    // default: 0x1;
		u32 color_std                                                :  3 ;    // default: 0x0;
		u32 res0                                                     :  4 ;    // default: ;
		u32 burst_gate_start_time                                    :  8 ;    // default: 0x0;
		u32 burst_gate_end_time                                      :  8 ;    // default: 0x0;
		u32 wide_burst_gate                                          :  1 ;    // default: 0x0;
		u32 res1                                                     :  1 ;    // default: ;
		u32 chroma_lpf                                               :  2 ;    // default: 0x0;
		u32 color_std_ntsc                                           :  1 ;    // default: 0x0;
		u32 res2                                                     :  3 ;    // default: ;
	} bits;
} tvd_clock1_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 c_sample_step                                                 ;    // default: 0x0;
	} bits;
} tvd_clock2_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 _3d_comb_filter_mode                                  	:  3 ;    // default: 0x1;
		u32 _3d_comb_filter_dis                                   	:  1 ;    // default: 0x0;
		u32 _2d_comb_filter_mode                                  	:  4 ;    // default: 0x0;
		u32 secam_notch_wide                                        :  1 ;    // default: 0x0;
		u32 chroma_bandpass_filter_en                               :  1 ;    // default: 0x1;
		u32 pal_chroma_level                                        :  6 ;    // default: 0x0;
		u32 comb_filter_buffer_clear                                :  1 ;    // default: 0x0;
		u32 res0                                                    :  3 ;    // default: ;
		u32 notch_factor                                            :  3 ;    // default: 0x0;
		u32 _2d_comb_factor                                        	:  3 ;    // default: 0x0;
		u32 _3d_comb_factor                                       	:  3 ;    // default: 0x0;
		u32 chroma_coring_enable                                    :  1 ;    // default: 0x1;
		u32 res1                                                    :  2 ;    // default: ;
	} bits;
} tvd_yc_sep1_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 horizontal_luma_filter_gain                              :  2 ;    // default: 0x3;
		u32 horizontal_chroma_filter_gain                            :  2 ;    // default: 0x3;
		u32 luma_vertical_filter_gain                                :  2 ;    // default: 0x2;
		u32 chroma_vertical_filter_gain                              :  2 ;    // default: 0x2;
		u32 motion_detect_noise_detect_en                            :  1 ;    // default: 0x0;
		u32 motion_detect_noise_threshold                            :  7 ;    // default: 0x0;
		u32 noise_detect_en                                          :  1 ;    // default: 0x0;
		u32 noise_threshold                                          :  7 ;    // default: 0x0;
		u32 luma_noise_factor                                        :  2 ;    // default: 0x3;
		u32 chroma_noise_factor                                      :  2 ;    // default: 0x3;
		u32 burst_noise_factor                                       :  2 ;    // default: 0x3;
		u32 vertical_noise_factor                                    :  2 ;    // default: 0x3;
	} bits;
} tvd_yc_sep2_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 yc_delay                                                 :  4 ;    // default: 0x0;
		u32 res0                                                     :  4 ;    // default: ;
		u32 contrast_gain                                            :  8 ;    // default: 0x80;
		u32 bright_offset                                            :  8 ;    // default: 0x20;
		u32 sharp_en                                                 :  1 ;    // default: 0x0;
		u32 sharp_coef1                                              :  3 ;    // default: 0x2;
		u32 sharp_coef2                                              :  2 ;    // default: 0x1;
		u32 res1                                                     :  2 ;    // default: ;
	} bits;
} tvd_enhance1_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 saturation_gain                                          :  8 ;    // default: 0x80;
		u32 chroma_enhance_en                                        :  1 ;    // default: 0x0;
		u32 chroma_enhance_strength                                  :  2 ;    // default: 0x3;
		u32 res0                                                     : 21 ;    // default: ;
	} bits;
} tvd_enhance2_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 cb_gain                                                  : 12 ;    // default: 0x80;
		u32 res0                                                     :  4 ;    // default: ;
		u32 cr_gain                                                  : 12 ;    // default: 0x0;
		u32 cbcr_gain_en                                             :  1 ;    // default: 0x0;
		u32 res1                                                     :  3 ;    // default: ;
	} bits;
} tvd_enhance3_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 wb_en:1;
		u32 wb_format:1;
		u32 field_sel:1;
		u32 hyscale_en:1;
		u32 wb_mb_mode:1;
		u32 wb_frame_mode:1;
		u32 flip_field:1;
		u32 res0:1;
		u32 wb_addr_valid:1;
		u32 res1:7;
		u32 hactive_stride:12;
		u32 yuv420_fil_en:1;
		u32 res2:2;
		/* 0x0->nv12, 0x1->nv21 */
		u32 wb_uv_swap:1;
	} bits;
} tvd_wb1_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 hactive_num                                              : 12 ;    // default: 0x0;
		u32 res0                                                     :  4 ;    // default: ;
		u32 vactive_num                                              : 11 ;    // default: 0x0;
		u32 res1                                                     :  5 ;    // default: ;
	} bits;
} tvd_wb2_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 ch1_y_addr                                                    ;    // default: 0x0;
	} bits;
} tvd_wb3_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 ch1_c_addr                                                    ;    // default: 0x0;
	} bits;
} tvd_wb4_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 lock                                                     :  1 ;    // Default: 0x0;
		u32 unlock                                                   :  1 ;    // Default: 0x0;
		u32 res0                                                     :  2 ;    // Default: ;
		u32 fifo_c_o                                                 :  1 ;    // Default: 0x0;
		u32 fifo_y_o                                                 :  1 ;    // Default: 0x0;
		u32 res1                                                     :  1 ;    // Default: 0x0;
		u32 fifo_c_u                                                 :  1 ;    // Default: 0x0;
		u32 fifo_y_u                                                 :  1 ;    // Default: 0x0;
		u32 res2                                                     :  7 ;    // Default: ;
		u32 wb_addr_change_err                                       :  1 ;    // Default: 0x0;
		u32 res3                                                     :  7 ;    // Default: ;
		u32 frame_end                                                :  1 ;    // Default: 0x0;
		u32 res4                                                     :  3 ;    // Default: ;
		u32 fifo_3d_rx_u                                             :  1 ;    // Default: 0x0;
		u32 fifo_3d_rx_o                                             :  1 ;    // Default: 0x0;
		u32 fifo_3d_tx_u                                             :  1 ;    // Default: 0x0;
		u32 fifo_3d_tx_o                                             :  1 ;    // Default: 0x0;
	} bits;
} tvd_irq_ctl_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 lock                                                     :  1 ;    // Default: 0x0;
		u32 unlock                                                   :  1 ;    // Default: 0x0;
		u32 res0                                                     :  2 ;    // Default: ;
		u32 fifo_c_o                                                 :  1 ;    // Default: 0x0;
		u32 fifo_y_o                                                 :  1 ;    // Default: 0x0;
		u32 res1                                                     :  1 ;    // Default: 0x0;
		u32 fifo_c_u                                                 :  1 ;    // Default: 0x0;
		u32 fifo_y_u                                                 :  1 ;    // Default: 0x0;
		u32 res2                                                     :  7 ;    // Default: ;
		u32 wb_addr_change_err                                       :  1 ;    // Default: 0x0;
		u32 res3                                                     :  7 ;    // Default: ;
		u32 frame_end                                                :  1 ;    // Default: 0x0;
		u32 res4                                                     :  3 ;    // Default: ;
		u32 fifo_3d_rx_u                                             :  1 ;    // Default: 0x0;
		u32 fifo_3d_rx_o                                             :  1 ;    // Default: 0x0;
		u32 fifo_3d_tx_u                                             :  1 ;    // Default: 0x0;
		u32 fifo_3d_tx_o                                             :  1 ;    // Default: 0x0;
	} bits;
} tvd_irq_status_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 res0                                                     :  8 ;    // default: ;
		u32 afe_gain_value                                           :  8 ;    // default: 0x0;
		u32 tvin_lock_debug                                          :  1 ;    // default: 0x0;
		u32 tvin_lock_high                                           :  1 ;    // default: 0x0;
		u32 truncation2_reset_gain_enable                            :  1 ;    // default: 0x0;
		u32 truncation_reset_gain_enable                             :  1 ;    // default: 0x0;
		u32 unlock_reset_gain_enable                                 :  1 ;    // default: 0x0;
		u32 afe_gain_mode                                            :  1 ;    // default: 0x0;
		u32 clamp_mode                                               :  1 ;    // default: 0;
		u32 clamp_up_start                                           :  1 ;    // default: 0x0;
		u32 clamp_dn_start                                           :  1 ;    // default: 0x0;
		u32 clamp_updn_cycles                                        :  7 ;    // default: 0x0;
	} bits;
} tvd_debug1_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 res0                                                     :  3 ;    // default;
		u32 agc_gate_thresh                                          :  5 ;    // default: 0xa;
		u32 ccir656_en                                               :  1 ;    // default: 0x0;
		u32 adc_cbcr_pump_swap                                       :  1 ;    // default: 0x0;
		u32 adc_updn_swap                                            :  1 ;    // default: 0x1;
		u32 adc_input_swap                                           :  1 ;    // default: 0x0;
		u32 hv_dely                                                  :  1 ;    // default: 0x0;
		u32 cv_inv                                                   :  1 ;    // default: 0x0;
		u32 tvd_src                                                  :  1 ;    // default: 0x0;
		u32 res1                                                     :  3 ;    // default: 0x0;
		u32 adc_wb_mode                                              :  2 ;    // default: 0x0;
		u32 hue                                                      :  8 ;    // default: 0x0;
		u32 res2                                                     :  4 ;    // default;
	} bits;
} tvd_debug2_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 res0                                                     : 20 ;    // default: ;
		u32 noise_thresh                                             :  8 ;    // default: 0x32;
		u32 ccir656_cbcr_write_back_sequence                         :  1 ;    // default: 0x0;
		u32 cbcr_swap                                                :  1 ;    // default: 0x0;
		u32 nstd_hysis                                               :  2 ;    // default: 0x0;
	} bits;
} tvd_debug3_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 fixed_burstgate                                          :  1 ;    // default: 0x1;
		u32 cautopos                                                 :  5 ;    // default: 0xc;
		u32 vnon_std_threshold                                       :  4 ;    // default: 0x0;
		u32 hnon_std_threshold                                       :  4 ;    // default: 0x6;
		u32 user_ckill_mode                                          :  2 ;    // default: 0x0;
		u32 hlock_ckill                                              :  1 ;    // default: 0x0;
		u32 vbi_ckill                                                :  1 ;    // default: 0x0;
		u32 chroma_kill                                              :  4 ;    // default: 0x7;
		u32 agc_gate_vsync_stip                                      :  1 ;    // default: 0x0;
		u32 agc_gate_vsync_coarse                                    :  1 ;    // default: 0x1;
		u32 agc_gate_kill_mode                                       :  2 ;    // default: 0x3;
		u32 agc_peak_en                                              :  1 ;    // default: 0x1;
		u32 hstate_unlocked                                          :  1 ;    // default: 0x1;
		u32 disable_hfine                                            :  1 ;    // default: 0x0;
		u32 hstate_fixed                                             :  1 ;    // default: 0x0;
		u32 hlock_vsync_mode                                         :  2 ;    // default: 0x3;
	} bits;
} tvd_debug4_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 vsync_clamp_mode                                         :  2 ;    // default: 0x2;
		u32 vsync_vbi_lockout_start                                  :  7 ;    // default: 0x70;
		u32 vsync_vbi_max                                            :  7 ;    // default: 0xe;
		u32 vlock_wide_range                                         :  1 ;    // default: 0x0;
		u32 locked_count_clean_max                                   :  4 ;    // default: 0x4;
		u32 locked_count_noisy_max                                   :  4 ;    // default: 0x7;
		u32 hstate_max                                               :  3 ;    // default: 0x3;
		u32 fixed_cstate                                             :  1 ;    // default: 0x0;
		u32 vodd_delayed                                             :  1 ;    // default: 0x0;
		u32 veven_delayed                                            :  1 ;    // default: 0x0;
		u32 field_polarity                                           :  1 ;    // default: 0x0;
	} bits;
} tvd_debug5_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 cstate                                                   :  3 ;    // default: 0x5;
		u32 lose_chromalock_level                                    :  3 ;    // default: 0x7;
		u32 lose_chromalock_count                                    :  4 ;    // default: 0x6;
		u32 palsw_level                                              :  2 ;    // default: 0x2;
		u32 vsync_thresh                                             :  6 ;    // default: 0x0;
		u32 vsync_cntl                                               :  2 ;    // default: 0x0;
		u32 vloop_tc                                                 :  2 ;    // default: 0x2;
		u32 field_detect_mode                                        :  2 ;    // default: 0x2;
		u32 cpump_delay                                              :  8 ;    // default: 0xb9;
	} bits;
} tvd_debug6_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 hresampler_2up                                           :  1 ;    // default: 0x1;
		u32 cpump_adjust_polarity                                    :  1 ;    // default: 0x0;
		u32 cpump_adjust_delay                                       :  6 ;    // default: 0x28;
		u32 cpump_adjust                                             :  8 ;    // default: 0xc8;
		u32 cpump_delay_en                                           :  1 ;    // default: 0x0;
		u32 vf_nstd_en                                               :  1 ;    // default: 0x1;
		u32 vcr_auto_switch_en                                       :  1 ;    // default: 0x1;
		u32 mv_hagc                                                  :  1 ;    // default: 0x1;
		u32 dagc_en                                                  :  1 ;    // default: 0x1;
		u32 agc_half_en                                              :  1 ;    // default: 0x1;
		u32 dc_clamp_mode                                            :  2 ;    // default: 0x0;
		u32 ldpause_threshold                                        :  4 ;    // default: 0x0;
		u32 res0                                                     :  4 ;    // default: ;
	} bits;
} tvd_debug7_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 chroma_step_ntsc                                              ;    // default: 0x0;
	} bits;
} tvd_debug8_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 chroma_step_paln                                              ;    // default: 0x0;
	} bits;
} tvd_debug9_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 chroma_step_palm                                              ;    // default: 0x0;
	} bits;
} tvd_debug10_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 chroma_step_pal                                               ;    // default: 0x0;
	} bits;
} tvd_debug11_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 y_wb_protect                                                  ;    // default: 0x0;
	} bits;
} tvd_debug12_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 uv_wb_protect                                                 ;    // default: 0x0;
	} bits;
} tvd_debug13_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 agc_peak_nominal                                         :  7 ;    // default: 0xa;
		u32 agc_peak_cntl                                            :  3 ;    // default: 0x1;
		u32 vsync_agc_lockout_start                                  :  7 ;    // default: 0x6c;
		u32 vsync_agc_max                                            :  6 ;    // default: 0x10;
		u32 noise_line                                               :  5 ;    // default: 0x0;
		u32 res0                                                     :  4 ;    // default: ;
	} bits;
} tvd_debug14_reg_t;

typedef union {
	u32 dwval;
	struct { 	u32 adc_lock_mode:1;
		u32 res0:3;			   /* default: 0x1; */
		u32 adc_lock_interval_period:10; /* default: 0x6c; */
		u32 res1:2;			   /* default: 0x10; */
		u32 adc_lock_interval_low:10;    /* default: 0x0; */
		u32 res2:6;			   /* default: ; */
	} bits;
} tvd_debug15_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 agc_analog_gain_status                                   :  8 ;    // default: 0x4;
		u32 agc_digital_gain_status                                  :  8 ;    // default: 0x0;
		u32 chroma_magnitude_status                                  :  8 ;    // default: 0x0;
		u32 res0                                                     :  8 ;    // default: ;
	} bits;
} tvd_status1_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 chroma_sync_dto_increment_status                              ;    // default: 0x21f07c1f;
	} bits;
} tvd_status2_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 horizontal_sync_dto_increment_status                     : 30 ;    // default: 0x20000000;
		u32 res0                                                     :  2 ;    // default: ;
	} bits;
} tvd_status3_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 no_signal_detected                                       :  1 ;    // default: 0x0;
		u32 h_locked     		                                     :  1 ;    // default: 0x0;
		u32 v_locked                                                 :  1 ;    // default: 0x1;
		u32 chroma_pll_locked_to_colour_burst                        :  1 ;    // default: 0x1;
		u32 macrovision_vbi_pseudosync_pulses_detection              :  1 ;    // default: 0x0;
		u32 macrovision_colour_stripes_detected                      :  3 ;    // default: 0x0;
		u32 proscan_detected                                         :  1 ;    // default: 0x0;
		u32 hnon_standard                                            :  1 ;    // default: 0x0;
		u32 vnon_standard                                            :  1 ;    // default: 0x0;
		u32 res0                                                     :  5 ;    // default: 0x0;
		u32 pal_detected                                             :  1 ;    // default: 0x0;
		u32 secam_detected                                           :  1 ;    // default: 0x0;
		u32 _625lines_detected                                       :  1 ;    // default: 0x0;
		u32 noisy                                                    :  1 ;    // default: 0x0;
		u32 vcr                                                      :  1 ;    // default: 0x0;
		u32 vcr_trick                                                :  1 ;    // default: 0x0;
		u32 vcr_ff                                                   :  1 ;    // default: 0x0;
		u32 vcr_rew                                                  :  1 ;    // default: 0x0;
		u32 res1                                                     :  8 ;    // default: ;
	} bits;
} tvd_status4_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 sync_level:11;
		u32 res0:5;
		u32 blank_level:11;
		u32 res1:5;
	} bits;
} tvd_status5_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 auto_detect_finish                                       :  1 ;    // default: 0x0;
		u32 tv_standard                                              :  3 ;    // default: 0x0;
		u32 auto_detect_en                                           :  1 ;    // default: 0x0;
		u32 mask_palm                                                :  1 ;    // default: 0x0;
		u32 mask_palcn                                               :  1 ;    // default: 0x0;
		u32 mask_pal60                                               :  1 ;    // default: 0x0;
		u32 mask_ntsc443                                             :  1 ;    // default: 0x0;
		u32 mask_secam                                               :  1 ;    // default: 0x0;
		u32 mask_unknown                                             :  1 ;    // default: 0x0;
		u32 res0                                                     : 21 ;    // default: ;
	} bits;
} tvd_status6_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 teletext_vbi_frame_code_register1                        :  8 ;    // default: 0x0;
		u32 teletext_vbi_frame_code_register2                        :  8 ;    // default: 0x0;
		u32 data_high_level_register                                 :  8 ;    // default: 0x0;
		u32 vbi_data_type_configuration_register_for_line7           :  8 ;    // default: 0x0;
	} bits;
} tvd_vbi1_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 vbi_data_type_configuration_register_for_line8           :  8 ;    // default: 0x0;
		u32 vbi_data_type_configuration_register_for_line9           :  8 ;    // default: 0x0;
		u32 vbi_data_type_configuration_register_for_line10          :  8 ;    // default: 0x0;
		u32 vbi_data_type_configuration_register_for_line11          :  8 ;    // default: 0x0;
	} bits;
} tvd_vbi2_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 vbi_data_type_configuration_register_for_line12          :  8 ;    // default: 0x0;
		u32 vbi_data_type_configuration_register_for_line13          :  8 ;    // default: 0x0;
		u32 vbi_data_type_configuration_register_for_line14          :  8 ;    // default: 0x0;
		u32 vbi_data_type_configuration_register_for_line15          :  8 ;    // default: 0x0;
	} bits;
} tvd_vbi3_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 vbi_data_type_configuration_register_for_line16          :  8 ;    // default: 0x0;
		u32 vbi_data_type_configuration_register_for_line17          :  8 ;    // default: 0x0;
		u32 vbi_data_type_configuration_register_for_line18          :  8 ;    // default: 0x0;
		u32 vbi_data_type_configuration_register_for_line19          :  8 ;    // default: 0x0;
	} bits;
} tvd_vbi4_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 vbi_data_type_configuration_register_for_line20          :  8 ;    // default: 0x0;
		u32 vbi_data_type_configuration_register_for_line21          :  8 ;    // default: 0x0;
		u32 vbi_data_type_configuration_register_for_line22          :  8 ;    // default: 0x0;
		u32 vbi_data_type_configuration_register_for_line23          :  8 ;    // default: 0x0;
	} bits;
} tvd_vbi5_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 vbi_data_type_configuration_register_for_remaining_lines :  8 ;    // default: 0x0;
		u32 vbi_loop_filter_gain                                     :  8 ;    // default: 0x0;
		u32 vbi_loop_filter_i_gain                                   :  8 ;    // default: 0x0;
		u32 vbi_loop_filter_g_gain                                   :  8 ;    // default: 0x0;
	} bits;
} tvd_vbi6_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 upper_byte_vbi_close_caption_dto                         :  8 ;    // default: 0x0;
		u32 lower_byte_vbi_close_caption_dto                         :  8 ;    // default: 0x0;
		u32 upper_byte_vbi_teletext_dto                              :  8 ;    // default: 0x0;
		u32 lower_byte_vbi_teletext_dto                              :  8 ;    // default: 0x0;
	} bits;
} tvd_vbi7_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 upper_byte_vbi_wss625_dto                                :  8 ;    // default: 0x0;
		u32 lower_byte_vbi_wss625_dto                                :  8 ;    // default: 0x0;
		u32 vbi_close_caption_data_1_register1                       :  8 ;    // default: 0x0;
		u32 vbi_close_caption_data_1_register2                       :  8 ;    // default: 0x0;
	} bits;
} tvd_vbi8_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 vbi_close_caption_data_1_register3                       :  8 ;    // default: 0x0;
		u32 vbi_close_caption_data_1_register4                       :  8 ;    // default: 0x0;
		u32 vbi_close_caption_data_2_register                        :  8 ;    // default: 0x0;
		u32 vbi_wss_data_1_register                                  :  8 ;    // default: 0x0;
	} bits;
} tvd_vbi9_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 vbi_wss_data_2_register                                  :  8 ;    // default: 0x0;
		u32 vbi_data_status_register                                 :  8 ;    // default: 0x0;
		u32 vbi_caption_start_register                               :  8 ;    // default: 0x0;
		u32 vbi_wss625_start_register                                :  8 ;    // default: 0x0;
	} bits;
} tvd_vbi10_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 vbi_teletext_start_register                              :  8 ;    // default: 0x0;
		u32 res0                                                     :  8 ;    // default: 0x0;
		u32 res1                                                     :  8 ;    // default: 0x0;
		u32 res2                                                     :  8 ;    // default: 0x0;
	} bits;
} tvd_vbi11_reg_t;

typedef union {
	u32 dwval;
	struct {
		u32 res0                       	  ;    // default: ;
	} bits;
} tvd_reservd_reg_t;

//device define
typedef struct {
	tvd_top_map_reg_t 				tvd_top_map;				//0x000
	tvd_reservd_reg_t				tvd_top_reg004;				//0x004
	tvd_3d_ctl1_reg_t 				tvd_3d_ctl1;				//0x008
	tvd_3d_ctl2_reg_t 				tvd_3d_ctl2;				//0x00c
	tvd_3d_ctl3_reg_t 				tvd_3d_ctl3;				//0x010
	tvd_3d_ctl4_reg_t 				tvd_3d_ctl4;				//0x014
	tvd_3d_ctl5_reg_t 				tvd_3d_ctl5;				//0x018
	tvd_reservd_reg_t				tvd_top_reg01c[2];			//0x01c~0x020
	tvd_adc_dig_reg_t				tvd_adc0_dig;				//0x024
	tvd_adc_ctl_reg_t 				tvd_adc0_ctl;				//0x028
	tvd_adc_cfg_reg_t 				tvd_adc0_cfg;				//0x02c
	tvd_reservd_reg_t				tvd_top_reg030[5];			//0x030~0x040
	tvd_adc_dig_reg_t				tvd_adc1_dig;				//0x044
	tvd_adc_ctl_reg_t 				tvd_adc1_ctl;				//0x048
	tvd_adc_cfg_reg_t 				tvd_adc1_cfg;				//0x04c
	tvd_reservd_reg_t				tvd_top_reg050[5];			//0x050~0x060
	tvd_adc_dig_reg_t				tvd_adc2_dig;				//0x064
	tvd_adc_ctl_reg_t 				tvd_adc2_ctl;				//0x068
	tvd_adc_cfg_reg_t 				tvd_adc2_cfg;				//0x06c
	tvd_reservd_reg_t				tvd_top_reg060[5];			//0x070~0x080
	tvd_adc_dig_reg_t				tvd_adc3_dig;				//0x084
	tvd_adc_ctl_reg_t 				tvd_adc3_ctl;				//0x088
	tvd_adc_cfg_reg_t 				tvd_adc3_cfg;				//0x08c
	tvd_reservd_reg_t				tvd_top_reg090[24];			//0x070~0x0ec
	tvd_adc_dump_reg_t				tvd_adc_dump;				//0x0f0
} __tvd_top_dev_t;

//device define
typedef struct {
	tvd_en_reg_t					tvd_en;						//0x000
	tvd_mode_reg_t					tvd_mode;					//0x004
	tvd_clamp_agc1_reg_t			tvd_clamp_agc1;				//0x008
	tvd_clamp_agc2_reg_t			tvd_clamp_agc2;				//0x00c
	tvd_hlock1_reg_t				tvd_hlock1;					//0x010
	tvd_hlock2_reg_t				tvd_hlock2;					//0x014
	tvd_hlock3_reg_t				tvd_hlock3;					//0x018
	tvd_hlock4_reg_t				tvd_hlock4;					//0x01c
	tvd_hlock5_reg_t				tvd_hlock5;					//0x020
	tvd_vlock1_reg_t				tvd_vlock1;					//0x024
	tvd_vlock2_reg_t				tvd_vlock2;					//0x028
	tvd_reservd_reg_t				tvd_reg02c;				    //0x02c
	tvd_clock1_reg_t				tvd_clock1;					//0x030
	tvd_clock2_reg_t				tvd_clock2;					//0x034
	tvd_reservd_reg_t				tvd_reg038[2];				//0x038~0x03c
	tvd_yc_sep1_reg_t				tvd_yc_sep1;				//0x040
	tvd_yc_sep2_reg_t				tvd_yc_sep2;				//0x044
	tvd_reservd_reg_t				tvd_reg048[2];				//0x048~0x04c
	tvd_enhance1_reg_t				tvd_enhance1;				//0x050
	tvd_enhance2_reg_t				tvd_enhance2;				//0x054
	tvd_enhance3_reg_t				tvd_enhance3;				//0x058
	tvd_reservd_reg_t				tvd_reg05c;					//0x05c
	tvd_wb1_reg_t					tvd_wb1;					//0x060
	tvd_wb2_reg_t					tvd_wb2;					//0x064
	tvd_wb3_reg_t					tvd_wb3;					//0x068
	tvd_wb4_reg_t					tvd_wb4;					//0x06c
	tvd_reservd_reg_t				tvd_reg070[4];				//0x070~0x07c
	tvd_irq_ctl_reg_t				tvd_irq_ctl;				//0x080
	tvd_reservd_reg_t				tvd_reg084[3];				//0x084~0x08c
	tvd_irq_status_reg_t			tvd_irq_status;				//0x090
	tvd_reservd_reg_t				tvd_reg094[27];				//0x094~0x0fc
	tvd_debug1_reg_t				tvd_debug1;					//0x100
	tvd_debug2_reg_t				tvd_debug2;					//0x104
	tvd_debug3_reg_t				tvd_debug3;					//0x108
	tvd_debug4_reg_t				tvd_debug4;					//0x10c
	tvd_debug5_reg_t				tvd_debug5;					//0x110
	tvd_debug6_reg_t				tvd_debug6;					//0x114
	tvd_debug7_reg_t				tvd_debug7;					//0x118
	tvd_debug8_reg_t				tvd_debug8;					//0x11c
	tvd_debug9_reg_t				tvd_debug9;					//0x120
	tvd_debug10_reg_t				tvd_debug10;				//0x124
	tvd_debug11_reg_t				tvd_debug11;				//0x128
	tvd_debug12_reg_t				tvd_debug12;				//0x12c
	tvd_debug13_reg_t				tvd_debug13;				//0x130
	tvd_debug14_reg_t				tvd_debug14;				//0x134
	tvd_debug15_reg_t				tvd_debug15;/*0x138 */
	tvd_reservd_reg_t				tvd_reg13c[17];/*0x13c~0x17c */
	tvd_status1_reg_t				tvd_status1;				//0x180
	tvd_status2_reg_t				tvd_status2;				//0x184
	tvd_status3_reg_t				tvd_status3;				//0x188
	tvd_status4_reg_t				tvd_status4;				//0x18c
	tvd_status5_reg_t				tvd_status5;				//0x190
	tvd_status6_reg_t				tvd_status6;				//0x194
	tvd_reservd_reg_t				tvd_reg198[906];			//0x198~0xfbc
	tvd_vbi1_reg_t					tvd_vbi1;					//0xfc0
	tvd_vbi2_reg_t					tvd_vbi2;					//0xfc4
	tvd_vbi3_reg_t					tvd_vbi3;					//0xfc8
	tvd_vbi4_reg_t					tvd_vbi4;					//0xfcc
	tvd_vbi5_reg_t					tvd_vbi5;					//0xfd0
	tvd_vbi6_reg_t					tvd_vbi6;					//0xfd4
	tvd_vbi7_reg_t					tvd_vbi7;					//0xfd8
	tvd_vbi8_reg_t					tvd_vbi8;					//0xfdc
	tvd_vbi9_reg_t					tvd_vbi9;					//0xfe0
	tvd_vbi10_reg_t               	tvd_vbi10;					//0xfe4
	tvd_vbi11_reg_t                	tvd_vbi11;					//0xfe8
} __tvd_dev_t;


typedef enum {
	TVD_IRQ_LOCK = 0,
	TVD_IRQ_UNLOCK = 1,
	TVD_IRQ_FIFO_C_O = 4,
	TVD_IRQ_FIFO_Y_O = 5,
	TVD_IRQ_FIFO_C_U = 7,
	TVD_IRQ_FIFO_Y_U = 8,
	TVD_IRQ_WB_ADDR_CHANGE_ERR = 16,
	TVD_IRQ_FRAME_END = 24,
	TVD_IRQ_FIFO_3D_RX_U = 28,
	TVD_IRQ_FIFO_3D_RX_O = 29,
	TVD_IRQ_FIFO_3D_TX_U = 30,
	TVD_IRQ_FIFO_3D_TX_O = 31,
} TVD_IRQ_T;

typedef enum {
    TVD_PL_YUV420 					=	0,
    TVD_MB_YUV420					=	1,
    TVD_PL_YUV422					=	2,
} TVD_FMT_T;

s32 tvd_top_set_reg_base(unsigned long base);
s32 tvd_set_reg_base(u32 sel, unsigned long base);
s32 tvd_init(u32 sel, u32 interface);
s32 tvd_deinit(u32 sel, u32 interface);
s32 tvd_get_status(u32 sel, u32 *locked, u32 *system);
s32 tvd_config(u32 sel, u32 interface, u32 mode);
s32 tvd_set_wb_width(u32 sel, u32 width);
s32 tvd_set_wb_width_jump(u32 sel, u32 width_jump);
s32 tvd_set_wb_height(u32 sel, u32 height);
s32 tvd_set_wb_addr(u32 sel, u32 addr_y, u32 addr_c);
s32 tvd_set_wb_fmt(u32 sel, TVD_FMT_T fmt);
s32 tvd_set_wb_uv_swap(u32 sel, u32 swap);
s32 tvd_set_wb_field(u32 sel, u32 is_field_mode, u32 is_field_even);
s32 tvd_capture_on(u32 sel);
s32 tvd_capture_off(u32 sel);
s32 tvd_irq_enable(u32 sel, TVD_IRQ_T irq_id);
s32 tvd_irq_disable(u32 sel, TVD_IRQ_T irq_id);
s32 tvd_irq_status_get(u32 sel, TVD_IRQ_T irq_id, u32 *irq_status);
s32 tvd_irq_status_clear(u32 sel, TVD_IRQ_T irq_id);
s32 tvd_dma_irq_status_get(u32 sel, u32 *irq_status);
s32 tvd_dma_irq_status_clear_err_flag(u32 sel, u32 irq_status);

void tvd_enable_chanel(u32 sel, u32 en);

s32 tvd_adc_config(u32 adc, u32 en);
s32 tvd_set_saturation(u32 sel, u32 saturation);
s32 tvd_set_sharpness(u32 sel, u32 sharpness);
s32 tvd_set_hue(u32 sel, u32 hue);
s32 tvd_set_luma(u32 sel, u32 luma);
s32 tvd_set_contrast(u32 sel, u32 contrast);
u32 tvd_get_saturation(u32 sel);
u32 tvd_get_sharpness(u32 sel);
u32 tvd_get_hue(u32 sel);
u32 tvd_get_luma(u32 sel);
u32 tvd_get_contrast(u32 sel);
void tvd_3d_mode(u32 _3d_sel, u32 _3d_en, u32 _3d_addr);
u32 tvd_dbgmode_dump_data(u32 chan_sel, u32 mode, uintptr_t dump_dst_addr,
			  u32 data_length);
void tvd_agc_auto_config(u32 sel);
void tvd_agc_manual_config(u32 sel, u32 agc_manual_val);
void tvd_cagc_config(u32 sel, u32 enable);
s32 tvd_get_lock(u32 sel);
void tvd_blue_display_mode(u32 sel, u32 mode);
void tvd_reset(u32 sel);
void tvd_input_sel(u32 input);
#endif
