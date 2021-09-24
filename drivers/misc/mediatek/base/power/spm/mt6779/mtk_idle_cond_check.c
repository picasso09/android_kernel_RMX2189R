// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2017 MediaTek Inc.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/spinlock.h>

#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/io.h>

#include <trace/events/mtk_idle_event.h>

#include <mtk_idle.h> /* IDLE_TYPE_xxx */
#include <mtk_idle_internal.h>

#include "mtk_spm_internal.h"
#include "mtk_spm_resource_req.h"

/***********************************************************
 * Local definitions
 ***********************************************************/

static void __iomem *infrasys_base;    /* INFRA_REG, INFRA_SW_CG_x_STA */
static void __iomem *mmsys_base;       /* MM_REG, DISP_CG_CON_x */
static void __iomem *imgsys_base;      /* IMGSYS_REG, IMG_CG_CON */
static void __iomem *mfgsys_base;      /* MFGSYS_REG, MFG_CG_CON */
static void __iomem *vencsys_base;     /* VENCSYS_REG, VENCSYS_CG_CON */
static void __iomem *sleepsys_base;    /* SPM_REG */
static void __iomem *topck_base;       /* TOPCK_REG */
static void __iomem *apmixedsys_base;  /* APMIXEDSYS */

#define idle_readl(addr)    __raw_readl(addr)

#define INFRA_REG(ofs)      (infrasys_base + ofs)
#define MM_REG(ofs)         (mmsys_base + ofs)
#define IMGSYS_REG(ofs)     (imgsys_base + ofs)
#define MFGSYS_REG(ofs)     (mfgsys_base + ofs)
#define VENCSYS_REG(ofs)    (vencsys_base + ofs)
#define SPM_REG(ofs)        (sleepsys_base + ofs)
#define TOPCK_REG(ofs)      (topck_base + ofs)
#define APMIXEDSYS(ofs)     (apmixedsys_base + ofs)

#undef SPM_PWR_STATUS
#define SPM_PWR_STATUS      SPM_REG(0x0160)
#undef SPM_PWR_STATUS_2ND
#define SPM_PWR_STATUS_2ND  SPM_REG(0x0164)
#define SPM_ULPOSC_CON      SPM_REG(0x0440)
#define	INFRA_SW_CG_0_STA   INFRA_REG(0x0094)
#define	INFRA_SW_CG_1_STA   INFRA_REG(0x0090)
#define	INFRA_SW_CG_2_STA   INFRA_REG(0x00AC)
#define	INFRA_SW_CG_3_STA   INFRA_REG(0x00C8)
#define DISP_CG_CON_0       MM_REG(0x100)
#define DISP_CG_CON_1       MM_REG(0x110)

/* SPM_PWR_STATUS bit definition */
#define PWRSTA_BIT_MD       (1U << 0)
#define PWRSTA_BIT_CONN     (1U << 1)
#define PWRSTA_BIT_DISP     (1U << 3)
#define PWRSTA_BIT_MFG      (1U << 4)
#define PWRSTA_BIT_INFRA    (1U << 6)
#define PWRSTA_BIT_ALL		(0xffffffff)

/***********************************************************
 * Functions for external modules
 ***********************************************************/

/***********************************************************
 * Check clkmux registers
 ***********************************************************/
#define NF_CLKMUX_COND_SET          9 /* NF_CLKMUX_PASS_CRITERIA + 1 */
#define CLK_CFG(id) TOPCK_REG((id != (CLKMUX_MEM/4) ? 0x20+id*0x10 : 0x640))
#define IDLE_VCORE_CHECK_FOR_LP_MODE        0
#define IDLE_VCORE_FORCE_LP_MODE            1
#define IDLE_VCORE_FORCE_NORMAL_MODE        2
#define IDLE_VCORE_BYPASS_CHECK_FOR_LP_MODE 3

static int idle_force_vcore_lp_mode = IDLE_VCORE_CHECK_FOR_LP_MODE;
static bool clkmux_cond[NR_TYPES];
static unsigned int clkmux_block_mask[NR_TYPES][NF_CLK_CFG];
/* FIX ME*/

static bool check_clkmux_pdn(unsigned int clkmux_id)
{
	unsigned int reg, val, idx;

	if (clkmux_id & CLK_CHECK) {
		clkmux_id = (clkmux_id & ~CLK_CHECK);
		reg = clkmux_id / 4;
		val = idle_readl(CLK_CFG(reg));
		idx = clkmux_id % 4;
		val = (val >> (idx * 8)) & 0x80;
		return val ? true : false;
	}

	return false;
}

/***********************************************************
 * Check cg idle condition for dp/sodi/sodi3
 ***********************************************************/
/* Local definitions */
struct idle_cond_info {
	/* check SPM_PWR_STATUS for bit definition */
	unsigned int    subsys_mask;
	/* cg name */
	const char      *name;
	/* cg address */
	void __iomem    *addr;
	/* bitflip value from *addr ? */
	bool            bBitflip;
	/* check clkmux if bit 31 = 1, id is bit[30:0] */
	unsigned int    clkmux_id;
};

/* NOTE: null address will be updated in mtk_idle_cond_check_init() */
static struct idle_cond_info idle_cg_info[] = {
	{ PWRSTA_BIT_ALL, "MTCMOS1", NULL, false, 0 },
	{ PWRSTA_BIT_ALL, "MTCMOS2", NULL, false, 0 },
	{ PWRSTA_BIT_INFRA, "INFRA0 ", NULL, true,  0 },
	{ PWRSTA_BIT_INFRA, "INFRA1 ", NULL, true,  0 },
	{ PWRSTA_BIT_INFRA, "INFRA2 ", NULL, true,  0 },
	{ PWRSTA_BIT_INFRA, "INFRA3 ", NULL, true,  0 },
	{ PWRSTA_BIT_DISP, "MMSYS0 ", NULL, true,  (CLKMUX_MM | CLK_CHECK) },
	{ PWRSTA_BIT_DISP, "MMSYS1 ", NULL, true,  (CLKMUX_MM | CLK_CHECK) },
};

