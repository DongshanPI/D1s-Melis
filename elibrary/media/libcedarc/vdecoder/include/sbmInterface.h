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
#ifndef __SBM_INTERFACE__
#define __SBM_INTERFACE__

#include "vdecoder.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SBM_LESS_DATA_SIZE (8*1024) //8 kb

#define MAX_FRAME_BUFFER_NUM 2
typedef struct SbmConfig
{
    int bVirFlag;// only for jpeg tile mode create sbm buffer
    int nSbmBufferTotalSize;
    struct ScMemOpsS * memops;
    VeOpsS*           veOpsS;
    void*             pVeOpsSelf;
    int bSecureVideoFlag;
    int nWidth;
    int nConfigSbmBufferSize;
    int nNaluLength;
}SbmConfig;

#define MAX_FRAME_PIC_NUM (100)
#define DEFAULT_NALU_NUM (32)
#define MAX_FRAME_PTS_LIST_NUM (10)

enum SbmInterfaceType
{
    SBM_TYPE_STREAM = 0,
    SBM_TYPE_FRAME  = 1,
    SBM_TYPE_FRAME_AVS = 2,
    SBM_TYPE_FRAME_MPEG2 = 3,
    SBM_TYPE_FRAME_AVC = 4
};

typedef struct STREAMNALUINFO
{
    int   nType;
    int nNalRefIdc;
    char* pDataBuf;
    int   nDataSize;
}NaluInfo;

typedef struct SBM_FRAME_BUFFER_MANAGER
{
    char* pFrameBuffer;
    size_addr pPhyFrameBuffer;
    size_addr pPhyFrameBufferEnd;
    unsigned int nFrameBufferSize;
}SbmFrameBufferManager;


typedef struct FRAMEPICINFO
{
    NaluInfo* pNaluInfoList;
    int       nMaxNaluNum;
    int       nCurNaluIdx;
    int       nlength;
    char*     pDataStartAddr;
    int64_t   nPts;
    int64_t   nPcr;
    int       bValidFlag;
    int       nFrameNaluType;
    unsigned int  bVideoInfoFlag;
    void*     pVideoInfo;
    SbmFrameBufferManager* pSbmFrameBufferManager;
}FramePicInfo;

typedef struct FRAMEPICFIFO
{
    FramePicInfo*    pFramePics;
    int              nMaxFramePicNum;
    int              nValidFramePicNum;
    int              nUnReadFramePicNum;
    int              nFPReadPos;
    int              nFPWritePos;
    int              nFPFlushPos;
}FramePicFifo;

typedef struct STREAMFRAMEFIFO
{
    VideoStreamDataInfo* pFrames;
    int                  nMaxFrameNum;
    int                  nValidFrameNum;
    int                  nUnReadFrameNum;
    int                  nReadPos;
    int                  nWritePos;
    int                  nFlushPos;
}StreamFrameFifo;


typedef struct DETECTFRAMEPICINFO
{
    VideoStreamDataInfo* pCurStream;
    char*                pCurStreamDataptr;
    int                  nCurStreamDataSize;
    int                  nCurStreamRebackFlag; // have two truck data buffer
    FramePicInfo*        pCurFramePic;
    int                  bCurFrameStartCodeFound;
    int64_t              nCurFramePtsList[MAX_FRAME_PTS_LIST_NUM];
}DetectFramePicInfo;


typedef struct SbmInterface SbmInterface;

struct SbmInterface
{
    int   (*init)(SbmInterface* pSelf, SbmConfig* pSbmConfig);

    void  (*destroy)(SbmInterface* pSelf);

    void  (*reset)(SbmInterface* pSelf);

    void* (*getBufferAddress)(SbmInterface* pSelf);

    int   (*getBufferSize)(SbmInterface* pSelf);

    int   (*getStreamFrameNum)(SbmInterface* pSelf);

    int   (*getStreamDataSize)(SbmInterface* pSelf);

    int   (*requestBuffer)(SbmInterface* pSelf, int nRequireSize, char** ppBuf, int* pBufSize);

