/*
 * task_sensor.c
 *
 *  Created on: 16 Feb 2024
 *      Author: DwiSetyabudi
 */

#include "task_sensor.h"
#include "main.h"

sensor_data dps_sensor;
sensor_data bmp_sensor;

xensiv_dps3xx_t pressure_sensor;

void sensor_App(void *arg)
{
	//	printf(" task sensor \r\n");
	//if (bmp280.init(&i2c, BMP280_ADDR) != BMP280_SUCCESS)
	//{

//	if( xensiv_dps3xx_mtb_init_i2c(&pressure_sensor, &i2c, 0x77) == CY_RSLT_SUCCESS )
//		systemReady = true;
	//}

	while(!systemReady){
		vTaskDelay(5);
	}

	uint32_t time_update = 0;
	while(1)
	{
		if( xTaskGetTickCount() - time_update >= 1000)
		{
			if (semphr_i2c_dev != NULL){
				if(xSemaphoreTake(semphr_i2c_dev, ( TickType_t ) 100)){

					xensiv_dps3xx_read(&pressure_sensor, &dps_sensor.pressure, &dps_sensor.temperature);
					printf("%0.2f\r\n",dps_sensor.pressure);
					//BMP280_readValue(&bmp_sensor.temperature, &bmp_sensor.pressure, 100);

					xSemaphoreGive(semphr_i2c_dev);
					time_update = xTaskGetTickCount();
				}
			}

		}
		vTaskDelay(100);
	};
}
