#include "main_page.h"
#include "task_interface.h"
#include "task_button.h"
#include "task_sensor.h"
#include "rtc_sc.h"

#define MAIN_PAGE_ID 1
#define MENU_PAGE_ID 2

static enum mode_t{
	DEFAULT_MODE,
	BLUETOOTH_MODE
};

struct tm RTC_TIME;
char buf_temp [20];

static uint8_t THIS_PAGE = 0;
static uint8_t SMART_CLOCK_MODE;
static uint8_t x = 0, y = 0;

void main_page(){
	init_main_page();

	while (1){
		if (THIS_PAGE == MAIN_PAGE_ID){
			if (SMART_CLOCK_MODE == DEFAULT_MODE)
				default_mode_draw();
			else
				bluetooth_mode_draw();
		}
		else{
			deinit_main_page();
			menu_disp();
			init_main_page();
		}
		vTaskDelay(50);
	}
	deinit_main_page();
}

static void default_mode_draw(){

	char buf_time[STRING_BUFFER_SIZE];
	char buf_date[STRING_BUFFER_SIZE];

	cyhal_rtc_read(&rtc_obj, &RTC_TIME);

	strftime(buf_time, sizeof(buf_time), "%X %p", &RTC_TIME);
	strftime(buf_date, STRING_BUFFER_SIZE, "%b %d, %Y", &RTC_TIME);

	sprintf(buf_temp,"%0.0f C\xB0\r\n", dps_sensor.temperature);

	u8g2_DrawStr(&u8g2_obj, x+110, y+8, "80%");
	u8g2_DrawStr(&u8g2_obj, x+35, y+25, buf_time);
	u8g2_DrawStr(&u8g2_obj, x+30, y+35, buf_date);
	u8g2_DrawStr(&u8g2_obj, x+45, y+50, buf_temp);

	send_buffer_u8g2();
}

static void bluetooth_mode_draw(){

	u8g2_DrawStr(&u8g2_obj, x+110, y+8, "80%");
	u8g2_DrawStr(&u8g2_obj, x+20, y+25, "Bluetooth Mode");

	send_buffer_u8g2();
}

static void init_main_page()
{
	// attach button
	button.attachPressed(&btn_obj[BUTTON_UP], moveToMenuPage);
	button.attachPressed(&btn_obj[BUTTON_DOWN], changeMode);

	THIS_PAGE = MAIN_PAGE_ID;
	SMART_CLOCK_MODE = 0;
}

static void deinit_main_page(){

	// de attach button
	for (uint8_t i = 0; i < 2; i++)
		button.dettachPressed(&btn_obj[i]);
}

static void moveToMenuPage(){
	THIS_PAGE = MENU_PAGE_ID;
}

static void changeMode(){
	SMART_CLOCK_MODE++;
	if (SMART_CLOCK_MODE > BLUETOOTH_MODE)
		SMART_CLOCK_MODE = 0;
}