#define NR_CG_GRPS \
	(sizeof(idle_cg_info)/sizeof(struct idle_cond_info))

static bool spm_resource_arch;
static unsigned int *idle_pll_cond_mask;
static unsigned int *idle_pll_block_mask;

/* scenario-oriented */
static unsigned int idle_cond_mask_scenario
	[NR_IDLE_TYPES][NR_CG_GRPS] = {
	[IDLE_TYPE_DP] = {
		0xBE7000B8,	/* MTCMOS1 */
		0xBE7000B8,	/* MTCMOS2 */
		0x08040816,	/* INFRA0  */
		0x03AFB900,	/* INFRA1  */
#ifdef OPLUS_BUG_STABILITY
		/* Yongzhi.Zhang@MULTIMEDIA.AUDIODRIVER.PLATFORM.1910014, 2019/04/01,
		 * modify to cancel low power mode for P90 SPI5 transfer-timeout issue */
		0x040000C5,	/* INFRA2  */
#else /* OPLUS_BUG_STABILITY */
		0x000000C5,	/* INFRA2  */
#endif /* OPLUS_BUG_STABILITY */
		0x00000000,	/* INFRA3  */
		0xFFFFFFFF,	/* MMSYS0  */
		0x0001FFFF,	/* MMSYS1  */
	},
	[IDLE_TYPE_SO3] = {
		0xBE7000B0,	/* MTCMOS1 */
		0xBE7000B0,	/* MTCMOS2 */
		0x08040816,	/* INFRA0  */
		0x03AFB900,	/* INFRA1  */
#ifdef OPLUS_BUG_STABILITY
		/* Yongzhi.Zhang@MULTIMEDIA.AUDIODRIVER.PLATFORM.1910014, 2019/04/01,
		 * modify to cancel low power mode for P90 SPI5 transfer-timeout issue */
		0x040000D1,	/* INFRA2  */
#else /* OPLUS_BUG_STABILITY */
		0x000000D1,	/* INFRA2  */
#endif /* OPLUS_BUG_STABILITY */
		0x08000000,	/* INFRA3  */
		0xFFFFFFFF,	/* MMSYS0  */
		0x0001FFFF,	/* MMSYS1  */
	},
	[IDLE_TYPE_SO] = {
		0xBE7000B0,	/* MTCMOS1 */
		0xBE7000B0,	/* MTCMOS2 */
		0x08040816,	/* INFRA0  */
		0x03AFB900,	/* INFRA1  */
#ifdef OPLUS_BUG_STABILITY
		/* Yongzhi.Zhang@MULTIMEDIA.AUDIODRIVER.PLATFORM.1910014, 2019/04/01,
		 * modify to cancel low power mode for P90 SPI5 transfer-timeout issue */
		0x040000C1,	/* INFRA2  */
#else /* OPLUS_BUG_STABILITY */
		0x000000C1,	/* INFRA2  */
#endif /* OPLUS_BUG_STABILITY */
		0x00000000,	/* INFRA3  */
		0x000DFC00,	/* MMSYS0  */
		0x00003F7C,	/* MMSYS1  */
	},
	[IDLE_TYPE_RG] = {
		0, 0, 0, 0, 0, 0, 0, 0},
};

/* resource-oriented */
static unsigned int idle_cond_mask_resource
	[NR_SPM_RES_LEVEL_TYPES][NR_CG_GRPS] = {
	[SPM_RES_LEVEL_DRAM] = {
		0xBE7000B0,	/* MTCMOS1 */
		0xBE7000B0,	/* MTCMOS2 */
		0x08040816,	/* INFRA0  */
		0x03AFB900,	/* INFRA1  */
#ifdef OPLUS_BUG_STABILITY
		/* Yongzhi.Zhang@MULTIMEDIA.AUDIODRIVER.PLATFORM.1910014, 2019/04/01,
		 * modify to cancel low power mode for P90 SPI5 transfer-timeout issue */
		0x040000C1,	/* INFRA2  */
#else /* OPLUS_BUG_STABILITY */
		0x000000C1,	/* INFRA2  */
#endif /* OPLUS_BUG_STABILITY */
		0x00000000,	/* INFRA3  */
		0x01023000,	/* MMSYS0  */
		0x00000000,	/* MMSYS1  */
	},
	[SPM_RES_LEVEL_SYSPLL] = {
		0xBE7000B0,	/* MTCMOS1 */
		0xBE7000B0,	/* MTCMOS1 */
		0x08040816,	/* INFRA0  */
		0x03AFB900,	/* INFRA1  */
#ifdef OPLUS_BUG_STABILITY
		/* Yongzhi.Zhang@MULTIMEDIA.AUDIODRIVER.PLATFORM.1910014, 2019/04/01,
		 * modify to cancel low power mode for P90 SPI5 transfer-timeout issue */
		0x040000C1,	/* INFRA2  */
#else /* OPLUS_BUG_STABILITY */
		0x000000C1,	/* INFRA2  */
#endif /* OPLUS_BUG_STABILITY */
		0x00000000,	/* INFRA3  */
		0x03F63000,	/* MMSYS0  */
		0x00000000,	/* MMSYS1  */
	},
	[SPM_RES_LEVEL_BUS_26M] = {
		0xBE7000B0,	/* MTCMOS1 */
		0xBE7000B0,	/* MTCMOS1 */
		0x08040816,	/* INFRA0  */
		0x03AFB900,	/* INFRA1  */
#ifdef OPLUS_BUG_STABILITY
		/* Yongzhi.Zhang@MULTIMEDIA.AUDIODRIVER.PLATFORM.1910014, 2019/04/01,
		 * modify to cancel low power mode for P90 SPI5 transfer-timeout issue */
		0x040000D1,	/* INFRA2  */
#else /* OPLUS_BUG_STABILITY */
		0x000000D1,	/* INFRA2  */
#endif /* OPLUS_BUG_STABILITY */
		0x08000000,	/* INFRA3  */
		0x00000000,	/* MMSYS0  */
		0x00000000,	/* MMSYS1  */
	},
	[SPM_RES_LEVEL_PMIC_LP] = {
		0, 0, 0, 0, 0, 0, 0, 0},
};

