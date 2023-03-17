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
#ifndef __TXTLAYER_H__
#define __TXTLAYER_H__

#include "txtcfg.h"
#include "txtbuffer.h"
#include "txtlist.h"
#include "txtbox_i.h"

struct tag_TXTBOX_DATA;

#define   LINE_MODE    1
#define   OK_MODE      0

#define   NO_FOUCS     0
#define   REAL_FOUCS   1     /*实际设置焦点*/
#define   VAR_FOUCS    2     /*虚拟设置焦点(快速滑动时设置)*/

#define   WAIT_LOAD    0x01
//------------------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------------------
typedef struct tag_TXTLAYER_MAN
{
    __u32                        FoucsTID;
    __u32                        FoucsPrio;
    __u8                        mode;
    __u8                        lastmode;
    __u8                        scnnum;
    __pos_t                     start_pos;
    __bool                      backup;
    H_LYR                       layer;         /*窗口图层的句柄*/
    __rect_t                    scnrect;
    txtbuffer_man_t            *txtbuffer;
    void                       *foucs_FB;
    __disp_layer_para_t         sec_layer;
    H_LYR                       focus_lyr;
    __bool                      backalpha;
    void                       *chg_fb;     /*备份的目的地址*/
    void                       *head_fb;     /*备份的头framebuffer*/
    void                       *tail_fb;     /*备份的尾alpha framebuffer*/
    void                       *head_addr;   /*备份的源地址*/
    void                       *tail_addr;   /*备份的尾地址*/
    __u32                       asize;       /*备份大小*/
    void                       *res_addr;    /*备份的源地址*/
    __u32                       res_x;
    __u32                       res_y;
    __u32                       back_size;   /*备份的framebuffer大小*/
    __u32                       back_count;  /*备份的item count*/
    __pos_t                     back_pos;
    txtlist_t                  *txtlist;
    struct tag_TXTBOX_DATA     *ptxtbox;
    __u32                       status;
    __u32                       font_size;
    GUI_FONT                   *draw_font;
    __epdk_charset_enm_e        draw_code;   /*字符编码*/
    GUI_COLOR                   bk_color;
} txtlayer_man_t;

__s32               TxtLayer_GetBPP(txtlayer_man_t *ptxt_layer);
__s32               TxtLayer_SwitchFB(txtlayer_man_t *txtlayer, __u32 x, __u32 y);
txtlayer_man_t     *TxtLayer_Create(H_LYR txtlayer, __hdle listmenu, __u32 item_w);
__u32               TxtLayer_Destroy(txtlayer_man_t *listlayer);
__u32               TxtLayer_OnDraw(txtlayer_man_t *listlayer);

#endif
