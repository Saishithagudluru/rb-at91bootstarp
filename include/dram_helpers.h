/*
 * Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __DRAM_HELPERS_H__
#define __DRAM_HELPERS_H__

#define WAIT_WHILE_COND(x, time)					\
{ 									\
	unsigned int timeout = (time);					\
	while ((x) && (timeout--));					\
									\
	if (timeout == 0xFFFFFFFF) {					\
		dbg_printf("Timed out while waiting for  " #x "\n");	\
		return -1;						\
	}								\
}

#define ROUNDUP(x, y)	((x) + (y) - 1)/(y)
#define ROUNDDWN(x, y)	((x) / (y))
/*
 * ns * 10^-9 (ns to seconds)  * CLOCK * 10^6 (beats/sec in Mhz, to seconds)
 * / 1000 = clock cycles
 * ps * 10^-12 (ps to seconds) * CLOCK * 10^6 (beats/sec in Mhz, to seconds)
 * /10^6 = clock cycles
 */
#define DDR_CLOCK_PERIOD	ROUNDDWN(1000000L, CONFIG_MEM_CLOCK)
/*
 * 1/ frequency = period.
 * CLOCK is in Mhz
 * 1/ (CLOCK * 10^6) = seconds. To obtain picoseconds, multiply by 10^12
 * 1 * 10 ^12 / (CLOCK * 10^6) = 10^6/ CLOCK (picoseconds)
 */

#define MAX(x, y)	((x) > (y) ? (x) : (y))
#define MIN(x, y)	((x) > (y) ? (y) : (x))

#define OFFSETOF(TYPE, ELEMENT) ((unsigned int)&(((TYPE *)0)->ELEMENT))
#define CTRL_RATIO		2

#if defined(CONFIG_DDR2)
#if defined(CONFIG_DDR_SET_BY_TIMING)
#define AL			0
#define WL			(CWL + AL)
#define BL			8
#define RL			(CL + AL)
#define TRCD			TRP
#endif
#if defined (CONFIG_DDR_EXT_TEMP_RANGE)
#define TREFI			3900000
#else
#define TREFI			7800000
#endif
#define TPRECKE			200000000
#define TPOSTCKE		400000
#define TRASMIN			45000
#define TRASMAX			70000000
#define TRTP			7500
#define TWR			15000
#define TMRD			2
#define TCCD			2
#define TCKE			3
#define TXSNR			(TRFC + 10000)
#define TXSRD			200
#define TAOND			2

#define T_RFC_MIN		ROUNDUP(ROUNDUP(TRFC, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_RFC_NOM_X1_X32	ROUNDDWN(ROUNDDWN(TREFI, 32 * DDR_CLOCK_PERIOD), CTRL_RATIO)
#define PRE_CKE_X1024		ROUNDUP(ROUNDUP(TPRECKE, 1024 * DDR_CLOCK_PERIOD), CTRL_RATIO) + 1
#define POST_CKE_X1024		2
#define DRAM_RSTN_X1024		0
#define PRE_OCD_X32		ROUNDUP(ROUNDUP(200, 32), CTRL_RATIO)
#define MIN_STABLE_CLOCK_X1	0
#define IDLE_AFTER_RESET_X32	0
#define WR			ROUNDUP(TWR, DDR_CLOCK_PERIOD)
#define MR_CL			CL
#define MR_WR			(WR - 1)
#define MR_BL			((BL == 8) ? 3 : 2)
#define MR_DLL_RESET		1
#define MR			(MR_WR << 9) | (MR_DLL_RESET << 8) | (MR_CL << 4) | (MR_BL << 0)
#define MR1_DIC			1
#define MR1_RTTNOM		1
#define EMR			(((MR1_RTTNOM & 0x2) >> 1) << 6) | (AL << 3) | (((MR1_RTTNOM & 0x1) >> 0) << 2) | (MR1_DIC << 1)
#if defined(CONFIG_DDR_EXT_TEMP_RANGE)
#define EMR2			(1 << 7)
#else
#define EMR2			(0 << 7)
#endif
#define EMR3			0
#define DEV_ZQINIT_X32		0
#define MAX_AUTO_INIT_X1024	0
#define T_RAS_MIN		ROUNDDWN(ROUNDUP(TRASMIN, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_RAS_MAX		ROUNDDWN((ROUNDDWN(TRASMAX, 1024 * DDR_CLOCK_PERIOD) - 1), CTRL_RATIO)
#define T_FAW			ROUNDUP(ROUNDUP(TFAW, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define WR2PRE			ROUNDDWN(WL + (BL / 2) + WR, CTRL_RATIO)
#define T_RC			ROUNDUP(ROUNDUP(TRC, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define RD2PRE			ROUNDDWN(AL + (BL / 2) + MAX(ROUNDUP(TRTP, DDR_CLOCK_PERIOD), 2)\
				- 2, CTRL_RATIO)
