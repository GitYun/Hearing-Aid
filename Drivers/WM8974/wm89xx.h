// Copyright (c) 2019 Yoki
// Licensed under the MIT License

// Header:
// File Name: wm89xx.h
// Author: RQY
// Date: 2017-7-16


#ifndef WM89XX_H
#define WM89XX_H

#ifdef __cplusplus
extern "C"	{
#endif

#include "stm32f3xx_hal.h"
	
typedef struct wm89xx_ctrlWord_s
{
	uint16_t value;				// take up 2 bytes
	uint8_t reg;					// take up 2 bytes, first byte is variable 'reg', second byte filled to satisfy byte alignment
} wm89xx_ctrlWord_t;		// 'wm89xx_ctrlWord_t' total 4 bytes

typedef struct wm89xx_clockConfig_s
{
	uint8_t mode;				// MS bit, 0 = slave mode, 1 = master mode
	uint8_t bclkDiv;		// BCLKDIV bit, Configures the BCLK and FRAME output frequency
	uint8_t mclkDiv;		// MCLKDIV bit, Sets the scaling for either the MCLK or PLL clock output
	uint8_t clkSel;			// Controls the source of the clock for all internal operation
} wm89xx_clockConfig_t;

typedef struct wm89xx_audioInterface_s
{
	uint8_t adcLRSwap;			// Controls whether ADC data appears in 'right' or 'left' phases of FRAME clock
	uint8_t dacLRSwap;			// COntrols whether DAC data appears in 'right' or 'left' phases of FRAME clock
	uint8_t format;					// Data format select, R4(): 4:3bit 10h=I2S format
	uint8_t wordLen;				// word length, 00h=16bits, 01h=20bits, 10h=24bits, 11h=32bits
	uint8_t framePolarity;	// Frame clock polarity, 0=normal, 1= inverted
	uint8_t bclkPolarity;		// BCLK polarity, 0 = normal, 1= inverted
} wm89xx_audioInterface_t;


int8_t wm89xx_WriteOneRegister(I2C_HandleTypeDef *hi2c, uint16_t DevAddr, uint16_t value, uint8_t reg);
int8_t wm89xx_WriteRegisters(I2C_HandleTypeDef *hi2c, uint16_t DevAddr, wm89xx_ctrlWord_t * ctrlWord, uint16_t size);
int8_t wm8974_DigitalAudioInterface(wm89xx_clockConfig_t clock, wm89xx_audioInterface_t audioInterface);

#ifdef __cpulspuls
}
#endif

#endif
