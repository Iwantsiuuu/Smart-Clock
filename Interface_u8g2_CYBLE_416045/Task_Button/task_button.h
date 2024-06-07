#ifndef TASK_BUTTON_H_
#define TASK_BUTTON_H_

#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

/*Include FreeRTOS*/
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "queue.h"
#include "task.h"

#include "button.h"

#define BTN_ENTER 	(P10_6)
#define BTN_BACK	(P9_6)
#define BTN_UP		(P0_4)
#define BTN_DOWN	(P0_5)

typedef enum buttonCode {
	BUTTON_UP 		= 0,
	BUTTON_DOWN 	= 1,
	BUTTON_ENTER 	= 2,
	BUTTON_BACK 	= 3
}BTN_CODE;

//extern bool systemReady;

void ButtonApp(void *arg);

extern button_var btn_obj[NUM_OF_BTN];

#endif
