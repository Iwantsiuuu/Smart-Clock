//#include "../../test/dps/task_dps310.h"
//
//#include "task_interface.h"
//
//xensiv_dps3xx_t pressure_sensor;
//
//float pressure;
//float temperature;
//
//void dps310_val(void *arg){
//
//	xensiv_dps3xx_mtb_init_i2c(&pressure_sensor, &i2c, 0x77);
//
//	while(1){
//		xensiv_dps3xx_read(&pressure_sensor, &pressure, &temperature);
//		vTaskDelay(1000);
//	}
//}
