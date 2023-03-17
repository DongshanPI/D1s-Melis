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
#ifndef __SLISTBOX_I_H__
#define __SLISTBOX_I_H__

#include "../winclass_i.h"

#define slistbox_malloc(size)           esMEMS_Malloc(0,size)
#define slistbox_free(ptr)              esMEMS_Mfree(0,ptr)
#define slistbox_balloc(size)           esMEMS_Balloc(size)
#define slistbox_bfree(ptr,size)        esMEMS_Bfree(ptr,size)
#define slistbox_palloc(size)           esMEMS_Palloc(((size + 1023 )/1024), MEMS_PALLOC_MODE_BND_1K);
#define slistbox_pfree(ptr,size)        esMEMS_Pfree(ptr,((size + 1023 )/1024));
#define slistbox_memcpy                 eLIBs_memcpy
#define slistbox_memset                 eLIBs_memset

typedef __hdle  h_listboxsitem;

#define LISTITEMST_PUSHED              (1<<1)

#define LISTITEMST_FOCUS               (1<<2)

/*全局链表保留用户menuitem数据*/
typedef struct tag_LISTBOX_MEMUITEM
{
    struct tag_LISTBOX_MEMUITEM        *Prev;
    struct tag_LISTBOX_MEMUITEM        *Next;
    __u32                               itemno;
    ListboxItem_DrawCB                  cb;                         /* item draw回调函数                                          */
    H_WIN                               handle;                     /*menuitem所在listmenu的句柄*/
    void                               *attr;
    __u32                               item_w;
    __bool                              enable;
} __listbox_menuitem_t;

#define   SLISTBOX_ItemH2P(h_item)       ((__listbox_menuitem_t *)h_item)
#define   SLISTBOX_ItemP2H(pitem)        ((h_listboxitem)pitem)

/*定义需要绘制的Item区域和绘制参数*/
typedef struct tag_LISTBOX_SITEM
{
    RECT                                rect;
    ListboxItem_DrawCB                  cb;
    __listbox_menuitem_t               *menuitem;
} __listbox_sitem_t;

//------------------------------------------------------------------------------------------------------------
typedef struct tag_LISTBOX_MENULIST
{
    /*last current item*/
    __listbox_menuitem_t               *head;
    __listbox_menuitem_t               *tail;
    __u32                               ItemCount;

    /*only used in listbox mod*/
    __listbox_menuitem_t               *HeadItem;

    /*the number of page item num*/
    __u32                               pagenum;
} __listbox_menulist_t;

typedef struct tag_SLITBOX_DATA
{
    __u8                                scnnum;         /*实际数量*/
    __u32                               bk_color;
    __u32                               status;
    __u32                               draw_sts;
    __listbox_menulist_t               *menulist;
    H_WIN                               handle;        /*listmenu所在窗口的句柄*/
    __u32                               lastmsg;
    void                               *bk_bmp;
    __u32                               bmp_pos;
    __bool                              bk_draw;
    h_listboxsitem                      *sitem_array;

    /*当前正在listbox中显示有效条目数*/
    __u32                               valid_num;
    __u32                               cur_index;
    __u32                               last_index;
    GUI_MEMDEV_Handle                   hmem;

    __u32                               bpp;
    __u32                               lyr_w;
    __u32                               lyr_h;
    void                               *fb_addr;
    H_LYR                               lyr_win;
} __slistbox_data_t;

typedef __slistbox_data_t *plistboxdata;

#define LISTBOX_DRAWSTATUS(pCtrl)                    (((plistboxdata)GUI_CtrlWinGetAddData(pCtrl))->draw_sts)
#define LISTBOX_STATUS(pCtrl)                        (((plistboxdata)GUI_CtrlWinGetAddData(pCtrl))->status)
//#define BUTTON_STSTRANS(pCtrl)                     (BUTTON_OLDSTATUS(pCtrl) != BUTTON_STATUS(pCtrl))
#define LISTBOX_DATA(pCtrl)                          (((plistboxdata)GUI_CtrlWinGetAddData(pCtrl))->data)

__s32                   SItem_Destory(__listbox_sitem_t *sitem);
__listbox_sitem_t      *SItem_Create(__listbox_sitem_t *sitem_attr);

__u32                   SMenuItem_Destroy(__listbox_menuitem_t *menuitem);
__listbox_menuitem_t   *SMenuItem_Create(__slistbox_item_attr_t *item_attr, H_WIN  hWnd);
__listbox_menuitem_t   *SMenuItem_GetPrev(__listbox_menuitem_t *menuitem);
__listbox_menuitem_t   *SMenuItem_GetNext(__listbox_menuitem_t *menuitem);

__u32                   SMenuList_InsertAfter(__listbox_menulist_t *menulist, __listbox_menuitem_t *after, __listbox_menuitem_t *menuitem);
__listbox_menuitem_t   *SMenuList_GetMenuitem(__listbox_menulist_t *menulist, __s32 index);
__u32                   SMenuList_DelItem(__listbox_menulist_t *menulist, __listbox_menuitem_t *menuitem);
__u32                   SMenuList_DelAll(__listbox_menulist_t *menulist);
__u32                   SMenuList_AddTail(__listbox_menulist_t *menulist,  __listbox_menuitem_t *menuitem);
__u32                   SMenuList_AddHead(__listbox_menulist_t *menulist, __listbox_menuitem_t *menuitem);
__listbox_menulist_t   *SMenuList_Create(void);
__listbox_menuitem_t   *SMenuList_GetHead(__listbox_menulist_t *menulist);
H_WIN                   SMenuList_GetCurItem(__listbox_menulist_t *menulist);
__u32                   SMenuList_SetCurItem(__listbox_menulist_t *menulist, __listbox_menuitem_t *menuitem);
__listbox_menuitem_t   *SMenuList_GetTail(__listbox_menulist_t *menulist);
__u32                   SMenuList_GetItemCount(__listbox_menulist_t *menulist);
__u32                   SMenuList_Destroy(__listbox_menulist_t *menulist);
__listbox_menuitem_t   *SMenuList_FindNextEnable(__listbox_menulist_t *menulist, __listbox_menuitem_t *cur_item);
__listbox_menuitem_t   *SMenuList_FindPrevEnable(__listbox_menulist_t *menulist, __listbox_menuitem_t *cur_item);
__s32                   SMenuList_SetHeadItemFromItem(__listbox_menulist_t *menulist, __listbox_menuitem_t *cur_item);
__s32                   SMenuList_GetCurPageNum(__listbox_menulist_t *menulist);
#endif