static unsigned int idle_block_mask_scenario
			[NR_IDLE_TYPES][NR_CG_GRPS+1];
static unsigned int idle_block_mask_resource
			[NR_SPM_RES_LEVEL_TYPES][NR_CG_GRPS+1];
static unsigned int idle_value[NR_CG_GRPS];

/* FIX ME*/
/***********************************************************
 * Check pll idle condition
 ***********************************************************/

#define PLL_UNIVPLL APMIXEDSYS(0x240)
#define PLL_MFGPLL  APMIXEDSYS(0x250)
#define PLL_MSDCPLL APMIXEDSYS(0x260)
#define PLL_TVDPLL  APMIXEDSYS(0x270)
#define PLL_MMPLL   APMIXEDSYS(0x280)

#define PLL_BIT_UNIVPLL (1 << 0)
#define PLL_BIT_MFGPLL  (1 << 1)
#define PLL_BIT_MSDCPLL (1 << 2)
#define PLL_BIT_TVDPLL  (1 << 3)
#define PLL_BIT_MMPLL   (1 << 4)

/* scenario-oriented */
static unsigned int idle_pll_cond_mask_scenario[NR_IDLE_TYPES] = {
	[IDLE_TYPE_DP] = 0,
	[IDLE_TYPE_SO3] = PLL_BIT_UNIVPLL | PLL_BIT_MFGPLL |
			  PLL_BIT_MSDCPLL | PLL_BIT_TVDPLL |
			  PLL_BIT_MMPLL,
	[IDLE_TYPE_SO] = 0,
	};
static unsigned int idle_pll_block_mask_scenario[NR_IDLE_TYPES];

/* resource-oriented */
static unsigned int idle_pll_cond_mask_resource[NR_SPM_RES_LEVEL_TYPES] = {
	[SPM_RES_LEVEL_DRAM] = 0,
	[SPM_RES_LEVEL_SYSPLL] = 0,
	[SPM_RES_LEVEL_BUS_26M] = PLL_BIT_UNIVPLL | PLL_BIT_MFGPLL |
		PLL_BIT_MSDCPLL | PLL_BIT_TVDPLL |
		PLL_BIT_MMPLL,
	};
static unsigned int idle_pll_block_mask_resource[NR_SPM_RES_LEVEL_TYPES];

static unsigned int idle_pll_value;

#if MTK_SPM_HARDWARE_CG_CHECK
#define SPM_CG_CHECK_STA_BIT_0         (1U << 0)
#define SPM_CG_CHECK_STA_BIT_1         (1U << 1)
#define SPM_CG_CHECK_STA_BIT_2         (1U << 2)
#define SPM_CG_CHECK_STA_BIT_3         (1U << 3)
#define SPM_CG_CHECK_STA_BIT_ALL	(1U << 0 | 1U << 1 | 1U << 2 | 1U << 3)

static unsigned int hwcg_mask_scenario[NR_IDLE_TYPES] = {
	[IDLE_TYPE_DP] = SPM_CG_CHECK_STA_BIT_1,
	[IDLE_TYPE_SO3] = SPM_CG_CHECK_STA_BIT_2,
	[IDLE_TYPE_SO] = SPM_CG_CHECK_STA_BIT_3,
};
static unsigned int hwcg_mask_resource[NR_SPM_RES_LEVEL_TYPES] = {
	[SPM_RES_LEVEL_DRAM] = SPM_CG_CHECK_STA_BIT_1,
	[SPM_RES_LEVEL_SYSPLL] = SPM_CG_CHECK_STA_BIT_0,
	[SPM_RES_LEVEL_BUS_26M] = SPM_CG_CHECK_STA_BIT_2 |
				SPM_CG_CHECK_STA_BIT_3,
};
#endif

