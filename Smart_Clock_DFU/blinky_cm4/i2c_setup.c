#include "i2c_setup.h"

cyhal_i2c_t i2c_obj;

const cyhal_i2c_cfg_t i2c_cfg =
{
		.is_slave 		 = false,
		.address  		 = 0,
		.frequencyhal_hz = 400000
};

void i2c_init(){
	cy_rslt_t result;

	result = cyhal_i2c_init(&i2c_obj, CYBSP_I2C_SDA, CYBSP_I2C_SCL, NULL);
	if(result != CY_RSLT_SUCCESS)
		CY_ASSERT(0);

	result = cyhal_i2c_configure(&i2c_obj, &i2c_cfg);
	if(result != CY_RSLT_SUCCESS)
		CY_ASSERT(0);

}