    int   (*addStream)(SbmInterface* pSelf, VideoStreamDataInfo* pDataInfo);

    VideoStreamDataInfo* (*requestStream)(SbmInterface* pSelf);

    int    (*returnStream)(SbmInterface* pSelf, VideoStreamDataInfo* pDataInfo);

    int    (*flushStream)(SbmInterface* pSelf, VideoStreamDataInfo* pDataInfo);

    char*  (*getBufferWritePointer)(SbmInterface* pSelf);

    void*  (*getBufferDataInfo)(SbmInterface* pSelf);

    int    (*setEos)(SbmInterface* pSelf, int nEosFlag);

    int     nType;
    int     bUseNewVeMemoryProgram;

};

static inline int  SbmInit(SbmInterface* pSelf, SbmConfig* pSbmConfig)
{
    return pSelf->init(pSelf, pSbmConfig);
}

static inline void  SbmDestroy(SbmInterface* pSelf)
{
    pSelf->destroy(pSelf);
}

static inline void  SbmReset(SbmInterface* pSelf)
{
    pSelf->reset(pSelf);
}

static inline void* SbmBufferAddress(SbmInterface* pSelf)
{
    return pSelf->getBufferAddress(pSelf);
}

static inline int SbmBufferSize(SbmInterface* pSelf)
{
    return pSelf->getBufferSize(pSelf);
}

static inline int SbmStreamFrameNum(SbmInterface* pSelf)
{
    return pSelf->getStreamFrameNum(pSelf);
}

static inline int SbmStreamDataSize(SbmInterface* pSelf)
{
    return pSelf->getStreamDataSize(pSelf);
}

static inline int SbmRequestBuffer(SbmInterface* pSelf, int nRequireSize,
                                         char** ppBuf, int* pBufSize)
{
    return pSelf->requestBuffer(pSelf, nRequireSize, ppBuf, pBufSize);
}

static inline int SbmAddStream(SbmInterface* pSelf, VideoStreamDataInfo* pDataInfo)
{
    return pSelf->addStream(pSelf, pDataInfo);
}

static inline VideoStreamDataInfo* SbmRequestStream(SbmInterface* pSelf)
{
    return pSelf->requestStream(pSelf);
}

static inline int SbmReturnStream(SbmInterface* pSelf, VideoStreamDataInfo* pDataInfo)
{
    return pSelf->returnStream(pSelf, pDataInfo);
}

static inline int SbmFlushStream(SbmInterface* pSelf, VideoStreamDataInfo* pDataInfo)
{
    return pSelf->flushStream(pSelf, pDataInfo);
}

static inline char* SbmBufferWritePointer(SbmInterface* pSelf)
{
    return pSelf->getBufferWritePointer(pSelf);
}

static inline void* SbmBufferDataInfo(SbmInterface* pSelf)
{
    return pSelf->getBufferDataInfo(pSelf);
}

static inline int SbmSetEos(SbmInterface* pSelf, int nEosFlag)
{
    return pSelf->setEos(pSelf, nEosFlag);
}


typedef struct SBM_FRAME_BUFFER_NODE SbmFrameBufferNode;
struct SBM_FRAME_BUFFER_NODE
{
    SbmFrameBufferNode* pNext;
    FramePicInfo*       pFramePic;
    SbmFrameBufferManager* pSbmBufferManager;
};

typedef struct FIRST_IN_FIRST_OUT_INST  FiFoQueueInst;
struct FIRST_IN_FIRST_OUT_INST
{
    void*  pNext;
    void*  pParam1;
    void*  pParam2;
};

int SbmFrameBufferSizeCalculate(int nConfigSbmBufferSize,int nVideoWidth);

void FIFOEnqueue(FiFoQueueInst** ppHead, FiFoQueueInst* p);
FiFoQueueInst* FIFODequeue(FiFoQueueInst** ppHead);
void FIFOEnqueueToHead(FiFoQueueInst ** ppHead, FiFoQueueInst* p);

#ifdef __cplusplus
}
#endif

#endif
