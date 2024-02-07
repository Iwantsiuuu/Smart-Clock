#include "task_bmp280.h"
#include "i2c_init.h"

float temp,press;

void bmp280_data(void *arg){

//	uint8_t device_addr;
//	for (uint8_t i = 1; i < 0x7f; i++)
//		if (cyhal_i2c_master_write(&i2c_sens, i, &device_addr, 0,100,true) != 0)
//			CY_ASSERT(0);
//
//	if (bmp280.init(&i2c_sens, BMP280_ADDR) != BMP280_SUCCESS)
//		CY_ASSERT(0);
//
//	for (;;)
//	{
//		BMP280_readValue(&temp, &press, 100);
//		vTaskDelay(5000);
//	}
}
