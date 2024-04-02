#include "task_interface.h"
#include "menu.h"
#include "main_page.h"
#include "timeDatePage.h"
#include "rtc_sc.h"

#define ENABLE (1)

static bool RTC_ENABLE = false;

u8g2_t u8g2_obj;

void displayOled(){
	printf("Task Interface\r\n");

	while (!systemReady){
		vTaskDelay(5);
	}

	mtb_ssd1306_init_i2c(&i2c);
	init_u8g2();

	RTC_ENABLE = cyhal_rtc_is_enabled(&rtc_obj);
	if(RTC_ENABLE != ENABLE)
		rtc_set_first();

	while(1){

		main_page();
		vTaskDelay(10);
	}
}

static void init_u8g2(){
	/* Initialize the U8 Display */
	u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2_obj, U8G2_R0, u8x8_byte_hw_i2c,
			u8x8_gpio_and_delay_cb);

	/* Send init sequence to the display, display is in sleep mode after this */
	u8g2_InitDisplay(&u8g2_obj);

	/* Wake up display */
	u8g2_SetPowerSave(&u8g2_obj, 0);

	/* Prepare display for printing */
	u8g2_SetFont(&u8g2_obj, u8g2_font_6x12_tf);
	u8g2_ClearDisplay(&u8g2_obj);
	u8g2_ClearBuffer(&u8g2_obj);
}

void send_buffer_u8g2(){
	if (semphr_i2c_dev != NULL){
		if(xSemaphoreTake(semphr_i2c_dev, ( TickType_t ) 10)){
			u8g2_SendBuffer(&u8g2_obj);
			u8g2_ClearBuffer(&u8g2_obj);
			xSemaphoreGive(semphr_i2c_dev);
		}
	}
}