#define T_XP			ROUNDUP(TXP, CTRL_RATIO)
#define WR2RD			ROUNDUP(CWL + (BL / 2) + ROUNDUP(TWTR, DDR_CLOCK_PERIOD) ,CTRL_RATIO)
#define RD2WR			ROUNDUP(RL + (BL / 2) + 2 - WL, CTRL_RATIO)
#define READ_LATENCY		5
#define WRITE_LATENCY		3
#define T_MRD			ROUNDUP(TMRD, CTRL_RATIO)
#define T_MOD			0
#define T_MRW			0
#define T_RP			ROUNDDWN(ROUNDUP(TRP, DDR_CLOCK_PERIOD), CTRL_RATIO) + 1
#define T_RRD			ROUNDUP(ROUNDUP(TRRD, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_CCD			ROUNDUP(TCCD, CTRL_RATIO)
#define T_RCD			ROUNDUP(ROUNDUP(TRCD, DDR_CLOCK_PERIOD) - AL, CTRL_RATIO)
#define T_CKE			ROUNDUP(TCKE, CTRL_RATIO)
#define T_CKESR			T_CKE
#define T_CKSRE			ROUNDUP(1, CTRL_RATIO)
#define T_CKSRX			ROUNDUP(1, CTRL_RATIO)
#define T_CKCSX			0
#define T_CKDPDX		0
#define T_CKDPDE		0
#define T_CKPDX			0
#define T_CKPDE			0
#define T_XS_X32		ROUNDUP(ROUNDUP(TXSNR, 32 * DDR_CLOCK_PERIOD), CTRL_RATIO) + 1
#define T_XS_DLL_X32		ROUNDUP(ROUNDUP(TXSRD, 32), CTRL_RATIO) + 1
#define T_XSR			0
#define T_DPD			0
#define T_ZQ_SHORT_NOP		0
#define T_ZQ_LONG_NOP		0
#define T_ZQ_SHORT_INTERVAL_X1024	0
#define T_ZQ_RESET_NOP		0
#define WLTPHY			WL
#define RLTPHY			RL

#elif defined(CONFIG_DDR3)
#define BL			8
#define AL			0
#define RL			(CL + AL)
#define WL			(CWL + AL)
#define TRCD			TRP

#define TCKESR			(TCKE + DDR_CLOCK_PERIOD)
#if defined (CONFIG_DDR_EXT_TEMP_RANGE)
#define TREFI			3900000
#else
#define TREFI			7800000
#endif
#define TPRECKE			500000000
#define TXPR			MAX(5 * DDR_CLOCK_PERIOD, TRFC + 10000)
#define TPOSTCKE		TXPR
#define TRASMAX			(9 * TREFI)
#define TXPDLL			MAX(10 * DDR_CLOCK_PERIOD, 24000)
#define TXP			TXPDLL
#define TRTP			MAX(4 * DDR_CLOCK_PERIOD, 7500)
#define TWTR			MAX(4 * DDR_CLOCK_PERIOD, 7500)
#define TWR			15000
#define TMRD			4
#define TMOD			MAX(12 * DDR_CLOCK_PERIOD, 15000)
#define TCCD			4
#define TDLLK			512
#define TXS			MAX(5 * DDR_CLOCK_PERIOD, TRFC + 10000)
#define TXSDLL			TDLLK
#define TCKSRX			MAX(5 * DDR_CLOCK_PERIOD, 10000)
#define TCKSRE			MAX(5 * DDR_CLOCK_PERIOD, 10000)
#define TZQCS			MAX(64 * DDR_CLOCK_PERIOD, 80000)
#define TZQ_INTERVAL_LL		128000000000LL
/* ps ZQCS every 128ms in DDR3 spec chap 4.48.1 (must be longlong to avoid int overflow) */
#define TZQOPER			MAX(256 * DDR_CLOCK_PERIOD, 320000)
#define TZQINIT			MAX(512 * DDR_CLOCK_PERIOD, 640000)
#define RD_ODT_DELAY		(CL - CWL)
#define RD_ODT_HOLD		6
#define WR_ODT_DELAY		0
#define WR_ODT_HOLD		6

