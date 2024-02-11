#ifndef TASK_DPS310_H_
#define TASK_DPS310_H_

#include "cyhal.h"
#include "cybsp.h"
//#include "cy_retarget_io.h"

/*Include FreeRTOS*/
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "queue.h"
#include "task.h"

#include "xensiv_dps3xx_mtb.h"

extern float pressure;
extern float temperature;

void dps310_val(void *arg);

#endif
