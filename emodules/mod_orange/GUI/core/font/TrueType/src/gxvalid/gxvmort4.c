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
/*  gxvmort4.c                                                             */
/*                                                                         */
/*    TrueTypeGX/AAT mort table validation                                 */
/*    body for type4 (Non-Contextual Glyph Substitution) subtable.         */
/*                                                                         */
/*  Copyright 2005 by suzuki toshiya, Masatake YAMATO, Red Hat K.K.,       */
/*  David Turner, Robert Wilhelm, and Werner Lemberg.                      */
/*                                                                         */
/*  This file is part of the FreeType project, and may only be used,       */
/*  modified, and distributed under the terms of the FreeType project      */
/*  license, LICENSE.TXT.  By continuing to use, modify, or distribute     */
/*  this file you indicate that you have read the license and              */
/*  understand and accept it fully.                                        */
/*                                                                         */
/***************************************************************************/

/***************************************************************************/
/*                                                                         */
/* gxvalid is derived from both gxlayout module and otvalid module.        */
/* Development of gxlayout is supported by the Information-technology      */
/* Promotion Agency(IPA), Japan.                                           */
/*                                                                         */
/***************************************************************************/
#include "gxvmort.h"


/*************************************************************************/
/*                                                                       */
/* The macro FT_COMPONENT is used in trace mode.  It is an implicit      */
/* parameter of the FT_TRACE() and FT_ERROR() macros, used to print/log  */
/* messages during execution.                                            */
/*                                                                       */
#undef  FT_COMPONENT
#define FT_COMPONENT  trace_gxvmort


static void gxv_mort_subtable_type4_lookupval_validate(FT_UShort            glyph,
        GXV_LookupValueDesc  value,
        GXV_Validator        valid)
{
    FT_UNUSED(glyph);
    gxv_glyphid_validate(value.u, valid);
}

/*
  +===============+ --------+
  | lookup header |         |
  +===============+         |
  | BinSrchHeader |         |
  +===============+         |
  | lastGlyph[0]  |         |
  +---------------+         |
  | firstGlyph[0] |         |    head of lookup table
  +---------------+         |             +
  | offset[0]     |    ->   |          offset            [byte]
  +===============+         |             +
  | lastGlyph[1]  |         | (glyphID - firstGlyph) * 2 [byte]
  +---------------+         |
  | firstGlyph[1] |         |
  +---------------+         |
  | offset[1]     |         |
  +===============+         |
                            |
   ....                     |
                            |
  16bit value array         |
  +===============+         |
  |     value     | <-------+
   ....
*/

static GXV_LookupValueDesc gxv_mort_subtable_type4_lookupfmt4_transit(
    FT_UShort            relative_gindex,
    GXV_LookupValueDesc  base_value,
    FT_Bytes             lookuptbl_limit,
    GXV_Validator        valid)
{
    FT_Bytes             p;
    FT_Bytes             limit;
    FT_UShort            offset;
    GXV_LookupValueDesc  value;
    /* XXX: check range? */
    offset = (FT_UShort)(base_value.u +
                         relative_gindex * sizeof(FT_UShort));
    p     = valid->lookuptbl_head + offset;
    limit = lookuptbl_limit;
    GXV_LIMIT_CHECK(2);
    value.u = FT_NEXT_USHORT(p);
    return value;
}


FT_LOCAL_DEF(void)
gxv_mort_subtable_type4_validate(FT_Bytes       table,
                                 FT_Bytes       limit,
                                 GXV_Validator  valid)
{
    FT_Bytes  p = table;
    GXV_NAME_ENTER("mort chain subtable type4 "
                   "(Non-Contextual Glyph Substitution)");
    valid->lookupval_sign   = GXV_LOOKUPVALUE_UNSIGNED;
    valid->lookupval_func   = gxv_mort_subtable_type4_lookupval_validate;
    valid->lookupfmt4_trans = gxv_mort_subtable_type4_lookupfmt4_transit;
    gxv_LookupTable_validate(p, limit, valid);
    GXV_EXIT;
}


/* END */
