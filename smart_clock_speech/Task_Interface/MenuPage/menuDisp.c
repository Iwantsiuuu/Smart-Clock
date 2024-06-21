#include "menuDisp.h"
#include "menu.h"
#include "EnvironmentPage.h"
#include "airQualityPage.h"
#include "timeDatePage.h"

#define TOTAL_MENU 5

menu_t menuObj;
u8g2_t u8g2;

uint8_t CURSOR;
uint8_t INDEX_BACK = TOTAL_MENU;

enum menu_var {
	TIME_DATE,
	ENVIRONMENT,
	AIRQUALITY,
	STOPWATCH,
	ALARM
};

const char *MENU_SMART_CLOCK[]={
		"TIME AND DATE",
		"ENVIRONMENT",
		"AIR QUALITY",
		"STOPWATCH",
		"ALARM"
};

const char TITLE_MENU[9] = {
		"MENU PAGE"
};

void init_menu_disp(){
	button.attachPressed(&btn_obj[BUTTON_UP],up_Cb);
	button.attachPressed(&btn_obj[BUTTON_DOWN],down_Cb);
	button.attachPressed(&btn_obj[BUTTON_ENTER],ok_Cb);
	button.attachPressed(&btn_obj[BUTTON_BACK],back_Cb);

	interface_construct(&menuObj, &u8g2);
	interface_begin(&menuObj);
	interface_setTitle(&menuObj, TITLE_MENU);
	interface_set_menu(&menuObj, MENU_SMART_CLOCK, TOTAL_MENU);
	interface_clearAll(&menuObj);
	CURSOR=255;
}

void deinit_menu_disp(){
	//	Melakukan deattach button
	for (uint8_t i = 0; i < NUM_OF_BTN; i++)
		button.dettachPressed(&btn_obj[i]);
	interface_clearAll(&menuObj);
}

void menu_enter(uint8_t *disp){
	switch(*disp){
	case TIME_DATE :
		//		Function setting time and date
		rtc_disp();
		break;

	case ENVIRONMENT :
		//		Function BMP Value
		environment_disp();
		break;

	case AIRQUALITY :
		//		Function PASCO2
		airQuality_disp();
		break;

	case STOPWATCH :
		//		Function StopWatch
		stopWatch_disp();
		break;

	case ALARM :
		//		Function StopWatch
		stopWatch_disp();
		break;
	}
}

void draw_menu(){
	interface_draw_menu(&menuObj);
	send_buffer_u8g2();
}

void menu_disp(){

	init_menu_disp();

	while (1){

		speech_menu_cmd(&speech_command);

		if (CURSOR != 255){
			if (CURSOR == INDEX_BACK){
				u8g2_ClearBuffer(&u8g2);
				main_page();
				break;
			}
			else{
				deinit_menu_disp();
				menu_enter(&CURSOR);
				init_menu_disp();
			}
		}
		else
			draw_menu();
		vTaskDelay(20);
	}
	deinit_menu_disp();
}

static void up_Cb(){
	interface_previous(&menuObj);
}

static void down_Cb(){
	interface_next(&menuObj);
}

static void ok_Cb(){
	CURSOR = interface_getPosition(&menuObj);
}

static void back_Cb(){

	//	Jika page sedang di dalam menu setting jam/tanggal maka akan kembali ke menu page
	CURSOR = INDEX_BACK; //INDEX_BACK
}

static void speech_menu_cmd(uint8_t *cmd){

	switch(*cmd)
	{
	case BACK_CMD:
		CURSOR = INDEX_BACK;
		break;

	case CLOCK_SETTING_CMD:
		CURSOR = TIME_DATE;
		break;

	case ENVIRONMENT_CMD:
		CURSOR = ENVIRONMENT;
		break;

	case AIR_QUALITY_CMD:
		CURSOR = AIRQUALITY;
		break;

	case STOPWATCH_CMD:
		CURSOR = STOPWATCH;
		break;

	case ALARM_SETTING_CMD:
		CURSOR = ALARM;
		break;
	}
}
