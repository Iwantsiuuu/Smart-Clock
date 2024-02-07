#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

/*Include FreeRTOS*/
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "queue.h"
#include "task.h"

#include "task_button.h"
#include "task_interface.h"
#include "task_bmp280.h"

#define taskPriority  		(6)

int main(void)
{
	cy_rslt_t result;

	TaskHandle_t buttonHandle;
	TaskHandle_t displayHandle;

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

	cy_retarget_io_init(P5_1, P5_0, CY_RETARGET_IO_BAUDRATE);

	xTaskCreate(ButtonApp, "ButtonApp", 1024*2, NULL, taskPriority, &buttonHandle);
	xTaskCreate(displayOled, "DisplayApp", 1024*2, NULL, (taskPriority-1), &displayHandle);

	vTaskStartScheduler();

	CY_ASSERT(0);

}
