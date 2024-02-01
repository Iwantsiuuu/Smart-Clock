#ifndef TASK_INTERFACE_H_
#define TASK_INTERFACE_H_

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

//extern interface_t interface_obj;
void test_CB();
void displayOled(void *arg);

#endif
