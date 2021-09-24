// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 MediaTek Inc.
 */

#include "imgsensor_common.h"
#include "imgsensor_i2c.h"
#include <linux/ratelimit.h>

struct IMGSENSOR_I2C gi2c;
#ifdef OPLUS_FEATURE_CAMERA_COMMON
//weiriqin@Cam.drv 2020/06/18, Modify for async power-on-off, ALPS04924900
struct mutex i2c_resource_mutex;
#endif
static const struct i2c_device_id gi2c_dev_id[] = {
	{IMGSENSOR_I2C_DRV_NAME_0, 0},
	{IMGSENSOR_I2C_DRV_NAME_1, 0},
	{IMGSENSOR_I2C_DRV_NAME_2, 0},
	/**Feiping.Li@Cam.Drv, 20200401, modify for 19537**/
	{IMGSENSOR_I2C_DRV_NAME_3, 0},
	{IMGSENSOR_I2C_DRV_NAME_4, 0},
	{IMGSENSOR_I2C_DRV_NAME_5, 0},
	{}
};

#ifdef CONFIG_OF
static const struct of_device_id gof_device_id_0[] = {
	{.compatible = IMGSENSOR_I2C_OF_DRV_NAME_0,},
	{}
};

static const struct of_device_id gof_device_id_1[] = {
	{.compatible = IMGSENSOR_I2C_OF_DRV_NAME_1,},
	{}
};

static const struct of_device_id gof_device_id_2[] = {
	{.compatible = IMGSENSOR_I2C_OF_DRV_NAME_2,},
	{}
};
/**Feiping.Li@Cam.Drv, 20200401, modify for 19537**/
static const struct of_device_id gof_device_id_3[] = {
	{.compatible = IMGSENSOR_I2C_OF_DRV_NAME_3,},
	{}
};
static const struct of_device_id gof_device_id_4[] = {
	{.compatible = IMGSENSOR_I2C_OF_DRV_NAME_4,},
	{}
};
static const struct of_device_id gof_device_id_5[] = {
	{.compatible = IMGSENSOR_I2C_OF_DRV_NAME_5,},
	{}
};
#endif

static int imgsensor_i2c_probe_0(struct i2c_client *client,
				const struct i2c_device_id *id)
{
	gi2c.inst[IMGSENSOR_I2C_DEV_0].pi2c_client = client;
	return 0;
}

static int imgsensor_i2c_probe_1(struct i2c_client *client,
				const struct i2c_device_id *id)
{
	gi2c.inst[IMGSENSOR_I2C_DEV_1].pi2c_client = client;
	return 0;
}

static int imgsensor_i2c_probe_2(struct i2c_client *client,
				const struct i2c_device_id *id)
{
	gi2c.inst[IMGSENSOR_I2C_DEV_2].pi2c_client = client;
	return 0;
}
/**Feiping.Li@Cam.Drv, 20200401, modify for 19537**/
static int imgsensor_i2c_probe_3(struct i2c_client *client,
				const struct i2c_device_id *id)
{
	gi2c.inst[IMGSENSOR_I2C_DEV_3].pi2c_client = client;
	return 0;
}
static int imgsensor_i2c_probe_4(struct i2c_client *client,
				const struct i2c_device_id *id)
{
	gi2c.inst[IMGSENSOR_I2C_DEV_4].pi2c_client = client;
	return 0;
}
static int imgsensor_i2c_probe_5(struct i2c_client *client,
				const struct i2c_device_id *id)
{
	gi2c.inst[IMGSENSOR_I2C_DEV_5].pi2c_client = client;
	return 0;
}


static int imgsensor_i2c_remove(struct i2c_client *client)
{
	return 0;
}

