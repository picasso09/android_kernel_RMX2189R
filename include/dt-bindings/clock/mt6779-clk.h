/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2019 MediaTek Inc.
 * Author: Wendell Lin <wendell.lin@mediatek.com>
 */

#ifndef _DT_BINDINGS_CLK_MT6779_H
#define _DT_BINDINGS_CLK_MT6779_H

/* TOPCKGEN */
#define CLK_TOP_AXI			1
#define CLK_TOP_MM			2
#define CLK_TOP_CAM			3
#define CLK_TOP_MFG			4
#define CLK_TOP_CAMTG			5
#define CLK_TOP_UART			6
#define CLK_TOP_SPI			7
#define CLK_TOP_MSDC50_0_HCLK		8
#define CLK_TOP_MSDC50_0		9
#define CLK_TOP_MSDC30_1		10
#define CLK_TOP_MSDC30_2		11
#define CLK_TOP_AUD			12
#define CLK_TOP_AUD_INTBUS		13
#define CLK_TOP_FPWRAP_ULPOSC		14
#define CLK_TOP_SCP			15
#define CLK_TOP_ATB			16
#define CLK_TOP_SSPM			17
#define CLK_TOP_DPI0			18
#define CLK_TOP_SCAM			19
#define CLK_TOP_AUD_1			20
#define CLK_TOP_AUD_2			21
#define CLK_TOP_DISP_PWM		22
#define CLK_TOP_SSUSB_TOP_XHCI		23
#define CLK_TOP_USB_TOP			24
#define CLK_TOP_SPM			25
#define CLK_TOP_I2C			26
#define CLK_TOP_F52M_MFG		27
#define CLK_TOP_SENINF			28
#define CLK_TOP_DXCC			29
#define CLK_TOP_CAMTG2			30
#define CLK_TOP_AUD_ENG1		31
#define CLK_TOP_AUD_ENG2		32
#define CLK_TOP_FAES_UFSFDE		33
#define CLK_TOP_FUFS			34
#define CLK_TOP_IMG			35
#define CLK_TOP_DSP			36
#define CLK_TOP_DSP1			37
#define CLK_TOP_DSP2			38
#define CLK_TOP_IPU_IF			39
#define CLK_TOP_CAMTG3			40
#define CLK_TOP_CAMTG4			41
#define CLK_TOP_PMICSPI			42
#define CLK_TOP_MAINPLL_CK		43
#define CLK_TOP_MAINPLL_D2		44
#define CLK_TOP_MAINPLL_D3		45
#define CLK_TOP_MAINPLL_D5		46
#define CLK_TOP_MAINPLL_D7		47
#define CLK_TOP_MAINPLL_D2_D2		48
#define CLK_TOP_MAINPLL_D2_D4		49
#define CLK_TOP_MAINPLL_D2_D8		50
#define CLK_TOP_MAINPLL_D2_D16		51
#define CLK_TOP_MAINPLL_D3_D2		52
#define CLK_TOP_MAINPLL_D3_D4		53
#define CLK_TOP_MAINPLL_D3_D8		54
#define CLK_TOP_MAINPLL_D5_D2		55
#define CLK_TOP_MAINPLL_D5_D4		56
#define CLK_TOP_MAINPLL_D7_D2		57
#define CLK_TOP_MAINPLL_D7_D4		58
#define CLK_TOP_UNIVPLL_CK		59
#define CLK_TOP_UNIVPLL_D2		60
#define CLK_TOP_UNIVPLL_D3		61
#define CLK_TOP_UNIVPLL_D5		62
#define CLK_TOP_UNIVPLL_D7		63
#define CLK_TOP_UNIVPLL_D2_D2		64
#define CLK_TOP_UNIVPLL_D2_D4		65
#define CLK_TOP_UNIVPLL_D2_D8		66
#define CLK_TOP_UNIVPLL_D3_D2		67
#define CLK_TOP_UNIVPLL_D3_D4		68
#define CLK_TOP_UNIVPLL_D3_D8		69
#define CLK_TOP_UNIVPLL_D5_D2		70
#define CLK_TOP_UNIVPLL_D5_D4		71
#define CLK_TOP_UNIVPLL_D5_D8		72
#define CLK_TOP_APLL1_CK		73
#define CLK_TOP_APLL1_D2		74
#define CLK_TOP_APLL1_D4		75
#define CLK_TOP_APLL1_D8		76
#define CLK_TOP_APLL2_CK		77
#define CLK_TOP_APLL2_D2		78
#define CLK_TOP_APLL2_D4		79
#define CLK_TOP_APLL2_D8		80
#define CLK_TOP_TVDPLL_CK		81
#define CLK_TOP_TVDPLL_D2		82
#define CLK_TOP_TVDPLL_D4		83
#define CLK_TOP_TVDPLL_D8		84
#define CLK_TOP_TVDPLL_D16		85
#define CLK_TOP_MSDCPLL_CK		86
#define CLK_TOP_MSDCPLL_D2		87
#define CLK_TOP_MSDCPLL_D4		88
#define CLK_TOP_MSDCPLL_D8		89
#define CLK_TOP_MSDCPLL_D16		90
#define CLK_TOP_AD_OSC_CK		91
#define CLK_TOP_OSC_D2			92
#define CLK_TOP_OSC_D4			93
#define CLK_TOP_OSC_D8			94
#define CLK_TOP_OSC_D16			95
#define CLK_TOP_F26M_CK_D2		96
#define CLK_TOP_MFGPLL_CK		97
#define CLK_TOP_UNIVP_192M_CK		98
#define CLK_TOP_UNIVP_192M_D2		99
#define CLK_TOP_UNIVP_192M_D4		100
#define CLK_TOP_UNIVP_192M_D8		101
#define CLK_TOP_UNIVP_192M_D16		102
#define CLK_TOP_UNIVP_192M_D32		103
#define CLK_TOP_MMPLL_CK		104
#define CLK_TOP_MMPLL_D4		105
#define CLK_TOP_MMPLL_D4_D2		106
#define CLK_TOP_MMPLL_D4_D4		107
#define CLK_TOP_MMPLL_D5		108
#define CLK_TOP_MMPLL_D5_D2		109
#define CLK_TOP_MMPLL_D5_D4		110
#define CLK_TOP_MMPLL_D6		111
#define CLK_TOP_MMPLL_D7		112
#define CLK_TOP_CLK26M			113
#define CLK_TOP_CLK13M			114
#define CLK_TOP_ADSP			115
#define CLK_TOP_DPMAIF			116
#define CLK_TOP_VENC			117
#define CLK_TOP_VDEC			118
#define CLK_TOP_CAMTM			119
#define CLK_TOP_PWM			120
#define CLK_TOP_ADSPPLL_CK		121
#define CLK_TOP_I2S0_M_SEL		122
#define CLK_TOP_I2S1_M_SEL		123
#define CLK_TOP_I2S2_M_SEL		124
#define CLK_TOP_I2S3_M_SEL		125
#define CLK_TOP_I2S4_M_SEL		126
#define CLK_TOP_I2S5_M_SEL		127
#define CLK_TOP_APLL12_DIV0		128
#define CLK_TOP_APLL12_DIV1		129
#define CLK_TOP_APLL12_DIV2		130
#define CLK_TOP_APLL12_DIV3		131
#define CLK_TOP_APLL12_DIV4		132
#define CLK_TOP_APLL12_DIVB		133
#define CLK_TOP_APLL12_DIV5		134
#define CLK_TOP_IPE			135
#define CLK_TOP_DPE			136
#define CLK_TOP_CCU			137
#define CLK_TOP_DSP3			138
#define CLK_TOP_SENINF1			139
#define CLK_TOP_SENINF2			140
#define CLK_TOP_AUD_H			141
#define CLK_TOP_CAMTG5			142
#define CLK_TOP_TVDPLL_MAINPLL_D2_CK	143
#define CLK_TOP_AD_OSC2_CK		144
#define CLK_TOP_OSC2_D2			145
#define CLK_TOP_OSC2_D3			146
#define CLK_TOP_FMEM_466M_CK		147
#define CLK_TOP_ADSPPLL_D4		148
#define CLK_TOP_ADSPPLL_D5		149
#define CLK_TOP_ADSPPLL_D6		150
#define CLK_TOP_OSC_D10			151
#define CLK_TOP_UNIVPLL_D3_D16		152
#define CLK_TOP_NR_CLK			153

