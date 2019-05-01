
#include "main.h"
#include "keys.h"
#include "cmsis_os.h"
#include "wm8974_audio.h"

static void vKeysOpTask(void * pvParameters);
static uint32_t keysCheck(void);

void keysTaskInit()
{
	TaskHandle_t handle;
	xTaskCreate(vKeysOpTask, "Keys opretor task", 256, NULL, 9UL, &handle);
}

static void vKeysOpTask(void * const pvParameters)
{
	uint32_t keysCode;
	uint8_t currentVol;
	
	if ((wmGetCtrlWord(WM8974_PWR_MANAGF2).value & 0x04) != 0x04)
		wm8974_InputPGAEnable(1);
	
	if ((wmGetCtrlWord(WM8974_ALC_CTRL1).value & 0x0100) != 0x0100)
		wm8974_ALCEnable(1);

	currentVol = (g_wm8974AllCtrlWordArr[WM8974_PWR_MANAGF2].value & 0x3F);
	keysCode = keysCheck();
	
	if (keysCode == 0x01)
	{
		g_wm8974AllCtrlWordArr[WM8974_PWR_MANAGF2].value |= ((++currentVol) & 0x3F);
	}
	else if (keysCode == 0x02)
	{
		g_wm8974AllCtrlWordArr[WM8974_PWR_MANAGF2].value |= (currentVol ? --currentVol : 0);
	}
	else
	{
		return;
	}
	wm8974_InputPGAVolumeCtrl(currentVol);
}

static uint32_t keysCheck(void)
{
	uint32_t activeKeysCode = 0;
	
	if (HAL_GPIO_ReadPin(VOL_UP_GPIO_Port, VOL_UP_Pin) == 0) activeKeysCode |= 0x01;
	if (HAL_GPIO_ReadPin(VOL_DN_GPIO_Port, VOL_DN_Pin) == 0) activeKeysCode |= 0x02;
	
	return activeKeysCode;
}