#define T_RFC_MIN		ROUNDUP(ROUNDUP(TRFC,DDR_CLOCK_PERIOD), 2)
#define T_RFC_NOM_X1_X32	ROUNDDWN(ROUNDDWN(TREFI, 32 * DDR_CLOCK_PERIOD), 2)
#define PRE_CKE_X1024		ROUNDUP(ROUNDUP(TPRECKE, 1024 * DDR_CLOCK_PERIOD), 2) + 1
#define POST_CKE_X1024		ROUNDUP(ROUNDUP(TPOSTCKE, 1024 * DDR_CLOCK_PERIOD), 2) + 1
#define DRAM_RSTN_X1024		ROUNDUP(ROUNDUP(200000000, 1024 * DDR_CLOCK_PERIOD), 2) + 1
#define PRE_OCD_X32		0
#define MIN_STABLE_CLOCK_X1	0
#define IDLE_AFTER_RESET_X32	0
#define WR			ROUNDUP(TWR, DDR_CLOCK_PERIOD)
#define MR_CL			((CL == 5) ? 2 : (CL == 6) ? 4 : (CL == 7) ? 6 :\
				(CL == 8) ? 8 : (CL == 9) ? 10 : (CL == 10) ? 12 :\
				(CL == 11) ? 14 : (CL == 12) ? 1 : (CL == 13) ? 3 :\
				(CL == 14) ? 5 : (CL == 15) ? 7 : 9)
#define MR_WR			((WR == 16) ? 0 : (WR <= 5) ? 1 : (WR == 6) ? 2 :\
				(WR == 7) ? 3 : (WR == 8) ? 4 : (WR == 10) ? 5 : (WR == 12) ? 6 : 7)
#define MR_BL			1
#define MR_DLL_RESET		1
#define MR			(MR_WR << 9) |\
				(MR_DLL_RESET << 8) |\
				(((MR_CL & 0xE) >> 1) << 4) |\
				(((MR_CL & 0x1) >> 0) << 2) |\
				(MR_BL << 0)
#define MR1_DIC			0
#define MR1_RTTNOM		1
#define EMR			(((MR1_RTTNOM & 0x4) >> 2) << 9) |\
				(((MR1_RTTNOM & 0x2) >> 1) << 6) |\
				(((MR1_DIC & 0x2) >> 1) << 5) |\
				(AL << 3) |\
				(((MR1_RTTNOM & 0x1) >> 0) << 2) |\
				(((MR1_DIC & 0x1) >> 0) << 1)
#if defined(CONFIG_DDR_EXT_TEMP_RANGE)
#define EMR2			((DDR3_HIGH_TEMP_SUPPORT << 6)|\
				((CWL - 5) << 3)) 
