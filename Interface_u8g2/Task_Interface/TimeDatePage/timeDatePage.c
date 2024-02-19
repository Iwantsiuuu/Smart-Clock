#include "timeDatePage.h"

u8g2_t TD_obj;

//void init_menu_disp(){
//	button.attachPressed(&btn_obj[0],up_Cb);
//	button.attachPressed(&btn_obj[1],down_Cb);
//	button.attachPressed(&btn_obj[2],ok_Cb);
//	button.attachPressed(&btn_obj[3],back_Cb);
//}
//
//void deinit_menu_disp(){
//	//	Melakukan deattach button
//	button.dettachPressed(&btn_obj[0]);//UP
//	button.dettachPressed(&btn_obj[1]);//DOWN
//	button.dettachPressed(&btn_obj[2]);//ENTER
//	button.dettachPressed(&btn_obj[3]);//BACK
//}

void setTimeDate(){
	printf("SETTING TIME AND DATE\r\n");
}

//void menu_disp(){
//	init_menu_disp();
//	/**
//	 * wwhile(1)
//	 * {
//	 * 	if(menu_cursor !=255)
//	 * 	{
//	 *
//	 * 		if (menu_cursor==(tot_menu-1)
//	 * 			break;
//	 * 		else
//	 * 			menu_sel(menu_sel);
//	 * 	}else
//	 * 		interface_draw_menu
//	 * 	delay(50);
//	 * };
//	 * deinit_menu_disp();
//	 */
//
//	while (1){
//		if (menu_cursor != 255){
//			if (menu_cursor == index_back){
//				init_main_page();
//				break;
//			}
//			else
//				menu_enter(menu_cursor);
//		}
//		else
//			interface_draw_menu(&interface_obj);
//		vTaskDelay(20);
//	}
//	deinit_menu_disp();
//}
//
//static void up_Cb(void *arg){
//	interface_previous(&interface_obj);
//}
//
//static void down_Cb(void *arg){
//	interface_next(&interface_obj);
//}
//
//static void ok_Cb(void *arg){
//	menu_cursor = interface_getPosition(&interface_obj);
//}
//
//static void back_Cb(void *arg){
//
//	//	Jika page sedang di dalam menu setting jam/tanggal maka akan kembali ke menu page
//	//	if (this_page != MAIN_PAGE_ID && this_page != MENU_PAGE_ID)
//	menu_cursor = index_back; //index_back
//
//	//	jika page berada di menu page, maka akan kembali ke main page
//	if (this_page == MENU_PAGE_ID)
//		this_page = MAIN_PAGE_ID;
//}