static struct i2c_driver gi2c_driver[IMGSENSOR_I2C_DEV_MAX_NUM] = {
	{
		.probe = imgsensor_i2c_probe_0,
		.remove = imgsensor_i2c_remove,
		.driver = {
		.name = IMGSENSOR_I2C_DRV_NAME_0,
		.owner = THIS_MODULE,
#ifdef CONFIG_OF
		.of_match_table = gof_device_id_0,
#endif
		},
		.id_table = gi2c_dev_id,
	},
	{
		.probe = imgsensor_i2c_probe_1,
		.remove = imgsensor_i2c_remove,
		.driver = {
		.name = IMGSENSOR_I2C_DRV_NAME_1,
		.owner = THIS_MODULE,
#ifdef CONFIG_OF
		.of_match_table = gof_device_id_1,
#endif
		},
		.id_table = gi2c_dev_id,
	},
	{
		.probe = imgsensor_i2c_probe_2,
		.remove = imgsensor_i2c_remove,
		.driver = {
		.name = IMGSENSOR_I2C_DRV_NAME_2,
		.owner = THIS_MODULE,
#ifdef CONFIG_OF
		.of_match_table = gof_device_id_2,
#endif
		},
		.id_table = gi2c_dev_id,
	},
/**Feiping.Li@Cam.Drv, 20200401, modify for 19537**/
	{
		.probe = imgsensor_i2c_probe_3,
		.remove = imgsensor_i2c_remove,
		.driver = {
		.name = IMGSENSOR_I2C_DRV_NAME_3,
		.owner = THIS_MODULE,
#ifdef CONFIG_OF
		.of_match_table = gof_device_id_3,
#endif
		},
		.id_table = gi2c_dev_id,
	},
	{
		.probe = imgsensor_i2c_probe_4,
		.remove = imgsensor_i2c_remove,
		.driver = {
		.name = IMGSENSOR_I2C_DRV_NAME_4,
		.owner = THIS_MODULE,
#ifdef CONFIG_OF
		.of_match_table = gof_device_id_4,
#endif
		},
		.id_table = gi2c_dev_id,
	},
	{
		.probe = imgsensor_i2c_probe_5,
		.remove = imgsensor_i2c_remove,
		.driver = {
		.name = IMGSENSOR_I2C_DRV_NAME_5,
		.owner = THIS_MODULE,
#ifdef CONFIG_OF
		.of_match_table = gof_device_id_5,
#endif
		},
		.id_table = gi2c_dev_id,
	}
};

enum IMGSENSOR_RETURN imgsensor_i2c_create(void)
{
	int i;

	for (i = 0; i < IMGSENSOR_I2C_DEV_MAX_NUM; i++)
		i2c_add_driver(&gi2c_driver[i]);

	return IMGSENSOR_RETURN_SUCCESS;
}

enum IMGSENSOR_RETURN imgsensor_i2c_delete(void)
{
	int i;

	for (i = 0; i < IMGSENSOR_I2C_DEV_MAX_NUM; i++)
		i2c_del_driver(&gi2c_driver[i]);

	return IMGSENSOR_RETURN_SUCCESS;
}

enum IMGSENSOR_RETURN imgsensor_i2c_init(
		struct IMGSENSOR_I2C_CFG *pi2c_cfg,
		enum IMGSENSOR_I2C_DEV device)
{
	if (!pi2c_cfg ||
			device >= IMGSENSOR_I2C_DEV_MAX_NUM ||
			device < IMGSENSOR_I2C_DEV_0)
		return IMGSENSOR_RETURN_ERROR;

	pi2c_cfg->pinst       = &gi2c.inst[device];
	pi2c_cfg->pi2c_driver = &gi2c_driver[device];

	mutex_init(&pi2c_cfg->i2c_mutex);
	#ifdef OPLUS_FEATURE_CAMERA_COMMON
	//weiriqin@Cam.drv 2020/06/18, Modify for async power-on-off, ALPS04924900
	mutex_init(&i2c_resource_mutex);
	#endif

	return IMGSENSOR_RETURN_SUCCESS;
}

