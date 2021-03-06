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
#include "bsp_led.h"
#include <stdint.h>
#include <stdbool.h>
#include "frameworks/hw/hw_api.h"
#include "frameworks/hw/hw_api_null.h"
#include "frameworks/app_eventpool.h"
#include "frameworks/app_lifecycle.h"
#include "nrf_gpio.h"
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
static uint8_t led_status = 0x00;
/*---------------------------------------------------------------------------*/
int
bsp_led_write(const void *buf, uint32_t len, uint32_t offset)
{
  uint8_t *p_led_ctrl = (uint8_t*)buf;
  if (p_led_ctrl[0]){ nrf_gpio_pin_set(LED0);}
  else { nrf_gpio_pin_clear(LED0);}
  return ENONE;
}
/*---------------------------------------------------------------------------*/
int
bsp_led_read(void *buf, uint32_t len, uint32_t offset)
{
  uint8_t *p_led_ctrl = (uint8_t*)buf;
  p_led_ctrl[0] = nrf_gpio_pin_read(LED0);
  return ENONE;
}
/*---------------------------------------------------------------------------*/
static void
app_terminating(void)
{
  // disable all led
  nrf_gpio_pin_clear(LED0);
}
/*---------------------------------------------------------------------------*/
static struct app_lifecycle_event lifecycle_event = {
	.name = "hw_bsp_led",
	.terminating = app_terminating
};
/*---------------------------------------------------------------------------*/
int
bsp_led_init(void)
{
	app_lifecycle_register(&lifecycle_event);
  nrf_gpio_cfg_output(LED0);
  nrf_gpio_pin_clear(LED0);
}
/*---------------------------------------------------------------------------*/
