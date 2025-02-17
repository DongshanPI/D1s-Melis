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
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef _ENC_ADAPTER_H
#define _ENC_ADAPTER_H

//#include "memoryAdapter.h"
//#include "secureMemoryAdapter.h"
#include <cdc_config.h>
#include <sc_interface.h>

int  EncAdapterInitializeVe(void);

int   EncAdapterInitializeMem(struct ScMemOpsS *memops);

void  EncAdpaterRelease(struct ScMemOpsS *memops);

int   EncAdapterLockVideoEngine(void);

void  EncAdapterUnLockVideoEngine(void);

void  EncAdapterVeReset(void);

int   EncAdapterVeWaitInterrupt(void);

void* EncAdapterVeGetBaseAddress(void);

int   EncAdapterMemGetDramType(void);

void EncAdapterEnableEncoder(void);

void EncAdapterDisableEncoder(void);

void EncAdapterResetEncoder(void);

void EncAdapterInitPerformance(int nMode);

void EncAdapterUninitPerformance(int nMode);

unsigned int EncAdapterGetICVersion(void* pTopBaseAddr);

void EncAdapterSetDramType(void);

void EncAdapterPrintTopVEReg(void* pTopBaseAddr);

void EncAdapterPrintEncReg(void* pTopBaseAddr);

void EncAdapterPrintIspReg(void* pTopBaseAddr);

unsigned int EncAdapterGetVeAddrOffset(void);

int __EncAdapterMemOpen(struct ScMemOpsS *memops);

void __EncAdapterMemClose(struct ScMemOpsS *memops);

void* __EncAdapterMemPalloc(struct ScMemOpsS *memops, int nSize, void *veOps, void *pVeopsSelf);

void* __EncAdapterMemNoCachePalloc(struct ScMemOpsS *memops, int nSize, void *veOps, void *pVeopsSelf);

void __EncAdapterMemPfree(struct ScMemOpsS *memops, void* pMem, void *veOps, void *pVeopsSelf);

void __EncAdapterMemFlushCache(struct ScMemOpsS *memops, void* pMem, int nSize);

void* __EncAdapterMemGetPhysicAddress(struct ScMemOpsS *memops, void* pVirtualAddress);

void* __EncAdapterMemGetPhysicAddressCpu(struct ScMemOpsS *memops, void* pVirtualAddress);

void* __EncAdapterMemGetVirtualAddress(struct ScMemOpsS *memops, void* pPhysicAddress);

unsigned int __EncAdapterMemGetVeAddrOffset(struct ScMemOpsS *memops);

#define EncMemAdapterOpen() __EncAdapterMemOpen(_memops)

#define EncMemAdapterClose() __EncAdapterMemClose(_memops)

#define EncAdapterMemPalloc(nSize) __EncAdapterMemPalloc(_memops, nSize, veOps, pVeopsSelf)

#define EncAdapterNoCacheMemPalloc(nSize) __EncAdapterMemNoCachePalloc(_memops, nSize, veOps, pVeopsSelf)

#define EncAdapterMemPfree(pMem) __EncAdapterMemPfree(_memops, pMem, veOps, pVeopsSelf)

#define EncAdapterMemFlushCache(pMem, nSize) __EncAdapterMemFlushCache(_memops, pMem, nSize)

#define  EncAdapterGetVeAddrOffset() __EncAdapterMemGetVeAddrOffset(_memops)

#define EncAdapterMemGetPhysicAddress(pVirtualAddress) \
   __EncAdapterMemGetPhysicAddress(_memops, pVirtualAddress)

#define EncAdapterMemGetPhysicAddressCpu(pVirtualAddress) \
   __EncAdapterMemGetPhysicAddressCpu(_memops, pVirtualAddress)

#define EncAdapterMemGetVirtualAddress(pPhysicAddress) \
   __EncAdapterMemGetVirtualAddress(_memops, pPhysicAddress)

#endif //_ENC_ADAPTER_H

#ifdef __cplusplus
}
#endif /* __cplusplus */
