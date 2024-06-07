#include "setup_i2c.h"

cyhal_i2c_t i2c;

cyhal_i2c_cfg_t i2c_cfg = {
		.is_slave = false,
		.address = 0,
		.frequencyhal_hz = 400000
};

uint32_t initialize_i2c(){

    cy_rslt_t result;

	result = cyhal_i2c_init(&i2c, P10_1, P10_0, NULL);
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

	result = cyhal_i2c_configure(&i2c, &i2c_cfg);
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }
    return result;
}