/* APMIXED */
#define CLK_APMIXED_ARMPLL_LL		1
#define CLK_APMIXED_ARMPLL_BL		2
#define CLK_APMIXED_ARMPLL_BB		3
#define CLK_APMIXED_CCIPLL		4
#define CLK_APMIXED_MAINPLL		5
#define CLK_APMIXED_UNIV2PLL		6
#define CLK_APMIXED_MSDCPLL		7
#define CLK_APMIXED_ADSPPLL		8
#define CLK_APMIXED_MMPLL		9
#define CLK_APMIXED_MFGPLL		10
#define CLK_APMIXED_TVDPLL		11
#define CLK_APMIXED_APLL1		12
#define CLK_APMIXED_APLL2		13
#define CLK_APMIXED_SSUSB26M		14
#define CLK_APMIXED_APPLL26M		15
#define CLK_APMIXED_MIPIC0_26M		16
#define CLK_APMIXED_MDPLLGP26M		17
#define CLK_APMIXED_MM_F26M		18
#define CLK_APMIXED_UFS26M		19
#define CLK_APMIXED_MIPIC1_26M		20
#define CLK_APMIXED_MEMPLL26M		21
#define CLK_APMIXED_CLKSQ_LVPLL_26M	22
#define CLK_APMIXED_MIPID0_26M		23
#define CLK_APMIXED_MIPID1_26M		24
#define CLK_APMIXED_NR_CLK		25

/* CAMSYS */
#define CLK_CAM_LARB10			1
#define CLK_CAM_DFP_VAD			2
#define CLK_CAM_LARB11			3
#define CLK_CAM_LARB9			4
#define CLK_CAM_CAM			5
#define CLK_CAM_CAMTG			6
#define CLK_CAM_SENINF			7
#define CLK_CAM_CAMSV0			8
#define CLK_CAM_CAMSV1			9
#define CLK_CAM_CAMSV2			10
#define CLK_CAM_CAMSV3			11
#define CLK_CAM_CCU			12
#define CLK_CAM_FAKE_ENG		13
#define CLK_CAM_NR_CLK			14

/* INFRA */
#define CLK_INFRA_PMIC_TMR		1
#define CLK_INFRA_PMIC_AP		2
#define CLK_INFRA_PMIC_MD		3
#define CLK_INFRA_PMIC_CONN		4
#define CLK_INFRA_SCPSYS		5
#define CLK_INFRA_SEJ			6
#define CLK_INFRA_APXGPT		7
#define CLK_INFRA_ICUSB			8
#define CLK_INFRA_GCE			9
#define CLK_INFRA_THERM			10
#define CLK_INFRA_I2C0			11
#define CLK_INFRA_I2C1			12
#define CLK_INFRA_I2C2			13
#define CLK_INFRA_I2C3			14
#define CLK_INFRA_PWM_HCLK		15
#define CLK_INFRA_PWM1			16
#define CLK_INFRA_PWM2			17
#define CLK_INFRA_PWM3			18
#define CLK_INFRA_PWM4			19
#define CLK_INFRA_PWM			20
#define CLK_INFRA_UART0			21
#define CLK_INFRA_UART1			22
#define CLK_INFRA_UART2			23
#define CLK_INFRA_UART3			24
#define CLK_INFRA_GCE_26M		25
#define CLK_INFRA_CQ_DMA_FPC		26
#define CLK_INFRA_BTIF			27
#define CLK_INFRA_SPI0			28
#define CLK_INFRA_MSDC0			29
#define CLK_INFRA_MSDC1			30
#define CLK_INFRA_MSDC2			31
#define CLK_INFRA_MSDC0_SCK		32
#define CLK_INFRA_DVFSRC		33
#define CLK_INFRA_GCPU			34
#define CLK_INFRA_TRNG			35
#define CLK_INFRA_AUXADC		36
#define CLK_INFRA_CPUM			37
#define CLK_INFRA_CCIF1_AP		38
#define CLK_INFRA_CCIF1_MD		39
#define CLK_INFRA_AUXADC_MD		40
#define CLK_INFRA_MSDC1_SCK		41
#define CLK_INFRA_MSDC2_SCK		42
#define CLK_INFRA_AP_DMA		43
#define CLK_INFRA_XIU			44
#define CLK_INFRA_DEVICE_APC		45
#define CLK_INFRA_CCIF_AP		46
#define CLK_INFRA_DEBUGSYS		47
#define CLK_INFRA_AUD			48
#define CLK_INFRA_CCIF_MD		49
#define CLK_INFRA_DXCC_SEC_CORE		50
#define CLK_INFRA_DXCC_AO		51
#define CLK_INFRA_DRAMC_F26M		52
#define CLK_INFRA_IRTX			53
#define CLK_INFRA_DISP_PWM		54
#define CLK_INFRA_DPMAIF_CK		55
#define CLK_INFRA_AUD_26M_BCLK_CK	56
#define CLK_INFRA_SPI1			57
#define CLK_INFRA_I2C4			58
#define CLK_INFRA_MODEM_TEMP_SHARE	59
#define CLK_INFRA_SPI2			60
#define CLK_INFRA_SPI3			61
#define CLK_INFRA_UNIPRO_SCK		62
#define CLK_INFRA_UNIPRO_TICK		63
#define CLK_INFRA_UFS_MP_SAP_BCLK	64
#define CLK_INFRA_MD32_BCLK		65
#define CLK_INFRA_SSPM			66
#define CLK_INFRA_UNIPRO_MBIST		67
#define CLK_INFRA_SSPM_BUS_HCLK		68
#define CLK_INFRA_I2C5			69
#define CLK_INFRA_I2C5_ARBITER		70
#define CLK_INFRA_I2C5_IMM		71
#define CLK_INFRA_I2C1_ARBITER		72
#define CLK_INFRA_I2C1_IMM		73
#define CLK_INFRA_I2C2_ARBITER		74
#define CLK_INFRA_I2C2_IMM		75
#define CLK_INFRA_SPI4			76
#define CLK_INFRA_SPI5			77
#define CLK_INFRA_CQ_DMA		78
#define CLK_INFRA_UFS			79
#define CLK_INFRA_AES_UFSFDE		80
#define CLK_INFRA_UFS_TICK		81
#define CLK_INFRA_MSDC0_SELF		82
#define CLK_INFRA_MSDC1_SELF		83
#define CLK_INFRA_MSDC2_SELF		84
#define CLK_INFRA_SSPM_26M_SELF		85
#define CLK_INFRA_SSPM_32K_SELF		86
#define CLK_INFRA_UFS_AXI		87
#define CLK_INFRA_I2C6			88
#define CLK_INFRA_AP_MSDC0		89
#define CLK_INFRA_MD_MSDC0		90
#define CLK_INFRA_USB			91
#define CLK_INFRA_DEVMPU_BCLK		92
#define CLK_INFRA_CCIF2_AP		93
#define CLK_INFRA_CCIF2_MD		94
#define CLK_INFRA_CCIF3_AP		95
#define CLK_INFRA_CCIF3_MD		96
#define CLK_INFRA_SEJ_F13M		97
#define CLK_INFRA_AES_BCLK		98
#define CLK_INFRA_I2C7			99
#define CLK_INFRA_I2C8			100
#define CLK_INFRA_FBIST2FPC		101
#define CLK_INFRA_CCIF4_AP		102
#define CLK_INFRA_CCIF4_MD		103
#define CLK_INFRA_FADSP			104
#define CLK_INFRA_SSUSB_XHCI		105
#define CLK_INFRA_SPI6			106
#define CLK_INFRA_SPI7			107
#define CLK_INFRA_NR_CLK		108

