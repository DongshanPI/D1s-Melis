/*
 * ekernel/components/avframework/v4l2/platform/sunxi-vin/vin-mipi/dphy/dphy.h
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


#ifndef __DPHY_H__
#define __DPHY_H__

enum dphy_lane {
	LANE_D0,
	LANE_D1,
	LANE_D2,
	LANE_D3,
	LANE_CLK,
};

enum dphy_int {
	SOT_D0,
	SOT_D1,
	SOT_D2,
	SOT_D3,
	SOT_ERR_D0,
	SOT_ERR_D1,
	SOT_ERR_D2,
	SOT_ERR_D3,
	SOT_SYNC_ERR_D0,
	SOT_SYNC_ERR_D1,
	SOT_SYNC_ERR_D2,
	SOT_SYNC_ERR_D3,
	RX_ALG_ERR_D0,
	RX_ALG_ERR_D1,
	RX_ALG_ERR_D2,
	RX_ALG_ERR_D3,
	CD_LP0_ERR_CLK,
	CD_LP1_ERR_CLK,
	CD_LP0_ERR_D0,
	CD_LP1_ERR_D0,
	CD_LP0_ERR_D1,
	CD_LP1_ERR_D1,
	CD_LP0_ERR_D2,
	CD_LP1_ERR_D2,
	CD_LP0_ERR_D3,
	CD_LP1_ERR_D3,
	ULPS_D0,
	ULPS_D1,
	ULPS_D2,
	ULPS_D3,
	ULPS_WP_D0,
	ULPS_WP_D1,
	ULPS_WP_D2,
	ULPS_WP_D3,
	ULPS_CLK,
	ULPS_WP_CLK,
	LPDT_D0,
	RX_TRND_D0,
	TX_TRND_ERR_D0,
	UNDEF1_D0,
	UNDEF2_D0,
	UNDEF3_D0,
	UNDEF4_D0,
	UNDEF5_D0,
	RST_D0,
	RST_D1,
	RST_D2,
	RST_D3,
	ESC_CMD_ERR_D0,
	ESC_CMD_ERR_D1,
	ESC_CMD_ERR_D2,
	ESC_CMD_ERR_D3,
	FALSE_CTL_D0,
	FALSE_CTL_D1,
	FALSE_CTL_D2,
	FALSE_CTL_D3,
};

enum dphy_lane_state {
	LP00,
	LP01,
	LP10,
	LP11,
	TRND,
	HS,
	LPDT,
	ESCP,
	ULPS,
	RSET,
	UDF1,
	UDF2,
	UDF3,
	UDF4,
	UDF5,
};

#endif
