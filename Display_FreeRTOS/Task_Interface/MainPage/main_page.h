#ifndef MAIN_PAGE_H_
#define MAIN_PAGE_H_

#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

/*Include FreeRTOS*/
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "queue.h"
#include "task.h"

#include "button.h"
#include "task_button.h"
#include "task_interface.h"
#include "menuDisp.h"

#define MAIN_PAGE_ID (1)

void main_page();
void deinit_main_page();

void tempVal(uint8_t val);

void enter_menu_cb();
void wake_up_cb();

#endif