#else
#define EMR2			((CWL - 5) << 3)
#endif
/* Dynamic ODT : disabled, useless with only one rank, ASR enabled if hi temp supported */
#define EMR3			0
#define DEV_ZQINIT_X32		ROUNDUP(ROUNDUP(TZQINIT, 32 * DDR_CLOCK_PERIOD), CTRL_RATIO) + 1
#define MAX_AUTO_INIT_X1024	0
#define T_RAS_MIN		ROUNDDWN(ROUNDUP (TRASMIN, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_RAS_MAX		ROUNDDWN((ROUNDDWN(TRASMAX, 1024 * DDR_CLOCK_PERIOD) - 1), CTRL_RATIO)
#define T_FAW			ROUNDUP(ROUNDUP(TFAW, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define WR2PRE			ROUNDDWN(WL + (BL / 2) + WR, CTRL_RATIO) /* WL+BL/2+T_WR */
#define T_RC			ROUNDUP(ROUNDUP(TRC, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define RD2PRE			ROUNDDWN(AL + MAX(ROUNDUP(TRTP, DDR_CLOCK_PERIOD), 4), CTRL_RATIO)
/* AL+max(tRTP,4)*/
#define T_XP			ROUNDUP(ROUNDUP(TXP, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define WR2RD			ROUNDUP(CWL + (BL / 2) + ROUNDUP(TWTR, DDR_CLOCK_PERIOD), CTRL_RATIO)
/* CWL + BL/2 + tWTR */
#define RD2WR			ROUNDUP(RL + (BL / 2) + 2 - WL, CTRL_RATIO)
/* RL + BL/2 + 2 - WL */
#define READ_LATENCY		5
#define WRITE_LATENCY		3
#define T_MRD			ROUNDUP(TMRD, CTRL_RATIO)
#define T_MOD			ROUNDUP(ROUNDUP(TMOD, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_MRW			0
#define T_RP			ROUNDDWN(ROUNDUP(TRP, DDR_CLOCK_PERIOD), CTRL_RATIO) + 1
#define T_RRD			ROUNDUP(ROUNDUP(TRRD, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_CCD			ROUNDUP(TCCD, CTRL_RATIO)
#define T_RCD			ROUNDUP(ROUNDUP(TRCD, DDR_CLOCK_PERIOD) - AL, CTRL_RATIO)
#define T_CKE			ROUNDUP(ROUNDUP(TCKE, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_CKESR			ROUNDUP(ROUNDUP(TCKESR, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_CKSRE			ROUNDUP(ROUNDUP(TCKSRE, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_CKSRX			ROUNDUP(ROUNDUP(TCKSRX, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_CKCSX			0
#define T_CKDPDX		0
#define T_CKDPDE		0
#define T_CKPDX			0
#define T_CKPDE			0
#define T_XS_X32		ROUNDUP(ROUNDUP(TXS, 32 * DDR_CLOCK_PERIOD), CTRL_RATIO) + 1
#define T_XS_DLL_X32		ROUNDUP(ROUNDUP(TXSDLL, 32), CTRL_RATIO) + 1
#define T_XSR			0
#define T_DPD			0
#define T_ZQ_SHORT_NOP		ROUNDUP(ROUNDUP(TZQCS, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_ZQ_LONG_NOP		ROUNDUP(ROUNDUP(TZQOPER, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_ZQ_SHORT_INTERVAL_X1024	(unsigned int)(ROUNDUP(ROUNDUP(TZQ_INTERVAL_LL,\
					1024 * DDR_CLOCK_PERIOD), CTRL_RATIO) + 1)
#define T_ZQ_RESET_NOP		0
#define WLTPHY			WL
#define RLTPHY			RL

#elif defined(CONFIG_LPDDR2)
#define BL			8
#define TXP			MAX(7500, 2 * DDR_CLOCK_PERIOD)
#define TRCD			MAX(24000, 3 * DDR_CLOCK_PERIOD)
#define TRASMIN			MAX(42000, 3 * DDR_CLOCK_PERIOD)
#define TRASMAX			70000000
#define TRPpb			MAX(24000, 3 * DDR_CLOCK_PERIOD)
#if (NB_BANK_BITS == 3)
#define TRPab			MAX(27000, 3 * DDR_CLOCK_PERIOD)
#else
#define TRPab			MAX(24000, 3 * DDR_CLOCK_PERIOD)
#endif
#define TRCpb			(TRASMIN + TRPpb)
#define TRCab			(TRASMIN + TRPab)
#define TRTP			MAX(7500, 2 * DDR_CLOCK_PERIOD)
#define TWR			MAX(15000, 3 * DDR_CLOCK_PERIOD)
#define TRRD			MAX(10000, 2 * DDR_CLOCK_PERIOD)
#define TMRW			5
#define TCKE			3
#define TCKESR			MAX(15000, 3 * DDR_CLOCK_PERIOD)
#define TXSR			MAX(TRFCab + 10000, 2 * DDR_CLOCK_PERIOD)
#define TDPD			500000000
#define TDQSCK_MIN		2500
#define TZQCS			90000
#define TZQCL			360000
#define TZQRESET		MAX(50000, 3 * DDR_CLOCK_PERIOD)
#define TZQ_INTERVAL_LL		400000000000LL
#define TINIT1			100000
#define TINIT2			5
#define TINIT3			200000000
#define TINIT4			1000000
#define TINIT5			10000000
#define TZQINIT			1000000
#ifdef RTL_SIMU
#define TTSI_LL			2000000
#else
#define TTSI_LL			167000000000LL
#endif

