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
bool oledReady = false;

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

	result = initialize_i2c();

	if(result != CY_RSLT_SUCCESS)
		printf("fail init I2C\r\n");

	printf("Initialize I2C Success\r\n");

	result = xensiv_dps3xx_mtb_init_i2c(&pressure_sensor, &i2c, 0x77);
	if(result == CY_RSLT_SUCCESS)
		printf("Initialize DPS310 Success\r\n");

//	init_u8g2();
//	printf("Initialize Oled Success\r\n");

	buttonInit();
	printf("Initialize Button Success\r\n");


	if(cyhal_rtc_init(&rtc_obj) == CY_RSLT_SUCCESS)
		systemReady = true;
	printf("Initialize RTC Success\r\n");

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
