#ifndef MAIN_BLE_H_
#define MAIN_BLE_H_

#include "cybsp.h"
#include "cyhal.h"
#include "cy_retarget_io.h"

/* Library for malloc and free */
#include "stdlib.h"

/* FreeRTOS */
#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>

/* btstack */
#include "wiced_bt_stack.h"

/* App utilities */
#include "app_bt_utils.h"

/* Include header files from BT configurator */
#include "cycfg_bt_settings.h"
#include "cycfg_gap.h"
#include "cycfg_gatt_db.h"
#include "rtc_sc.h"
#include <string.h>

#define APP_TIMEOUT_LED_BLINK          (200)

/* Typdef for function used to free allocated buffer to stack */
typedef void (*pfn_free_buffer_t)(uint8_t *);

/*******************************************************************
 * Function Prototypes
 ******************************************************************/
/* Callback function for Bluetooth stack management type events */
void app_bt_timeout_led_blink(TimerHandle_t timer_handle);
void app_bt_led_blink(uint16_t num_of_blinks);
wiced_bt_dev_status_t app_bt_management_callback             (wiced_bt_management_evt_t event, wiced_bt_management_evt_data_t *p_event_data);

/* GATT Event Callback and Handler Functions */
static wiced_bt_gatt_status_t app_bt_gatt_event_callback            (wiced_bt_gatt_evt_t event, wiced_bt_gatt_event_data_t *p_event_data);

static wiced_bt_gatt_status_t app_bt_connect_event_handler          (wiced_bt_gatt_connection_status_t *p_conn_status);
static wiced_bt_gatt_status_t app_bt_server_event_handler           (wiced_bt_gatt_event_data_t *p_data);

static wiced_bt_gatt_status_t app_bt_write_handler                  (wiced_bt_gatt_event_data_t *p_data);
static wiced_bt_gatt_status_t app_bt_gatt_req_read_handler          (uint16_t conn_id, wiced_bt_gatt_opcode_t opcode,
		wiced_bt_gatt_read_t *p_read_req, uint16_t len_requested);
static wiced_bt_gatt_status_t app_bt_gatt_req_read_multi_handler    (uint16_t conn_id, wiced_bt_gatt_opcode_t opcode,
		wiced_bt_gatt_read_multiple_req_t *p_read_req, uint16_t len_requested);
static wiced_bt_gatt_status_t app_bt_gatt_req_read_by_type_handler  (uint16_t conn_id, wiced_bt_gatt_opcode_t opcode,
		wiced_bt_gatt_read_by_type_t *p_read_req, uint16_t len_requested);

/* Helper functions to find GATT database handles and allocate/free buffers for GATT operations */
static gatt_db_lookup_table_t 	*app_bt_find_by_handle(uint16_t handle);
static uint8_t 					*app_bt_alloc_buffer(uint16_t len);
static void 					app_bt_free_buffer(uint8_t *p_data);

extern cyhal_pwm_t PWM_obj;
extern TimerHandle_t timer_led_blink;

extern uint16_t connection_id;

extern bool set_rtc;
extern bool flag_bt_actived;

#endif