enum IMGSENSOR_RETURN imgsensor_i2c_buffer_mode(int enable)
{
	struct IMGSENSOR_I2C_INST *pinst =
		&gi2c.inst[IMGSENSOR_I2C_BUFF_MODE_DEV];
	enum   IMGSENSOR_RETURN    ret   = IMGSENSOR_RETURN_SUCCESS;

	PK_DBG("i2c_buf_mode_en %d\n", enable);

	if (pinst->pi2c_client == NULL) {
		pr_info("pi2c_client is NULL!\n");
		return IMGSENSOR_RETURN_ERROR;
	}

	ret = (enable) ?
		hw_trig_i2c_enable(pinst->pi2c_client->adapter) :
		hw_trig_i2c_disable(pinst->pi2c_client->adapter);

	return ret;
}

enum IMGSENSOR_RETURN imgsensor_i2c_read(
		struct IMGSENSOR_I2C_CFG *pi2c_cfg,
		u8 *pwrite_data,
		u16 write_length,
		u8 *pread_data,
		u16 read_length,
		u16 id,
		int speed)
{
	struct IMGSENSOR_I2C_INST *pinst = pi2c_cfg->pinst;
	enum   IMGSENSOR_RETURN    ret   = IMGSENSOR_RETURN_SUCCESS;

	if (pinst->pi2c_client == NULL) {
		pr_info("pi2c_client is NULL!\n");
		return IMGSENSOR_RETURN_ERROR;
	}

	mutex_lock(&pi2c_cfg->i2c_mutex);

	pinst->msg[0].addr  = id >> 1;
	pinst->msg[0].flags = 0;
	pinst->msg[0].len   = write_length;
	pinst->msg[0].buf   = pwrite_data;

	pinst->msg[1].addr  = id >> 1;
	pinst->msg[1].flags = I2C_M_RD;
	pinst->msg[1].len   = read_length;
	pinst->msg[1].buf   = pread_data;

	if (mtk_i2c_transfer(
			pinst->pi2c_client->adapter,
			pinst->msg,
			IMGSENSOR_I2C_MSG_SIZE_READ,
			(pi2c_cfg->pinst->status.filter_msg)
				? I2C_A_FILTER_MSG : 0,
			((speed > 0) && (speed <= 1000))
				? speed * 1000 : IMGSENSOR_I2C_SPEED * 1000)
			!= IMGSENSOR_I2C_MSG_SIZE_READ) {
		static DEFINE_RATELIMIT_STATE(ratelimit, 1 * HZ, 30);

		if (__ratelimit(&ratelimit))
			pr_info(
			"I2C read failed (0x%x)! speed(0=%d) (0x%x)\n",
			ret, speed, *pwrite_data);
		ret = IMGSENSOR_RETURN_ERROR;
	}

	mutex_unlock(&pi2c_cfg->i2c_mutex);

	return ret;
}

enum IMGSENSOR_RETURN imgsensor_i2c_write(
		struct IMGSENSOR_I2C_CFG *pi2c_cfg,
		u8 *pwrite_data,
		u16 write_length,
		u16 write_per_cycle,
		u16 id,
		int speed)
{
	struct IMGSENSOR_I2C_INST *pinst = pi2c_cfg->pinst;
	enum   IMGSENSOR_RETURN    ret   = IMGSENSOR_RETURN_SUCCESS;
	struct i2c_msg     *pmsg  = pinst->msg;
	u8                 *pdata = pwrite_data;
	u8                 *pend  = pwrite_data + write_length;
	int i   = 0;

	if (pinst->pi2c_client == NULL) {
		pr_info("pi2c_client is NULL!\n");
		return IMGSENSOR_RETURN_ERROR;
	}

	mutex_lock(&pi2c_cfg->i2c_mutex);

	while (pdata < pend && i < IMGSENSOR_I2C_CMD_LENGTH_MAX) {
		pmsg->addr  = id >> 1;
		pmsg->flags = 0;
		pmsg->len   = write_per_cycle;
		pmsg->buf   = pdata;

		i++;
		pmsg++;
		pdata += write_per_cycle;
	}

	if (mtk_i2c_transfer(
			pinst->pi2c_client->adapter,
			pinst->msg,
			i,
			(pi2c_cfg->pinst->status.filter_msg)
				? I2C_A_FILTER_MSG : 0,
			((speed > 0) && (speed <= 1000))
				? speed * 1000 : IMGSENSOR_I2C_SPEED * 1000)
			!= i) {
		static DEFINE_RATELIMIT_STATE(ratelimit, 1 * HZ, 30);

		if (__ratelimit(&ratelimit))
			pr_info(
				"I2C write failed (0x%x)! speed(0=%d) (0x%x)\n",
				ret, speed, *pwrite_data);
		ret = IMGSENSOR_RETURN_ERROR;
	}

	mutex_unlock(&pi2c_cfg->i2c_mutex);

	return ret;
}

