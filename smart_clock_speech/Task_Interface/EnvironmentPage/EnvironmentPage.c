#include "EnvironmentPage.h"
#include "menuDisp.h"

#define ENVI_PAGE 1

static char dps_buf_pressure[20],dps_buf_temperatur[20];

static uint8_t THIS_PAGE = 0;
static uint8_t INDEX_BACK = ENVI_PAGE+1;

void init_environment_disp(){

	button.attachPressed(&btn_obj[3],prev_Cb);

	u8g2_ClearDisplay(&u8g2_obj);
	u8g2_ClearBuffer(&u8g2_obj);

	THIS_PAGE = ENVI_PAGE;
}

void deinit_environment_disp(){

	//	Melakukan deattach button
	button.dettachPressed(&btn_obj[3]);//BACK

	u8g2_ClearDisplay(&u8g2_obj);
	u8g2_ClearBuffer(&u8g2_obj);
}

void environment_getVal(){
	sprintf(dps_buf_pressure  ,"Pres :%0.2f\t hPa",dps_sensor.pressure);
	sprintf(dps_buf_temperatur,"Temp :%0.2f\t C\xB0",dps_sensor.temperature);
}

void environment_draw(){
	environment_getVal();
	u8g2_DrawStr(&u8g2_obj, 0, 10, "Environment Data");
	u8g2_DrawStr(&u8g2_obj, 0, 30, dps_buf_pressure);
	u8g2_DrawStr(&u8g2_obj, 0, 40, dps_buf_temperatur);
	send_buffer_u8g2();
}

void environment_disp(){

	init_environment_disp();

	while (1){

		speech_environment_cmd(&speech_command);

		if (THIS_PAGE == ENVI_PAGE)
			environment_draw();

		else {
			deinit_environment_disp();
			menu_disp();
		}
		vTaskDelay(20);
	}
	deinit_environment_disp();
}

static void prev_Cb(){

	THIS_PAGE = INDEX_BACK; //Back to menu display
}

static void speech_environment_cmd(uint8_t* cmd){
	switch(*cmd)
	{
	case BACK_CMD:
		THIS_PAGE = INDEX_BACK;
		break;
	}
}
