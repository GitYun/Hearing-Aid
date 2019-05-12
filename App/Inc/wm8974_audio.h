// Copyright (c) 2019 Yoki
// Licensed under the MIT License

// Header:
// File Name: 
// Author:
// Date: 2017-7-19

#ifndef WM8974_AUDIO_H
#define WM8974_AUDIO_H

#ifdef __cpulspuls
extern "C"	{
#endif

#include "stm32f3xx_hal.h"
#include "wm89xx.h"
#include "wm8974.h"

int8_t wmAudioInit(wm89xx_ctrlWord_t * wm89xxCtrlWord, uint32_t size);
wm89xx_ctrlWord_t wmGetCtrlWord(uint32_t idx);
void wmSetOneCtrlWord(const wm89xx_ctrlWord_t * const ctrlWord);


#ifdef __cpulspuls
}
#endif

#endif

