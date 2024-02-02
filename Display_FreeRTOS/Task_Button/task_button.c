#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

/*Include FreeRTOS*/
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "queue.h"
#include "task.h"

#include "button.h"
#include "task_button.h"

button_var btn_obj[NUM_OF_BTN];

cyhal_gpio_t btn_pin[NUM_OF_BTN] = {
		BTN_UP,
		BTN_DOWN,
		BTN_ENTER,
		BTN_BACK
};

bool systemReady = false;
void ButtonApp(void *arg){

	button.setTick(xTaskGetTickCount);

	button.setHoldTime(&btn_obj[0], 100);	//Button Up
	button.setHoldTime(&btn_obj[1], 100);	//Button Down
	button.setHoldTime(&btn_obj[2], 200);	//Button Enter
	button.setHoldTime(&btn_obj[3], 200);	//Button Back

	button.setDebounceTime(&btn_obj[0],10);
	button.setDebounceTime(&btn_obj[1],10);
	button.setDebounceTime(&btn_obj[2],50);
	button.setDebounceTime(&btn_obj[3],50);

	for (uint8_t i = 0; i < NUM_OF_BTN; i++){
		if( button.create(&btn_obj[i], btn_pin[i], BUTTON_LOW, 200) == CY_RSLT_SUCCESS )
			printf(" button initialize success \r\n");
	}

	systemReady = true;
	uint8_t btn_num = 0;

	button.attachPressed(&btn_obj[0], cb);

	for(;;){

		button.check(&btn_obj[btn_num]);
		btn_num++;
		if (btn_num >= NUM_OF_BTN)
			btn_num = 0;

		vTaskDelay(2);

	}
}

void cb(){
	printf("This Task Button\r\n");
}
