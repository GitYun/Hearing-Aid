// Copyright (c) 2019 Yoki
// Licensed under the MIT License

#include "main.h"
#include "keys.h"
#include "cmsis_os.h"
#include "wm8974_audio.h"

static void vKeysOpTask(void * pvParameters);
static uint32_t keysCheck(void);

void keysTaskInit()
{
	TaskHandle_t handle;
	xTaskCreate(vKeysOpTask, "Keys opretor task", 128, NULL, 1UL, &handle);
}

static void vKeysOpTask(void * const pvParameters)
{
	uint32_t keysCode, preKeysCode = 0;
	uint8_t currentVol;
    TickType_t xLastWakeTick = xTaskGetTickCount();
	
    if ((wmGetCtrlWord(WM8974_PWR_MANAGF2).value & 0x04) != 0x04)
        wm8974_InputPGAEnable(1);
        
    // When the Automatic Level Control (ALC) is enabled the input PGA gain is then 
    // controlled automatically and the INPPGAVOL bits should not be used
    //if ((wmGetCtrlWord(WM8974_ALC_CTRL1).value & 0x0100) != 0x0100)
    //    wm8974_ALCEnable(1);
    
    for(;;)
    {
        currentVol = (g_wm8974AllCtrlWordArr[WM8974_INPUT_PGA_GAIN_CTRL].value & 0x3F);
        keysCode = keysCheck();
        
        // Change WM8974's R45 register feild: INPPGAVOL[5:0]
        if (keysCode && (keysCode == preKeysCode))
        {
            if (keysCode == 0x01)
            {
                (currentVol < 0x3F) && (++currentVol);
            }
            else if (keysCode == 0x02)
            {
                (currentVol > 0) && (--currentVol);
            }
            else
            {
                ;
            }
            wm8974_InputPGAVolumeCtrl(currentVol);
        }
        preKeysCode = keysCode;
        // Blocking 70ms
        vTaskDelayUntil(&xLastWakeTick, 70 / portTICK_PERIOD_MS);
    }
}

static uint32_t keysCheck(void)
{
	uint32_t activeKeysCode = 0;
	
	if (HAL_GPIO_ReadPin(VOL_UP_GPIO_Port, VOL_UP_Pin) == 0) activeKeysCode |= 0x01;
	if (HAL_GPIO_ReadPin(VOL_DN_GPIO_Port, VOL_DN_Pin) == 0) activeKeysCode |= 0x02;
	
	return activeKeysCode;
}