unsigned int
	clkmux_condition_mask[NF_CLKMUX][NF_VCORE][NF_CLKMUX_COND_SET] = {
	/* CLK_CFG_0 1000_0020 */
	[CLKMUX_AXI][VCORE_0P6V]
		= {
			0,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_AXI][VCORE_0P575V]
		= {
			0,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_MM][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_MM][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_SCP][VCORE_0P6V]
		= {
			4,
			0x80, 0x00, 0x02, 0x07,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_SCP][VCORE_0P575V]
		= {
			3,
			0x80, 0x00, 0x07, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_CKSYS_FMEM][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_CKSYS_FMEM][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	/* CLK_CFG_1 1000_0030*/
	[CLKMUX_IMG][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_IMG][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_IPE][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_IPE][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_DPE][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_DPE][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_CAM][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_CAM][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	/* CLK_CFG_2 1000_0040*/
	[CLKMUX_CCU][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_CCU][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_DSP][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_DSP][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_DSP1][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_DSP1][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_DSP2][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_DSP2][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	/* CLK_CFG_3 1000_0050*/
	[CLKMUX_DSP3][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_DSP3][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_IPU_IF][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_IPU_IF][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_MFG][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_MFG][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_MFG_52M][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_MFG_52M][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	/* CLK_CFG_4 1000_0060*/
	[CLKMUX_CAMTG][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_CAMTG][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_CAMTG2][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_CAMTG2][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_CAMTG3][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_CAMTG3][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_CAMTG4][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_CAMTG4][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	/* CLK_CFG_5 1000_0070*/
	[CLKMUX_UART][VCORE_0P6V]
		= {
			3,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_UART][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_SPI][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_SPI][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_MSDC50_0_HCLK][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_MSDC50_0_HCLK][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_MSDC50_0][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_MSDC50_0][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	/* CLK_CFG_6 1000_0080*/
	[CLKMUX_MSDC30_1][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_MSDC30_1][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_AUDIO][VCORE_0P6V]
		= {
			3,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_AUDIO][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_AUD_INTBUS][VCORE_0P6V]
		= {
			3,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_AUD_INTBUS][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_PWRAP_ULPOSC][VCORE_0P6V]
		= {
			0,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_PWRAP_ULPOSC][VCORE_0P575V]
		= {
			0,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	/* CLK_CFG_7 1000_0090*/
	[CLKMUX_ATB][VCORE_0P6V]
		= {
			3,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_ATB][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_POWMCU][VCORE_0P6V]
		= {
			0,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_POWMCU][VCORE_0P575V]
		= {
			0,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_DPI0][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_DPI0][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_SCAM][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_SCAM][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	/* CLK_CFG_8 1000_00A0*/
	[CLKMUX_DISP_PWM][VCORE_0P6V]
		= {
			0,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_DISP_PWM][VCORE_0P575V]
		= {
			0,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_USB_TOP][VCORE_0P6V]
		= {
			3,
			0x80, 0x00, 0x01, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_USB_TOP][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_SSUSB_XHCI][VCORE_0P6V]
		= {
			3,
			0x80, 0x00, 0x01, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_SSUSB_XHCI][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_SPM][VCORE_0P6V]
		= {
			0,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_SPM][VCORE_0P575V]
		= {
			0,
			0x00, 0x00, 0x01, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	/* CLK_CFG_9 1000_00B0*/
	[CLKMUX_I2C][VCORE_0P6V]
		= {
			3,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_I2C][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_SENINF][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_SENINF][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_SENINF1][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_SENINF1][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_SENINF2][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_SENINF2][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	/* CLK_CFG_10 1000_00C0*/
	[CLKMUX_DXCC][VCORE_0P6V]
		= {
			0,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_DXCC][VCORE_0P575V]
		= {
			0,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_AUD_ENGEN1][VCORE_0P6V]
		= {
			0,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_AUD_ENGEN1][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_AUD_ENGEN2][VCORE_0P6V]
		= {
			0,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_AUD_ENGEN2][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_AES_UFSFDE][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_AES_UFSFDE][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	/* CLK_CFG_11 1000_00D0*/
	[CLKMUX_UFS][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_UFS][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_AUD_1][VCORE_0P6V]
		= {
			0,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_AUD_1][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_AUD_2][VCORE_0P6V]
		= {
			0,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_AUD_2][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_ADSP][VCORE_0P6V]
		= {
			3,
			0x80, 0x00, 0x02, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_ADSP][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	/* CLK_CFG_12 1000_00E0*/
	[CLKMUX_DPMAIF_MAIN][VCORE_0P6V]
		= {
			0,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_DPMAIF_MAIN][VCORE_0P575V]
		= {
			0,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_VENC][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_VENC][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_VDEC][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_VDEC][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_CAMTM][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_CAMTM][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	/* CLK_CFG_13 1000_00F0*/
	[CLKMUX_PWM][VCORE_0P6V]
		= {
			3,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_PWM][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_AUDIO_H][VCORE_0P6V]
		= {
			0,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_AUDIO_H][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_BUS_AXIMEM][VCORE_0P6V]
		= {
			0,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_BUS_AXIMEM][VCORE_0P575V]
		= {
			0,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	[CLKMUX_CAMTG5][VCORE_0P6V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_CAMTG5][VCORE_0P575V]
		= {
			2,
			0x80, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },

	/* CLK_CFG_20 1000_0640*/
	[CLKMUX_MEM][VCORE_0P6V]
		= {
			0,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
	[CLKMUX_MEM][VCORE_0P575V]
		= {
			0,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 },
};

static void update_pll_state(void)
{
	idle_pll_value = 0;
	if (idle_readl(PLL_UNIVPLL) & 0x1)
		idle_pll_value |= PLL_BIT_UNIVPLL;
	if (idle_readl(PLL_MFGPLL) & 0x1)
		idle_pll_value |= PLL_BIT_MFGPLL;
	if (idle_readl(PLL_MSDCPLL) & 0x1)
		idle_pll_value |= PLL_BIT_MSDCPLL;
	if (idle_readl(PLL_TVDPLL) & 0x1)
		idle_pll_value |= PLL_BIT_TVDPLL;
	if (idle_readl(PLL_MMPLL) & 0x1)
		idle_pll_value |= PLL_BIT_MMPLL;

	/* scenario-oriented */
	if (!spm_resource_arch) {
		idle_pll_block_mask[IDLE_TYPE_DP] =
			idle_pll_value &
			idle_pll_cond_mask[IDLE_TYPE_DP];
		idle_pll_block_mask[IDLE_TYPE_SO3] =
			idle_pll_value &
			idle_pll_cond_mask[IDLE_TYPE_SO3];
		idle_pll_block_mask[IDLE_TYPE_SO] =
			idle_pll_value &
			idle_pll_cond_mask[IDLE_TYPE_SO];
	} else {
	/* resource-oriented */
		idle_pll_block_mask[SPM_RES_LEVEL_DRAM] =
			idle_pll_value &
			idle_pll_cond_mask[SPM_RES_LEVEL_DRAM];
		idle_pll_block_mask[SPM_RES_LEVEL_SYSPLL] =
			idle_pll_value &
			idle_pll_cond_mask[SPM_RES_LEVEL_SYSPLL];
		idle_pll_block_mask[SPM_RES_LEVEL_BUS_26M] =
			idle_pll_value &
			idle_pll_cond_mask[SPM_RES_LEVEL_BUS_26M];
	}
}

const char *mtk_resource_level_id_string[] = {
	"SPM_RES_LEVEL_DRAM",
	"SPM_RES_LEVEL_SYSPLL",
	"SPM_RES_LEVEL_BUS_26M",
	"SPM_RES_LEVEL_PMIC_LP",
};

static int cgmon_sel = -1;
#if MTK_SPM_HARDWARE_CG_CHECK
static int enable_idle_cond_update;
void mtk_idle_force_idle_cond_update(void)
{
	enable_idle_cond_update = 1;
	mtk_idle_cond_update_state();
	enable_idle_cond_update = ((cgmon_sel != -1) ? 1 : 0);
}

/* return 0/1/-1 : SPM HW CG check failed/succeed/invalid */
static int spm_hwcg_check(unsigned int check_bit)
{
	u32 spm_cg_check_sta = idle_readl(SPM_CG_CHECK_STA);

	if (check_bit > SPM_CG_CHECK_STA_BIT_ALL)
		return -1;
	else
		return !!(spm_cg_check_sta & check_bit);
}
#endif

void mtk_suspend_cond_info(void)
{
	int i, j;
	bool need_log = false;

	/* scenario-orietned */
	if (!spm_resource_arch)
		return;

#if MTK_SPM_HARDWARE_CG_CHECK
	/* If SPM Hardware CG check failed, force update idle condition*/
	/* for printing blocking suspend log */
	if (!spm_hwcg_check(SPM_CG_CHECK_STA_BIT_ALL))
		mtk_idle_force_idle_cond_update();
#endif

	/* resource-oriented */
	for (j = 0; j < NR_SPM_RES_LEVEL_TYPES; j++) {
		for (i = 0; i < NR_CG_GRPS; i++) {
			if (idle_block_mask_resource[j][i] && !need_log) {
				pr_info("[%s]\n",
				mtk_resource_level_id_string[j]);
				need_log = true;
			}

			if (idle_block_mask_resource[j][i]) {
				pr_info("[%02d %s] 0x%08x\n",
				i,
				idle_cg_info[i].name,
				idle_block_mask_resource[j][i]);
				/* WARN_ON(1); */
			}
		}
		if (idle_pll_block_mask[j] && !need_log)
			pr_info("[%s]\n",
			mtk_resource_level_id_string[j]);
		if (idle_pll_block_mask[j]) {
			pr_info("idle_pll_block_mask: 0x%08x\n",
				idle_pll_block_mask[j]);
			/* WARN_ON(1); */
		}
		need_log = false;
	}
}

/* dp/so3/so print blocking cond mask in debugfs */
int mtk_idle_cond_append_info(
	bool short_log, int idle_type, char *logptr, unsigned int logsize)
{
	int i, j;
	char *p = logptr;
	unsigned int s = logsize;
	bool need_log = false;

	#undef log
	#define log(fmt, args...) \
	do { \
		int l = scnprintf(p, s, fmt, ##args); \
		p += l; \
		s -= l; \
	} while (0)

	if (unlikely(idle_type < 0 || idle_type >= NR_IDLE_TYPES))
		return 0;

#if MTK_SPM_HARDWARE_CG_CHECK
	mtk_idle_force_idle_cond_update();
#endif

	/* scenario-oriented */
	if (!spm_resource_arch) {

		if (short_log) {
			for (i = 0; i < NR_CG_GRPS; i++)
				log("0x%08x, ",
				    idle_block_mask_scenario[idle_type][i]);
			log("idle_pll_block_mask: 0x%08x\n",
			    idle_pll_block_mask[idle_type]);
		} else {
			log("               Value");
			log("      Condition");
			log("  Block\n");
			for (i = 0; i < NR_CG_GRPS; i++) {
				log("[%02d %s] = 0x%08x "
				, i, idle_cg_info[i].name, idle_value[i]);
			log("0x%08x 0x%08x\n",
			    idle_cond_mask_scenario[idle_type][i]
				, idle_block_mask_scenario[idle_type][i]);
			}
			log("[%02d PLLCHK ] = 0x%08x "
				, i, idle_pll_value);
			log("0x%08x 0x%08x\n", idle_pll_cond_mask[idle_type]
				, idle_pll_block_mask[idle_type]);
		}

		return p - logptr;
	}

	/* resource-oriented */
	/* short log */
	if (short_log) {
		for (j = 0; j < NR_SPM_RES_LEVEL_TYPES - 1; j++) {
			for (i = 0; i < NR_CG_GRPS; i++) {
				if (!need_log) {
					log("[%s] ",
					mtk_resource_level_id_string[j]);
					need_log = true;
				}
				log("0x%08x, ",
					idle_block_mask_resource[j][i]);
			}
				if (!need_log) {
					log("%s: ",
					mtk_resource_level_id_string[j]);
				}
				log("idle_pll_block_mask: 0x%08x",
				    idle_pll_block_mask[j]);
				need_log = false;
		}

		return p - logptr;
	}

	/* full log */
	for (j = 0; j < NR_SPM_RES_LEVEL_TYPES - 1; j++) {
		for (i = 0; i < NR_CG_GRPS; i++) {
			if (!need_log) {
				log("%s:\n",
				mtk_resource_level_id_string[j]);
				log("               Value");
				log("      Condition");
				log("  Block\n");
				need_log = true;
			}
			log("[%02d %s] = 0x%08x ",
			    i, idle_cg_info[i].name, idle_value[i]);

			log("0x%08x 0x%08x\n",
			    idle_cond_mask_resource[j][i],
			    idle_block_mask_resource[j][i]);
		}
		if (!need_log)
			log("%s:\n", mtk_resource_level_id_string[j]);
		log("[%02d PLLCHK ] = 0x%08x ",
		    i, idle_pll_value);
		log("0x%08x 0x%08x\n",
			idle_pll_cond_mask[j],
			idle_pll_block_mask[j]);
		log("\n");
		need_log = false;
	}

	return p - logptr;
}

void mtk_idle_cond_update_mask(
	int idle_type, unsigned int reg, unsigned int mask)
{

	if (unlikely(idle_type < 0 || idle_type >= NR_IDLE_TYPES))
		return;

	/* scenario-oriented */
	/* dp/so3/so may update idle_cond_mask by debugfs */
	if (!spm_resource_arch) {
		if (reg < NR_CG_GRPS)
			idle_cond_mask_scenario[idle_type][reg] = mask;
		/* special case for sodi3 pll check */
		if (reg == NR_CG_GRPS)
			idle_pll_cond_mask_scenario[idle_type] = mask;
	} else {
	/* resource-oriented */
	/* dram/syspll/26m may update resource_cond_mask by debugfs */
		if (reg < NR_CG_GRPS)
			idle_cond_mask_resource[idle_type][reg] = mask;

		if (reg == NR_CG_GRPS)
			idle_pll_cond_mask_resource[idle_type] = mask;
	}
}

static unsigned int cgmon_sta[NR_CG_GRPS + 1];
static DEFINE_SPINLOCK(cgmon_spin_lock);

/* dp/so3/so print cg change state to ftrace log */
/* sel: -1/0/1/2 = off/dp/so3/so */
void mtk_idle_cg_monitor(int sel)
{
	unsigned long flags;

	spin_lock_irqsave(&cgmon_spin_lock, flags);
	cgmon_sel = sel;
#if MTK_SPM_HARDWARE_CG_CHECK
	enable_idle_cond_update = ((cgmon_sel != -1) ? 1 : 0);
#endif
	memset(cgmon_sta, 0, sizeof(cgmon_sta));
	spin_unlock_irqrestore(&cgmon_spin_lock, flags);
}

#define TRACE_CGMON(_g, _n, _cond)\
	trace_idle_cg(_g * 32 + _n, ((1 << _n) & _cond) ? 1 : 0)

static void mtk_idle_cgmon_trace_log(void)
{
	// Note: trace tag is defined at trace/events/mtk_idle_event.h
	#if MTK_IDLE_TRACE_TAG_ENABLE
	unsigned int diff, block, g, n;

	if (cgmon_sel == IDLE_TYPE_DP ||
		cgmon_sel == IDLE_TYPE_SO3 ||
		cgmon_sel == IDLE_TYPE_SO) {

		for (g = 0; g < NR_CG_GRPS + 1; g++) {
			block = (g < NR_CG_GRPS) ?
				(spm_resource_arch ?
				 idle_block_mask_resource[cgmon_sel][g] :
				 idle_block_mask_scenario[cgmon_sel][g]) :
				idle_pll_block_mask[cgmon_sel];
			diff = cgmon_sta[g] ^ block;
			if (diff) {
				cgmon_sta[g] = block;
				for (n = 0; n < 32; n++)
					if (diff & (1U << n))
						TRACE_CGMON(g, n, cgmon_sta[g]);
			}
		}
	}
	#endif
}

/* update secure cg state by secure call */
static void update_secure_cg_state(unsigned int clk[NR_CG_GRPS])
{
	/* Update INFRA0 bit 27 */
	#define INFRA0_BIT27	(1 << 27)

	clk[2] = clk[2] & ~INFRA0_BIT27;

	if (mt_secure_call(MTK_SIP_KERNEL_CHECK_SECURE_CG, 0, 0, 0, 0))
		clk[2] |= INFRA0_BIT27;
}

static void mtk_spm_res_level_set(void)
{
	if (!spm_resource_arch)
		return;

	spm_resource_req(SPM_RESOURCE_USER_SPM, SPM_RESOURCE_RELEASE);

#if MTK_SPM_HARDWARE_CG_CHECK
	if (!spm_hwcg_check(hwcg_mask_resource[SPM_RES_LEVEL_DRAM])) {
		spm_resource_req(SPM_RESOURCE_USER_SPM, SPM_RESOURCE_DRAM);
	} else if (!spm_hwcg_check(hwcg_mask_resource[SPM_RES_LEVEL_SYSPLL])) {
		spm_resource_req(SPM_RESOURCE_USER_SPM, SPM_RESOURCE_MAINPLL);
	} else if (!spm_hwcg_check(hwcg_mask_resource[SPM_RES_LEVEL_BUS_26M])) {
		spm_resource_req(SPM_RESOURCE_USER_SPM, SPM_RESOURCE_AXI_BUS);
		spm_resource_req(SPM_RESOURCE_USER_SPM, SPM_RESOURCE_CK_26M);
	}
#else
	if (idle_block_mask_resource[SPM_RES_LEVEL_DRAM][NR_CG_GRPS]
	    || idle_pll_block_mask[SPM_RES_LEVEL_DRAM]) {
		spm_resource_req(SPM_RESOURCE_USER_SPM, SPM_RESOURCE_DRAM);
	} else if (idle_block_mask_resource[SPM_RES_LEVEL_SYSPLL][NR_CG_GRPS]
		   || idle_pll_block_mask[SPM_RES_LEVEL_SYSPLL]) {
		spm_resource_req(SPM_RESOURCE_USER_SPM, SPM_RESOURCE_MAINPLL);
	} else if (idle_block_mask_resource[SPM_RES_LEVEL_BUS_26M][NR_CG_GRPS]
		   || idle_pll_block_mask[SPM_RES_LEVEL_BUS_26M]) {
		spm_resource_req(SPM_RESOURCE_USER_SPM, SPM_RESOURCE_AXI_BUS);
		spm_resource_req(SPM_RESOURCE_USER_SPM, SPM_RESOURCE_CK_26M);
	}
#endif
}

/* update all idle condition state: mtcmos/pll/cg/secure_cg */
void mtk_idle_cond_update_state(void)
{
	int i, j;
	unsigned int clk[NR_CG_GRPS];

#if MTK_SPM_HARDWARE_CG_CHECK
	if (enable_idle_cond_update == 0)
		return;
#endif

	/* read all cg state (not including secure cg) */
	for (i = 0; i < NR_CG_GRPS; i++) {
		idle_value[i] = clk[i] = 0;
		/* check mtcmos, if off set idle_value and clk to 0 disable */
		if (!(idle_readl(SPM_PWR_STATUS) &
			idle_cg_info[i].subsys_mask) &&
		    !(idle_readl(SPM_PWR_STATUS_2ND) &
			idle_cg_info[i].subsys_mask))
			continue;
		/* check clkmux */
		if (check_clkmux_pdn(idle_cg_info[i].clkmux_id))
			continue;
		idle_value[i] = clk[i] = idle_cg_info[i].bBitflip ?
			~idle_readl(idle_cg_info[i].addr) :
			idle_readl(idle_cg_info[i].addr);
	}

	/* update secure cg state */
	update_secure_cg_state(clk);

	/* update pll state */
	update_pll_state();

	if (!spm_resource_arch) {
	/* scenario-oriented */
	/* update block mask for dp/so/so3 */
		for (i = 0; i < NR_IDLE_TYPES; i++) {
			if (i == IDLE_TYPE_RG)
				continue;
			idle_block_mask_scenario[i][NR_CG_GRPS] = 0;
			for (j = 0; j < NR_CG_GRPS; j++) {
				idle_block_mask_scenario[i][j] =
					idle_cond_mask_scenario[i][j] & clk[j];
				idle_block_mask_scenario[i][NR_CG_GRPS] |=
					idle_block_mask_scenario[i][j];
			}
		}
	} else {
	/* resource-oriented */
	/* update block mask for DRAM/SYSPLL/BUS_26M */
		for (i = 0; i < NR_SPM_RES_LEVEL_TYPES; i++) {
			idle_block_mask_resource[i][NR_CG_GRPS] = 0;
			for (j = 0; j < NR_CG_GRPS; j++) {
				idle_block_mask_resource[i][j] =
					idle_cond_mask_resource[i][j] & clk[j];
				idle_block_mask_resource[i][NR_CG_GRPS] |=
					idle_block_mask_resource[i][j];
			}
		}
	}

	/* cg monitor: print cg change info to ftrace log */

	mtk_idle_cgmon_trace_log();

	mtk_spm_res_level_set();
}

#if MTK_SPM_HARDWARE_CG_CHECK
#define MMSYS_CG_INDEX 6
void mtk_idle_cond_update_mmcg_state_sodi3(void)
{
	int i, j;
	unsigned int clk[NR_CG_GRPS];

	/* Only read MM cg state */
	for (i = MMSYS_CG_INDEX; i < NR_CG_GRPS; i++) {
		idle_value[i] = clk[i] = 0;
		/* check mtcmos, if off set idle_value and clk to 0 disable */
		if (!(idle_readl(SPM_PWR_STATUS) &
			idle_cg_info[i].subsys_mask) &&
			!(idle_readl(SPM_PWR_STATUS_2ND) &
			idle_cg_info[i].subsys_mask))
			continue;
		/* check clkmux */
		if (check_clkmux_pdn(idle_cg_info[i].clkmux_id))
			continue;
		idle_value[i] = clk[i] = idle_cg_info[i].bBitflip ?
			~idle_readl(idle_cg_info[i].addr) :
			idle_readl(idle_cg_info[i].addr);
	}

	/* update block mask for so3 */
	idle_block_mask_scenario[IDLE_TYPE_SO3][NR_CG_GRPS] = 0;
	for (j = MMSYS_CG_INDEX; j < NR_CG_GRPS; j++) {
		idle_block_mask_scenario[IDLE_TYPE_SO3][j] =
			idle_cond_mask_scenario[IDLE_TYPE_SO3][j] & clk[j];
		idle_block_mask_scenario[IDLE_TYPE_SO3][NR_CG_GRPS] |=
			idle_block_mask_scenario[IDLE_TYPE_SO3][j];
	}
}
#endif

/* return final idle condition check result for each idle type */
bool mtk_idle_cond_check(int idle_type)
{
	bool ret = false;

	if (unlikely(idle_type < 0 || idle_type >= NR_IDLE_TYPES))
		return false;

	/* scenario-oriented */
	if (!spm_resource_arch) {
#if MTK_SPM_HARDWARE_CG_CHECK
		if (spm_hwcg_check(hwcg_mask_scenario[idle_type])) {
			if (idle_type == IDLE_TYPE_SO3) {
			/* SPM_CG_CHECK_STA_BIT_2 has no MMSYS CG check. */
			/* Use SW check for MMSYS CG check. */
				mtk_idle_cond_update_mmcg_state_sodi3();
				if (!idle_block_mask_scenario
					[IDLE_TYPE_SO3][NR_CG_GRPS])
					ret = true;
			} else {
				ret = true;
			}
		}

		if (ret == false)
			mtk_idle_force_idle_cond_update();
#else
		/* check cg state */
		ret = !(idle_block_mask_scenario
			[idle_type][NR_CG_GRPS]);

		/* check pll state */
		ret = (ret && !idle_pll_block_mask[idle_type]);
#endif
	} else {
	/* resource-oriented */
#if MTK_SPM_HARDWARE_CG_CHECK
		if (spm_hwcg_check(hwcg_mask_resource[SPM_RES_LEVEL_DRAM]))
			ret = true;

		if (ret == false)
			mtk_idle_force_idle_cond_update();
#else
		/* check dram with cg state */
		ret = !(idle_block_mask_resource
			[SPM_RES_LEVEL_DRAM][NR_CG_GRPS]);

		/* check dram with pll state */
		ret = (ret && !idle_pll_block_mask[SPM_RES_LEVEL_DRAM]);
#endif
	}

	return ret;
}

/***********************************************************
 * Clock mux check for vcore low power mode
 *
 * Check clkmux condition
 *   1. Only in deepidle/SODI3
 *   2. After mtk_idle_notifier_call_chain()
 *       - To ensure other subsystem controls its clkmux well
 ***********************************************************/
bool mtk_idle_cond_vcore_lp_mode(int idle_type)
{
	bool op_cond = false;

	if (idle_force_vcore_lp_mode == IDLE_VCORE_BYPASS_CHECK_FOR_LP_MODE)
		goto END;

	memset(clkmux_block_mask[idle_type],
		 0, NF_CLK_CFG * sizeof(unsigned int));

	clkmux_cond[idle_type] = mtk_idle_check_clkmux(idle_type,
		 clkmux_block_mask);

	switch (idle_force_vcore_lp_mode) {
	case IDLE_VCORE_CHECK_FOR_LP_MODE:
		/* by clkmux check */
		op_cond = (clkmux_cond[idle_type] ? true : false);
		break;
	case IDLE_VCORE_FORCE_LP_MODE:
		/* enter LP mode */
		op_cond = true;
		break;
	case IDLE_VCORE_FORCE_NORMAL_MODE:
		/* no enter LP mode */
		op_cond = false;
		break;
	default:
		op_cond = false;
		break;
	}

END:
	return op_cond;
}

unsigned int mtk_idle_cond_vcore_ulposc_state(void)
{
	int op_cond = 0;

	if (!(idle_readl(SPM_ULPOSC_CON) & 0x1))
		op_cond |= MTK_IDLE_OPT_VCORE_ULPOSC_OFF;

	return op_cond;
}


/***********************************************************
 * Fundamental build up functions
 ***********************************************************/
static void get_cg_addrs(void)
{
	/* Assign cg address to idle_cg_info */
	idle_cg_info[0].addr = SPM_PWR_STATUS;
	idle_cg_info[1].addr = SPM_PWR_STATUS_2ND;
	idle_cg_info[2].addr = INFRA_SW_CG_0_STA;
	idle_cg_info[3].addr = INFRA_SW_CG_1_STA;
	idle_cg_info[4].addr = INFRA_SW_CG_2_STA;
	idle_cg_info[5].addr = INFRA_SW_CG_3_STA;
	idle_cg_info[6].addr = DISP_CG_CON_0;
	idle_cg_info[7].addr = DISP_CG_CON_1;
}

static int get_base_from_node(
	const char *cmp, void __iomem **pbase, int idx)
{
	struct device_node *node;

	node = of_find_compatible_node(NULL, NULL, cmp);
	if (!node)
		pr_info("[IDLE] node '%s' not found!\n", cmp);

	*pbase = of_iomap(node, idx);
	if (!(*pbase))
		pr_info("[IDLE] node '%s' cannot iomap!\n", cmp);

	return 0;
}

void mtk_spm_arch_type_set(bool type)
{
	spm_resource_arch = type;

	/* scenario-oriented */
	if (!spm_resource_arch) {
		idle_pll_cond_mask = idle_pll_cond_mask_scenario;
		idle_pll_block_mask = idle_pll_block_mask_scenario;
	} else {
		idle_pll_cond_mask = idle_pll_cond_mask_resource;
		idle_pll_block_mask = idle_pll_block_mask_resource;
	}

#if MTK_SPM_HARDWARE_CG_CHECK
	/* Enable SPM hardware CG check again*/
	SMC_CALL(ARGS, SPM_ARGS_HARDWARE_CG_CHECK,
		MTK_SPM_HARDWARE_CG_CHECK, spm_resource_arch);
#endif
}

bool mtk_spm_arch_type_get(void)
{
	return spm_resource_arch;
}

void mtk_spm_arch_type_init(void)
{
	mtk_spm_arch_type_set(MTK_SPM_ARCH_TYPE ? true : false);
}

int __init mtk_idle_cond_check_init(void)
{
	get_base_from_node("mediatek,mt6779-infracfg_ao", &infrasys_base, 0);
	get_base_from_node("mediatek,mt6779-mmsys", &mmsys_base, 0);
	get_base_from_node("mediatek,mt6779-imgsys", &imgsys_base, 0);
	get_base_from_node("mediatek,mt6779-mfgcfg", &mfgsys_base, 0);
	get_base_from_node("mediatek,mt6779-vencsys", &vencsys_base, 0);
	get_base_from_node("mediatek,mt6779-apmixed", &apmixedsys_base, 0);
	get_base_from_node("mediatek,sleep", &sleepsys_base, 0);
	get_base_from_node("mediatek,mt6779-topckgen", &topck_base, 0);
	/* update cg address in idle_cg_info */
	get_cg_addrs();

	mtk_spm_arch_type_init();

	return 0;
}

static void get_all_clkcfg_state(u32 clkcfgs[NF_CLK_CFG])
{
	int i;

	for (i = 0; i < NF_CLK_CFG; i++) {
		clkcfgs[i] = idle_readl(CLK_CFG(i));
		trace_idle_clkcfg_state_rcuidle(i, clkcfgs[i]);
	}
}

#define MUX_OFF_MASK    0x80
#define MUX_ON_MASK     0x8F

bool mtk_idle_check_clkmux(
	int idle_type, unsigned int block_mask[NR_TYPES][NF_CLK_CFG])
{
	u32 clkcfgs[NF_CLK_CFG] = {0};
	int i, k;
	unsigned int idx;
	int offset;
	u32 masks[4] = {0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000};
	int shifts[4] = {0, 8, 16, 24};
	u32 clkmux_val;

	bool result = false;
	bool final_result = true;

	int check_num;
	u32 check_val;
	u32 mux_check_mask;
	int vcore_sel = VCORE_0P6V;

	get_all_clkcfg_state(clkcfgs);

	if (idle_type == IDLE_TYPE_DP)
		vcore_sel = VCORE_0P6V;
	else if (idle_type == IDLE_TYPE_SO3)
		vcore_sel = VCORE_0P575V;

	/* Check each clkmux setting */
	for (i = 0; i < NF_CLKMUX; i++) {
		result     = false;
		idx        = i / 4;
		offset     = i % 4;
		clkmux_val = ((clkcfgs[idx] & masks[offset]) >>
			      shifts[offset]);

		check_num = clkmux_condition_mask[i][vcore_sel][0];

		if (check_num == 0)
			result = true;

		for (k = 0; k < check_num; k++) {

			check_val  = clkmux_condition_mask[i][vcore_sel][1 + k];

			mux_check_mask = (k == 0) ? MUX_OFF_MASK : MUX_ON_MASK;

			if ((clkmux_val & mux_check_mask) == check_val) {
				result = true;
				break;
			}
		}

		if (result == false) {

			final_result = false;

			if (likely(idle_type >= 0)) {
				block_mask[idle_type][idx] |=
					(clkmux_val << shifts[offset]);
				trace_idle_check_clkmux_rcuidle(
					idle_type, idx,
					block_mask[idle_type][idx]);
			}
		}
	}

	return final_result;
}


late_initcall(mtk_idle_cond_check_init);
