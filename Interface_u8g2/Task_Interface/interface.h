#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

/*Include FreeRTOS*/
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "queue.h"
#include "task.h"

#include "mtb_ssd1306.h"
#include "u8g2.h"
#include "u8g2/u8x8.h"
#include "u8g2_support.h"

#include "button.h"
#include "task_button.h"
#include "task_interface.h"

#define MAIN_PAGE_ID 		1
#define MENU_PAGE_ID 		2
#define TIME_DATE_PAGE_ID 	3
#define ENVIRONMENT_PAGE_ID 4
#define AIRQUALITY_PAGE_ID  5
#define STOPWATCH_PAGE_ID   6

#endif
