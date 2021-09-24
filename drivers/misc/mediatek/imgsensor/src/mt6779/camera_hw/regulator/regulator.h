/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2019 MediaTek Inc.
 */

#ifndef __IMGSENSOR_HW_REGULATOR_H__
#define __IMGSENSOR_HW_REGULATOR_H__

#include <linux/of.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/regulator/consumer.h>

#include "imgsensor_hw.h"
#include "imgsensor_common.h"
/*Henry.Chang@Cam.Drv add for 19551 20191010*/
#ifndef OPLUS_FEATURE_CAMERA_COMMON
#define OPLUS_FEATURE_CAMERA_COMMON
#endif
#include "imgsensor.h"

enum REGULATOR_VOLTAGE {
	REGULATOR_VOLTAGE_0    = 0,
	REGULATOR_VOLTAGE_1000 = 1000000,
	REGULATOR_VOLTAGE_1100 = 1100000,
	REGULATOR_VOLTAGE_1200 = 1200000,
	REGULATOR_VOLTAGE_1210 = 1210000,
	REGULATOR_VOLTAGE_1220 = 1220000,
	REGULATOR_VOLTAGE_1500 = 1500000,
	REGULATOR_VOLTAGE_1800 = 1800000,
	REGULATOR_VOLTAGE_2500 = 2500000,
	REGULATOR_VOLTAGE_2800 = 2800000,
	REGULATOR_VOLTAGE_2900 = 2900000,
};

enum REGULATOR_TYPE {
	REGULATOR_TYPE_VCAMA,
	REGULATOR_TYPE_VCAMD,
	REGULATOR_TYPE_VCAMIO,
#ifdef OPLUS_FEATURE_CAMERA_COMMON
	//Feiping.Li@Cam.Drv, 20200402, add for fix coverity -- 69275
	REGULATOR_TYPE_VCAMA_1,
	/* Henry.Chang@Camera.Driver add for vcamaf 20191016 */
	REGULATOR_TYPE_VCAMD_1,
	REGULATOR_TYPE_VCAMAF,
#endif
	REGULATOR_TYPE_MAX_NUM
};

struct REGULATOR_CTRL {
	char *pregulator_type;
};

struct REGULATOR {
	struct regulator *pregulator[
		IMGSENSOR_SENSOR_IDX_MAX_NUM][REGULATOR_TYPE_MAX_NUM];
	atomic_t          enable_cnt[
		IMGSENSOR_SENSOR_IDX_MAX_NUM][REGULATOR_TYPE_MAX_NUM];
};
#ifdef OPLUS_FEATURE_CAMERA_COMMON
/*Henry.Chang@Cam.Drv add for 19551 20191010*/
extern struct IMGSENSOR gimgsensor;
#endif
enum IMGSENSOR_RETURN imgsensor_hw_regulator_open(
	struct IMGSENSOR_HW_DEVICE **pdevice);

#endif

