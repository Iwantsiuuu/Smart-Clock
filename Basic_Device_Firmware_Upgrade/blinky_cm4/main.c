#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_dfu.h"

/*Include FreeRTOS*/
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"

#include "task.h"
#include "semphr.h"
#include <timers.h>

#include "i2c_setup.h"
#include "oled_init.h"

/*******************************************************************************
 * Macros
 ********************************************************************************/
#define taskPriority    (6)
#define TASK_STACK_SIZE (1024u)

/* App ID of bootloader. */
#define    BOOTLOADER_ID                    (0u)

/* Define LED toggle frequency. */
#define LED_TOGGLE_INTERVAL_MS              (100u)

/*******************************************************************************
 * Function Prototypes
 ********************************************************************************/
void button_task();

/*******************************************************************************
 * Global Variables
 ********************************************************************************/
TaskHandle_t buttonHandle;
static bool systemReady = false;

/* Application signature. */
CY_SECTION(".cy_app_signature") __USED static const uint32_t cy_dfu_appSignature;

/*******************************************************************************
 * Function Name: main
 ********************************************************************************
 * Summary:
 * This is the main function for CM4 CPU.
 *   1. It blinks LED at "LED_TOGGLE_INTERVAL_MS" interval.
 *   2. If user button press event is detected, it will transfer control to
 *      Bootloader.
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

	/* Initialize the device and board peripherals */
	result = cybsp_init() ;
	if (result != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(0);
	}

	i2c_init();
	init_oled();

	__enable_irq();
	/* Initialize the User LED */
	result = cyhal_gpio_init(CYBSP_USER_LED, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, CYBSP_LED_STATE_OFF);
	/* GPIO init failed. Stop program execution */
	if (result != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(0);
	}

	/* Initialize the user button */
	result = cyhal_gpio_init(CYBSP_USER_BTN, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_PULLUP, CYBSP_BTN_OFF);
	/* GPIO init failed. Stop program execution */
	if (result != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(0);
	}

	systemReady	= true;

	xTaskCreate(button_task, "button", (TASK_STACK_SIZE*2), NULL, taskPriority, &buttonHandle);

	/* Start the FreeRTOS scheduler */
	vTaskStartScheduler();

	/* Should never get here */
	CY_ASSERT(0);
}

void button_task(){

	while(!systemReady){
		vTaskDelay(10);
	}

	uint32_t timePrev = xTaskGetTickCount();
	uint32_t timeDebounce = xTaskGetTickCount();

	for (;;)
	{
		/* If Button clicked - Switch to bootloader */

		/* Invert the USER LED state */
		if (xTaskGetTickCount() - timePrev >= 50){

			cyhal_gpio_toggle(CYBSP_USER_LED);

			u8g2_DrawStr(&u8g2_obj, 5, 10, "Hello World");
			u8g2_SendBuffer(&u8g2_obj);
			u8g2_ClearBuffer(&u8g2_obj);

			timePrev = xTaskGetTickCount();
		}

		/* Delay between LED toggles */
		if (cyhal_gpio_read(CYBSP_USER_BTN) == 0u)
		{
			/* 50 ms delay for button debounce on button press */
			if(xTaskGetTickCount() - timeDebounce >= 50){
				if (cyhal_gpio_read(CYBSP_USER_BTN) == 0u)
				{
					while (cyhal_gpio_read(CYBSP_USER_BTN) == 0u)
					{   /* 50 ms delay for button debounce on button release */
						if(xTaskGetTickCount() - timeDebounce >= 50)
							timeDebounce = xTaskGetTickCount();
					}
					Cy_DFU_ExecuteApp(BOOTLOADER_ID);
				}
				timeDebounce = xTaskGetTickCount();
			}
		}
		vTaskDelay(5);
	}
}
