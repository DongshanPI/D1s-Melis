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
#ifndef  __DSK_WKM_STAR_H__
#define  __DSK_WKM_STAR_H__

#ifdef __cplusplus
extern "C" {
#endif


#define DSK_WKM_STAR_MAX           5


/*
****************************************************************************************************
*Name        : dsk_wkm_set_star
*Prototype   : __s32  dsk_wkm_set_star( const char *file, __u32 star )
*Arguments   : file      input. file name, full name.
*              star      input. star value and it rangs 0~~DSK_WKM_STAR_MAX.
*Return      : ==0       succeed
*              !=0       fail
*Description : set the audio file's star.
*Other       :
****************************************************************************************************
*/
extern __s32  dsk_wkm_set_star(const char *file, __u32 star);

/*
****************************************************************************************************
*Name        : dsk_wkm_get_star
*Prototype   : __s32  dsk_wkm_get_star( const char *file )
*Arguments   : file    input. full path.
*Return      : the star of the file. If return value < 0, that means some error occured.
*Description : get the star of the file.
*Other       :
****************************************************************************************************
*/
extern __s32  dsk_wkm_get_star(const char *file);



#ifdef __cplusplus
}
#endif

#endif     //  ifndef __DSK_WKM_STAR_H__

/* end of dsk_wkm_star.h */
