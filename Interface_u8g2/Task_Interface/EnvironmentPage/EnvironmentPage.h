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

//#include "interface.h"
//#include "button.h"
#include "task_button.h"
#include "task_interface.h"
#include "task_bmp280.h"
//#include "main_page.h"

//#define ENVIRONMENT_PAGE_ID (4)

void init_environment_disp();
void deinit_environment_disp();
void environment_disp();
void environment_draw(float *Press, float *Temp);
void just_draw();


static void select_Cb();
static void prev_Cb();

#endif