/* MFGCFG */
#define CLK_MFGCFG_BG3D			1
#define CLK_MFGCFG_NR_CLK		2

/* IMG */
#define	CLK_IMG_WPE_A			1
#define	CLK_IMG_MFB			2
#define	CLK_IMG_DIP			3
#define	CLK_IMG_LARB6			4
#define	CLK_IMG_LARB5			5
#define CLK_IMG_NR_CLK			6

/* IPE */
#define	CLK_IPE_LARB7			1
#define	CLK_IPE_LARB8			2
#define	CLK_IPE_SMI_SUBCOM		3
#define	CLK_IPE_FD			4
#define	CLK_IPE_FE			5
#define CLK_IPE_RSC			6
#define CLK_IPE_DPE			7
#define CLK_IPE_NR_CLK			8

/* MM_CONFIG */
#define	CLK_MM_SMI_COMMON		1
#define	CLK_MM_SMI_LARB0		2
#define	CLK_MM_SMI_LARB1		3
#define	CLK_MM_GALS_COMM0		4
#define	CLK_MM_GALS_COMM1		5
#define	CLK_MM_GALS_CCU2MM		6
#define	CLK_MM_GALS_IPU12MM		7
#define	CLK_MM_GALS_IMG2MM		8
#define	CLK_MM_GALS_CAM2MM		9
#define	CLK_MM_GALS_IPU2MM		10
#define	CLK_MM_MDP_DL_TXCK		11
#define	CLK_MM_IPU_DL_TXCK		12
#define	CLK_MM_MDP_RDMA0		13
#define	CLK_MM_MDP_RDMA1		14
#define	CLK_MM_MDP_RSZ0			15
#define	CLK_MM_MDP_RSZ1			16
#define	CLK_MM_MDP_TDSHP		17
#define	CLK_MM_MDP_WROT0		18
#define	CLK_MM_FAKE_ENG			19
#define	CLK_MM_DISP_OVL0		20
#define	CLK_MM_DISP_OVL0_2L		21
#define	CLK_MM_DISP_OVL1_2L		22
#define	CLK_MM_DISP_RDMA0		23
#define	CLK_MM_DISP_RDMA1		24
#define	CLK_MM_DISP_WDMA0		25
#define	CLK_MM_DISP_COLOR0		26
#define	CLK_MM_DISP_CCORR0		27
#define	CLK_MM_DISP_AAL0		28
#define	CLK_MM_DISP_GAMMA0		29
#define	CLK_MM_DISP_DITHER0		30
#define	CLK_MM_DISP_SPLIT		31
#define	CLK_MM_DSI0_MM_CK		32
#define	CLK_MM_DSI0_IF_CK		33
#define	CLK_MM_DPI_MM_CK		34
#define	CLK_MM_DPI_IF_CK		35
#define	CLK_MM_FAKE_ENG2		36
#define	CLK_MM_MDP_DL_RX_CK		37
#define	CLK_MM_IPU_DL_RX_CK		38
#define	CLK_MM_26M			39
#define	CLK_MM_MM_R2Y			40
#define	CLK_MM_DISP_RSZ			41
#define CLK_MM_MDP_WDMA0		42
#define CLK_MM_MDP_AAL			43
#define CLK_MM_MDP_HDR			44
#define CLK_MM_DBI_MM_CK		45
#define CLK_MM_DBI_IF_CK		46
#define	CLK_MM_MDP_WROT1		47
#define	CLK_MM_DISP_POSTMASK0		48
#define	CLK_MM_DISP_HRT_BW		49
#define	CLK_MM_DISP_OVL_FBDC		50
#define CLK_MM_CONFIG_NR_CLK		51

/* VDEC_GCON */
#define	CLK_VDEC_VDEC			1
#define	CLK_VDEC_LARB1			2
#define CLK_VDEC_GCON_NR_CLK		3

/* VENC_GCON */
#define CLK_VENC_GCON_LARB		1
#define CLK_VENC_GCON_VENC		2
#define CLK_VENC_GCON_JPGENC		3
#define CLK_VENC_GCON_GALS		4
#define CLK_VENC_GCON_NR_CLK		5

/* AUD */
#define	CLK_AUD_AFE			1
#define	CLK_AUD_22M			2
#define	CLK_AUD_24M			3
#define	CLK_AUD_APLL2_TUNER		4
#define	CLK_AUD_APLL_TUNER		5
#define	CLK_AUD_TDM			6
#define	CLK_AUD_ADC			7
#define	CLK_AUD_DAC			8
#define	CLK_AUD_DAC_PREDIS		9
#define	CLK_AUD_TML			10
#define	CLK_AUD_NLE			11
#define	CLK_AUD_I2S1_BCLK_SW		12
#define CLK_AUD_I2S2_BCLK_SW		13
#define CLK_AUD_I2S3_BCLK_SW		14
#define CLK_AUD_I2S4_BCLK_SW		15
#define CLK_AUD_I2S5_BCLK_SW		16
#define	CLK_AUD_CONN_I2S_ASRC		17
#define	CLK_AUD_GENERAL1_ASRC		18
#define	CLK_AUD_GENERAL2_ASRC		19
#define	CLK_AUD_DAC_HIRES		20
#define CLK_AUD_PDN_ADDA6_ADC		21
#define CLK_AUD_ADC_HIRES		22
#define CLK_AUD_ADC_HIRES_TML		23
#define CLK_AUD_ADDA6_ADC_HIRES		24
#define CLK_AUD_3RD_DAC			25
#define CLK_AUD_3RD_DAC_PREDIS		26
#define CLK_AUD_3RD_DAC_TML		27
#define CLK_AUD_3RD_DAC_HIRES		28
#define CLK_AUD_NR_CLK			29

/* APU_CONN */
#define	CLK_APU_CONN_APU		1
#define	CLK_APU_CONN_AHB		2
#define	CLK_APU_CONN_AXI		3
#define	CLK_APU_CONN_ISP		4
#define	CLK_APU_CONN_CAM_ADL		5
#define	CLK_APU_CONN_IMG_ADL		6
#define CLK_APU_CONN_EMI_26M		7
#define CLK_APU_CONN_VPU_UDI		8
#define CLK_APU_CONN_NR_CLK		9

/* APU_CORE0 */
#define	CLK_APU0_JTAG			1
#define	CLK_APU0_AXI_M			2
#define	CLK_APU0_APU			3
#define CLK_APU0_NR_CLK			4

/* APU_CORE1 */
#define	CLK_APU1_JTAG			1
#define	CLK_APU1_AXI_M			2
#define	CLK_APU1_APU			3
#define CLK_APU1_NR_CLK			4

/* APU_VCORE */
#define	CLK_APU_VCORE_AHB		1
#define	CLK_APU_VCORE_AXI		2
#define	CLK_APU_VCORE_ADL		3
#define	CLK_APU_VCORE_QOS		4
#define CLK_APU_VCORE_NR_CLK		5

/* APU_MDLA */
#define	CLK_APU_MDLA_APB		1
#define	CLK_APU_MDLA_B0			2
#define	CLK_APU_MDLA_B1			3
#define	CLK_APU_MDLA_B2			4
#define	CLK_APU_MDLA_B3			5
#define	CLK_APU_MDLA_B4			6
#define	CLK_APU_MDLA_B5			7
#define	CLK_APU_MDLA_B6			8
#define	CLK_APU_MDLA_B7			9
#define	CLK_APU_MDLA_B8			10
#define	CLK_APU_MDLA_B9			11
#define	CLK_APU_MDLA_B10		12
#define	CLK_APU_MDLA_B11		13
#define	CLK_APU_MDLA_B12		14
#define	CLK_APU_MDLA_NR_CLK		15

