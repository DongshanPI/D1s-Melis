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
#ifndef __MOVIE_FF_RR_SHOW_H__
#define  __MOVIE_FF_RR_SHOW_H__

#include "beetles_app.h"
#include "ff_rr_show_ui.h"

typedef enum
{
    FF_RR_SHOW_SPEED_1  = 0x8,      //X8
    FF_RR_SHOW_SPEED_2  = 0x10,     //X16
    FF_RR_SHOW_SPEED_3  = 0x20,     //X32
    FF_RR_SHOW_SPEED_4  = 0x40      //X64
} MOVIE_FF_RR_SHOW_SPEED;

typedef enum
{
    FF_RR_SHOW_DIRECTION_LEFT,
    FF_RR_SHOW_DIRECTION_RIGHT
} MOVIE_FF_RR_SHOW_DIRECTION;

typedef struct
{
    H_WIN hparent;
    __s32 scene_id;
    __s32 sub_state;
} movie_ff_rr_show_create_para_t;

typedef struct
{
    __u32 text_id;
    __s32 direction;
    __u32 ff_rr_speed;
} movie_ff_rr_show_info_t;

void *movie_ff_rr_show_scene_create(movie_ff_rr_show_create_para_t *create_para);
__s32 movie_ff_rr_show_scene_delete(void *handle);
__s32 movie_ff_rr_show_scene_update_string(void *handle, movie_ff_rr_show_info_t *show_info);


#endif
