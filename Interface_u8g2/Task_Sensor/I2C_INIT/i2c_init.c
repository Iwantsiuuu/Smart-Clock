#include "i2c_init.h"

cyhal_i2c_t i2c_sens;

cyhal_i2c_cfg_t i2c_sens_cfg = {
    .is_slave = false,
    .address = 0,
    .frequencyhal_hz = 400000
};

void initialize_i2c(){

    cy_rslt_t result;

    result = cyhal_i2c_init(&i2c_sens, CYBSP_I2C_SDA, CYBSP_I2C_SCL, NULL);
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    result = cyhal_i2c_configure(&i2c_sens, &i2c_sens_cfg);
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }
}