/* SCP_SYS */
#define SCP_SYS_MD1			1
#define SCP_SYS_CONN			2
#define SCP_SYS_DIS			3
#define SCP_SYS_MFG1			4
#define SCP_SYS_ISP			5
#define SCP_SYS_VEN			6
#define SCP_SYS_MFG0			7
#define SCP_SYS_AUD			8
#define SCP_SYS_CAM			9
#define SCP_SYS_MFG3			10
#define SCP_SYS_MFG2			11
#define SCP_SYS_IPE			12
#define SCP_SYS_VDE			13
#define SCP_SYS_VPU_VCORE_DORMANT	14
#define SCP_SYS_VPU_VCORE_SHUTDOWN	15
#define SCP_SYS_VPU_CORE0_DORMANT	16
#define SCP_SYS_VPU_CORE0_SHUTDOWN	17
#define SCP_SYS_VPU_CORE1_DORMANT	18
#define SCP_SYS_VPU_CORE1_SHUTDOWN	19
#define SCP_SYS_VPU_CONN_DORMANT	20
#define SCP_SYS_VPU_CONN_SHUTDOWN	21
#define SCP_SYS_VPU_CORE2_DORMANT	22
#define SCP_SYS_VPU_CORE2_SHUTDOWN	23
#define SCP_SYS_MFG4			24
#define SCP_SYS_CONN_W			25
#define SCP_NR_SYSS			26


/*
 * compatible with CLK name define in kernel-4.9,
 * using new clk name redefine old one.
 */

/* TOPCKGEN */
#define TOP_MUX_AXI			CLK_TOP_AXI
#define TOP_MUX_MM			CLK_TOP_MM
#define TOP_MUX_CAM			CLK_TOP_CAM
#define TOP_MUX_MFG			CLK_TOP_MFG
#define TOP_MUX_CAMTG		CLK_TOP_CAMTG
#define TOP_MUX_UART		CLK_TOP_UART
#define TOP_MUX_SPI			CLK_TOP_SPI
#define TOP_MUX_MSDC50_0_HCLK	CLK_TOP_MSDC50_0_HCLK
#define TOP_MUX_MSDC50_0	CLK_TOP_MSDC50_0
#define TOP_MUX_MSDC30_1	CLK_TOP_MSDC30_1
#define TOP_MUX_MSDC30_2	CLK_TOP_MSDC30_2
#define TOP_MUX_AUDIO		CLK_TOP_AUD
#define TOP_MUX_AUD_INTBUS	CLK_TOP_AUD_INTBUS
#define TOP_MUX_FPWRAP_ULPOSC	CLK_TOP_FPWRAP_ULPOSC
#define TOP_MUX_SCP			CLK_TOP_SCP
#define TOP_MUX_ATB			CLK_TOP_ATB
#define TOP_MUX_SSPM		CLK_TOP_SSPM
#define TOP_MUX_DPI0		CLK_TOP_DPI0
#define TOP_MUX_SCAM		CLK_TOP_SCAM
#define TOP_MUX_AUD_1		CLK_TOP_AUD_1
#define TOP_MUX_AUD_2		CLK_TOP_AUD_2
#define TOP_MUX_DISP_PWM	CLK_TOP_DISP_PWM
#define TOP_MUX_SSUSB_TOP_XHCI	CLK_TOP_SSUSB_TOP_XHCI
#define TOP_MUX_USB_TOP		CLK_TOP_USB_TOP
#define TOP_MUX_SPM			CLK_TOP_SPM
#define TOP_MUX_I2C			CLK_TOP_I2C
#define TOP_MUX_F52M_MFG	CLK_TOP_F52M_MFG
#define TOP_MUX_SENINF		CLK_TOP_SENINF
#define TOP_MUX_DXCC		CLK_TOP_DXCC
#define TOP_MUX_CAMTG2		CLK_TOP_CAMTG2
#define TOP_MUX_AUD_ENG1	CLK_TOP_AUD_ENG1
#define TOP_MUX_AUD_ENG2	CLK_TOP_AUD_ENG2
#define TOP_MUX_FAES_UFSFDE	CLK_TOP_FAES_UFSFDE
#define TOP_MUX_FUFS		CLK_TOP_FUFS
#define TOP_MUX_IMG			CLK_TOP_IMG
#define TOP_MUX_DSP			CLK_TOP_DSP
#define TOP_MUX_DSP1		CLK_TOP_DSP1
#define TOP_MUX_DSP2		CLK_TOP_DSP2
#define TOP_MUX_IPU_IF		CLK_TOP_IPU_IF
#define TOP_MUX_CAMTG3		CLK_TOP_CAMTG3
#define TOP_MUX_CAMTG4		CLK_TOP_CAMTG4
#define TOP_MUX_PMICSPI		CLK_TOP_PMICSPI
#define TOP_MAINPLL_CK		CLK_TOP_MAINPLL_CK
#define TOP_MAINPLL_D2		CLK_TOP_MAINPLL_D2
#define TOP_MAINPLL_D3		CLK_TOP_MAINPLL_D3
#define TOP_MAINPLL_D5		CLK_TOP_MAINPLL_D5
#define TOP_MAINPLL_D7		CLK_TOP_MAINPLL_D7
#define TOP_MAINPLL_D2_D2	CLK_TOP_MAINPLL_D2_D2
#define TOP_MAINPLL_D2_D4	CLK_TOP_MAINPLL_D2_D4
#define TOP_MAINPLL_D2_D8	CLK_TOP_MAINPLL_D2_D8
#define TOP_MAINPLL_D2_D16	CLK_TOP_MAINPLL_D2_D16
#define TOP_MAINPLL_D3_D2	CLK_TOP_MAINPLL_D3_D2
#define TOP_MAINPLL_D3_D4	CLK_TOP_MAINPLL_D3_D4
#define TOP_MAINPLL_D3_D8	CLK_TOP_MAINPLL_D3_D8
#define TOP_MAINPLL_D5_D2	CLK_TOP_MAINPLL_D5_D2
#define TOP_MAINPLL_D5_D4	CLK_TOP_MAINPLL_D5_D4
#define TOP_MAINPLL_D7_D2	CLK_TOP_MAINPLL_D7_D2
#define TOP_MAINPLL_D7_D4	CLK_TOP_MAINPLL_D7_D4
#define TOP_UNIVPLL_CK		CLK_TOP_UNIVPLL_CK
#define TOP_UNIVPLL_D2		CLK_TOP_UNIVPLL_D2
#define TOP_UNIVPLL_D3		CLK_TOP_UNIVPLL_D3
#define TOP_UNIVPLL_D5		CLK_TOP_UNIVPLL_D5
#define TOP_UNIVPLL_D7		CLK_TOP_UNIVPLL_D7
#define TOP_UNIVPLL_D2_D2	CLK_TOP_UNIVPLL_D2_D2
#define TOP_UNIVPLL_D2_D4	CLK_TOP_UNIVPLL_D2_D4
#define TOP_UNIVPLL_D2_D8	CLK_TOP_UNIVPLL_D2_D8
#define TOP_UNIVPLL_D3_D2	CLK_TOP_UNIVPLL_D3_D2
#define TOP_UNIVPLL_D3_D4	CLK_TOP_UNIVPLL_D3_D4
#define TOP_UNIVPLL_D3_D8	CLK_TOP_UNIVPLL_D3_D8
#define TOP_UNIVPLL_D5_D2	CLK_TOP_UNIVPLL_D5_D2
#define TOP_UNIVPLL_D5_D4	CLK_TOP_UNIVPLL_D5_D4
#define TOP_UNIVPLL_D5_D8	CLK_TOP_UNIVPLL_D5_D8
#define TOP_APLL1_CK		CLK_TOP_APLL1_CK
#define TOP_APLL1_D2		CLK_TOP_APLL1_D2
#define TOP_APLL1_D4		CLK_TOP_APLL1_D4
#define TOP_APLL1_D8		CLK_TOP_APLL1_D8
#define TOP_APLL2_CK		CLK_TOP_APLL2_CK
#define TOP_APLL2_D2		CLK_TOP_APLL2_D2
#define TOP_APLL2_D4		CLK_TOP_APLL2_D4
#define TOP_APLL2_D8		CLK_TOP_APLL2_D8
#define TOP_TVDPLL_CK		CLK_TOP_TVDPLL_CK
#define TOP_TVDPLL_D2		CLK_TOP_TVDPLL_D2
#define TOP_TVDPLL_D4		CLK_TOP_TVDPLL_D4
#define TOP_TVDPLL_D8		CLK_TOP_TVDPLL_D8
#define TOP_TVDPLL_D16		CLK_TOP_TVDPLL_D16
#define TOP_MSDCPLL_CK		CLK_TOP_MSDCPLL_CK
#define TOP_MSDCPLL_D2		CLK_TOP_MSDCPLL_D2
#define TOP_MSDCPLL_D4		CLK_TOP_MSDCPLL_D4
#define TOP_MSDCPLL_D8		CLK_TOP_MSDCPLL_D8
#define TOP_MSDCPLL_D16		CLK_TOP_MSDCPLL_D16
#define TOP_AD_OSC_CK		CLK_TOP_AD_OSC_CK
#define TOP_OSC_D2			CLK_TOP_OSC_D2
#define TOP_OSC_D4			CLK_TOP_OSC_D4
#define TOP_OSC_D8			CLK_TOP_OSC_D8
#define TOP_OSC_D16			CLK_TOP_OSC_D16
#define TOP_F26M_CK_D2		CLK_TOP_F26M_CK_D2
#define TOP_MFGPLL_CK		CLK_TOP_MFGPLL_CK
#define TOP_UNIVP_192M_CK	CLK_TOP_UNIVP_192M_CK
#define TOP_UNIVP_192M_D2	CLK_TOP_UNIVP_192M_D2
#define TOP_UNIVP_192M_D4	CLK_TOP_UNIVP_192M_D4
#define TOP_UNIVP_192M_D8	CLK_TOP_UNIVP_192M_D8
#define TOP_UNIVP_192M_D16	CLK_TOP_UNIVP_192M_D16
#define TOP_UNIVP_192M_D32	CLK_TOP_UNIVP_192M_D32
#define TOP_MMPLL_CK		CLK_TOP_MMPLL_CK
#define TOP_MMPLL_D4		CLK_TOP_MMPLL_D4
#define TOP_MMPLL_D4_D2		CLK_TOP_MMPLL_D4_D2
#define TOP_MMPLL_D4_D4		CLK_TOP_MMPLL_D4_D4
#define TOP_MMPLL_D5		CLK_TOP_MMPLL_D5
#define TOP_MMPLL_D5_D2		CLK_TOP_MMPLL_D5_D2
#define TOP_MMPLL_D5_D4		CLK_TOP_MMPLL_D5_D4
#define TOP_MMPLL_D6		CLK_TOP_MMPLL_D6
#define TOP_MMPLL_D7		CLK_TOP_MMPLL_D7
#define TOP_CLK26M			CLK_TOP_CLK26M
#define TOP_CLK13M			CLK_TOP_CLK13M
#define TOP_MUX_ADSP		CLK_TOP_ADSP
#define TOP_MUX_DPMAIF		CLK_TOP_DPMAIF
#define TOP_MUX_VENC		CLK_TOP_VENC
#define TOP_MUX_VDEC		CLK_TOP_VDEC
#define TOP_MUX_CAMTM		CLK_TOP_CAMTM
#define TOP_MUX_PWM			CLK_TOP_PWM
#define TOP_ADSPPLL_CK		CLK_TOP_ADSPPLL_CK
#define TOP_I2S0_M_SEL		CLK_TOP_I2S0_M_SEL
#define TOP_I2S1_M_SEL		CLK_TOP_I2S1_M_SEL
#define TOP_I2S2_M_SEL		CLK_TOP_I2S2_M_SEL
#define TOP_I2S3_M_SEL		CLK_TOP_I2S3_M_SEL
#define TOP_I2S4_M_SEL		CLK_TOP_I2S4_M_SEL
#define TOP_I2S5_M_SEL		CLK_TOP_I2S5_M_SEL
#define TOP_APLL12_DIV0		CLK_TOP_APLL12_DIV0
#define TOP_APLL12_DIV1		CLK_TOP_APLL12_DIV1
#define TOP_APLL12_DIV2		CLK_TOP_APLL12_DIV2
#define TOP_APLL12_DIV3		CLK_TOP_APLL12_DIV3
#define TOP_APLL12_DIV4		CLK_TOP_APLL12_DIV4
#define TOP_APLL12_DIVB		CLK_TOP_APLL12_DIVB
#define TOP_APLL12_DIV5		CLK_TOP_APLL12_DIV5
#define TOP_MUX_IPE			CLK_TOP_IPE
#define TOP_MUX_DPE			CLK_TOP_DPE
#define TOP_MUX_CCU			CLK_TOP_CCU
#define TOP_MUX_DSP3		CLK_TOP_DSP3
#define TOP_MUX_SENINF1		CLK_TOP_SENINF1
#define TOP_MUX_SENINF2		CLK_TOP_SENINF2
#define TOP_MUX_AUDIO_H		CLK_TOP_AUD_H
#define TOP_MUX_CAMTG5		CLK_TOP_CAMTG5
#define TOP_TVDPLL_MAINPLL_D2_CK	CLK_TOP_TVDPLL_MAINPLL_D2_CK
#define TOP_AD_OSC2_CK		CLK_TOP_AD_OSC2_CK
#define TOP_OSC2_D2			CLK_TOP_OSC2_D2
#define TOP_OSC2_D3			CLK_TOP_OSC2_D3
#define TOP_FMEM_466M_CK	CLK_TOP_FMEM_466M_CK
#define TOP_ADSPPLL_D4		CLK_TOP_ADSPPLL_D4
#define TOP_ADSPPLL_D5		CLK_TOP_ADSPPLL_D5
#define TOP_ADSPPLL_D6		CLK_TOP_ADSPPLL_D6
#define TOP_OSC_D10			CLK_TOP_OSC_D10
#define TOP_UNIVPLL_D3_D16	CLK_TOP_UNIVPLL_D3_D16
#define TOP_NR_CLK			CLK_TOP_NR_CLK

