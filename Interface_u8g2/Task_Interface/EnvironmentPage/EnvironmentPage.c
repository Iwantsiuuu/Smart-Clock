#include "EnvironmentPage.h"
#include "menuDisp.h"

u8g2_t u8g2_obj1;
uint8_t id_envr;
uint8_t idx_back = 150;

void init_environment_disp(){

	button.attachPressed(&btn_obj[3],prev_Cb);

	THIS_PAGE = ENVIRONMENT_PAGE_ID;

	/* Initialize the U8 Display */
	u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2_obj1, U8G2_R0, u8x8_byte_hw_i2c,
			u8x8_gpio_and_delay_cb);
	/* Send init sequence to the display, display is in sleep mode after this */
	u8g2_InitDisplay(&u8g2_obj1);
	/* Wake up display */
	u8g2_SetPowerSave(&u8g2_obj1, 0);

	/* Prepare display for printing */
	u8g2_SetFont(&u8g2_obj1, u8g2_font_6x12_tf);
	u8g2_ClearDisplay(&u8g2_obj1);
	u8g2_ClearBuffer(&u8g2_obj1);

	id_envr=255;
}

void deinit_environment_disp(){

	//	Melakukan deattach button
	button.dettachPressed(&btn_obj[3]);//BACK

	u8g2_ClearDisplay(&u8g2_obj1);
	u8g2_ClearBuffer(&u8g2_obj1);
}

void environment_draw(float *Press, float *Temp){
	u8g2_DrawStr(&u8g2_obj1, 20, 30, "Tess");
}

void just_draw(){
	u8g2_DrawStr(&u8g2_obj1, 20, 30, "Tess");
}

void environment_disp(){

	init_environment_disp();
	deinit_menu_disp();
	while (1){

		if (THIS_PAGE == ENVIRONMENT_PAGE_ID)
			just_draw();

		if (id_envr == idx_back)
			menu_disp();
//			break;
		u8g2_ClearBuffer(&u8g2_obj1);

		vTaskDelay(20);
	}
	deinit_environment_disp();
}

static void prev_Cb(){

	id_envr = idx_back; //index_back

	//	jika page berada di menu page, maka akan kembali ke main page
	if (THIS_PAGE == ENVIRONMENT_PAGE_ID)
		THIS_PAGE = MENU_PAGE_ID;

}
