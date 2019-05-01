/**
  *******************************************************************************
  * @file			virtual_i2c.cpp
  * @author		Okteach Application Team
  * @version	V1.0
  * @date			2017-4-16
  * @brief		Use GPIO virtual i2c protocol
  ********************************************************************************
  */

#include "stm32f1xx_hal_def.h"
#include "virtual_i2c.h"

class VirtualI2C {
	public:
		VirtualI2C(GPIO_TypeDef* _gpioPort, uint16_t _i2cSclPin, uint16_t _i2cSdaPin);		// Construcator
		void i2cStart(void);
		void i2cStop(void);
		void i2cSendByte(uint8_t ucByte);
		uint8_t i2cReadByte(void);
		uint8_t i2cWaitAck(void);
		void i2cAck(void);
		void i2cNAck(void);
		uint8_t i2cCheckDevice(uint8_t ucDevAddr);

	private:
		GPIO_TypeDef*	gpioPort;
		uint16_t		i2cSclPin;
		uint16_t		i2cSdaPin;
};