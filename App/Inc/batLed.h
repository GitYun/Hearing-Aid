// Header:
// File Name: 
// Author:
// Date:

#ifndef BAT_LED_H
#define BAT_LED_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f3xx.h"
#include "stm32f3xx_hal.h"
  
typedef enum {
  BAT_STATE_UNDEF = 0,
  BAT_CHARGING,
  BAT_CHARGE_END,
  BAT_UVLO,
} ChargeState_t;

typedef enum  {
  PIN_CONFIG_UNDEF = 0,
  PULL_PUSH_OUTPUT,
  ANALOG_IMPEDANCE
} PinConfig_t;
  
ChargeState_t isBatterCharging(void);
ChargeState_t isBatterChargingEnd(void);
void batterTaskInit(void);

#ifdef __cplusplus
}
#endif
#endif