void imgsensor_i2c_filter_msg(struct IMGSENSOR_I2C_CFG *pi2c_cfg, bool en)
{
	pi2c_cfg->pinst->status.filter_msg = en;
}
#ifndef OPLUS_FEATURE_CAMERA_COMMON
//weiriqin@Cam.drv 2020/06/18, Modify for async power-on-off, ALPS04924900
#ifdef IMGSENSOR_LEGACY_COMPAT
struct IMGSENSOR_I2C_CFG *pgi2c_cfg_legacy;
void imgsensor_i2c_set_device(struct IMGSENSOR_I2C_CFG *pi2c_cfg)
{
	pgi2c_cfg_legacy = pi2c_cfg;
}
#endif
#else
#ifdef IMGSENSOR_LEGACY_COMPAT
#include <linux/unistd.h>
//#include <linux/sched.h>



struct IMGSENSOR_I2C_CFG *pgi2c_cfg_legacy[IMGSENSOR_SENSOR_IDX_MAX_NUM];
pid_t tid_mapping[IMGSENSOR_SENSOR_IDX_MAX_NUM];



void imgsensor_i2c_set_device(struct IMGSENSOR_I2C_CFG *pi2c_cfg)
{
	int i = 0;
	pid_t _tid = task_pid_vnr(current);
	mutex_lock(&i2c_resource_mutex);
	if (pi2c_cfg == NULL) {
		for (i = 0; i < IMGSENSOR_SENSOR_IDX_MAX_NUM; i++) {
			if (tid_mapping[i] == _tid) {
				pgi2c_cfg_legacy[i] = NULL;
				tid_mapping[i] = 0;
				break;
			}
		}
	} else {
		for (i = 0; i < IMGSENSOR_SENSOR_IDX_MAX_NUM; i++) {
			if (tid_mapping[i] == 0) {
				pgi2c_cfg_legacy[i] = pi2c_cfg;
				tid_mapping[i] = _tid;
				break;
			}
		}
	}
	mutex_unlock(&i2c_resource_mutex);
	/* PK_DBG("set tid = %d i = %d pi2c_cfg %p\n", _tid, i, pi2c_cfg); */
}
struct IMGSENSOR_I2C_CFG *imgsensor_i2c_get_device(void)
{
	int i = 0;
	struct IMGSENSOR_I2C_CFG *pi2c_cfg = NULL;
	pid_t _tid = task_pid_vnr(current);
	/* mutex_lock(&i2c_resource_mutex); */

	for (i = 0; i < IMGSENSOR_SENSOR_IDX_MAX_NUM; i++) {
		if (tid_mapping[i] == _tid) {
			pi2c_cfg = pgi2c_cfg_legacy[i];
			break;
		}
	}
	/* mutex_unlock(&i2c_resource_mutex); */
	/* PK_DBG("get tid %d, i =%d, pi2c_cfg %p\n",_tid, i,pi2c_cfg); */
	return pi2c_cfg;
}
#endif
#endif