#define DRIVER_IMPEDANCE	40
#define T_RFC_MIN		ROUNDUP(ROUNDUP(TRFCab, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_RFC_NOM_X1_X32	ROUNDDWN(ROUNDDWN(TREFI, 32 * DDR_CLOCK_PERIOD), CTRL_RATIO)
#define PRE_CKE_X1024		ROUNDUP(ROUNDUP(TINIT1, 1024 * DDR_CLOCK_PERIOD), CTRL_RATIO) + 1
#define POST_CKE_X1024		ROUNDUP(ROUNDUP(TINIT3, 1024 * DDR_CLOCK_PERIOD), CTRL_RATIO) + 1
#define DRAM_RSTN_X1024		0
#define PRE_OCD_X32		0
#define MIN_STABLE_CLOCK_X1	ROUNDUP(TINIT2, CTRL_RATIO)
#define IDLE_AFTER_RESET_X32	ROUNDUP(ROUNDUP(TINIT4, 32 * DDR_CLOCK_PERIOD), CTRL_RATIO) + 1
#define WR			ROUNDUP(TWR, DDR_CLOCK_PERIOD)
#define MR1_BL			((BL == 16) ? 4 : (BL == 8) ? 3 : 2)
#define MR1_nWR			(WR - 2)
#define MR			(MR1_nWR << 5) | (MR1_BL << 0)
#define MR2_RLWL		(RL - 2)
#define EMR			(MR2_RLWL << 0)
#define MR3_DS			((DRIVER_IMPEDANCE == 34) ? 1 : (DRIVER_IMPEDANCE == 40) ? 2 :\
				(DRIVER_IMPEDANCE == 48) ? 3 : (DRIVER_IMPEDANCE == 60) ? 4 :\
				(DRIVER_IMPEDANCE == 80) ? 6 : 7)