/* APMIXED */
#define APMIXED_ARMPLL_LL	CLK_APMIXED_ARMPLL_LL
#define APMIXED_ARMPLL_BL	CLK_APMIXED_ARMPLL_BL
#define APMIXED_ARMPLL_BB	CLK_APMIXED_ARMPLL_BB
#define APMIXED_CCIPLL		CLK_APMIXED_CCIPLL
#define APMIXED_MAINPLL		CLK_APMIXED_MAINPLL
#define APMIXED_UNIV2PLL	CLK_APMIXED_UNIV2PLL
#define APMIXED_MSDCPLL		CLK_APMIXED_MSDCPLL
#define APMIXED_ADSPPLL		CLK_APMIXED_ADSPPLL
#define APMIXED_MMPLL		CLK_APMIXED_MMPLL
#define APMIXED_MFGPLL		CLK_APMIXED_MFGPLL
#define APMIXED_TVDPLL		CLK_APMIXED_TVDPLL
#define APMIXED_APLL1		CLK_APMIXED_APLL1
#define APMIXED_APLL2		CLK_APMIXED_APLL2
#define APMIXED_SSUSB26M	CLK_APMIXED_SSUSB26M
#define APMIXED_APPLL26M	CLK_APMIXED_APPLL26M
#define APMIXED_MIPIC0_26M	CLK_APMIXED_MIPIC0_26M
#define APMIXED_MDPLLGP26M	CLK_APMIXED_MDPLLGP26M
#define APMIXED_MMSYS_F26M	CLK_APMIXED_MM_F26M
#define APMIXED_UFS26M		CLK_APMIXED_UFS26M
#define APMIXED_MIPIC1_26M	CLK_APMIXED_MIPIC1_26M
#define APMIXED_MEMPLL26M	CLK_APMIXED_MEMPLL26M
#define APMIXED_CLKSQ_LVPLL_26M		CLK_APMIXED_CLKSQ_LVPLL_26M
#define APMIXED_MIPID0_26M	CLK_APMIXED_MIPID0_26M
#define APMIXED_MIPID1_26M	CLK_APMIXED_MIPID1_26M
#define APMIXED_NR_CLK		CLK_APMIXED_NR_CLK

