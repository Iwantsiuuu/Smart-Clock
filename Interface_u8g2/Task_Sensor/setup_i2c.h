#ifndef SETUP_I2C_H_
#define SETUP_I2C_H_

#include "cyhal.h"
#include "cybsp.h"

extern cyhal_i2c_t i2c;

uint32_t initialize_i2c();

#endif
