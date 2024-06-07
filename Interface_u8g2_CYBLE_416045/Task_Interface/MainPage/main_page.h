#ifndef MAIN_PAGE_H_
#define MAIN_PAGE_H_

#include "task_button.h"
#include "interface.h"

void main_page();

static void init_main_page();
static void deinit_main_page();
static void default_mode_draw();
static void bluetooth_mode_draw();

static void moveToMenuPage();
static void changeMode();

#endif