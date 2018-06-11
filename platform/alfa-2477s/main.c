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
#include "contiki.h"
#include <stdint.h>
#include <stdbool.h>
#include "sys/clock.h"
#include "sys/ctimer.h"
#include "sys/procinit.h"
#include "sys/init.h"
#include "sys/hardfault.h"
#include "sys/autostart.h"
#include "sys/systime.h"
#include "sys/random.h"
#include "sys/pm.h"
#include "sys/mpu.h"
#include "dev/watchdog.h"
#include "dev/uart.h"
#include "dev/lpm.h"
#include "dev/adc.h"
#include "nest/nest.h"
#include "spiffs/spiffs.h"
#include "loader/lunchr.h"

// arch/cortex-m4
#include "dev/adc-arch.h"
#include "nrf.h"
#include "nrf_soc.h"
#include "nrf_sdm.h"
#include "nrf_gpio.h"
#include "nrf_drv_clock.h"
#include "nrf_drv_saadc.h"
#include "ble.h"
#include "ble_hci.h"
#include "softdevice_arch.h"
#include "nordic_common.h"
#include "softdevice_handler.h"
#include "gpiote.h"
#include "spiffs-flash-arch.h"
#include "spiffs-arch.h"
#include "bsp_init.h"
#include "bsp_button.h"
#include "bsp_led.h"
#include "bsp_rfatte.h"
#include "bsp_buzzer.h"
#include "bsp_mpudmp.h"

// FreeRTOS
#if defined(USE_FREERTOS)
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#endif

// Framework layer
#if defined(USE_FRAMEWORK)
#include "frameworks/app_framework.h"
#include "frameworks/app_eventpool.h"
#endif

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
#define mainMAIN_CONTIKI_TASK_PRIORITY         	  ( FREERTOS_CONTIKI_TASK_PRIORITY_CONF)
#define ADC_REF_VOLTAGE_IN_MILLIVOLTS        1200
#define ADC_PRE_SCALING_COMPENSATION         3
#define DIODE_FWD_VOLT_DROP_MILLIVOLTS       270
#define ADC_RESULT_IN_MILLI_VOLTS(ADC_VALUE)\
				((((ADC_VALUE) * ADC_REF_VOLTAGE_IN_MILLIVOLTS) / 1023) * ADC_PRE_SCALING_COMPENSATION)
