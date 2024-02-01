#include "task_interface.h"
#include "interface.h"
#include "menuDisp.h"

interface_t interface_obj;

void displayOled(void *arg){

	const cyhal_i2c_cfg_t i2c_cfg =
	{
			.is_slave 		 = false,
			.address  		 = 0,
			.frequencyhal_hz = 400000
	};

	cyhal_i2c_t i2c;

	cyhal_i2c_init(&i2c, P6_1, P6_0, NULL);
	cyhal_i2c_configure(&i2c, &i2c_cfg);

	interface_construct(&interface_obj, &i2c);
	interface_begin(&interface_obj);

	//	while (!systemReady){
	//		vTaskDelay(5);
	//	}

	button.attachPressed(&btn_obj[1],test_CB);
	while(1){

		GUI_DispStringAt("Hallo", 10, 20);
		vTaskDelay(100);
	}
}

void test_CB(){
	printf("This Task Interface\r\n");
}