#define EMR2			(MR3_DS << 0)
#define EMR3			0
#define DEV_ZQINIT_X32		ROUNDUP(ROUNDUP(TZQINIT, 32 * DDR_CLOCK_PERIOD), CTRL_RATIO) + 1
#define MAX_AUTO_INIT_X1024	ROUNDUP(ROUNDUP(TINIT5, 1024 * DDR_CLOCK_PERIOD), CTRL_RATIO) + 1
#define T_RAS_MIN		ROUNDDWN(ROUNDUP(TRASMIN, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_RAS_MAX		ROUNDDWN((ROUNDDWN(TRASMAX, 1024 * DDR_CLOCK_PERIOD) - 1), CTRL_RATIO)
#define T_FAW			ROUNDUP(ROUNDUP(TFAW, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define WR2PRE			ROUNDDWN(WL + (BL / 2) + WR + 1, CTRL_RATIO)
#define T_RC			ROUNDUP(ROUNDUP(TRCab, DDR_CLOCK_PERIOD), CTRL_RATIO)
#if defined(CONFIG_LPDDR2_S4)
#define RD2PRE			ROUNDDWN((BL / 2) + MAX(ROUNDUP(TRTP, DDR_CLOCK_PERIOD), 2) - 2, CTRL_RATIO)
#else
#define RD2PRE			ROUNDDWN((BL / 2) + ROUNDUP(TRTP, DDR_CLOCK_PERIOD) - 1, CTRL_RATIO)
#endif
#define T_XP			ROUNDUP(ROUNDUP(TXP, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define WR2RD			ROUNDUP(WL + (BL / 2) + ROUNDUP(TWTR, DDR_CLOCK_PERIOD) + 1, CTRL_RATIO)
#define RD2WR			ROUNDUP(RL + (BL / 2) + ROUNDUP(TDQSCK_MAX, DDR_CLOCK_PERIOD) + 1 - WL, CTRL_RATIO)
#define READ_LATENCY		ROUNDUP(RL, CTRL_RATIO)
#define WRITE_LATENCY		ROUNDUP(WL, CTRL_RATIO)
#define T_MRD			0
#define T_MOD			0
#define T_MRW			ROUNDUP(TMRW, CTRL_RATIO)
#define T_RP			ROUNDDWN(ROUNDUP(TRPab, DDR_CLOCK_PERIOD), CTRL_RATIO) + 1
#define T_RRD			ROUNDUP(ROUNDUP(TRRD, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_CCD			ROUNDUP(TCCD, CTRL_RATIO)
#define T_RCD			ROUNDUP(ROUNDUP(TRCD, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_CKE			ROUNDUP(MAX(TCKE, ROUNDUP(TCKESR, DDR_CLOCK_PERIOD)), CTRL_RATIO)
#define T_CKESR			ROUNDUP(ROUNDUP(TCKESR, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_CKSRE			ROUNDUP(2, CTRL_RATIO)
#define T_CKSRX			ROUNDUP(2, CTRL_RATIO)
#define T_CKCSX			ROUNDUP(ROUNDUP(TXP, DDR_CLOCK_PERIOD) + 2, CTRL_RATIO)
#define T_CKDPDX		ROUNDUP(2, CTRL_RATIO)
#define T_CKDPDE		ROUNDUP(2, CTRL_RATIO)
#define T_CKPDX			ROUNDUP(2, CTRL_RATIO)
#define T_CKPDE			ROUNDUP(2, CTRL_RATIO)
#define T_XS_X32		0
#define T_XS_DLL_X32		0
#define T_XSR			ROUNDUP(ROUNDUP(TXSR, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_DPD			ROUNDUP(ROUNDUP(TDPD, 4096 * DDR_CLOCK_PERIOD), CTRL_RATIO) + 1
#define T_ZQ_SHORT_NOP		ROUNDUP(ROUNDUP(TZQCS, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_ZQ_LONG_NOP		ROUNDUP(ROUNDUP(TZQCL, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_ZQ_SHORT_INTERVAL_X1024	\
				(unsigned int)(ROUNDUP(ROUNDUP(TZQ_INTERVAL_LL, 1024 * DDR_CLOCK_PERIOD),\
				CTRL_RATIO) + 1)
#define T_ZQ_RESET_NOP		ROUNDUP(ROUNDUP(TZQRESET, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_TSI			(unsigned int)(ROUNDUP(ROUNDUP(TTSI_LL, DDR_CLOCK_PERIOD), CTRL_RATIO))

/* ODT pin not used in LPDDR2 */
#define RD_ODT_DELAY		0
#define RD_ODT_HOLD		0
#define WR_ODT_DELAY		0
#define WR_ODT_HOLD		0
#define WLTPHY			(WL + 1)
#define RLTPHY			(RL + ROUNDDWN(TDQSCK_MIN, DDR_CLOCK_PERIOD))

#elif defined(CONFIG_LPDDR3)
#define DRIVER_IMPEDANCE	40
#define BL			8
#define TXP			MAX(7500, 3 * DDR_CLOCK_PERIOD)
#define TRCD			MAX(24000, 3 * DDR_CLOCK_PERIOD)
#define TFAW			MAX(50000, 8 * DDR_CLOCK_PERIOD)
#define TRASMIN			MAX(42000, 3 * DDR_CLOCK_PERIOD)
#define RM			1
#define TRASMAX			MIN(70200000, 9 * RM * TREFI)
#define TRPpb			MAX(24000, 3 * DDR_CLOCK_PERIOD)
#define TRPab			MAX(27000, 3 * DDR_CLOCK_PERIOD)
#define TRCpb			(TRASMIN + TRPpb)
#define TRCab			(TRASMIN + TRPab)
#define TRTP			MAX(7500, 4 * DDR_CLOCK_PERIOD)
#define TWR			MAX(15000, 4 * DDR_CLOCK_PERIOD)
#define TWTR			MAX(7500, 4 * DDR_CLOCK_PERIOD)
#define TMRD			MAX(14000, 10 * DDR_CLOCK_PERIOD)
#define TMRW			10
#define TRRD			MAX(10000, 2 * DDR_CLOCK_PERIOD)
#define TCCD			4
#define TCKE			MAX(7500, 3 * DDR_CLOCK_PERIOD)
#define TCKESR			MAX(15000, 3 * DDR_CLOCK_PERIOD)
#define TXSR			MAX(TRFCab + 10000, 2 * DDR_CLOCK_PERIOD)
#define TDPD			500000000
#define TDQSCK_MIN		2500
#if defined (CONFIG_DDR_EXT_TEMP_RANGE)
#define TDQSCK_MAX		5620
#else
#define TDQSCK_MAX		5500
#endif
#define TZQCS			90000
#define TZQCL			360000
#define TZQRESET		MAX(50000, 3 * DDR_CLOCK_PERIOD)
#define TZQ_INTERVAL_LL		400000000000LL
/* ps ZQCS every 0.4s in LPDDR3 spec chapter 4.11.2 (must be longlong to avoid int overflow) */
#define TINIT1			100000
#define TINIT2			5
#define TINIT3			200000000
#define TINIT4			1000000
#define TINIT5			10000000
#define TZQINIT			1000000
#ifdef RTL_SIMU
#define TTSI_LL			2000000 
/* ps  Every 2us, To check MR4 polling in simulation */
#else
#define TTSI_LL			167000000000LL 
/* ps  Every 167ms (must be longlong to avoid int overflow) */
#endif
#define TODTON_MAX		3500

