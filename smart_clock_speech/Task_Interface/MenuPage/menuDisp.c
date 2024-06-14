#include "menuDisp.h"
#include "menu.h"
#include "EnvironmentPage.h"
#include "airQualityPage.h"
#include "timeDatePage.h"

#define tot_menu 4

menu_t menuObj;
u8g2_t u8g2;

uint8_t menu_cursor;
uint8_t index_back = tot_menu;

typedef enum {
	TIME_DATE,
	ENVIRONMENT,
	AIRQUALITY,
	STOPWATCH
}menu_var;

const char *menTest[]={
		"TIME AND DATE",
		"ENVIRONMENT",
		"AIR QUALITY",
		"STOPWATCH"
};

const char title_menu[] = {
		"Menu Page"
};

void init_menu_disp(){
	button.attachPressed(&btn_obj[BUTTON_UP],up_Cb);
	button.attachPressed(&btn_obj[BUTTON_DOWN],down_Cb);
	button.attachPressed(&btn_obj[BUTTON_ENTER],ok_Cb);
	button.attachPressed(&btn_obj[BUTTON_BACK],back_Cb);

	interface_construct(&menuObj, &u8g2);
	interface_begin(&menuObj);
	interface_setTitle(&menuObj, title_menu);
	interface_set_menu(&menuObj, menTest, tot_menu);
	interface_clearAll(&menuObj);
	menu_cursor=255;
}

void deinit_menu_disp(){
	//	Melakukan deattach button
	for (uint8_t i = 0; i < NUM_OF_BTN; i++)
		button.dettachPressed(&btn_obj[i]);
	interface_clearAll(&menuObj);
}

void menu_enter(uint8_t disp){
	switch(disp){
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
	}
}

void draw_menu(){
	interface_draw_menu(&menuObj);
	send_buffer_u8g2();
}

void menu_disp(){

	init_menu_disp();

	while (1){
		if (menu_cursor != 255){
			if (menu_cursor == index_back){
				u8g2_ClearBuffer(&u8g2);
				main_page();
				break;
			}
			else{
				deinit_menu_disp();
				menu_enter(menu_cursor);
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
	menu_cursor = interface_getPosition(&menuObj);
}

static void back_Cb(){

	//	Jika page sedang di dalam menu setting jam/tanggal maka akan kembali ke menu page
	menu_cursor = index_back; //index_back
}