/* CAMSYS */
#define CAMSYS_LARB10_CGPDN		CLK_CAM_LARB10
#define CAMSYS_DFP_VAD_CGPDN	CLK_CAM_DFP_VAD
#define CAMSYS_LARB11_CGPDN		CLK_CAM_LARB11
#define CAMSYS_LARB9_CGPDN		CLK_CAM_LARB9
#define CAMSYS_CAM_CGPDN		CLK_CAM_CAM
#define CAMSYS_CAMTG_CGPDN		CLK_CAM_CAMTG
#define CAMSYS_SENINF_CGPDN		CLK_CAM_SENINF
#define CAMSYS_CAMSV0_CGPDN		CLK_CAM_CAMSV0
#define CAMSYS_CAMSV1_CGPDN		CLK_CAM_CAMSV1
#define CAMSYS_CAMSV2_CGPDN		CLK_CAM_CAMSV2
#define CAMSYS_CAMSV3_CGPDN		CLK_CAM_CAMSV3
#define CAMSYS_CCU_CGPDN		CLK_CAM_CCU
#define CAMSYS_FAKE_ENG_CGPDN	CLK_CAM_FAKE_ENG
#define CAMSYS_NR_CLK			CLK_CAM_NR_CLK

/* INFRACFG_AO */
#define INFRACFG_AO_PMIC_CG_TMR		CLK_INFRA_PMIC_TMR
#define INFRACFG_AO_PMIC_CG_AP		CLK_INFRA_PMIC_AP
#define INFRACFG_AO_PMIC_CG_MD		CLK_INFRA_PMIC_MD
#define INFRACFG_AO_PMIC_CG_CONN	CLK_INFRA_PMIC_CONN
#define INFRACFG_AO_SCPSYS_CG		CLK_INFRA_SCPSYS
#define INFRACFG_AO_SEJ_CG			CLK_INFRA_SEJ
#define INFRACFG_AO_APXGPT_CG		CLK_INFRA_APXGPT
#define INFRACFG_AO_ICUSB_CG		CLK_INFRA_ICUSB
#define INFRACFG_AO_GCE_CG			CLK_INFRA_GCE
#define INFRACFG_AO_THERM_CG		CLK_INFRA_THERM
#define INFRACFG_AO_I2C0_CG			CLK_INFRA_I2C0
#define INFRACFG_AO_I2C1_CG			CLK_INFRA_I2C1
#define INFRACFG_AO_I2C2_CG			CLK_INFRA_I2C2
#define INFRACFG_AO_I2C3_CG			CLK_INFRA_I2C3
#define INFRACFG_AO_PWM_HCLK_CG		CLK_INFRA_PWM_HCLK
#define INFRACFG_AO_PWM1_CG			CLK_INFRA_PWM1
#define INFRACFG_AO_PWM2_CG			CLK_INFRA_PWM2
#define INFRACFG_AO_PWM3_CG			CLK_INFRA_PWM3
#define INFRACFG_AO_PWM4_CG			CLK_INFRA_PWM4
#define INFRACFG_AO_PWM_CG			CLK_INFRA_PWM
#define INFRACFG_AO_UART0_CG		CLK_INFRA_UART0
#define INFRACFG_AO_UART1_CG		CLK_INFRA_UART1
#define INFRACFG_AO_UART2_CG		CLK_INFRA_UART2
#define INFRACFG_AO_UART3_CG		CLK_INFRA_UART3
#define INFRACFG_AO_GCE_26M_CG		CLK_INFRA_GCE_26M
#define INFRACFG_AO_CQ_DMA_FPC_CG	CLK_INFRA_CQ_DMA_FPC
#define INFRACFG_AO_BTIF_CG			CLK_INFRA_BTIF
#define INFRACFG_AO_SPI0_CG			CLK_INFRA_SPI0
#define INFRACFG_AO_MSDC0_CG		CLK_INFRA_MSDC0
#define INFRACFG_AO_MSDC1_CG		CLK_INFRA_MSDC1
#define INFRACFG_AO_MSDC2_CG		CLK_INFRA_MSDC2
#define INFRACFG_AO_MSDC0_SCK_CG	CLK_INFRA_MSDC0_SCK
#define INFRACFG_AO_DVFSRC_CG		CLK_INFRA_DVFSRC
#define INFRACFG_AO_GCPU_CG			CLK_INFRA_GCPU
#define INFRACFG_AO_TRNG_CG			CLK_INFRA_TRNG
#define INFRACFG_AO_AUXADC_CG		CLK_INFRA_AUXADC
#define INFRACFG_AO_CPUM_CG			CLK_INFRA_CPUM
#define INFRACFG_AO_CCIF1_AP_CG		CLK_INFRA_CCIF1_AP
#define INFRACFG_AO_CCIF1_MD_CG		CLK_INFRA_CCIF1_MD
#define INFRACFG_AO_AUXADC_MD_CG	CLK_INFRA_AUXADC_MD
#define INFRACFG_AO_MSDC1_SCK_CG	CLK_INFRA_MSDC1_SCK
#define INFRACFG_AO_MSDC2_SCK_CG	CLK_INFRA_MSDC2_SCK
#define INFRACFG_AO_AP_DMA_CG		CLK_INFRA_AP_DMA
#define INFRACFG_AO_XIU_CG			CLK_INFRA_XIU
#define INFRACFG_AO_DEVICE_APC_CG	CLK_INFRA_DEVICE_APC
#define INFRACFG_AO_CCIF_AP_CG		CLK_INFRA_CCIF_AP
#define INFRACFG_AO_DEBUGSYS_CG		CLK_INFRA_DEBUGSYS
#define INFRACFG_AO_AUDIO_CG		CLK_INFRA_AUD
#define INFRACFG_AO_CCIF_MD_CG		CLK_INFRA_CCIF_MD
#define INFRACFG_AO_DXCC_SEC_CORE_CG	CLK_INFRA_DXCC_SEC_CORE
#define INFRACFG_AO_DXCC_AO_CG		CLK_INFRA_DXCC_AO
#define INFRACFG_AO_DRAMC_F26M_CG	CLK_INFRA_DRAMC_F26M
#define INFRACFG_AO_IRTX_CG			CLK_INFRA_IRTX
#define INFRACFG_AO_DISP_PWM_CG		CLK_INFRA_DISP_PWM
#define INFRACFG_AO_DPMAIF_CK		CLK_INFRA_DPMAIF_CK
#define INFRACFG_AO_AUDIO_26M_BCLK_CK	CLK_INFRA_AUD_26M_BCLK_CK
#define INFRACFG_AO_SPI1_CG			CLK_INFRA_SPI1
#define INFRACFG_AO_I2C4_CG			CLK_INFRA_I2C4
#define INFRACFG_AO_MODEM_TEMP_SHARE_CG	CLK_INFRA_MODEM_TEMP_SHARE
#define INFRACFG_AO_SPI2_CG			CLK_INFRA_SPI2
#define INFRACFG_AO_SPI3_CG			CLK_INFRA_SPI3
#define INFRACFG_AO_UNIPRO_SCK_CG	CLK_INFRA_UNIPRO_SCK
#define INFRACFG_AO_UNIPRO_TICK_CG	CLK_INFRA_UNIPRO_TICK
#define INFRACFG_AO_UFS_MP_SAP_BCLK_CG	CLK_INFRA_UFS_MP_SAP_BCLK
#define INFRACFG_AO_MD32_BCLK_CG	CLK_INFRA_MD32_BCLK
#define INFRACFG_AO_SSPM_CG			CLK_INFRA_SSPM
#define INFRACFG_AO_UNIPRO_MBIST_CG	CLK_INFRA_UNIPRO_MBIST
#define INFRACFG_AO_SSPM_BUS_HCLK_CG	CLK_INFRA_SSPM_BUS_HCLK
#define INFRACFG_AO_I2C5_CG			CLK_INFRA_I2C5
#define INFRACFG_AO_I2C5_ARBITER_CG	CLK_INFRA_I2C5_ARBITER
#define INFRACFG_AO_I2C5_IMM_CG		CLK_INFRA_I2C5_IMM
#define INFRACFG_AO_I2C1_ARBITER_CG	CLK_INFRA_I2C1_ARBITER
#define INFRACFG_AO_I2C1_IMM_CG		CLK_INFRA_I2C1_IMM
#define INFRACFG_AO_I2C2_ARBITER_CG	CLK_INFRA_I2C2_ARBITER
#define INFRACFG_AO_I2C2_IMM_CG		CLK_INFRA_I2C2_IMM
#define INFRACFG_AO_SPI4_CG			CLK_INFRA_SPI4
#define INFRACFG_AO_SPI5_CG			CLK_INFRA_SPI5
#define INFRACFG_AO_CQ_DMA_CG		CLK_INFRA_CQ_DMA
#define INFRACFG_AO_UFS_CG			CLK_INFRA_UFS
#define INFRACFG_AO_AES_UFSFDE_CG	CLK_INFRA_AES_UFSFDE
#define INFRACFG_AO_UFS_TICK_CG		CLK_INFRA_UFS_TICK
#define INFRACFG_AO_MSDC0_SELF_CG	CLK_INFRA_MSDC0_SELF
#define INFRACFG_AO_MSDC1_SELF_CG	CLK_INFRA_MSDC1_SELF
#define INFRACFG_AO_MSDC2_SELF_CG	CLK_INFRA_MSDC2_SELF
#define INFRACFG_AO_SSPM_26M_SELF_CG	CLK_INFRA_SSPM_26M_SELF
#define INFRACFG_AO_SSPM_32K_SELF_CG	CLK_INFRA_SSPM_32K_SELF
#define INFRACFG_AO_UFS_AXI_CG		CLK_INFRA_UFS_AXI
#define INFRACFG_AO_I2C6_CG			CLK_INFRA_I2C6
#define INFRACFG_AO_AP_MSDC0_CG		CLK_INFRA_AP_MSDC0
#define INFRACFG_AO_MD_MSDC0_CG		CLK_INFRA_MD_MSDC0
#define INFRACFG_AO_USB_CG			CLK_INFRA_USB
#define INFRACFG_AO_DEVMPU_BCLK_CG	CLK_INFRA_DEVMPU_BCLK
#define INFRACFG_AO_CCIF2_AP_CG		CLK_INFRA_CCIF2_AP
#define INFRACFG_AO_CCIF2_MD_CG		CLK_INFRA_CCIF2_MD
#define INFRACFG_AO_CCIF3_AP_CG		CLK_INFRA_CCIF3_AP
#define INFRACFG_AO_CCIF3_MD_CG		CLK_INFRA_CCIF3_MD
#define INFRACFG_AO_SEJ_F13M_CG		CLK_INFRA_SEJ_F13M
#define INFRACFG_AO_AES_BCLK_CG		CLK_INFRA_AES_BCLK
#define INFRACFG_AO_I2C7_CG			CLK_INFRA_I2C7
#define INFRACFG_AO_I2C8_CG			CLK_INFRA_I2C8
#define INFRACFG_AO_FBIST2FPC_CG	CLK_INFRA_FBIST2FPC
#define INFRACFG_AO_CCIF4_AP_CG		CLK_INFRA_CCIF4_AP
#define INFRACFG_AO_CCIF4_MD_CG		CLK_INFRA_CCIF4_MD
#define INFRACFG_AO_FADSP_CG		CLK_INFRA_FADSP
#define INFRACFG_AO_SSUSB_XHCI_CG	CLK_INFRA_SSUSB_XHCI
#define INFRACFG_AO_SPI6_CG			CLK_INFRA_SPI6
#define INFRACFG_AO_SPI7_CG			CLK_INFRA_SPI7
#define INFRACFG_AO_NR_CLK			CLK_INFRA_NR_CLK