#define T_RFC_MIN		ROUNDUP(ROUNDUP(TRFCab, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_RFC_NOM_X1_X32	ROUNDDWN(ROUNDDWN(TREFI, 32 * DDR_CLOCK_PERIOD), CTRL_RATIO)
#define PRE_CKE_X1024		ROUNDUP(ROUNDUP(TINIT1, 1024 * DDR_CLOCK_PERIOD), CTRL_RATIO) + 1
#define POST_CKE_X1024		ROUNDUP(ROUNDUP(TINIT3 ,1024 * DDR_CLOCK_PERIOD), CTRL_RATIO) + 1
#define DRAM_RSTN_X1024		0
#define PRE_OCD_X32		0
#define MIN_STABLE_CLOCK_X1	ROUNDUP(TINIT2, CTRL_RATIO)
#define IDLE_AFTER_RESET_X32	ROUNDUP(ROUNDUP(TINIT4, 32 * DDR_CLOCK_PERIOD), CTRL_RATIO) + 1
#define WR			ROUNDUP(TWR,DDR_CLOCK_PERIOD)
#define WR_SEL			((WR <= 3) ? 3 : ((WR <= 6) ? 6 : ((WR <= 8) ? 8 : 9)))
#define MR1_BL			3
#define MR1_nWR			(WR_SEL - 2)
#define MR			(MR1_nWR << 5) | (MR1_BL << 0)
#define MR2_RLWL		(RL - 2)
#define EMR			(MR2_RLWL << 0)
#define MR3_DS			((DRIVER_IMPEDANCE == 34) ? 1 : (DRIVER_IMPEDANCE == 40) ? 2 : 3)
#define EMR2			(MR3_DS << 0)
#define EMR3			0
#define DEV_ZQINIT_X32		ROUNDUP(ROUNDUP(TZQINIT, 32 * DDR_CLOCK_PERIOD), CTRL_RATIO) + 1
#define MAX_AUTO_INIT_X1024	ROUNDUP(ROUNDUP(TINIT5, 1024 * DDR_CLOCK_PERIOD), CTRL_RATIO) + 1
#define T_RAS_MIN		ROUNDDWN(ROUNDUP(TRASMIN, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_RAS_MAX		ROUNDDWN((ROUNDDWN(TRASMAX, 1024 * DDR_CLOCK_PERIOD) - 1), CTRL_RATIO)
#define T_FAW			ROUNDUP(ROUNDUP(TFAW, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define WR2PRE			ROUNDDWN(WL + (BL / 2) + WR_SEL + 1, CTRL_RATIO)
#define T_RC			ROUNDUP(ROUNDUP(TRCab, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define RD2PRE			ROUNDDWN((BL / 2) + MAX(ROUNDUP(TRTP, DDR_CLOCK_PERIOD), 4) - 4, CTRL_RATIO)
#define T_XP			ROUNDUP(ROUNDUP(TXP, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define WR2RD			ROUNDUP(WL + (BL / 2) + ROUNDUP(TWTR, DDR_CLOCK_PERIOD) + 1, CTRL_RATIO)
#define RD2WR			ROUNDUP(RL + (BL / 2) + \
				ROUNDUP(TDQSCK_MAX, DDR_CLOCK_PERIOD) + 1 - WL, CTRL_RATIO)
				/* RL + BL/2 + RU(tDQSCKmax/tCK) + 1 - WL */
