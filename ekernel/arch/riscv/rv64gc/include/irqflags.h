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
#ifndef _ASM_RISCV_IRQFLAGS_H
#define _ASM_RISCV_IRQFLAGS_H

#include "csr.h"

/* read interrupt enabled status */
static inline unsigned long arch_local_save_flags(void)
{
    return csr_read(CSR_SSTATUS);
}

/* test flags */
static inline int arch_irqs_disabled_flags(unsigned long flags)
{
    return !(flags & SR_SIE);
}

/* test hardware interrupt enable bit */
static inline int arch_irqs_disabled(void)
{
    return arch_irqs_disabled_flags(arch_local_save_flags());
}

/* unconditionally enable interrupts */
static inline void arch_local_irq_enable(void)
{
    csr_set(CSR_SSTATUS, SR_SIE);
}

/* unconditionally disable interrupts */
static inline void arch_local_irq_disable(void)
{
    csr_clear(CSR_SSTATUS, SR_SIE);
}

/* get status and disable interrupts */
static inline unsigned long arch_local_irq_save(void)
{
    return csr_read_clear(CSR_SSTATUS, SR_SIE);
}

/* set interrupt enabled status */
static inline void arch_local_irq_restore(unsigned long flags)
{
    csr_set(CSR_SSTATUS, flags & SR_SIE);
}

static inline void wait_for_interrupt(void)
{
    __asm__ __volatile__("wfi");
}

#endif /* _ASM_RISCV_IRQFLAGS_H */
