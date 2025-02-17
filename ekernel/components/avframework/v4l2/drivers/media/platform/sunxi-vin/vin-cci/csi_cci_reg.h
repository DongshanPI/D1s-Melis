/*
 * ekernel/components/avframework/v4l2/platform/sunxi-vin/vin-cci/csi_cci_reg.h
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
 * csi_cci_reg.h
 *
 * Hawkview ISP - csi_cci_reg.h module
 *
 * Copyright (c) 2015 by Allwinnertech Co., Ltd.  http://www.allwinnertech.com
 *
 * Version          Author         Date        Description
 *
 *   3.0         Yang Feng     2015/12/02   ISP Tuning Tools Support
 *
 ******************************************************************************
 */

#ifndef __CSI__CCI__REG__H__
#define __CSI__CCI__REG__H__

#define MAX_CSIC_CCI_NUM 4
#define CCI_HCLK (24*1000*1000)
#define FIFO_DEPTH 64

#ifdef _OS
#define CCI_INLINE inline
#define csi_cci_udelay(x) udelay(x)
#else
#define CCI_INLINE
#define csi_cci_udelay(x) udelay(x)
#endif

enum cci_io_vol {
	LOW,
	HIGH,
};

enum cci_trans_mode {
	SINGLE,
	REPEAT,
};

enum cci_rs_mode {
	RESTART = 0,
	STOP_START = 1,
};

enum cci_rd_start {
	START_WITH_ID_W = 0,
	START_WITHOUT_ID_W = 1,
};

enum cci_src {
	FIFO = 0,
	DRAM = 1,
};

enum cci_packet_mode {
	COMPACT = 0,
	COMPLETE = 1,
};

enum cci_trig_src {
	NO_TRIG = 0,
	CSI0_TRIG = 2,
	CSI1_TRIG = 3,
};

enum cci_trig_con {
	TRIG_DEFAULT = 0,
	TRIG_HREF_FIRST = 0,
	TRIG_HREF_LAST = 1,
	TRIG_LN_CNT = 2,
};

struct cci_bus_fmt {
	enum cci_rs_mode rs_mode;
	enum cci_rd_start rs_start;
	unsigned char saddr_7bit;
	unsigned char wr_flag;
	unsigned char addr_len;
	unsigned char data_len;
};

struct cci_tx_buf {
	enum cci_src buf_src;
	enum cci_packet_mode pkt_mode;
	unsigned int pkt_cnt;
};

struct cci_tx_trig {
	enum cci_trig_src trig_src;
	enum cci_trig_con trig_con;
};

struct cci_int_status {
	_Bool complete;
	_Bool error;
};

enum cci_int_sel {
	CCI_INT_FINISH = 0X1,
	CCI_INT_ERROR = 0X2,
	CCI_INT_ALL = 0x3,
};

struct cci_line_status {
	enum cci_io_vol cci_sck;
	enum cci_io_vol cci_sda;
};

enum cci_bus_status {
	BUS_ERR = 0x00,
	START_TX = 0x08,
	RPT_START_TX = 0x10,
	ADDR_WR_TX_WI_ACK = 0x18,
	ADDR_WR_TX_WO_ACK = 0x20,
	DATA_TX_WI_ACK = 0x28,
	DATA_TX_WO_ACK = 0x30,
	ARBIT_LOST = 0x38,
	ADDR_RD_TX_WI_ACK = 0x40,
	ADDR_RD_TX_WO_ACK = 0x48,
	DATA_RX_WI_ACK = 0x50,
	DATA_RX_WO_ACK = 0x58,
	ACK_TIMEOUT = 0x01,
	NONE_DEFINED,
};

int csi_cci_set_base_addr(unsigned int sel, unsigned long addr);
void csi_cci_enable(unsigned int sel);
void csi_cci_disable(unsigned int sel);
void csi_cci_reset(unsigned int sel);
void csi_cci_set_clk_div(unsigned int sel, unsigned char *div_coef);
/*interval unit in 40 scl cycles*/
void csi_cci_set_pkt_interval(unsigned int sel, unsigned char interval);
/*timeout unit in scl cycle*/
void csi_cci_set_ack_timeout(unsigned int sel, unsigned char to_val);
/*trig delay unit in scl cycle*/
void csi_cci_set_trig_dly(unsigned int sel, unsigned int dly);
void csi_cci_trans_start(unsigned int sel, enum cci_trans_mode trans_mode);
unsigned int csi_cci_get_trans_done(unsigned int sel);
void csi_cci_set_bus_fmt(unsigned int sel, struct cci_bus_fmt *bus_fmt);
void csi_cci_set_tx_buf_mode(unsigned int sel,
			struct cci_tx_buf *tx_buf_mode);
void csi_cci_fifo_pt_reset(unsigned int sel);
void csi_cci_fifo_pt_add(unsigned int sel, unsigned int byte_cnt);
void csi_cci_fifo_pt_sub(unsigned int sel, unsigned int byte_cnt);
void csi_cci_wr_tx_buf(unsigned int sel, unsigned char *buf,
		       unsigned int byte_cnt);
void csi_cci_rd_tx_buf(unsigned int sel, unsigned char *buf,
		       unsigned int byte_cnt);
void csi_cci_set_trig_mode(unsigned int sel,
			struct cci_tx_trig *tx_trig_mode);
void csi_cci_set_trig_line_cnt(unsigned int sel, unsigned int line_cnt);
void cci_int_enable(unsigned int sel, enum cci_int_sel interrupt);
void cci_int_disable(unsigned int sel, enum cci_int_sel interrupt);
void CCI_INLINE cci_int_get_status(unsigned int sel,
					struct cci_int_status *status);
void CCI_INLINE cci_int_clear_status(unsigned int sel,
					  enum cci_int_sel interrupt);
enum cci_bus_status CCI_INLINE cci_get_bus_status(unsigned int sel);
void cci_get_line_status(unsigned int sel, struct cci_line_status *status);
void cci_pad_en(unsigned int sel);
void cci_stop(unsigned int sel);
void cci_sck_cycles(unsigned int sel, unsigned int cycle_times);
void cci_print_info(unsigned int sel);

#endif /*__CSI__CCI__REG__H__*/
