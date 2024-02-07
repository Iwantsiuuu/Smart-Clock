#include "main_page.h"
#include "stdio.h"

char volatile buf_time_date [20];
uint8_t Temps = 0;
uint8_t x, y;

void TempsVal(uint8_t val){
	Temps += val;
}

void main_page(){
	init_main_page();
	while (1){
		TempsVal(1);
		if (this_page == MAIN_PAGE_ID){
			sprintf(buf_time_date,"%4d C\xB0\r\n", Temps);
			GUI_DispStringAt("80%", x+110, y+0);
			GUI_DispStringAt("08:00 am", x+35, y+20);
			GUI_DispStringAt("Feb 5, 2024", x+30, y+30);
			GUI_DispStringAt(buf_time_date, x+45, y+40);
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
	GUI_Clear();
}

void deinit_main_page(){
	// de attach button
	for (uint8_t i = 0; i < 2; i++)
		button.dettachPressed(&btn_obj[i]);
}

void enter_menu_cb(){
	this_page = MENU_PAGE_ID;
	printf("Test enter\r\n");

}

void wake_up_cb(){
	this_page = MAIN_PAGE_ID;
	printf("Test WakeUp\r\n");
}
