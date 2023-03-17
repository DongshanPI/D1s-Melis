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
CDX_INTERFACE void __DecoderListAdd(struct DecoderListNodeS *newList,
                        struct DecoderListNodeS *prev, struct DecoderListNodeS *next)
{
    next->prev = newList;
    newList->next = next;
    newList->prev = prev;
    prev->next = newList;
}

CDX_INTERFACE void DecoderListAdd(struct DecoderListNodeS *newList, struct DecoderListS *list)
{
    __DecoderListAdd(newList, (struct DecoderListNodeS *)list, list->head);
}

CDX_INTERFACE void DecoderListAddBefore(struct DecoderListNodeS *newList,
                                    struct DecoderListNodeS *pos)
{
    __DecoderListAdd(newList, pos->prev, pos);
}

CDX_INTERFACE void DecoderListAddAfter(struct DecoderListNodeS *newList,
                                    struct DecoderListNodeS *pos)
{
    __DecoderListAdd(newList, pos, pos->next);
}

CDX_INTERFACE void DecoderListAddTail(struct DecoderListNodeS *newList, struct DecoderListS *list)
{
    __DecoderListAdd(newList, list->tail, (struct DecoderListNodeS *)list);
}

CDX_INTERFACE void __DecoderListDel(struct DecoderListNodeS *prev, struct DecoderListNodeS *next)
{
    next->prev = prev;
    prev->next = next;
}

CDX_INTERFACE void DecoderListDel(struct DecoderListNodeS *node)
{
    __DecoderListDel(node->prev, node->next);
    node->next = CDX_LIST_POISON1;
    node->prev = CDX_LIST_POISON2;
}

CDX_INTERFACE int DecoderListEmpty(const struct DecoderListS *list)
{
    return (list->head == (struct DecoderListNodeS *)list)
           && (list->tail == (struct DecoderListNodeS *)list);
}
