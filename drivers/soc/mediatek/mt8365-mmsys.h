/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef __SOC_MEDIATEK_MT8365_MMSYS_H
#define __SOC_MEDIATEK_MT8365_MMSYS_H

#define MT8365_DISP_REG_CONFIG_DISP_OVL0_MOUT_EN	0xf3c
#define MT8365_DISP_REG_CONFIG_DISP_RDMA0_SOUT_SEL	0xf4c
#define MT8365_DISP_REG_CONFIG_DISP_DITHER0_MOUT_EN	0xf50
#define MT8365_DISP_REG_CONFIG_DISP_RDMA0_SEL_IN	0xf54
#define MT8365_DISP_REG_CONFIG_DISP_RDMA0_RSZ0_SEL_IN	0xf60
#define MT8365_DISP_REG_CONFIG_DISP_COLOR0_SEL_IN	0xf64
#define MT8365_DISP_REG_CONFIG_DISP_DSI0_SEL_IN		0xf68

#define MT8365_RDMA0_SOUT_COLOR0			0x1
#define MT8365_DITHER_MOUT_EN_DSI0			0x1
#define MT8365_DSI0_SEL_IN_DITHER			0x1
#define MT8365_RDMA0_SEL_IN_OVL0			0x0
#define MT8365_RDMA0_RSZ0_SEL_IN_RDMA0			0x0
#define MT8365_DISP_COLOR_SEL_IN_COLOR0			0x0
#define MT8365_OVL0_MOUT_PATH0_SEL			BIT(0)

static const struct mtk_mmsys_routes mt8365_mmsys_routing_table[] = {
	{
		DDP_COMPONENT_OVL0, DDP_COMPONENT_RDMA0,
		MT8365_DISP_REG_CONFIG_DISP_OVL0_MOUT_EN,
		MT8365_OVL0_MOUT_PATH0_SEL, MT8365_OVL0_MOUT_PATH0_SEL
	},
	{
		DDP_COMPONENT_OVL0, DDP_COMPONENT_RDMA0,
		MT8365_DISP_REG_CONFIG_DISP_RDMA0_SEL_IN,
		MT8365_RDMA0_SEL_IN_OVL0, MT8365_RDMA0_SEL_IN_OVL0
	},
	{
		DDP_COMPONENT_RDMA0, DDP_COMPONENT_COLOR0,
		MT8365_DISP_REG_CONFIG_DISP_RDMA0_SOUT_SEL,
		MT8365_RDMA0_SOUT_COLOR0, MT8365_RDMA0_SOUT_COLOR0
	},
	{
		DDP_COMPONENT_COLOR0, DDP_COMPONENT_CCORR,
		MT8365_DISP_REG_CONFIG_DISP_COLOR0_SEL_IN,
		MT8365_DISP_COLOR_SEL_IN_COLOR0,MT8365_DISP_COLOR_SEL_IN_COLOR0
	},
	{
		DDP_COMPONENT_DITHER, DDP_COMPONENT_DSI0,
		MT8365_DISP_REG_CONFIG_DISP_DITHER0_MOUT_EN,
		MT8365_DITHER_MOUT_EN_DSI0, MT8365_DITHER_MOUT_EN_DSI0
	},
	{
		DDP_COMPONENT_DITHER, DDP_COMPONENT_DSI0,
		MT8365_DISP_REG_CONFIG_DISP_DSI0_SEL_IN,
		MT8365_DSI0_SEL_IN_DITHER, MT8365_DSI0_SEL_IN_DITHER
	},
	{
		DDP_COMPONENT_RDMA0, DDP_COMPONENT_COLOR0,
		MT8365_DISP_REG_CONFIG_DISP_RDMA0_RSZ0_SEL_IN,
		MT8365_RDMA0_RSZ0_SEL_IN_RDMA0, MT8365_RDMA0_RSZ0_SEL_IN_RDMA0
	},
};

#endif /* __SOC_MEDIATEK_MT8365_MMSYS_H */
