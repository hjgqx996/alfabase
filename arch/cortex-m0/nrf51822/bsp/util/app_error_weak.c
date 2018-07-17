/* Copyright (c) 2016 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

#include "app_error.h"

#define NRF_LOG_MODULE_NAME "APP_ERROR"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
/*lint -save -e14 */


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

/**
 * Function is implemented as weak so that it can be overwritten by custom application error handler
 * when needed.
 */
__WEAK void app_error_fault_handler(uint32_t id, uint32_t pc, uint32_t info)
{
    PRINTF("Fatal\n");
    //NRF_LOG_FINAL_FLUSH();
    // On assert, the system can only recover with a reset.
//#ifndef DEBUG
   NVIC_SystemReset();
//#else
    app_error_save_and_stop(id, pc, info);
//#endif // DEBUG
}

/*lint -restore */
