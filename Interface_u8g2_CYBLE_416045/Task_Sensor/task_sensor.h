/*
 * task_sensor.h
 *
 *  Created on: 16 Feb 2024
 *      Author: DwiSetyabudi
 */

#ifndef TASK_SENSOR_TASK_SENSOR_H_
#define TASK_SENSOR_TASK_SENSOR_H_


#include "BMP280.h"
#include "xensiv_dps3xx_mtb.h"

typedef struct{
	float temperature,
		  pressure;
}sensor_data;

extern sensor_data dps_sensor;
extern sensor_data bmp_sensor;
void sensor_App(void *arg);


#endif /* TASK_SENSOR_TASK_SENSOR_H_ */
