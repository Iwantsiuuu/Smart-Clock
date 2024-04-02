#include "main.h"
#include "interface.h"

#include "rtc_sc.h"
#include "task_button.h"
#include "task_interface.h"
#include "task_sensor.h"

#define taskPriority  		(6)

// task handler
TaskHandle_t buttonHandle;
TaskHandle_t displayHandle;
TaskHandle_t sensorHandle;

// semaphore
SemaphoreHandle_t semphr_i2c_dev;

bool systemReady = false;

int main(void)
{
	struct tm RTC_MAIN;
	char bufff[80];
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
	if (result != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(0);
	}

	/* Enable global interrupts */
	__enable_irq();

// initialize peripheral
	cy_retarget_io_init(P5_1, P5_0, CY_RETARGET_IO_BAUDRATE);
	initialize_i2c();

	result = cyhal_rtc_init(&rtc_obj);

// task initialize
	semphr_i2c_dev = xSemaphoreCreateMutex();
	if (semphr_i2c_dev != NULL)
		xSemaphoreGive(semphr_i2c_dev);

	xTaskCreate(ButtonApp, "ButtonApp", 1024*2, NULL, taskPriority, &buttonHandle);
	xTaskCreate(displayOled, "DisplayApp", 1024*2, NULL, (taskPriority-1), &displayHandle);
	xTaskCreate(sensor_App, "Sensor", 1024*2, NULL, (taskPriority-3), &sensorHandle);

	vTaskStartScheduler();

	CY_ASSERT(0);

}
