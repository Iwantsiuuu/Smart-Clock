#include "airQualityPage.h"
#include "menuDisp.h"
#include "stdio.h"
#include "string.h"

#define ENVI_PAGE 1

static char dps_buf_pressure[20],dps_buf_temperatur[20];

static uint8_t THIS_PAGE = 0;
static uint8_t INDEX_BACK = ENVI_PAGE+1;

void airQuality_disp(){

	init_airQuality_disp();

	while (1){

		speech_airQuality_cmd(&speech_command);
		if (THIS_PAGE == ENVI_PAGE)
			airQuality_draw();

		else {
			deinit_airQuality_disp();
			menu_disp();
		}
		vTaskDelay(20);
	}
	deinit_airQuality_disp();
}

static void init_airQuality_disp(){

	button.attachPressed(&btn_obj[3],prev_Cb);

	u8g2_ClearDisplay(&u8g2_obj);
	u8g2_ClearBuffer(&u8g2_obj);

	THIS_PAGE = ENVI_PAGE;
}

static void deinit_airQuality_disp(){

	//	Melakukan deattach button
	button.dettachPressed(&btn_obj[BUTTON_BACK]);//BACK

	u8g2_ClearDisplay(&u8g2_obj);
	u8g2_ClearBuffer(&u8g2_obj);
}

static void airQuality_getVal(){
	sprintf(dps_buf_pressure  ,"Pres :%0.2f\t hPa",dps_sensor.pressure);
	sprintf(dps_buf_temperatur,"Temp :%0.2f\t C\xB0",dps_sensor.temperature);
}

static void airQuality_draw(){
	airQuality_getVal();
	u8g2_DrawStr(&u8g2_obj, 0, 10, "Environment Data");
	u8g2_DrawStr(&u8g2_obj, 0, 30, dps_buf_pressure);
	u8g2_DrawStr(&u8g2_obj, 0, 40, dps_buf_temperatur);
	send_buffer_u8g2();
}

static void prev_Cb(){

	THIS_PAGE = INDEX_BACK; //index_back
}

static void speech_airQuality_cmd(uint8_t* cmd){
	switch(*cmd)
	{
	case BACK_CMD:
		THIS_PAGE = INDEX_BACK; //index_back
		break;
	}
}
