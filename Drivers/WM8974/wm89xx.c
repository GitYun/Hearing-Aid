// Copyright (c) 2019 Yoki
// Licensed under the MIT License

#include "wm89xx.h"

int8_t wm89xx_WriteOneRegister(	I2C_HandleTypeDef *hi2c, 
																uint16_t DevAddr, 
																uint16_t value, 
																uint8_t reg)
{
	value |= ((uint16_t)reg << 9);
    
    /**
     * WM89xx require send first control byte is the register address([15:9]bits) and 1st-data-bit([8]bit),
     * then second control byte is remaining 8 bits of data([7:0]bits). I2C send data MSB first.
     */
    value = __REV16(value);
	
    // I2C slave address need to left shift 1-bit, refer I2C registers
	if (HAL_I2C_Master_Transmit(hi2c, (DevAddr<<1), (uint8_t *)&value, sizeof(value), 10) == HAL_OK)
		return 0;
	return 1;
}

int8_t wm89xx_WriteRegisters(	I2C_HandleTypeDef *hi2c, 
															uint16_t DevAddr, 
															wm89xx_ctrlWord_t * ctrlWord,
															uint16_t size)
{
	for (; size != 0; size--)
	{
		if (wm89xx_WriteOneRegister(hi2c, DevAddr, ctrlWord->value, ctrlWord->reg) == 0)
			ctrlWord++;
		else return 1;
	}
	return 0;
}