/* MFGCFG */
#define MFGCFG_BG3D			CLK_MFGCFG_BG3D
#define MFGCFG_NR_CLK		CLK_MFGCFG_NR_CLK

/* IMG */
#define	IMG_WPE_A		CLK_IMG_WPE_A
#define	IMG_MFB			CLK_IMG_MFB
#define	IMG_DIP			CLK_IMG_DIP
#define	IMG_LARB6		CLK_IMG_LARB6
#define	IMG_LARB5		CLK_IMG_LARB5
#define IMG_NR_CLK		CLK_IMG_NR_CLK

/* IPE */
#define	IPE_LARB7		CLK_IPE_LARB7
#define	IPE_LARB8		CLK_IPE_LARB8
#define	IPE_SMI_SUBCOM	CLK_IPE_SMI_SUBCOM
#define	IPE_FD			CLK_IPE_FD
#define	IPE_FE			CLK_IPE_FE
#define IPE_RSC			CLK_IPE_RSC
#define IPE_DPE			CLK_IPE_DPE
#define IPE_NR_CLK		CLK_IPE_NR_CLK

/* MMSYS_CONFIG */
#define	MMSYS_SMI_COMMON		CLK_MM_SMI_COMMON
#define	MMSYS_SMI_LARB0			CLK_MM_SMI_LARB0
#define	MMSYS_SMI_LARB1			CLK_MM_SMI_LARB1
#define	MMSYS_GALS_COMM0		CLK_MM_GALS_COMM0
#define	MMSYS_GALS_COMM1		CLK_MM_GALS_COMM1
#define	MMSYS_GALS_CCU2MM		CLK_MM_GALS_CCU2MM
#define	MMSYS_GALS_IPU12MM		CLK_MM_GALS_IPU12MM
#define	MMSYS_GALS_IMG2MM		CLK_MM_GALS_IMG2MM
#define	MMSYS_GALS_CAM2MM		CLK_MM_GALS_CAM2MM
#define	MMSYS_GALS_IPU2MM		CLK_MM_GALS_IPU2MM
#define	MMSYS_MDP_DL_TXCK		CLK_MM_MDP_DL_TXCK
#define	MMSYS_IPU_DL_TXCK		CLK_MM_IPU_DL_TXCK
#define	MMSYS_MDP_RDMA0			CLK_MM_MDP_RDMA0
#define	MMSYS_MDP_RDMA1			CLK_MM_MDP_RDMA1
#define	MMSYS_MDP_RSZ0			CLK_MM_MDP_RSZ0
#define	MMSYS_MDP_RSZ1			CLK_MM_MDP_RSZ1
#define	MMSYS_MDP_TDSHP			CLK_MM_MDP_TDSHP
#define	MMSYS_MDP_WROT0			CLK_MM_MDP_WROT0
#define	MMSYS_FAKE_ENG			CLK_MM_FAKE_ENG
#define	MMSYS_DISP_OVL0			CLK_MM_DISP_OVL0
#define	MMSYS_DISP_OVL0_2L		CLK_MM_DISP_OVL0_2L
#define	MMSYS_DISP_OVL1_2L		CLK_MM_DISP_OVL1_2L
#define	MMSYS_DISP_RDMA0		CLK_MM_DISP_RDMA0
#define	MMSYS_DISP_RDMA1		CLK_MM_DISP_RDMA1
#define	MMSYS_DISP_WDMA0		CLK_MM_DISP_WDMA0
#define	MMSYS_DISP_COLOR0		CLK_MM_DISP_COLOR0
#define	MMSYS_DISP_CCORR0		CLK_MM_DISP_CCORR0
#define	MMSYS_DISP_AAL0			CLK_MM_DISP_AAL0
#define	MMSYS_DISP_GAMMA0		CLK_MM_DISP_GAMMA0
#define	MMSYS_DISP_DITHER0		CLK_MM_DISP_DITHER0
#define	MMSYS_DISP_SPLIT		CLK_MM_DISP_SPLIT
#define	MMSYS_DSI0_MM_CK		CLK_MM_DSI0_MM_CK
#define	MMSYS_DSI0_IF_CK		CLK_MM_DSI0_IF_CK
#define	MMSYS_DPI_MM_CK			CLK_MM_DPI_MM_CK
#define	MMSYS_DPI_IF_CK			CLK_MM_DPI_IF_CK
#define	MMSYS_FAKE_ENG2			CLK_MM_FAKE_ENG2
#define	MMSYS_MDP_DL_RX_CK		CLK_MM_MDP_DL_RX_CK
#define	MMSYS_IPU_DL_RX_CK		CLK_MM_IPU_DL_RX_CK
#define	MMSYS_26M				CLK_MM_26M
#define	MMSYS_MMSYS_R2Y			CLK_MM_MM_R2Y
#define	MMSYS_DISP_RSZ			CLK_MM_DISP_RSZ
#define MMSYS_MDP_WDMA0			CLK_MM_MDP_WDMA0
#define MMSYS_MDP_AAL			CLK_MM_MDP_AAL
#define MMSYS_MDP_HDR			CLK_MM_MDP_HDR
#define MMSYS_DBI_MM_CK			CLK_MM_DBI_MM_CK
#define MMSYS_DBI_IF_CK			CLK_MM_DBI_IF_CK
#define	MMSYS_MDP_WROT1			CLK_MM_MDP_WROT1
#define	MMSYS_DISP_POSTMASK0	CLK_MM_DISP_POSTMASK0
#define	MMSYS_DISP_HRT_BW		CLK_MM_DISP_HRT_BW
#define	MMSYS_DISP_OVL_FBDC		CLK_MM_DISP_OVL_FBDC
#define MMSYS_CONFIG_NR_CLK		CLK_MM_CONFIG_NR_CLK

