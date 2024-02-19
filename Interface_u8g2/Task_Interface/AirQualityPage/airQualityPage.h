#ifndef AIRQUALITY_H_
#define AIRQUALITY_H_

#include "task_button.h"
#include "task_interface.h"
#include "task_sensor.h"

void init_air_quality_disp();
void deinit_air_quality_disp();
void air_quality_disp();
void air_quality_draw(float *Press, float *Temp);

static void BackAQ_Cb();

#endif
