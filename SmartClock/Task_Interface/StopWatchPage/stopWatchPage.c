#include "stopWatchPage.h"
#include "menuDisp.h"

#define SW_PAGE 1

static bool countSW = false;
static char buf_stopWatch[100];

static uint8_t THIS_PAGE = 0;
static uint8_t idx_back = SW_PAGE+1;
static uint16_t hour = 0, minute = 0, second = 0, mili_second = 0, over;
static uint32_t firstT, time_now, dtStopWatch;

void init_stopWatch_disp(){

	button.attachPressed(&btn_obj[BUTTON_ENTER],startSW_Cb);
	button.attachPressed(&btn_obj[BUTTON_DOWN],pauseSW_Cb);
	button.attachPressed(&btn_obj[BUTTON_UP],resetSW_Cb);
	button.attachPressed(&btn_obj[BUTTON_BACK],BackSW_Cb);

	u8g2_ClearDisplay(&u8g2_obj);
	u8g2_ClearBuffer(&u8g2_obj);

	THIS_PAGE = SW_PAGE;
}

void deinit_stopWatch_disp(){

	//	Melakukan deattach button
	for (uint8_t i = 0; i < 4; i++)
		button.dettachPressed(&btn_obj[i]);
}

void stopwatch(){
	if (countSW){
		time_now = xTaskGetTickCount();
		dtStopWatch = time_now - firstT;

		hour 		= dtStopWatch / 3600000;
		over 		= dtStopWatch % 3600000;
		minute 		= over / 60000;
		over 		= over % 60000;
		second 		= over / 1000;
		mili_second = over % 1000;
	}
	else if (countSW == false && dtStopWatch == 0){
		hour = 0, minute = 0, second = 0, mili_second = 0;
	}
	sprintf(buf_stopWatch,"%d:%d:%d:%d\r\n",hour,minute,second,mili_second);
}

void stopWatch_draw(){
	stopwatch();
	u8g2_DrawStr(&u8g2_obj, 0, 15, "StopWatch");
	u8g2_DrawStr(&u8g2_obj, 0, 25, buf_stopWatch);
	send_buffer_u8g2();
}

void stopWatch_disp(){

	init_stopWatch_disp();

	while (1){
		if (THIS_PAGE == SW_PAGE)
			stopWatch_draw();
		else {
			deinit_stopWatch_disp();
			menu_disp();
		}
		vTaskDelay(20);
	}
	deinit_stopWatch_disp();
}

static void startSW_Cb(){
	firstT = xTaskGetTickCount() - dtStopWatch;
	countSW = true;
}

static void pauseSW_Cb(){
	countSW = false;
}

static void resetSW_Cb(){
	countSW = false;
	dtStopWatch = 0;
}

static void BackSW_Cb(){
	THIS_PAGE = idx_back; //index_back
}
