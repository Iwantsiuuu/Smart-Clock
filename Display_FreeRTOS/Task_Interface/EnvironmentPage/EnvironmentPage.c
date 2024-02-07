#include "EnvironmentPage.h"
#include "menuDisp.h"
uint8_t cursor;
uint8_t idx_back = 150;

void init_environment_disp(){
//	button.attachPressed(&btn_obj[2],select_Cb);
	button.attachPressed(&btn_obj[3],prev_Cb);

	GUI_Clear();
	cursor=255;
}

void deinit_environment_disp(){
	//	Melakukan deattach button
//	button.dettachPressed(&btn_obj[2]);//ENTER
	button.dettachPressed(&btn_obj[3]);//BACK
	GUI_Clear();
}

void environment_draw(float *Press, float *Temp){
	GUI_DispStringAt("Hallo", 20, 20);
}

void environment_disp(){

	init_environment_disp();
	deinit_menu_disp();
	while (1){
		if (cursor == idx_back){
			init_main_page();
			break;
		}
		else
			environment_draw(&press,&temp);

		vTaskDelay(20);
	}
	deinit_environment_disp();
	menu_disp();
}

//static void selsect_Cb(){
//	menu_cursor = ;
//}

static void prev_Cb(){

	cursor = idx_back; //index_back

	//	jika page berada di menu page, maka akan kembali ke main page
	if (this_page == ENVIRONMENT_PAGE_ID)
		this_page = MENU_PAGE_ID;

}
