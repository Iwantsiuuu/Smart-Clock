#include "timeDatePage.h"
#include "rtc_sc.h"

#define RTC_PAGE 1

#define DEAFULT_VARIABLE_VALUE 		(0)
#define NUM_DAY						(31)
#define NUM_MONTH					(12)
#define NUM_HOUR					(23)
#define NUM_MINUTE					(59)
#define NUM_SECON					(59)

#define NUM_BUTTON					(4)

#define BUTTON_INCREMENT_VAR 		(0)
#define BUTTON_DECREMENT_VAR		(1)
#define BUTTON_OK_AND_SWITCH_VAR	(2)
#define BUTTON_BACK_TO_MENU			(3)

static uint8_t THIS_PAGE = 0;
static uint8_t idx_back = RTC_PAGE+1;
static uint8_t current_var = 0;
static uint8_t num_var = 6;
static bool confirm_flag = false;

enum var_rtc{
	Hour,
	Minute,
	Secon,
	Day,
	Month,
	Year
};

void init_rtc_disp(){

	button.attachPressed(&btn_obj[BUTTON_INCREMENT_VAR],increment_var_cb);
	button.attachPressed(&btn_obj[BUTTON_DECREMENT_VAR],decrement_var_cb);
	button.attachPressed(&btn_obj[BUTTON_OK_AND_SWITCH_VAR],switch_var_cb);
	button.attachPressed(&btn_obj[BUTTON_BACK_TO_MENU],back_rtc_cb);

	button.attachHeld(&btn_obj[BUTTON_OK_AND_SWITCH_VAR],confirm_cb);

	u8g2_ClearDisplay(&u8g2_obj);
	u8g2_ClearBuffer(&u8g2_obj);

	THIS_PAGE = RTC_PAGE;
}

void deinit_rtc_disp(){
	//	Melakukan deattach button
	for (uint8_t i = 0; i < NUM_BUTTON; i++)
		button.dettachPressed(&btn_obj[i]);
}

static void rtc_draw(){

}

void rtc_disp(){
	init_rtc_disp();
	while (1){
		if (THIS_PAGE == RTC_PAGE)
			rtc_draw();
		else{
			deinit_rtc_disp();
			menu_disp();
		}
		vTaskDelay(20);
	}
	deinit_rtc_disp();
}

static void increment_var_cb(){
	switch (current_var){
	case Hour :
		RTC_Setup.hour++;
		if (RTC_Setup.hour > NUM_HOUR)
			RTC_Setup.hour = DEAFULT_VARIABLE_VALUE;
		break;

	case Minute :
		RTC_Setup.min++;
		if (RTC_Setup.min > NUM_MINUTE)
			RTC_Setup.min = DEAFULT_VARIABLE_VALUE;
		break;

	case Secon :
		RTC_Setup.sec++;
		if (RTC_Setup.sec > NUM_SECON)
			RTC_Setup.sec = DEAFULT_VARIABLE_VALUE;
		break;

	case Day :
		RTC_Setup.mday++;
		if (RTC_Setup.mday > NUM_DAY)
			RTC_Setup.mday = DEAFULT_VARIABLE_VALUE;
		break;

	case Month :
		RTC_Setup.month++;
		if (RTC_Setup.month > NUM_MONTH)
			RTC_Setup.month = DEAFULT_VARIABLE_VALUE;
		break;

	case Year :
		RTC_Setup.Year++;
		break;
	}
}
static void decrement_var_cb(){
	switch (current_var){
	case Hour :
		RTC_Setup.hour--;
		if (RTC_Setup.hour < DEAFULT_VARIABLE_VALUE)
			RTC_Setup.hour = NUM_HOUR;
		break;

	case Minute :
		RTC_Setup.min--;
		if (RTC_Setup.min < DEAFULT_VARIABLE_VALUE)
			RTC_Setup.min = NUM_MINUTE;
		break;

	case Secon :
		RTC_Setup.sec--;
		if (RTC_Setup.sec < DEAFULT_VARIABLE_VALUE)
			RTC_Setup.sec = NUM_SECON;
		break;

	case Day :
		RTC_Setup.mday--;
		if (RTC_Setup.mday < DEAFULT_VARIABLE_VALUE)
			RTC_Setup.mday = NUM_DAY;
		break;

	case Month :
		RTC_Setup.month--;
		if (RTC_Setup.month < DEAFULT_VARIABLE_VALUE)
			RTC_Setup.month = NUM_MONTH;
		break;

	case Year :
		RTC_Setup.Year--;
		break;
	}
}
static void switch_var_cb(){
	current_var++;
	if (current_var > num_var)
		current_var = 0;
}
static void confirm_cb(){
	confirm_flag = true;
}
static void back_rtc_cb(){
	THIS_PAGE = idx_back; //index_back
}
