#include "task_dps310.h"
#include "i2c_init.h"

xensiv_dps3xx_t pressure_sensor;

float pressure;
float temperature;

void dps310_val(void *arg){

	xensiv_dps3xx_mtb_init_i2c(&pressure_sensor, &i2c_sens, 0x77);

	while(1){
		xensiv_dps3xx_read(&pressure_sensor, &pressure, &temperature);
		vTaskDelay(1000);
	}
}
