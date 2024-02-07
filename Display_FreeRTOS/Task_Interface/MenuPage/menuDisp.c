#include "menuDisp.h"
#include "interface.h"
#include "EnvironmentPage.h"

interface_t interface_obj;

uint8_t menu_cursor;
uint8_t index_back = 150;

typedef enum {
	TIME_DATE,
	ENVIRONMENT,
	AIRQUALITY,
	STOPWATCH
};

const char *menTest[]={
		"TIME AND DATE",
		"ENVIRONMENT",
		"AIR QUALITY",
		"STOPWATCH"
};

const char ti_menu[] = {
		"Menu Page"
};

uint8_t tot_menu = (sizeof(menTest)/sizeof(menTest[0]));

void init_menu_disp(){
	button.attachPressed(&btn_obj[0],up_Cb);
	button.attachPressed(&btn_obj[1],down_Cb);
	button.attachPressed(&btn_obj[2],ok_Cb);
	button.attachPressed(&btn_obj[3],back_Cb);

	interface_construct(&interface_obj);
	interface_begin(&interface_obj);
	interface_setTitle(&interface_obj, ti_menu);
	interface_set_menu(&interface_obj, menTest, tot_menu);
	GUI_Clear();
	menu_cursor=255;
}

void deinit_menu_disp(){
	//	Melakukan deattach button
	button.dettachPressed(&btn_obj[0]);//UP
	button.dettachPressed(&btn_obj[1]);//DOWN
	button.dettachPressed(&btn_obj[2]);//ENTER
	button.dettachPressed(&btn_obj[3]);//BACK
	GUI_Clear();
}

/*
void menu_sel(uint8_t act){
	deinit
	switch(act)
	{
		menu1:
	}
	init
}*/

void menu_enter(uint8_t disp){
//	deinit_menu_disp();
	uint8_t x = 0, y = 0;
	switch(disp){
	case TIME_DATE :
		//		Function setting time and date
		GUI_DispStringAt("Time and Date", x+10, y+15);
		break;
	case ENVIRONMENT :
		//		Function BMP Value
		environment_disp();
		break;
	case AIRQUALITY :
		//		Function PASCO2
		GUI_DispStringAt("Air Quality", x+10, y+35);
		break;
	case STOPWATCH :
		//		Function StopWatch
		GUI_DispStringAt("StopWatch", x+10, y+45);
		break;
	}
}

void menu_disp(){
	init_menu_disp();
	/**
	 * wwhile(1)
	 * {
	 * 	if(menu_cursor !=255)
	 * 	{
	 *
	 * 		if (menu_cursor==(tot_menu-1)
	 * 			break;
	 * 		else
	 * 			menu_sel(menu_sel);
	 * 	}else
	 * 		interface_draw_menu
	 * 	delay(50);
	 * };
	 * deinit_menu_disp();
	 */

	while (1){
		if (menu_cursor != 255){
			if (menu_cursor == index_back){
				init_main_page();
				break;
			}
			else
				menu_enter(menu_cursor);
		}
		else
			interface_draw_menu(&interface_obj);
		vTaskDelay(20);
	}
	deinit_menu_disp();
}

static void up_Cb(void *arg){
	interface_previous(&interface_obj);
}

static void down_Cb(void *arg){
	interface_next(&interface_obj);
}

static void ok_Cb(void *arg){
	menu_cursor = interface_getPosition(&interface_obj);
}

static void back_Cb(void *arg){

	//	Jika page sedang di dalam menu setting jam/tanggal maka akan kembali ke menu page
	menu_cursor = index_back; //index_back

	//	jika page berada di menu page, maka akan kembali ke main page
	if (this_page == MENU_PAGE_ID)
		this_page = MAIN_PAGE_ID;

}
