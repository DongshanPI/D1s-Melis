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
#ifndef _PWRMAN_SCRIPT_H_
#define _PWRMAN_SCRIPT_H_
#include <typedef.h>

#define PWRMAN_SCRIPT_DEBUG     (0)
#define KEY_WORD_MAX_SIZE       (32)

#define TABLE           '\t'
#define SPACE           ' '
#define NEWLINE         '\n'
#define ENTER           '\r'
#define REMARK          ';'

typedef enum __PARS_SCRIPT_RESULT
{
    SCRIPT_PARSE_ERR_NONE   = 0,
    SCRIPT_PARSE_ERR_EOF    = 1,
} __pars_script_result_t;

typedef struct __PWRMAN_SCRIPT_FUNC_MAP
{
    char        keystr[KEY_WORD_MAX_SIZE];
    int32_t     (*func)(void);
} __pwrman_script_func_mapt_t;


typedef struct __PWRMAN_SCRIPT_PSR
{
    uint8_t     *buf_start;
    uint32_t    buf_size;
    uint8_t     *script_end;
    uint8_t     *cur_ptr;
    uint8_t     string[KEY_WORD_MAX_SIZE + 8];
} __pwrman_script_psr_t;


#endif  /* _PWRMAN_SCRIPT_H_ */