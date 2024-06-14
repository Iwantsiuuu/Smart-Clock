/*
 *
 * main_page.c
 *
 * Created on  : 03 April 2024
 * 	    Author : Ridwan Bahari
 * 	    E-Mail : ridwanbahari236@gmail.com
 *
 */
#include "rtc_sc.h"
#include "main_ble.h"
#include "main_page.h"
#include "task_button.h"
#include "task_sensor.h"
#include "voice_command.h"
#include "task_interface.h"

#define MAIN_PAGE_ID (1)
#define MENU_PAGE_ID (2)

enum mode{
	DEFAULT_MODE,
	BLUETOOTH_MODE
};

struct tm RTC_TIME;

char buf_temp [20];

static uint8_t THIS_PAGE = 0;
static uint8_t MODE_DISPLAY = 0;

uint8_t RTC_ENABLE;

uint8_t koordinatX_oled = 0, koordinatY_oled = 0;

void main_page(){
	init_main_page();

	while (1){

		speech_cmd_main_page(&speech_command);

		if (THIS_PAGE == MAIN_PAGE_ID){
			if (MODE_DISPLAY == DEFAULT_MODE)
				default_mode_draw();
			else
				bluetooth_mode_draw();
		}
		else{
			deinit_main_page();
			menu_disp();
			init_main_page();
		}
		vTaskDelay(50);
	}
	deinit_main_page();
}

static void default_mode_draw(){
	disable_ble();

	char buf_time[STRING_BUFFER_SIZE];
	char buf_date[STRING_BUFFER_SIZE];

//	wiced_bt_start_advertisements( BTM_BLE_ADVERT_UNDIRECTED_HIGH, 0, NULL );

	cyhal_rtc_read(&rtc_obj, &RTC_TIME);

	strftime(buf_time, sizeof(buf_time), "%X %p", &RTC_TIME);
	strftime(buf_date, STRING_BUFFER_SIZE, "%b %d, %Y", &RTC_TIME);

	sprintf(buf_temp,"%0.0f C\xB0\r\n", dps_sensor.temperature);

	u8g2_DrawStr(&u8g2_obj, (koordinatX_oled+110), (koordinatY_oled+8), "80%");
	u8g2_DrawStr(&u8g2_obj, (koordinatX_oled+35), (koordinatY_oled+25), buf_time);
	u8g2_DrawStr(&u8g2_obj, (koordinatX_oled+30), (koordinatY_oled+35), buf_date);
	u8g2_DrawStr(&u8g2_obj, (koordinatX_oled+45), (koordinatY_oled+50), buf_temp);

	send_buffer_u8g2();
}

static void bluetooth_mode_draw(){

	wiced_bt_start_advertisements( BTM_BLE_ADVERT_UNDIRECTED_HIGH, 0, NULL );

	u8g2_DrawStr(&u8g2_obj, koordinatX_oled+110, koordinatY_oled+8, "80%");
	u8g2_DrawStr(&u8g2_obj, koordinatX_oled+20, koordinatY_oled+25, "Bluetooth Mode");

	send_buffer_u8g2();
}

static void init_main_page()
{
	// attach button
	button.attachPressed(&btn_obj[BUTTON_ENTER], enter_menu_cb);
	button.attachPressed(&btn_obj[BUTTON_DOWN], main_page_mode);

	THIS_PAGE = MAIN_PAGE_ID;
	MODE_DISPLAY = 0;
}

static void deinit_main_page(){
	// de attach button
	for (uint8_t i = 0; i < NUM_OF_BTN; i++)
		button.dettachPressed(&btn_obj[i]);

	disable_ble();
}

static void enter_menu_cb()
{
	THIS_PAGE = MENU_PAGE_ID;
}

static void main_page_mode()
{
	MODE_DISPLAY++;
	if (MODE_DISPLAY > BLUETOOTH_MODE)
		MODE_DISPLAY = DEFAULT_MODE;
}

static void speech_cmd_main_page(uint8_t* cmd)
{
	switch(*cmd){
	case DEFAULT_MODE_CMD:
		printf("Default Mode\r\n");
		MODE_DISPLAY = DEFAULT_MODE;
		break;

	case BLUETOOTH_MODE_CMD:
		printf("Bluetooth Mode\r\n");
		MODE_DISPLAY = BLUETOOTH_MODE;
		break;

	case SHOW_MENU_CMD:
		printf("Go to menu\r\n");
		THIS_PAGE = MENU_PAGE_ID;
	}
}

static void disable_ble()
{

	if(wiced_bt_ble_get_current_advert_mode() ==  BTM_BLE_ADVERT_UNDIRECTED_HIGH)
		wiced_bt_start_advertisements( BTM_BLE_ADVERT_OFF, 0, NULL );

	if(connection_id != 0)
		wiced_bt_gatt_disconnect(connection_id);
}
