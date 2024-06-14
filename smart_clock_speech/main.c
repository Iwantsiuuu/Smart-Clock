/*******************************************************************************
 * Header Files
 *******************************************************************************/
#include "main.h"

/*******************************************************************************
 * Macros
 *******************************************************************************/
#define LDO_ENABLE P7_1

#define TASK_STACK_SIZE (1024u)
#define taskPriority    (6)

/*******************************************************************************
 * Global Variables
 *******************************************************************************/
TaskHandle_t voiceHandle;
TaskHandle_t notifyHandle;
TaskHandle_t buttonHandle;
TaskHandle_t sensorHandle;
TaskHandle_t displayHandle;

SemaphoreHandle_t semphr_i2c_dev;

bool systemReady = false;

/*******************************************************************************
 * Function Name: main
 ********************************************************************************
 * Summary:
 * This is the main function for CPU. It...
 *    1.
 *    2.
 *
 * Parameters:
 *  void
 *
 * Return:
 *  int
 *
 *******************************************************************************/
int main(void)
{
	cy_rslt_t result;
	RTC_Setup.Year = 2000;

#if defined (CY_DEVICE_SECURE)
	cyhal_wdt_t wdt_obj;

	/* Clear watchdog timer so that it doesn't trigger a reset */
	result = cyhal_wdt_init(&wdt_obj, cyhal_wdt_get_max_timeout_ms());
	CY_ASSERT(CY_RSLT_SUCCESS == result);
	cyhal_wdt_free(&wdt_obj);
#endif

	/* Initialize the device and board peripherals */
	result = cybsp_init();

	/* Board init failed. Stop program execution */
	if (result != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(0);
	}

	/* Enable global interrupts */
	__enable_irq();

	cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, CY_RETARGET_IO_BAUDRATE);

	result = cyhal_gpio_init(LDO_ENABLE, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_OPENDRAINDRIVESHIGH, CYBSP_LED_STATE_ON);
	if(result == CY_RSLT_SUCCESS)
		cyhal_gpio_write(LDO_ENABLE, 1u);

	init_i2c();
	init_u8g2();
	clock_init();
	ButtonInit();
	cyhal_rtc_init(&rtc_obj);
	init_pdm_pcm();

	printf("**********Application Start*****************\n\r");

	result = cyhal_pwm_init(&PWM_obj, CYBSP_USER_LED1, NULL);
	cyhal_pwm_start(&PWM_obj);

	/* Configure platform specific settings for the BT device */
	cybt_platform_config_init(&cybsp_bt_platform_cfg);

	/* Initialize stack and register the callback function */
	wiced_bt_stack_init (app_bt_management_callback, &wiced_bt_cfg_settings);

	if(sensorInit() == CY_RSLT_SUCCESS)
		systemReady = true;

	semphr_i2c_dev = xSemaphoreCreateMutex();
	if (semphr_i2c_dev != NULL)
		xSemaphoreGive(semphr_i2c_dev);

	xTaskCreate (ButtonApp, "Button", (TASK_STACK_SIZE*2), NULL, taskPriority, &buttonHandle);
	xTaskCreate (displayOled, "Interface", (TASK_STACK_SIZE*2), NULL, taskPriority-1, &displayHandle);
	xTaskCreate (sensor_App, "Sensor", (TASK_STACK_SIZE*2), NULL, taskPriority-2, &sensorHandle);
	xTaskCreate (notify_task, "Bluetooth_Notify", (TASK_STACK_SIZE*2), NULL, taskPriority-3, &notifyHandle);
	xTaskCreate (voice_command_task, "Speech_command", (TASK_STACK_SIZE*2), NULL, taskPriority-4, &voiceHandle);

	/* Start the FreeRTOS scheduler */
	vTaskStartScheduler();

	/* Should never get here */
	CY_ASSERT(0);

}
