#pragma once
#ifndef OLED_INIT_H_
#define OLED_INIT_H_

#include "cyhal.h"
#include "cybsp.h"
#include "i2c_setup.h"
#include "mtb_ssd1306.h"

#include "u8g2.h"
#include "u8g2_support.h"

void init_oled();

extern u8g2_t u8g2_obj;

#endif
