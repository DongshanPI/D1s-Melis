/*
 * ekernel/components/avframework/v4l2/platform/sunxi-vin/vin-cci/sunxi_cci.h
 *
 * Copyright (c) 2007-2017 Allwinnertech Co., Ltd.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

/*
 ******************************************************************************
 *
 * sunxi_cci.h
 *
 * Hawkview ISP - sunxi_cci.h module
 *
 * Copyright (c) 2014 by Allwinnertech Co., Ltd.  http://www.allwinnertech.com
 *
 * Version         Author         Date         Description
 *
 *   2.0         Yang Feng     2014/06/23     Second Version
 *
 ******************************************************************************
 */

#ifndef _SUNXI_CCI_H_
#define _SUNXI_CCI_H_

#include "../platform/platform_cfg.h"
#include <waitqueue.h>
#include <aw_list.h>

struct cci_dev {
	unsigned int id;
	int irq;
	int use_cnt;
	rt_wqueue_t wait;

	void *base;

	struct list_head cci_list;
	struct pinctrl *pctrl;
	struct clk *clock;
};

int sunxi_cci_platform_register(void);
void sunxi_cci_platform_unregister(void);

#endif /*_SUNXI_CCI_H_*/
