#include "wm8974_audio.h"


#define I2C_HANDLE	hi2c1

extern I2C_HandleTypeDef I2C_HANDLE;

int8_t wmAudioInit(wm89xx_ctrlWord_t * wm89xxCtrlWord, uint32_t size)
{
	for (uint32_t cnt = size; cnt != 0; cnt--)
	{
		g_wm8974AllCtrlWordArr[wm89xxCtrlWord[size-cnt].reg].value = wm89xxCtrlWord[size-cnt].value;
	}
	return wm89xx_WriteRegisters(&I2C_HANDLE, WM8974_I2C_ADDR, wm89xxCtrlWord, size);
}


wm89xx_ctrlWord_t wmGetCtrlWord(uint32_t idx)
{
	assert_param((idx <= 0x38));
	return g_wm8974AllCtrlWordArr[idx];
}

void wmSetOneCtrlWord(const wm89xx_ctrlWord_t * const ctrlWord)
{
	wm89xx_WriteOneRegister(&I2C_HANDLE, WM8974_I2C_ADDR, ctrlWord->value, ctrlWord->reg);
	
	g_wm8974AllCtrlWordArr[ctrlWord->reg].value = ctrlWord->value;
}

