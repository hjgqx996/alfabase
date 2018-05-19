/**
 * © Copyright AlfaLoop Technology Co., Ltd. 2018
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 **/
#include "bsp_mpudmp.h"
#include <stdint.h>
#include <stdbool.h>
#include "frameworks/hw/hw_api.h"
#include "frameworks/hw/hw_api_null.h"
#include "frameworks/app_eventpool.h"
#include "frameworks/app_lifecycle.h"
#include "mpu9250-dmp-arch.h"
#include "nrf_gpio.h"
#include "sys/clock.h"
#include "errno.h"
#include "bsp_init.h"
/*---------------------------------------------------------------------------*/
#if defined(DEBUG_ENABLE)
#define DEBUG_MODULE 1
#if DEBUG_MODULE
#include "dev/syslog.h"
#define PRINTF(...) syslog(__VA_ARGS__)
#else
#define PRINTF(...)
#endif  /* DEBUG_MODULE */
#else
#define PRINTF(...)
#endif  /* DEBUG_ENABLE */
/*---------------------------------------------------------------------------*/

static bool m_mpu9250_active = false;
/*---------------------------------------------------------------------------*/
void
mpu9250_dmp_data_update(uint32_t source)
{

}
/*---------------------------------------------------------------------------*/
int
bsp_mpu9250_dmp_open(void *args)
{
  if (m_mpu9250_active) {
    return EINVALSTATE;
  }

  SENSOR_MOTIONFUSION.poweron();
  m_mpu9250_active = true;
  return ENONE;
}
/*---------------------------------------------------------------------------*/
int
bsp_mpu9250_dmp_write(const void *buf, uint32_t len, uint32_t offset)
{
  return ENOSUPPORT;
}
/*---------------------------------------------------------------------------*/
int
bsp_mpu9250_dmp_read(void *buf, uint32_t len, uint32_t offset)
{
  switch (offset) {
    case 0:
    {
      mems_data_t *p_acc_data = (mems_data_t *)buf;
      SENSOR_MOTIONFUSION.get_accel(p_acc_data->value, p_acc_data->data, p_acc_data->timestamp);
    }
    break;
    case 1:
    {
      mems_data_t *p_data = (mems_data_t *)buf;
      SENSOR_MOTIONFUSION.get_gyro(p_data->value, p_data->data, p_data->timestamp);
    }
    break;
  }
  return ENONE;
}
/*---------------------------------------------------------------------------*/
int
bsp_mpu9250_dmp_subscribe(void *buf, uint32_t len, HWCallbackHandler handler)
{
  return ENOSUPPORT;
}
/*---------------------------------------------------------------------------*/
int
bsp_mpu9250_dmp_close(void *args)
{
  if (!m_mpu9250_active) {
    return EINVALSTATE;
  }
  SENSOR_MOTIONFUSION.poweroff(false);
  m_mpu9250_active = false;
  return ENONE;
}
/*---------------------------------------------------------------------------*/
static void
app_terminating(void)
{
	bsp_mpu9250_dmp_close(NULL);
}
/*---------------------------------------------------------------------------*/
static struct app_lifecycle_event lifecycle_event = {
	.name = "hw_bsp_mpudmp",
	.terminating = app_terminating
};
/*---------------------------------------------------------------------------*/
int
bsp_mpu9250_dmp_init(void)
{
	app_lifecycle_register(&lifecycle_event);

  mpu9250_dmp_config_t mpu9250_dmp_config = {
		.data_source = mpu9250_dmp_data_update
	};
	SENSOR_MOTIONFUSION.init(&mpu9250_dmp_config);
	SENSOR_MOTIONFUSION.poweroff(false);
}
/*---------------------------------------------------------------------------*/
