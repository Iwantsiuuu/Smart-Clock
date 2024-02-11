#ifndef TASK_BMP280_H_
#define TASK_BMP280_H_

#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

/*Include FreeRTOS*/
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "queue.h"
#include "task.h"

#include "BMP280.h"

extern float temp,press;

void bmp280_data(void *arg);

#endif
