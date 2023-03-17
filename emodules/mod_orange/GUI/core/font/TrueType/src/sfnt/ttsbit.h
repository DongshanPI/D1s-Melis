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
/*                                                                         */
/*  ttsbit.h                                                               */
/*                                                                         */
/*    TrueType and OpenType embedded bitmap support (specification).       */
/*                                                                         */
/*  Copyright 1996-2001, 2002, 2003, 2004, 2005, 2006, 2007 by             */
/*  David Turner, Robert Wilhelm, and Werner Lemberg.                      */
/*                                                                         */
/*  This file is part of the FreeType project, and may only be used,       */
/*  modified, and distributed under the terms of the FreeType project      */
/*  license, LICENSE.TXT.  By continuing to use, modify, or distribute     */
/*  this file you indicate that you have read the license and              */
/*  understand and accept it fully.                                        */
/*                                                                         */
/***************************************************************************/
#ifndef __TTSBIT_H__
#define __TTSBIT_H__


#include "ft2build.h"
#include "ttload.h"


FT_BEGIN_HEADER


FT_LOCAL(FT_Error)
tt_face_load_eblc(TT_Face    face,
                  FT_Stream  stream);

FT_LOCAL(void)
tt_face_free_eblc(TT_Face  face);


FT_LOCAL(FT_Error)
tt_face_set_sbit_strike(TT_Face          face,
                        FT_Size_Request  req,
                        FT_ULong        *astrike_index);

FT_LOCAL(FT_Error)
tt_face_load_strike_metrics(TT_Face           face,
                            FT_ULong          strike_index,
                            FT_Size_Metrics  *metrics);

#if defined FT_CONFIG_OPTION_OLD_INTERNALS
FT_LOCAL(FT_Error)
tt_find_sbit_image(TT_Face          face,
                   FT_UInt          glyph_index,
                   FT_ULong         strike_index,
                   TT_SBit_Range   *arange,
                   TT_SBit_Strike  *astrike,
                   FT_ULong        *aglyph_offset);

FT_LOCAL(FT_Error)
tt_load_sbit_metrics(FT_Stream        stream,
                     TT_SBit_Range    range,
                     TT_SBit_Metrics  metrics);

#endif /* FT_CONFIG_OPTION_OLD_INTERNALS */

FT_LOCAL(FT_Error)
tt_face_load_sbit_image(TT_Face              face,
                        FT_ULong             strike_index,
                        FT_UInt              glyph_index,
                        FT_UInt              load_flags,
                        FT_Stream            stream,
                        FT_Bitmap           *map,
                        TT_SBit_MetricsRec  *metrics);


FT_END_HEADER

#endif /* __TTSBIT_H__ */


/* END */
