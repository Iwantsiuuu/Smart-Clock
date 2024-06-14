#include "setup_i2c.h"

#define PIN_SDA	(P10_1)
#define PIN_SCL (P10_0)

cyhal_i2c_t i2c;

const cyhal_i2c_cfg_t i2c_cfg =
{
		.is_slave 		 = false,
		.address  		 = 0,
		.frequencyhal_hz = 400000
};

cy_rslt_t init_i2c(){

    cy_rslt_t result;

	result = cyhal_i2c_init(&i2c, PIN_SDA, PIN_SCL, NULL);
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
