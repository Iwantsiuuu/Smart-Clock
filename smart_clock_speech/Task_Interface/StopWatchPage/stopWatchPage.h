#pragma once

#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include "task_button.h"
#include "task_interface.h"

void init_stopWatch_disp();
void deinit_stopWatch_disp();
void stopWatch_disp();
void stopWatch_draw();
void stopwatch();

static void startSW_Cb();
static void pauseSW_Cb();
static void resetSW_Cb();
static void BackSW_Cb();
static void speech_stopwatch_cmd(uint8_t* cmd);

#endif
