/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the People's Republic of China and other countries.
* All Allwinner Technology Co.,Ltd. trademarks are used with permission.
*
* DISCLAIMER
* THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
* IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
* IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
* ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
* ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
* COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
* YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.
*
*
* THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
* PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
* THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
* OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef __MOVIE_SPSC_CTRL_UIPARA_H_
#define  __MOVIE_SPSC_CTRL_UIPARA_H_

#include "beetles_app.h"

#define MOVIE_SPSC_CTRL_MAX_ICON_RES_NUM 2

typedef struct
{
    __s32 x;
    __s32 y;
    __s32 w;
    __s32 h;
    __s32 res_id[MOVIE_SPSC_CTRL_MAX_ICON_RES_NUM];
    HTHEME res_hdl[MOVIE_SPSC_CTRL_MAX_ICON_RES_NUM];
    __s32 lang_id;
} movie_spsc_ctrl_rect_t;

typedef struct
{
    __s32 res_id;
    HTHEME res_hdl;
} movie_spsc_ctrl_res2hdl_t;

typedef enum
{
    movie_spsc_ctrl_res_id = 0,
    movie_spsc_ctrl_hdl
} movie_spsc_ctrl_res2hdl_e;

typedef enum
{
    movie_spsc_prog_icon_prog_bg = 0,
    movie_spsc_prog_icon_prog_left,
    movie_spsc_prog_icon_prog_mid,
    movie_spsc_prog_icon_prog_cursor,
    movie_spsc_prog_icon_num
} movie_prog_icon_t;


//定义spsc ctrl子场景的图标坐标
typedef struct
{
    movie_spsc_ctrl_rect_t  uipara_frm;
    __s32                   focus_icon_index;
    movie_spsc_ctrl_rect_t  uipara_bg;
    movie_spsc_ctrl_rect_t  uipara_icon[movie_spsc_ctrl_icon_num];
    movie_spsc_ctrl_rect_t  uipara_static_icon[movie_spsc_ctrl_static_icon_num];
    movie_spsc_ctrl_res2hdl_t             uipara_playmode_res[5];
    movie_spsc_ctrl_res2hdl_t             uipara_screenmode_res[5];
    movie_spsc_ctrl_res2hdl_t             uipara_playpause_res[2][MOVIE_SPSC_CTRL_MAX_ICON_RES_NUM];
    movie_spsc_ctrl_rect_t  cur_time;
    movie_spsc_ctrl_rect_t  uipara_time;
    movie_spsc_ctrl_rect_t uipara_spsc_prog[movie_spsc_prog_icon_num];
} movie_spsc_ctrl_uipara_t;

movie_spsc_ctrl_uipara_t *movie_spsc_ctrl_get_uipara(__s32 rotate);

#endif
