/*
 *  main.h
 *  Created on: 16 Feb 2024
 *      Author: DwiSetyabudi
 */
#pragma once
#ifndef MAIN_H_
#define MAIN_H_


#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

/*Include FreeRTOS*/
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "semphr.h"
#include "task.h"

#include "setup_i2c.h"

// task handler
extern TaskHandle_t buttonHandle;
extern TaskHandle_t displayHandle;
extern TaskHandle_t sensorHandle;

// semaphore
extern SemaphoreHandle_t semphr_i2c_dev;
extern bool systemReady;

#endif /* MAIN_H_ */
