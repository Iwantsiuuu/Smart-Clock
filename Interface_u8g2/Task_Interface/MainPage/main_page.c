#include "main_page.h"
#include "task_interface.h"
#include "task_button.h"
#include "task_sensor.h"
#include "rtc_sc.h"

#define MAIN_PAGE_ID 1
#define MENU_PAGE_ID 2

static uint8_t THIS_PAGE = 0;
struct tm RTC_TIME;
char buf_temp [20];
uint8_t RTC_ENABLE;

uint8_t x = 0, y = 0;

void main_page(){
	init_main_page();

	while (1){
		if (THIS_PAGE == MAIN_PAGE_ID){
			main_draw();
		}
		else{
			deinit_main_page();
			menu_disp();
			init_main_page();
		}
		vTaskDelay(50);	// perlu pake delay : karena terjadi infinite loop disini
	}
	deinit_main_page();
}

void main_draw(){

	char buf_time[STRING_BUFFER_SIZE];
	char buf_date[STRING_BUFFER_SIZE];

	cyhal_rtc_read(&rtc_obj, &RTC_TIME);

	strftime(buf_time, sizeof(buf_time), "%X %p", &RTC_TIME);
	strftime(buf_date, STRING_BUFFER_SIZE, "%b %d, %Y", &RTC_TIME);

//	printf("%s\r\n",buf_time);
//	printf("%s\r\n",buf_date);

	sprintf(buf_temp,"%0.0f C\xB0\r\n", dps_sensor.temperature);

	u8g2_DrawStr(&u8g2_obj, x+110, y+8, "80%");
	u8g2_DrawStr(&u8g2_obj, x+35, y+25, buf_time);
	u8g2_DrawStr(&u8g2_obj, x+30, y+35, buf_date);
	u8g2_DrawStr(&u8g2_obj, x+45, y+50, buf_temp);

	send_buffer_u8g2();
}

void init_main_page()
{
	// attach button
	button.attachPressed(&btn_obj[0], enter_menu_cb);
	button.attachPressed(&btn_obj[1], wake_up_cb);
	THIS_PAGE = MAIN_PAGE_ID;

//	RTC_ENABLE = cyhal_rtc_is_enabled(&rtc_obj);
//	if(RTC_ENABLE != CY_RSLT_SUCCESS){

//		cyhal_rtc_read(&rtc_obj,&RTC_MAIN);
//		strftime(bufff, 80, "%c", &RTC_MAIN);
//		printf("Data main: %s\r\n", bufff);

//	}
//	else{
//		set_new_time();
//	}
}

void deinit_main_page(){
	// de attach button
	for (uint8_t i = 0; i < 2; i++)
		button.dettachPressed(&btn_obj[i]);
}

void enter_menu_cb(){
	THIS_PAGE = MENU_PAGE_ID;
}

void wake_up_cb(){
	THIS_PAGE = MAIN_PAGE_ID;
}
