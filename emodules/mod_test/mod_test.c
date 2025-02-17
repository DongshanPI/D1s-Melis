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
#include <log.h>
#include <elibs_stdio.h>
#include "mod_test.h"
#include <csp_dma_para.h>
#include <unistd.h>
#include <fcntl.h>

void ftest_entry(void *para);

__mp ftest_mp = {0, 0};

/*
****************************************************************************************************
*
*                           ftest_MInit
*
*  Description:
*       ftest_MInit
*
*  Parameters:
*
*  Return value:
*       EPDK_OK
*       EPDK_FAIL
****************************************************************************************************
*/
int32_t ftest_MInit(void)
{
#if 0
    int32_t ft_fd = -1;

    __log("===============");
    ft_fd = open("/dev/uart0", O_RDWR);
    esKRNL_TimeDly(10);
    __log("===============ft_fd = %d", ft_fd);
    if(ft_fd >= 0)
    {
        esKRNL_TimeDly(10);
        write(ft_fd, "0123456789abcd\r\n", sizeof("0123456789abcd\r\n") - 1);
        esKRNL_TimeDly(10);
        close(ft_fd);
    }
#endif
    return EPDK_OK;
}

/*
****************************************************************************************************
*
*                           ftest_MExit
*
*  Description:
*       ftest_MExit
*
*  Parameters:
*
*  Return value:
*       EPDK_OK
*       EPDK_FAIL
****************************************************************************************************
*/
int32_t ftest_MExit(void)
{
    return EPDK_OK;
}

/*
****************************************************************************************************
*
*                           ftest_MOpen
*
*  Description:
*       ftest_MOpen
*
*  Parameters:
*
*  Return value:
*       EPDK_OK
*       EPDK_FAIL
****************************************************************************************************
*/
__mp *ftest_MOpen(uint32_t mid, uint32_t mod)
{
    __log("ftest_MOpen module test\t\n");

    //esKRNL_TCreate(ftest_entry, NULL, 0x8000, 3);
    return &ftest_mp;
}

/*
****************************************************************************************************
*
*             ftest_MClose
*
*  Description:
*       ftest_MClose
*
*  Parameters:
*
*  Return value:
*       EPDK_OK
*       EPDK_FAIL
****************************************************************************************************
*/
int32_t ftest_MClose(__mp *mp)
{
    return EPDK_OK;
}

/*
****************************************************************************************************
*
*             ftest_MRead
*
*  Description:
*       ftest_MRead
*
*  Parameters:
*
*  Return value:
*       EPDK_OK
*       EPDK_FAIL
****************************************************************************************************
*/
uint32_t ftest_MRead(void *pdata, uint32_t size, uint32_t n, __mp *mp)
{
    return size * n;
}

/*
****************************************************************************************************
*
*             ftest_MWrite
*
*  Description:
*       ftest_MWrite
*
*  Parameters:
*
*  Return value:
*       EPDK_OK
*       EPDK_FAIL
****************************************************************************************************
*/
uint32_t ftest_MWrite(const void *pdata, uint32_t size, uint32_t n, __mp *mp)
{
    return size * n;
}

/*
****************************************************************************************************
*
*             ftest_MIoctrl
*
*  Description:
*       ftest_MIoctrl
*
*  Parameters:
*
*  Return value:
*       EPDK_OK
*       EPDK_FAIL
****************************************************************************************************
*/
int32_t ftest_MIoctrl(__mp *mp, uint32_t cmd, int32_t aux, void *pbuffer)
{
    /* no ioctl command now */
    return EPDK_OK;
}

__hdle dma_sem_wait      = NULL;

void dma_test_callback(void *para)
{
    uint8_t err = 0;
    //eLIBs_printf("dma_cb\r\n");
    err = esKRNL_SemPost(dma_sem_wait);
    //eLIBs_printf("dma_cb\r\n");
}

void test_dma(void)
{
    void *hdma      = NULL;
    char *srcbuf    = esMEMS_Balloc(4096);
    char *dstbuf    = esMEMS_Balloc(4096);
    int ret         = 0;
    int8_t err      = 0;
    csp_dma_slave_config config = {0};

    dma_sem_wait = esKRNL_SemCreate(0);

    config.direction        = CSP_DMA_MEM_TO_MEM;
    config.src_addr         = (unsigned long)srcbuf;
    config.dst_addr         = (unsigned long)dstbuf;
    config.src_addr_width   = CSP_DMA_SLAVE_BUSWIDTH_8_BYTES;
    config.dst_addr_width   = CSP_DMA_SLAVE_BUSWIDTH_8_BYTES;
    config.src_maxburst     = CSP_DMA_SLAVE_BURST_16;
    config.dst_maxburst     = CSP_DMA_SLAVE_BURST_16;
    config.slave_id         = dma_slave_id(DRQSRC_SDRAM_RXTX, DRQSRC_SDRAM_RXTX);
    /*cylic is used for m2d/d2m/d2d because of the fifo is limited by hardware*/
    //config.cyclic           = 0
    config.total_bytes      = 4096;
    config.period_bytes     = 4096;

    hdma    = esDMA_Request();
    ret     = esDMA_Setting(hdma,(void *)&config);
	ret     = esDMA_RegDmaHdler(hdma, dma_test_callback, (void*)dma_sem_wait);
    while(1)
    {
        esKSRV_memset(srcbuf, 'a', 4096);
        esKSRV_memset(dstbuf,   0, 4096);
        esDMA_Start(hdma);

        esKRNL_SemPend(dma_sem_wait, 0, &err);
        if(OS_NO_ERR == err)
        {
            __log("dma memcpy completed!");
            esDMA_Stop(hdma);

            for(uint32_t i = 0; i < 4096; i ++)
            {
                if('a' != dstbuf[i])
                __log("dstbuf[%d] = 0x%X", i , dstbuf[i]);
            }
            __log("compare finish!");
        }
        esKRNL_TimeDly(100);
    }
}

void ftest_entry(void *para)
{
    test_dma();
}
