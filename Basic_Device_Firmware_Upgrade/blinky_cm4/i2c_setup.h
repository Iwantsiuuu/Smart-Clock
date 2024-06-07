#pragma once

#ifndef I2C_SETUP_H_
#define I2C_SETUP_H_

#include "cyhal.h"
#include "cybsp.h"

void i2c_init();

extern cyhal_i2c_t i2c_obj;

#endif
