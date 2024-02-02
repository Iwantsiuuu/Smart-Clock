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

//#include "interface.h"
#include "button.h"
#include "task_button.h"

//extern cyhal_i2c_t i2c;
//cyhal_i2c_t i2c;

void test_CB();
void displayOled(void *arg);

#endif
