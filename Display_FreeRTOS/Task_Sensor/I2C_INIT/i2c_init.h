#ifndef I2C_INIT_H_
#define I2C_INIT_H_

#include "cyhal.h"
#include "cybsp.h"

extern cyhal_i2c_t i2c_sens;

void initialize_i2c();

#endif
