#include "batLed.h"
#include "main.h"
#include "cmsis_os.h"

/*
 *		 ____	 ____		V+		 ___  ____
 *		|	  \/	 |		|		|	\/	  |
 *		| 	 		 | 800KOhm 		|		  |
 *		|	LTC4054	 |		|		|	MCU	  |
 *		|		 CHRG|------2KOhm-|OUT		  |
 *		|			 |		|_______|IN		  |
 *		 ----------					 ---------
 */

static uint8_t g_outputPinMode = PULL_PUSH_OUTPUT;
static PinConfig_t batterIndicateOutPinConfig(PinConfig_t set);
static void vCheckBatterChargeStateTask(void * const pvParameters);


void batterTaskInit()
{
	TaskHandle_t handle;
	xTaskCreate(vCheckBatterChargeStateTask, "Batter management task", 128, NULL, 2UL, &handle);
}

static void vCheckBatterChargeStateTask(void * const pvParameters)
{
	(void)(pvParameters);
	static ChargeState_t batterState = BAT_STATE_UNDEF;
    TickType_t xLastWakeTick = xTaskGetTickCount();
    uint16_t ledFlashTimeout = 0;
    
	for(;;)
	{
		switch(batterState)
        {
          case BAT_STATE_UNDEF: // Normal and no charging, or non-normal mode
            batterState = isBatterCharging();
            ledFlashTimeout == 0 && (ledFlashTimeout = 100);
            if ((--ledFlashTimeout) == 0)
                HAL_GPIO_TogglePin(BAT_LED_GPIO_Port, BAT_LED_Pin);
            break;
          case BAT_CHARGING:
            if (HAL_GPIO_ReadPin(BAT_LED_GPIO_Port, BAT_LED_Pin) == GPIO_PIN_RESET)
            {
              HAL_GPIO_WritePin(BAT_LED_GPIO_Port, BAT_LED_Pin, GPIO_PIN_SET);
            }
            batterState = isBatterChargingEnd();
            break;
          case BAT_CHARGE_END:
            if (HAL_GPIO_ReadPin(BAT_LED_GPIO_Port, BAT_LED_Pin) == GPIO_PIN_SET)
            {
              HAL_GPIO_WritePin(BAT_LED_GPIO_Port, BAT_LED_Pin, GPIO_PIN_RESET);
            }
            batterState = isBatterCharging();
            break;
          case BAT_UVLO:
            batterState = isBatterCharging();
            ledFlashTimeout == 0 && (ledFlashTimeout = 25);
            if ((--ledFlashTimeout) == 0)
                HAL_GPIO_TogglePin(BAT_LED_GPIO_Port, BAT_LED_Pin);
            break;
          default:
            batterState = BAT_STATE_UNDEF;
            break;
        }
        
        // Blocked 10ms
        vTaskDelayUntil(&xLastWakeTick, 10 / portTICK_PERIOD_MS);
	}
}

/**
* @breif		Check if batter is charing.
* @param		None
* @retval		Batter charge staus.
* @note			None
 */
ChargeState_t isBatterCharging()
{
	/*
	 * To detect when the LTC4054 is in charge mode, must be force the
	 * OUT pin of MCU output high and measure the voltage at the CHRG pin
	 * of LTC4054.
	 */
  if (g_outputPinMode != PULL_PUSH_OUTPUT)
  {
    if ((g_outputPinMode = batterIndicateOutPinConfig(PULL_PUSH_OUTPUT)) != PULL_PUSH_OUTPUT)
			return BAT_STATE_UNDEF;
    HAL_GPIO_WritePin(CHRG_OUT_GPIO_Port, CHRG_OUT_Pin, GPIO_PIN_SET);
  }
  
	/* 
	 * When the batter is charging, IN pin of MCU will be pull down with 
	 * CHAG pin of LTC4054 althouge OUT pin of MCU output is high.
	 */
  if (HAL_GPIO_ReadPin(CHRG_IN_GPIO_Port, CHRG_IN_Pin) == GPIO_PIN_RESET)	
  {
    return BAT_CHARGING;
  }
  
  return BAT_STATE_UNDEF;
}

ChargeState_t isBatterChargingEnd()
{
	/*
	 * When charge cycle terminates, CHRG pin of LTC4054 has a weak pull-down
	 * current(20uA), so the IN pin of MCU will be pulled high by OUT pin of MCU.
	 */
  if (HAL_GPIO_ReadPin(CHRG_IN_GPIO_Port, CHRG_IN_Pin) == GPIO_PIN_SET)
  {
		/*
		 * To determine if there is a weak pull-down current, the OUT pin of MCU is forced
		 * to a high impedance state.
		 */
    g_outputPinMode = (g_outputPinMode != ANALOG_IMPEDANCE) ? batterIndicateOutPinConfig(ANALOG_IMPEDANCE) : ANALOG_IMPEDANCE;
    
		if (g_outputPinMode != ANALOG_IMPEDANCE)
			return BAT_STATE_UNDEF;
		
    if (HAL_GPIO_ReadPin(CHRG_IN_GPIO_Port, CHRG_IN_Pin) == GPIO_PIN_RESET)
    {
      return BAT_CHARGE_END;
    }
    else
    {
      return BAT_UVLO;
    }
  }
  
  return BAT_STATE_UNDEF;
}

/*
 * Configure OUT pin mode of MCU.
 */
static PinConfig_t batterIndicateOutPinConfig(PinConfig_t set)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  static PinConfig_t pinMode = PIN_CONFIG_UNDEF;
  
  if (set == ANALOG_IMPEDANCE)
  {
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	pinMode = ANALOG_IMPEDANCE;
  }
  else if (set == PULL_PUSH_OUTPUT)
  {
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	pinMode = PULL_PUSH_OUTPUT;
  }
  GPIO_InitStruct.Pin = CHRG_OUT_Pin;
  GPIO_InitStruct.Pull = GPIO_NOPULL;  
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; 
  
  HAL_GPIO_Init(CHRG_OUT_GPIO_Port, &GPIO_InitStruct);
  
  return pinMode;
}
