#include "menuDisp.h"
#include "interface.h"

uint8_t menu_cursor;
uint8_t index_back;

void loop_menu_disp(){
	init_menu_disp();
	while(1){
		if (menu_cursor != 255){
			if (menu_cursor == index_back)
				break;
			switch (menu_cursor){
			case 0:
				uint8_t setTime;
			case 1:
				uint8_t BMP280;
			case 2:
				uint8_t PASCO2;
			case 3:
				uint8_t Air_quality;
			}
		vTaskDelay(5);
		}
	}
}

void init_menu_disp(){
	button.attachPressed(&btn_obj[0],up_Cb);
	button.attachPressed(&btn_obj[1],down_Cb);
	button.attachPressed(&btn_obj[2],ok_Cb);
	button.attachPressed(&btn_obj[3],back_Cb);
}

void deinit_menu_disp(){
	button.dettachPressed(&btn_obj[0]);//UP
	button.dettachPressed(&btn_obj[1]);//DOWN
	button.dettachPressed(&btn_obj[2]);//ENTER
	button.dettachPressed(&btn_obj[3]);//BACK
}

void menu(){
	init_menu_disp();
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
	menu_cursor = index_back; //index_back
}
