#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

/*Include FreeRTOS*/
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "queue.h"
#include "task.h"

#include "GUI.h"
#include "mtb_ssd1306.h"

#include "interface.h"
#include "button.h"

#define taskPriority  			(6)

#define BTN_ENTER 	(P0_2)
#define BTN_BACK	(P0_3)

#define MAIN_SCREEN 		(0)
#define MENU_LIST			(1)
#define SET_CLOCK_SCREEN 	(2)
#define BMP280_SCREEN 		(3)
#define PASCO2_SCREEN 		(4)

#define NUM_OF_BTN 			(4)

typedef enum buttonCode {
	BUTTON_UP 		= 0,
	BUTTON_DOWN 	= 1,
	BUTTON_ENTER 	= 2,
	BUTTON_BACK 	= 3
}BTN_CODE;

/*Prototipe function*/
void menuUp();
void menuDown();
void wakeUp();
void listMenu();
void backToMain();
void displayOled(void *arg);
void ButtonApp(void *arg);

button_var btn_obj[NUM_OF_BTN];

cyhal_gpio_t btn_pin[NUM_OF_BTN] = {
		CYBSP_USER_BTN,
		CYBSP_USER_BTN2,
		BTN_ENTER,
		BTN_BACK
};

interface_t interface_obj;

bool systemReady = false;
bool wakeUpF = false;
bool listMenuF = false;
uint8_t CURRENT_SCREEN = MAIN_SCREEN;

const char *menu[] = {"Time & Date", "Environmental", "Air Quality", "Stop Watch"};
const char testDisp [] = {"Test Display"};

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

	cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, CY_RETARGET_IO_BAUDRATE);

	xTaskCreate(ButtonApp, "ButtonApp", 1024*2, NULL, taskPriority-1, &buttonHandle);
	xTaskCreate(displayOled, "DisplayApp", 1024*2, NULL, (taskPriority), &displayHandle);

	vTaskStartScheduler();

	CY_ASSERT(0);

}

void menuUp(){
	interface_previous(&interface_obj);
}
void menuDown(){
	interface_next(&interface_obj);
}

void wakeUp(){
	CURRENT_SCREEN = MAIN_SCREEN;
	wakeUpF = true;
}

void listMenu(){

	interface_clear(&interface_obj);
	printf("ListMenu\r\n");
	CURRENT_SCREEN = MENU_LIST;
	wakeUpF = false;
	listMenuF = true;
}

void backToMain(){
	interface_clear(&interface_obj);
	CURRENT_SCREEN = MAIN_SCREEN;
	listMenuF = false;
	wakeUpF = true;
}

void displayOled(void *arg){

	const cyhal_i2c_cfg_t i2c_cfg =
	{
			.is_slave 		 = false,
			.address  		 = 0,
			.frequencyhal_hz = 400000
	};

	cyhal_i2c_t i2c;

	cyhal_i2c_init(&i2c, CYBSP_I2C_SDA, CYBSP_I2C_SCL, NULL);
	cyhal_i2c_configure(&i2c, &i2c_cfg);

	interface_construct(&interface_obj, &i2c);
	interface_begin(&interface_obj);
	interface_clear(&interface_obj);

	while (!systemReady){
		vTaskDelay(5);
	}

//	button.attachPressed(&btn_obj[0], menuUp);
//	button.attachPressed(&btn_obj[1], menuDown);

	while(1){

//		button.attachHeld(&btn_obj[2],listMenu);
		button.attachPressed(&btn_obj[2], listMenu);
		button.attachHeld(&btn_obj[3],wakeUp);
		button.attachPressed(&btn_obj[3], backToMain);

		if (CURRENT_SCREEN == MAIN_SCREEN){
			if (wakeUpF)
				GUI_DispStringAt("Main Smart Clock", 20,32);
			interface_reset_position(&interface_obj);
		}

		if (wakeUpF == false){
//			interface_clear(&interface_obj);
//			GUI_DispStringAt("              ", 10,32);
			if(CURRENT_SCREEN == MENU_LIST && listMenuF){
				interface_setTitle(&interface_obj, testDisp);
				interface_set_menu(&interface_obj, menu, (sizeof(menu)/sizeof(menu[0])));
				button.attachPressed(&btn_obj[0], menuUp);
				button.attachPressed(&btn_obj[1], menuDown);
				interface_draw_menu(&interface_obj);

			}
		}
//		interface_draw_menu(&interface_obj);
		vTaskDelay(5);
	}
}

void ButtonApp(void *arg){

	button.setTick(xTaskGetTickCount);

	button.setHoldTime(&btn_obj[0], 100);	//Button Up
	button.setHoldTime(&btn_obj[1], 100);	//Button Down
	button.setHoldTime(&btn_obj[2], 200);	//Button Enter
	button.setHoldTime(&btn_obj[3], 200);	//Button Back

	button.setDebounceTime(&btn_obj[0],10);
	button.setDebounceTime(&btn_obj[1],10);
	button.setDebounceTime(&btn_obj[2],50);
	button.setDebounceTime(&btn_obj[3],50);

	for (uint8_t i = 0; i < NUM_OF_BTN; i++){
		if( button.create(&btn_obj[i], btn_pin[i], BUTTON_LOW, 200) == CY_RSLT_SUCCESS )
			printf(" button initialize success \r\n");
	}

	systemReady = true;
	uint8_t btn_num = 0;

	for(;;){

		if (button.check(&btn_obj[btn_num]) != WAITING_btn)
			printf("action %d\r\n", btn_num);
//		button.check(&btn_obj[btn_num]);
		btn_num++;
		if (btn_num >= NUM_OF_BTN)
			btn_num = 0;
		vTaskDelay(1);
	}
}
