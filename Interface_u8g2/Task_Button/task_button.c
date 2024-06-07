#include "task_button.h"

button_var btn_obj[NUM_OF_BTN];

cyhal_gpio_t btn_pin[NUM_OF_BTN] = {
		BTN_UP,
		BTN_DOWN,
		BTN_ENTER,
		BTN_BACK
};


void ButtonApp(void *arg){

	while(!systemReady){
		vTaskDelay(5);
	}

	uint8_t btn_num = 0;

	for(;;){

		button.check(&btn_obj[btn_num]);
		btn_num++;
		if (btn_num >= NUM_OF_BTN)
			btn_num = 0;
		vTaskDelay(1);

	}
}

void buttonInit(void){
	button.setTick(xTaskGetTickCount);

	for (uint8_t i = 0; i < NUM_OF_BTN; i++){
		button.setHoldTime(&btn_obj[i], 150);
		button.setDebounceTime(&btn_obj[i],20);
	}

	for (uint8_t i = 0; i < NUM_OF_BTN; i++){
		if( button.create(&btn_obj[i], btn_pin[i], BUTTON_LOW, 200) == CY_RSLT_SUCCESS )
			printf(" button %i initialize success \r\n", i+1);
	}
}
