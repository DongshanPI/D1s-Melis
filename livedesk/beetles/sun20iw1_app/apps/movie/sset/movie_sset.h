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
#ifndef __MOVIE_SSET_H__
#define __MOVIE_SSET_H__
//////////////////////////////////////////////////////////////////////////
#include "beetles_app.h"

/*notify message of sset*/
typedef enum
{
    MOVIE_SSET_NC_RETURN = 1,
    MOVIE_SSET_NC_PRE,
    MOVIE_SSET_NC_PLAY,
    MOVIE_SSET_NC_NEXT,
    MOVIE_SSET_NC_ZOOM,
    MOVIE_SSET_NC_SUBTITLE,
    MOVIE_SSET_NC_PLAYMODE,
    MOVIE_SSET_NC_CHANNEL,
    MOVIE_SSET_NC_TRACK,
    //MOVIE_SSET_NC_TVOUT,
    MOVIE_SSET_NC_AB,
    MOVIE_SSET_NC_LIST//二级菜单发过来的消息
} __movie_sset_nc_t;

typedef struct
{
    __s32 sub_pos;
    __s32 track;
    __s32 channel;
    __s32 playmode;
    __s32 zoom;
} __movie_sset_list_para_t;

#define MOVIE_SSET_NC_ID_UNKNOW    0xff

__sset_create_para_t *Movie_SSET_Build_CreatePara(H_WIN hManwin, __u32 sub_id
        , __movie_sset_list_para_t *sset_list_para);


__s32 Movie_SSET_Destroy_CreatePara(__sset_create_para_t *create_para);

#endif //__MOVIE_SSET_H__
