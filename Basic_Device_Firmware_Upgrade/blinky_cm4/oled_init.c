#include "oled_init.h"

u8g2_t u8g2_obj;

void init_oled(){

	mtb_ssd1306_init_i2c(&i2c_obj);

	/* Initialize the U8 Display */
	u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2_obj, U8G2_R0, u8x8_byte_hw_i2c, u8x8_gpio_and_delay_cb);

	/* Send init sequence to the display, display is in sleep mode after this */
	u8g2_InitDisplay(&u8g2_obj);

	/* Wake up display */
	u8g2_SetPowerSave(&u8g2_obj, 0);

	/* Prepare display for printing */
	u8g2_SetFont(&u8g2_obj, u8g2_font_6x12_tf);
	u8g2_ClearDisplay(&u8g2_obj);
	u8g2_ClearBuffer(&u8g2_obj);

}
