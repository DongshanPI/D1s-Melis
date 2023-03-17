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
#ifndef  __robin_video_win_c
#define  __robin_video_win_c


#include "robin_i.h"



/***************************************************************************************************
*Name        : robin_set_video_win
*Prototype   : __s32  robin_set_video_win( __s32 x, __s32 y, __s32 width, __s32 height )
*Arguments   : x        input.
*              y        input.
*              width    input.
*              height   input.
*Return      : ==0       succeed
*              !=0       fail
*Description : set the rectangle of the video window.
*Other       :
***************************************************************************************************/
__s32  robin_set_video_win(__s32 x, __s32 y, __s32 width, __s32 height)
{
    RECT  image_win;
    image_win.x      = x;
    image_win.y      = y;
    image_win.width  = width;
    image_win.height = height;

    if (esMODS_MIoctrl(robin_hced, CEDAR_CMD_SET_VID_WINDOW, 0, &image_win) != EPDK_OK)
    {
        __wrn("Fail in setting video window information to cedar!");
        return -1;
    }

    return 0;
}



/***************************************************************************************************
*Name        : robin_get_video_win
*Prototype   : __s32 robin_get_video_win( RECT *rect_p )
*Arguments   : rect_p         output. store the rectangle information of the video window.
*Return      : ==0       succeed
*              !=0       fail
*Description : get the rectangle information of the video window.
*Other       :
***************************************************************************************************/
__s32 robin_get_video_win(RECT *rect_p)
{
    RECT  *rect_i;

    if (rect_p == NULL)
    {
        return -1;
    }

    rect_i = (RECT *)(unsigned long)esMODS_MIoctrl(robin_hced, CEDAR_CMD_GET_VID_WINDOW, 0, NULL);

    if (rect_i == NULL)
    {
        return -1;
    }

    g_memcpy(rect_p, rect_i, sizeof(RECT));
    return 0;
}



#endif     //  ifndef __robin_video_win_c

/* end of robin_video_win.c */
