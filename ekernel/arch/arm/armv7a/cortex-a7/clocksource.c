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
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#include <barrier.h>
#include <ktimer.h>
#include <log.h>

#include <hal_debug.h>
#include <hal_thread.h>

static inline uint32_t arch_timer_get_cntfrq(void)
{
    uint32_t val;
    asm volatile("mrc p15, 0, %0, c14, c0, 0" : "=r"(val));
    return val;
}

static inline uint64_t arch_counter_get_cntvct(void)
{
    uint64_t cval;

    isb();
    asm volatile("mrrc p15, 1, %Q0, %R0, c14" : "=r"(cval));
    return cval;
}

static inline uint64_t arch_counter_get_cntpct(void)
{
    uint64_t cval;

    isb();
    asm volatile("mrrc p15, 0, %Q0, %R0, c14" : "=r"(cval));
    return cval;
}

uint64_t (*arch_timer_read_counter)(void) = arch_counter_get_cntpct;
static cycle_t arch_counter_read(struct clocksource *cs)
{
    return arch_timer_read_counter();
}

static struct clocksource arch_timer_clocksource =
{
    .name   = "arch_sys_counter",
    .read   = arch_counter_read,
    .mask   = CLOCKSOURCE_MASK(56),
};

int64_t ktime_get(void)
{
    struct clocksource *cs = &arch_timer_clocksource;

    double ns_per_ticks = cs->mult / (1 << cs->shift);

    //~41.6666667 nano seconds per tick.
    ns_per_ticks = NS_PER_TICK;
    uint64_t arch_counter = cs->read(cs);

    return arch_counter * ns_per_ticks;
}

int do_gettimeofday(struct timespec64 *ts)
{
    if (ts == NULL)
    {
        __err("fatal error, not valide paramter.");
        hal_sys_abort();
    }

    int64_t nsecs = ktime_get();

    ts->tv_sec  = nsecs / NSEC_PER_SEC;
    ts->tv_nsec = nsecs % NSEC_PER_SEC;

    return 0;
}

void timekeeping_init(void)
{
    struct clocksource *cs = &arch_timer_clocksource;

    cs->shift = 24;
    cs->mult = 699050667;
    cs->arch_timer_rate = arch_timer_get_cntfrq();
    if (cs->arch_timer_rate == 0)
    {
        cs->arch_timer_rate = 24000000;
    }

    return;
}

void timestamp(char *tag)
{
    struct timespec64 ts;
    do_gettimeofday(&ts);

    printf("[TSM]: %*.*s]:sec %lld, nsec %ld.\n", 12, 12, tag, ts.tv_sec, ts.tv_nsec);
}

void udelay(unsigned int us)
{
    uint64_t start, target;
    uint64_t frequency;

    frequency = arch_timer_get_cntfrq();
    start = arch_counter_get_cntpct();
    target = frequency / 1000000ULL * us;

    while (arch_counter_get_cntpct() - start <= target) ;
}

int usleep(unsigned int usecs)
{
    int msecs = usecs / 1000;
    if (msecs >= (1000 / CONFIG_HZ))
    {
        int ticks = msecs / (1000 / CONFIG_HZ);
        kthread_sleep(ticks > 0 ? ticks : 1);
    }
    else
    {
        udelay(usecs);
    }
    return 0;
}