#define READ_LATENCY		ROUNDUP(RL, CTRL_RATIO)
#define WRITE_LATENCY		ROUNDUP(WL, CTRL_RATIO)
#define T_MRD			ROUNDUP(ROUNDUP(TMRD, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_MOD			0
#define T_MRW			ROUNDUP(TMRW, CTRL_RATIO)
#define T_RP			ROUNDDWN(ROUNDUP(TRPab, DDR_CLOCK_PERIOD), CTRL_RATIO) + 1
#define T_RRD			ROUNDUP(ROUNDUP(TRRD, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_CCD			ROUNDUP(TCCD, CTRL_RATIO)
#define T_RCD			ROUNDUP(ROUNDUP(TRCD, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_CKE			ROUNDUP(MAX(TCKE, ROUNDUP(TCKESR, DDR_CLOCK_PERIOD)), CTRL_RATIO)
#define T_CKESR			ROUNDUP(ROUNDUP(TCKESR, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_CKSRE			ROUNDUP(2, CTRL_RATIO)
#define T_CKSRX			ROUNDUP(2, CTRL_RATIO)
#define T_CKCSX			ROUNDUP(ROUNDUP(TXP, DDR_CLOCK_PERIOD) + 2, CTRL_RATIO)
#define T_CKDPDX		ROUNDUP(2, CTRL_RATIO)
#define T_CKDPDE		ROUNDUP(2, CTRL_RATIO)
#define T_CKPDX			ROUNDUP(2, CTRL_RATIO)
#define T_CKPDE			ROUNDUP(2, CTRL_RATIO)
#define T_XS_X32		0
#define T_XS_DLL_X32		0
#define T_XSR			ROUNDUP(ROUNDUP(TXSR, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_DPD			ROUNDUP(ROUNDUP(TDPD, 4096 * DDR_CLOCK_PERIOD), CTRL_RATIO) + 1
#define T_ZQ_SHORT_NOP		ROUNDUP(ROUNDUP(TZQCS, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_ZQ_LONG_NOP		ROUNDUP(ROUNDUP(TZQCL, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_ZQ_SHORT_INTERVAL_X1024	(unsigned int)(ROUNDUP(ROUNDUP(TZQ_INTERVAL_LL, 1024 *\
					DDR_CLOCK_PERIOD), CTRL_RATIO) + 1)
#define T_ZQ_RESET_NOP		ROUNDUP(ROUNDUP(TZQRESET, DDR_CLOCK_PERIOD), CTRL_RATIO)
#define T_TSI			(unsigned int)(ROUNDUP(ROUNDUP(TTSI_LL, DDR_CLOCK_PERIOD), CTRL_RATIO))
#define RD_ODT_DELAY		(ROUNDDWN(TDQSCK_MIN, DDR_CLOCK_PERIOD) - 1 -\
				ROUNDUP(TODTON_MAX, DDR_CLOCK_PERIOD))
#define RD_ODT_HOLD		(5 + ROUNDUP(TDQSCK_MAX, DDR_CLOCK_PERIOD) -\
 				ROUNDDWN(TDQSCK_MIN, DDR_CLOCK_PERIOD) + \
				ROUNDUP(TODTON_MAX, DDR_CLOCK_PERIOD))
#define WR_ODT_DELAY		(WL - 1 - ROUNDUP(TODTON_MAX, DDR_CLOCK_PERIOD))
#define WR_ODT_HOLD		(7 + ROUNDUP(TODTON_MAX, DDR_CLOCK_PERIOD))
#define WLTPHY			(WL+1)
#define RLTPHY			(RL + ROUNDDWN(TDQSCK_MIN,DDR_CLOCK_PERIOD))
#endif
#endif /* Endif of __DRAM_HELPERS_H__ */










