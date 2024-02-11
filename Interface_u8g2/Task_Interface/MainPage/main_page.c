#include "main_page.h"
#include "stdio.h"
#include "task_button.h"

char volatile buf_time_date [20];
uint8_t Temps = 0;
uint8_t x = 0, y = 0;
u8g2_t u8g2_obj;

void TempsVal(uint8_t val){
	Temps += val;
}

void main_page(){
	init_main_page();
	while (1){
		TempsVal(1);
		if (THIS_PAGE == MAIN_PAGE_ID){
			sprintf(buf_time_date,"%4d C\xB0\r\n", Temps);
			u8g2_DrawStr(&u8g2_obj, x+110, y, "80%");
			u8g2_DrawStr(&u8g2_obj, x+35, y+20, "08:00 am");
			u8g2_DrawStr(&u8g2_obj, x+30, y+30, "Feb 5, 2024");
			u8g2_DrawStr(&u8g2_obj, x+45, y+40, buf_time_date);
			u8g2_SendBuffer(&u8g2_obj);
			u8g2_ClearBuffer(&u8g2_obj);
		}else
			break;
	}
	deinit_main_page();
}

void init_main_page()
{
// attach button
	// clear display
	button.attachPressed(&btn_obj[0], enter_menu_cb);
	button.attachPressed(&btn_obj[1], wake_up_cb);

	/* Initialize the U8 Display */
	u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2_obj, U8G2_R0, u8x8_byte_hw_i2c,
			u8x8_gpio_and_delay_cb);
	/* Send init sequence to the display, display is in sleep mode after this */
	u8g2_InitDisplay(&u8g2_obj);
	/* Wake up display */
	u8g2_SetPowerSave(&u8g2_obj, 0);

	/* Prepare display for printing */
//	u8g2_SetFontPosCenter(&u8g2_obj);
	u8g2_SetFont(&u8g2_obj, u8g2_font_6x12_tf);
	u8g2_ClearDisplay(&u8g2_obj);
	u8g2_ClearBuffer(&u8g2_obj);

}

void deinit_main_page(){
	// de attach button
	for (uint8_t i = 0; i < 2; i++)
		button.dettachPressed(&btn_obj[i]);
}

void enter_menu_cb(){
	THIS_PAGE = MENU_PAGE_ID;
	printf("Enter");

}

void wake_up_cb(){
	THIS_PAGE = MAIN_PAGE_ID;
	printf("WakeUp");
}