#define BATTERY_MAX 		2600
#define BATTERY_MIN     2000
/*---------------------------------------------------------------------------*/
PROCINIT(&etimer_process, &hardfault_process);
/*---------------------------------------------------------------------------*/
SemaphoreHandle_t g_user_app_task_semaphore;
TaskHandle_t g_contiki_thread;
extern const struct uart_driver uart0;
/*---------------------------------------------------------------------------*/
static void
nrf_nest_serial_input(uint8_t data)
{
	PRINTF("[main] serial input 0x%02X\n", data);
	nest_serial_input(data);
}
/*---------------------------------------------------------------------------*/
static uart_config_t nest_serial_uart_cfg = {
	.tx = TX_PIN_NUMBER,
	.rx = RX_PIN_NUMBER,
	.cts = CTS_PIN_NUMBER,
	.rts = RTS_PIN_NUMBER,
	.baudrate = UART_BAUDRATE_BAUDRATE_Baud115200,
	.hwfc = UART_HWFC,
	.cb = nrf_nest_serial_input
};
/*---------------------------------------------------------------------------*/
void
nest_serial_bsp_send(uint8_t *data, uint32_t len)
{
	uart0.tx(data, len);
}
/*---------------------------------------------------------------------------*/
void
nest_serial_bsp_enable(void)
{
	uart0.init(&nest_serial_uart_cfg);
}
/*---------------------------------------------------------------------------*/
void
nest_serial_bsp_disable(void)
{
	uart0.disable();
}
/*---------------------------------------------------------------------------*/
static uint8_t
pm_bsp_get_charging_status(void)
{
	return PM_SOURCE_BATTERY;
}
/*---------------------------------------------------------------------------*/
static uint8_t
pm_bsp_get_battery_level(void)
{
	uint32_t err_code;
	nrf_saadc_channel_config_t  channel_config;
	int16_t adc_value;
	uint16_t mvolts;
	uint8_t battery_level;

	// initialized pressure sensor adc configuration
	channel_config.resistor_p = NRF_SAADC_RESISTOR_DISABLED;
	channel_config.resistor_n = NRF_SAADC_RESISTOR_DISABLED;
	channel_config.gain = NRF_SAADC_GAIN1_6;
	channel_config.reference = NRF_SAADC_REFERENCE_INTERNAL;
	channel_config.acq_time = NRF_SAADC_ACQTIME_10US;
	channel_config.mode = NRF_SAADC_MODE_SINGLE_ENDED;
	channel_config.burst = NRF_SAADC_BURST_DISABLED;
	channel_config.pin_p = (nrf_saadc_input_t)NRF_SAADC_INPUT_VDD;
	channel_config.pin_n = NRF_SAADC_INPUT_DISABLED;

	ADC.channel_init(ARCH_BATTERY_ADC_CHANNEL_CONF, (void *)&channel_config);
	adc_value = ADC.sample(ARCH_BATTERY_ADC_CHANNEL_CONF);
	ADC.channel_uninit(ARCH_BATTERY_ADC_CHANNEL_CONF);

	mvolts = ADC_RESULT_IN_MILLI_VOLTS(adc_value);
	PRINTF("[main] millivolts: %d\n", mvolts);
	if (mvolts < BATTERY_MIN) {
		battery_level = 0;
	} else if (mvolts > BATTERY_MAX) {
		battery_level = 100;
	} else {
		battery_level = ((mvolts - BATTERY_MIN)*100) / ( BATTERY_MAX - BATTERY_MIN);
	}
	return battery_level;
}
/*---------------------------------------------------------------------------*/
const struct pm_driver pm_bsp_driver = {
	.name = ARCH_BATTERY_ADC_VENDOR_CONF,
	.get_battery_level = pm_bsp_get_battery_level,
	.get_charging_status = pm_bsp_get_charging_status
};
/*---------------------------------------------------------------------------*/
void
assert_nrf_callback(uint16_t line_num, const uint8_t * p_file_name)
{
	PRINTF("line_num %d filename:%s\n", line_num, p_file_name);
	app_error_handler(0xDEADBEEF, line_num, p_file_name);
}
/*---------------------------------------------------------------------------*/
static int
bsp_device_init(void)
{
	const static adc_config_t adc_config = {
		.mode = ADC_MODE_BLOCK,
		.cb = NULL
	};
	ADC.init(&adc_config);

	bsp_led_init();
	bsp_button_init();
	bsp_rfatte_init();
	bsp_buzzer_init();
	PRINTF("[main] bsp_mpu9250_dmp_init!\n");
	bsp_mpu9250_dmp_init();

	return ENONE;
}
/*---------------------------------------------------------------------------*/
void
vApplicationIdleHook( void )
{
	watchdog_periodic();
	lpm_drop();
	watchdog_periodic();
}
/*---------------------------------------------------------------------------*/
void
vApplicationStackOverflowHook( TaskHandle_t task,
                                    signed char *pcTaskName )
{

	PRINTF("[main] application stack overflow: %s !\n", pcTaskName);
	nrf_delay_ms(5);
  watchdog_reboot();
  //NVIC_SystemReset();
  while(1);
}
/*---------------------------------------------------------------------------*/
void
vApplicationMallocFailedHook()
{
  PRINTF("[main] application malloc failed!\n");
	nrf_delay_ms(5);
	watchdog_reboot();
  // NVIC_SystemReset();
  while(1);
}
/*---------------------------------------------------------------------------*/
static void
board_init(void)
{
	ret_code_t err_code;
	err_code = nrf_drv_clock_init();
	APP_ERROR_CHECK(err_code);
	// initialize i2c interface
	// nrf_gpio_cfg_input(CHG_STAT_DET, NRF_GPIO_PIN_NOPULL);
}
/*---------------------------------------------------------------------------*/
void
contiki_task(void *arg)
{
	UNUSED_PARAMETER(arg);
	uint32_t ulNotificationValue;

	PRINTF("[main] Initialize softdevice .....\n");
	softdevice_init();
	process_init();
	clock_init();
	// Start the processes in "PROCINIT"
	procinit_init();
	ctimer_init();
	gpiote_init();
	random_init(0); // Random generator module

	// initialize the elfloader
#if defined(USE_ELFLOADER)
	elfloader_init();
#endif

// Initialize low-level driver of file system
#if defined(USE_SPIFFS)
	nrf_spiffs_arch_init(1);
	nrf_gpio_cfg_input(BUTTON0, NRF_GPIO_PIN_NOPULL);
	nrf_delay_ms(10);
	PRINTF("[main] button .....%d\n", nrf_gpio_pin_read(BUTTON0));
	if (nrf_gpio_pin_read(BUTTON0))
		spiffs_flash_arch_init(1);
	else
		spiffs_flash_arch_init(0);
#endif

	// initialate board-supported function
	bsp_device_init();
	pm_init();

#if defined(USE_FRAMEWORK)
	app_framework_init();
#endif

	// Initialize Nest Stack
#if defined(USE_NEST_STACK)
	const static nest_init_config_t config = {
		.scan_sleep_time = {14000, 16000, 18000, 20000}
	};
	nest_stack_init(&config);
#endif

	// setup a callback function to check filesystem
	sys_init(NULL);

	// initialize watchdog
	int ret_code = 0;
	watchdog_init();
	watchdog_start();
	PRINTF("[main] start process\n");
	for( ;; ) {
		uint32_t process_count;
		do {
			process_count = process_run();
			watchdog_periodic();
			// PRINTF("[main] ps count %d \n", process_count);
	  } while(process_count > 0);
		ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
		watchdog_periodic();
	}
}
/*---------------------------------------------------------------------------*/
int main(void)
{
	// Do not start any interrupt that uses system functions before system initialisation.
	// The best solution is to start the OS before any other initalisation.
	board_init();

#if defined(USE_FRAMEWORK)
	// Create kernel main task binary semaphore
	g_user_app_task_semaphore = xSemaphoreCreateBinary();

	/* Create a queue capable of containing 10 app_irq_event_t values. */
	g_app_irq_queue_handle = xQueueCreate( 10, sizeof( app_irq_event_t ) );
	if( g_app_irq_queue_handle == NULL ) {
		PRINTF("[main] queue create error.\n");
		APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
	}
#endif

	// Create contiki stack
#if  defined(USE_CONTIKI)
	if(pdPASS != xTaskCreate( contiki_task, "CTIK", CONTIKI_KERNEL_TASK_SIZE, ( void * ) 0, mainMAIN_CONTIKI_TASK_PRIORITY, &g_contiki_thread) )
	{
		APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
		PRINTF("[main] no memory. \n");
	}
#endif

	/* Activate deep sleep mode */
	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
	SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk | SCB_CCR_STKALIGN_Msk | SCB_CCR_BFHFNMIGN_Msk | SCB_CCR_USERSETMPEND_Msk | SCB_CCR_NONBASETHRDENA_Msk;

	PRINTF("[main] Start the scheduler... \n");
	// Start the scheduler running the tasks and co-routines just created.
	vTaskStartScheduler();
	for(;;) {
	}
}
