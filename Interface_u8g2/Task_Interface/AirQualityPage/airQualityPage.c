#include "airQualityPage.h"
#include "menuDisp.h"

#define AQ_PAGE 1

static uint8_t THIS_PAGE = 0;
static uint8_t idx_back = AQ_PAGE+1;

void init_air_quality_disp(){

	button.attachPressed(&btn_obj[3],BackAQ_Cb);

	u8g2_ClearDisplay(&u8g2_obj);
	u8g2_ClearBuffer(&u8g2_obj);

	THIS_PAGE = AQ_PAGE;
}

void deinit_air_quality_disp(){

	//	Melakukan deattach button
	button.dettachPressed(&btn_obj[3]);//BACK
}

void air_quality_draw(float *Press, float *Temp){

}

void air_quality_disp(){

	init_air_quality_disp();

	while (1){
		if (THIS_PAGE == AQ_PAGE){
			u8g2_DrawStr(&u8g2_obj, 50, 61, "Tesshadgsdafsjf");
			send_buffer_u8g2();
			printf("Page AQ\r\n");
		}

		else {
			deinit_air_quality_disp();
			menu_disp();
		}
		vTaskDelay(20);
	}
	deinit_air_quality_disp();
}

static void BackAQ_Cb(){

	THIS_PAGE = idx_back; //index_back
}
