#ifndef MENUDISP_H_
#define MENUDISP_H_

#include "task_interface.h"

void init_menu_disp();
void deinit_menu_disp();
void menu_disp();
void menu_enter(uint8_t disp);

static void up_Cb();
static void down_Cb();
static void ok_Cb();
static void back_Cb();

#endif
