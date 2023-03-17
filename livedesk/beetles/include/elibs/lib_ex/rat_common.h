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
#ifndef __RAT_COMMON_H__
#define __RAT_COMMON_H__
#include <kconfig.h>

#define RAT_MAX_FULL_PATH_LEN (256+1)

typedef __hdle  HRAT;
typedef HRAT HRATNPL;

/*!
* \brief
*     浏览的媒体类型
*/
typedef enum
{
    RAT_MEDIA_TYPE_ALL = 0,     //所有媒体类型
    RAT_MEDIA_TYPE_PIC,         //所有图片文件
    RAT_MEDIA_TYPE_AUDIO,       //所有音频文件
    RAT_MEDIA_TYPE_VIDEO,       //所有视频文件
    RAT_MEDIA_TYPE_EBOOK,       //所有电子书文件
    RAT_MEDIA_TYPE_GAME,        //所有游戏文件
    RAT_MEDIA_TYPE_FIRMWARE,    //所有固件文件
    RAT_MEDIA_TYPE_UNKNOWN,     //所有未知文件类型
    RAT_MEDIA_TYPE_FOLDER,      //文件夹
    RAT_MEDIA_TYPE_USB_DEVICE,  //USB设备
    RAT_MEDIA_TYPE_SD_DEVICE,   //SD设备
    RAT_MEDIA_TYPE_MAX,         //
} rat_media_type_t;

/* play mode */
typedef enum __rat_play_mode_e
{
    RAT_PLAY_MODE_ONLY_ONCE = 0,
    RAT_PLAY_MODE_ROTATE_ONE,
    RAT_PLAY_MODE_ROTATE_ALL,
    RAT_PLAY_MODE_SEQUENCE,
    RAT_PLAY_MODE_RANDOM,
    RAT_PLAY_MODE_EXIT,
    RAT_PLAY_MODE_MAX
} rat_play_mode_e;

/*!
* \brief
*     分区对应的设备
*/
typedef enum
{
    RAT_UNKNOWN,        //未知
    RAT_LOCAL,          //本地磁盘
    RAT_TF,             //TF卡
    RAT_USB,            //USB设备
    RAT_CD,             //CD-ROM
    RAT_MEDIA           //媒体库
} rat_type_t;

enum
{
    RAT_TF_SWITCH_TO_USB = 0,
    RAT_USB_SWITCH_TO_TF,
    RAT_NOT_FOUND_TF,
    RAT_NOT_FOUND_USB,
};
#endif//__RAT_COMMON_H__
