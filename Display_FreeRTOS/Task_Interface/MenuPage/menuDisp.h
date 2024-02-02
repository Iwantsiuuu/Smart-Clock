#ifndef MENUDISP_H_
#define MENUDISP_H_

#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

/*Include FreeRTOS*/
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "queue.h"
#include "task.h"

//#include "interface.h"
#include "button.h"
#include "task_button.h"
#include "task_interface.h"

void loop_menu_disp();
void init_menu_disp();
void deinit_menu_disp();
void menu_disp();

static void up_Cb();
static void down_Cb();
static void ok_Cb();
static void back_Cb();

#endif
