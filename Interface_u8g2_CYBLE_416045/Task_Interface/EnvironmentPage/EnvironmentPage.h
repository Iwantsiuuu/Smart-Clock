#ifndef ENVIRONMENTPAGE_H_
#define ENVIRONMENTPAGE_H_

#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

/*Include FreeRTOS*/
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "queue.h"
#include "task.h"

#include "task_button.h"
#include "task_interface.h"
#include "task_sensor.h"

void init_environment_disp();
void deinit_environment_disp();
void environment_disp();
void environment_draw();
void environment_getVal();

static void select_Cb();
static void prev_Cb();

#endif