/* VDEC_GCON */
#define	VDEC_VDEC			CLK_VDEC_VDEC
#define	VDEC_LARB1			CLK_VDEC_LARB1
#define VDEC_GCON_NR_CLK	CLK_VDEC_GCON_NR_CLK

/* VENC_GCON */
#define VENC_GCON_LARB		CLK_VENC_GCON_LARB
#define VENC_GCON_VENC		CLK_VENC_GCON_VENC
#define VENC_GCON_JPGENC	CLK_VENC_GCON_JPGENC
#define VENC_GCON_GALS		CLK_VENC_GCON_GALS
#define VENC_GCON_NR_CLK	CLK_VENC_GCON_NR_CLK

/* AUDIO */
#define	AUDIO_AFE			CLK_AUD_AFE
#define	AUDIO_22M			CLK_AUD_22M
#define	AUDIO_24M			CLK_AUD_24M
#define	AUDIO_APLL2_TUNER	CLK_AUD_APLL2_TUNER
#define	AUDIO_APLL_TUNER	CLK_AUD_APLL_TUNER
#define	AUDIO_TDM			CLK_AUD_TDM
#define	AUDIO_ADC			CLK_AUD_ADC
#define	AUDIO_DAC			CLK_AUD_DAC
#define	AUDIO_DAC_PREDIS	CLK_AUD_DAC_PREDIS
#define	AUDIO_TML			CLK_AUD_TML
#define	AUDIO_NLE			CLK_AUD_NLE
#define	AUDIO_I2S1_BCLK_SW	CLK_AUD_I2S1_BCLK_SW
#define AUDIO_I2S2_BCLK_SW	CLK_AUD_I2S2_BCLK_SW
#define AUDIO_I2S3_BCLK_SW	CLK_AUD_I2S3_BCLK_SW
#define AUDIO_I2S4_BCLK_SW	CLK_AUD_I2S4_BCLK_SW
#define AUDIO_I2S5_BCLK_SW	CLK_AUD_I2S5_BCLK_SW
#define	AUDIO_CONN_I2S_ASRC	CLK_AUD_CONN_I2S_ASRC
#define	AUDIO_GENERAL1_ASRC	CLK_AUD_GENERAL1_ASRC
#define	AUDIO_GENERAL2_ASRC	CLK_AUD_GENERAL2_ASRC
#define	AUDIO_DAC_HIRES		CLK_AUD_DAC_HIRES
#define AUDIO_PDN_ADDA6_ADC	CLK_AUD_PDN_ADDA6_ADC
#define AUDIO_ADC_HIRES		CLK_AUD_ADC_HIRES
#define AUDIO_ADC_HIRES_TML	CLK_AUD_ADC_HIRES_TML
#define AUDIO_ADDA6_ADC_HIRES	CLK_AUD_ADDA6_ADC_HIRES
#define AUDIO_3RD_DAC		CLK_AUD_3RD_DAC
#define AUDIO_3RD_DAC_PREDIS	CLK_AUD_3RD_DAC_PREDIS
#define AUDIO_3RD_DAC_TML	CLK_AUD_3RD_DAC_TML
#define AUDIO_3RD_DAC_HIRES	CLK_AUD_3RD_DAC_HIRES
#define AUDIO_NR_CLK		CLK_AUD_NR_CLK

/* APU_CONN */
#define	APU_CONN_APU_CG		CLK_APU_CONN_APU
#define	APU_CONN_AHB_CG		CLK_APU_CONN_AHB
#define	APU_CONN_AXI_CG		CLK_APU_CONN_AXI
#define	APU_CONN_ISP_CG		CLK_APU_CONN_ISP
#define	APU_CONN_CAM_ADL_CG	CLK_APU_CONN_CAM_ADL
#define	APU_CONN_IMG_ADL_CG	CLK_APU_CONN_IMG_ADL
#define APU_CONN_EMI_26M_CG	CLK_APU_CONN_EMI_26M
#define APU_CONN_VPU_UDI_CG	CLK_APU_CONN_VPU_UDI
#define APU_CONN_NR_CLK		CLK_APU_CONN_NR_CLK

/* APU_CORE0 */
#define	APU0_JTAG_CG		CLK_APU0_JTAG
#define	APU0_AXI_M_CG		CLK_APU0_AXI_M
#define	APU0_APU_CG			CLK_APU0_APU
#define APU0_NR_CLK			CLK_APU0_NR_CLK

/* APU_CORE1 */
#define	APU1_JTAG_CG		CLK_APU1_JTAG
#define	APU1_AXI_M_CG		CLK_APU1_AXI_M
#define	APU1_APU_CG			CLK_APU1_APU
#define APU1_NR_CLK			CLK_APU1_NR_CLK

/* APU_VCORE */
#define	APU_VCORE_AHB_CG	CLK_APU_VCORE_AHB
#define	APU_VCORE_AXI_CG	CLK_APU_VCORE_AXI
#define	APU_VCORE_ADL_CG	CLK_APU_VCORE_ADL
#define	APU_VCORE_QOS_CG	CLK_APU_VCORE_QOS
#define APU_VCORE_NR_CLK	CLK_APU_VCORE_NR_CLK

/* APU_MDLA */
#define	APU_MDLA_APB_CG		CLK_APU_MDLA_APB
#define	APU_MDLA_CG_B0		CLK_APU_MDLA_B0
#define	APU_MDLA_CG_B1		CLK_APU_MDLA_B1
#define	APU_MDLA_CG_B2		CLK_APU_MDLA_B2
#define	APU_MDLA_CG_B3		CLK_APU_MDLA_B3
#define	APU_MDLA_CG_B4		CLK_APU_MDLA_B4
#define	APU_MDLA_CG_B5		CLK_APU_MDLA_B5
#define	APU_MDLA_CG_B6		CLK_APU_MDLA_B6
#define	APU_MDLA_CG_B7		CLK_APU_MDLA_B7
#define	APU_MDLA_CG_B8		CLK_APU_MDLA_B8
#define	APU_MDLA_CG_B9		CLK_APU_MDLA_B9
#define	APU_MDLA_CG_B10		CLK_APU_MDLA_B10
#define	APU_MDLA_CG_B11		CLK_APU_MDLA_B11
#define	APU_MDLA_CG_B12		CLK_APU_MDLA_B12
#define	APU_MDLA_NR_CLK		CLK_APU_MDLA_NR_CLK

/* SCP_SYS */
#define SCP_SYS_AUDIO			SCP_SYS_AUD

#endif /* _DT_BINDINGS_CLK_MT6779_H */
