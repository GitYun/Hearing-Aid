#ifndef WM8974_H
#define WM8974_H

#ifdef __cpulspuls
extern "C"	{
#endif
	
#include "stm32f3xx_hal.h"
#include "wm89xx.h"
	
//#define WM8974_SOFTWARE_RESET				0x00		/* R0 */
//	
//#define WM8974_PWR_MANAGE1					0x01		/* R1 */
//#define WM8974_PWR_MANAGF2					0x02		/* R2 */
//#define WM8974_PWR_MANAGE3					0x03		/* R3 */
//	
//#define WM8974_AUDIO_INTERFACE			0x04		/* R4 */
//	
//#define WM8974_COMPANDING_CTRL			0x05		/* R5 */
//	
//#define WM8974_CLOCK_GEN_CTRL				0x06		/* R6 */
//	
//#define WM8974_ADDITIONAL_CTRL			0x07		/* R7 */
//	
//#define WM8974_GPIO_CTRL						0x08		/* R8 */
//	
//#define WM8974_DAC_CTRL							0x0A		/* R10 */
//#define WM8974_DAC_DIGITAL_VOL			0x0B		/* R11 */
//	
//#define WM8974_ADC_CTRL							0x0E		/* R14 */
//#define WM8974_ADC_DIGITAL_VOL			0x0F		/* R15 */
//	
//#define WM8974_EQ1_LOW_SHELF				0x12		/* R18 */
//#define WM8974_EQ2_PEAK1						0x13		/* R19 */
//#define WM8974_EQ3_PEAK2						0x14		/* R20 */
//#define WM8974_EQ4_PEAK3						0x15		/* R21 */
//#define WM8974_EQ5_HIGH_SHELF				0x16		/* R22 */

//#define WM8974_DAC_LIMITER1					0x18		/* R24 */
//#define WM8974_DAC_LIMITER2					0x19		/* R25 */

//#define WM8974_NOTCH_FILTER1				0x1B		/* R27 */
//#define WM8974_NOTCH_FILTER2				0x1C		/* R28 */
//#define WM8974_NOTCH_FILTER3				0x1D		/* R29 */
//#define WM8974_NOTCH_FILTER4				0x1E		/* R30 */

//#define WM8974_ALC_CTRL1						0x20		/* R32 */
//#define WM8974_ALC_CTRL2						0x21		/* R33 */
//#define WM8974_ALC_CTRL3						0x22		/* R34 */

//#define WM8974_ALC_NOISE_GATE				0x23		/* R35 */

//#define WM8974_PLL_N								0x24		/* R36 */
//#define WM8974_PLL_K1								0x25		/* R37 */
//#define WM8974_PLL_K2								0x26		/* R38 */
//#define WM8974_PLL_K3								0x27		/* R39 */

//#define WM8974_ATTENUATION_CTRL			0x28		/* R40 */

//#define WM8974_INPUT_CTRL						0x2C		/* R44 */

//#define WM8974_INPUT_PGA_GAIN_CTRL	0x2D		/* R45 */

//#define WM8974_ADC_BOOST_CTRL				0x2F		/* R47 */

//#define WM8974_OUTPUT_CTRL					0x31		/* R49 */

//#define WM8974_SPK_MIXER_CTRL				0x32		/* R50 */
//#define WM8974_SPK_VOLUME_CTRL			0x36		/* R54 */

//#define WM8974_MONO_MIXER_CTRL			0x38		/* R56 */

typedef enum {
	WM8974_SOFTWARE_RESET			 	= 0x00,		/* R0 */
		
	WM8974_PWR_MANAGE1				 	= 0x01,		/* R1 */
	WM8974_PWR_MANAGF2					= 0x02,		/* R2 */
	WM8974_PWR_MANAGE3					= 0x03,		/* R3 */
		
	WM8974_AUDIO_INTERFACE			= 0x04,		/* R4 */
		
	WM8974_COMPANDING_CTRL			= 0x05,		/* R5 */
		
	WM8974_CLOCK_GEN_CTRL				= 0x06,		/* R6 */
		
	WM8974_ADDITIONAL_CTRL			= 0x07,		/* R7 */
		
	WM8974_GPIO_CTRL						= 0x08,		/* R8 */
	
	RESEVED_09									= 0x09,
	
	WM8974_DAC_CTRL							= 0x0A,		/* R10 */
	WM8974_DAC_DIGITAL_VOL			= 0x0B,		/* R11 */

	RESEVED_0C									= 0x0C,
	RESEVED_0D									= 0x0D,

	WM8974_ADC_CTRL							= 0x0E,		/* R14 */
	WM8974_ADC_DIGITAL_VOL			= 0x0F,		/* R15 */
	
	RESEVED_10									= 0x10,
	RESEVED_11									= 0x11,
		
	WM8974_EQ1_LOW_SHELF				= 0x12,		/* R18 */
	WM8974_EQ2_PEAK1						= 0x13,		/* R19 */
	WM8974_EQ3_PEAK2						= 0x14,		/* R20 */
	WM8974_EQ4_PEAK3						= 0x15,		/* R21 */
	WM8974_EQ5_HIGH_SHELF				= 0x16,		/* R22 */

	RESEVED_17									= 0x17,

	WM8974_DAC_LIMITER1					= 0x18,		/* R24 */
	WM8974_DAC_LIMITER2					= 0x19,		/* R25 */

	RESEVED_1A									= 0x1A,

	WM8974_NOTCH_FILTER1				= 0x1B,		/* R27 */
	WM8974_NOTCH_FILTER2				= 0x1C,		/* R28 */
	WM8974_NOTCH_FILTER3				= 0x1D,		/* R29 */
	WM8974_NOTCH_FILTER4				= 0x1E,		/* R30 */

	RESEVED_1F									= 0x1F,

	WM8974_ALC_CTRL1						= 0x20,		/* R32 */
	WM8974_ALC_CTRL2						= 0x21,		/* R33 */
	WM8974_ALC_CTRL3						= 0x22,		/* R34 */

	WM8974_ALC_NOISE_GATE				= 0x23,		/* R35 */

	WM8974_PLL_N								= 0x24,		/* R36 */
	WM8974_PLL_K1								= 0x25,		/* R37 */
	WM8974_PLL_K2								= 0x26,		/* R38 */
	WM8974_PLL_K3								= 0x27,		/* R39 */

	WM8974_ATTENUATION_CTRL			= 0x28,		/* R40 */
	
	RESEVED_29									= 0x29,
	RESEVED_2A									= 0x2A,
	RESEVED_2B									= 0x2B,	

	WM8974_INPUT_CTRL						= 0x2C,		/* R44 */

	WM8974_INPUT_PGA_GAIN_CTRL	= 0x2D,		/* R45 */

	RESEVED_2E									= 0x2E,

	WM8974_ADC_BOOST_CTRL				= 0x2F,		/* R47 */

	RESEVED_30									= 0x30,

	WM8974_OUTPUT_CTRL					= 0x31,		/* R49 */

	WM8974_SPK_MIXER_CTRL				= 0x32,		/* R50 */
	
	RESEVED_33									= 0x33,
	RESEVED_34									= 0x34,
	RESEVED_35									= 0x35,
	
	WM8974_SPK_VOLUME_CTRL			= 0x36,		/* R54 */

	RESEVED_37									= 0x37,

	WM8974_MONO_MIXER_CTRL			= 0x38,		/* R56 */
	
} WM8974_RegsAddress_t;


#define WM8974_I2C_ADDR							0x001A

extern wm89xx_ctrlWord_t g_wm8974InitCtrlWordArr[];
extern wm89xx_ctrlWord_t g_wm8974AllCtrlWordArr[];

uint16_t getCtrlWordArrSize(void);

int8_t wm8974_SoftwareReset(void);		// R44(00h):
// Input PGA configure function prototype
int8_t wm8974_InputPGAEnable(uint8_t newState);		// R2(): 2bit 
int8_t wm8974_InputPGAVolumeCtrl(uint8_t volume);	// R45(): 5:0bit
#define wm8974_InputPGAMuteCtrl(newState)		wm8974_InputPGAVolumeCtrl(newState)			// R45(): 6bit
#define wm8974_InputPGAZeroCrossCtrl(newState)	wm8974_InputPGAVolumeCtrl(newState)	// R45(): 7bit
int8_t wm8974_ALCEnable(uint8_t newState);				// R32(): 8bit

// Auxiliary input configure
#define wm8974_AuxInputPGA(newState)	wm8974_InputPGAVolumeCtrl(newState)		// R44(): 2bit
int8_t wm8974_AuxEnable(uint8_t newState);		// R1(): 5bit
int8_t wm8974_AuxMode(uint8_t newState);			// R44(): 3bit

// Input boost stage configure
int8_t wm8974_BoostEnable(uint8_t newState);	// R2(): 4bit
int8_t wm8974_PGABoost(uint8_t newState);			// R47(): 8bit
int8_t wm8974_AuxBoostVol(uint8_t gain);			// R47(): 2:0bit
int8_t wm8974_MICPBoostVol(uint8_t gain);			// R47(): 6:4bit

// Microphone bias circuit configure
int8_t wm8974_MicBiasEnable(uint8_t newState);	// R1(): 4bit
int8_t wm8974_MicBiasVoltage(uint8_t voltage);	// R44(): 8bit

// ADC configure
int8_t wm8974_ADCEnable(uint8_t newState);					// R2(): 0bit
int8_t wm8974_ADCOverSampleRate(uint8_t newState);	// R14(): 3bit
int8_t wm8974_ADCPolarity(uint8_t newState);				// R14(): 0bit
int8_t wm8974_HighPassFilter(uint8_t value);				// R14(): 8:4bit
int8_t wm8974_NotchFilter(uint8_t a0, uint8_t a1);	// R27(), R28(), R29(), R30()\
// Digital ADC volume control
int8_t wm8974_ADCDigitalVolume(uint8_t adcVolume);	// R15(): 7:0bit

int8_t wm8974_DACEnable(uint8_t newState);					// R3(): 0bit
// DAC digital Hi-Fi volume control
int8_t wm8974_DACDigitalVolume(uint8_t dacVolume);	// R11(): 7:0bit
// Hi-Fi DAC
int8_t wm8974_DACDeEmphasis(uint8_t newState);			// R10(): 5:4bit
// DAC mute
int8_t wm8974_DACSoftMute(uint8_t newState);				// R10(): 6bit
int8_t wm8974_DACAnalogueMute(uint8_t newState);		// R10(): 2bit

// 5-band graphic EQ
int8_t wm8974_EQMode(uint16_t mode);								// R18(): 8bit
int8_t wm8974_EQConfig(uint8_t mode, uint8_t bandIndex, uint16_t value);	// R18(), R19(), R20(), R21(), R22()

// Analogue outputs
int8_t wm8974_SpeakerBoost(uint8_t newState);				// R49(): 2bit
int8_t wm8974_MonoBoost(uint8_t newState);					// R48(): 3bit
int8_t wm8974_BufferDCLevelShiftEnable(uint16_t newState);		// R1(): 8bit

// Speaker output
int8_t wm8974_SelectPath2Speaker(uint8_t path);			// R50(): 1:0bit, 5bit
int8_t wm8974_SpeakerAttn(uint8_t newState);				// R40(): 1bit
int8_t wm8974_SpeakerVolume(uint8_t volume);				// R54(): 7:0bit
// Zero cross timeout
int8_t wm8974_SlowClkEnable(uint8_t newState);			// R7(): 0bit

// Mono output
int8_t wm8974_SelectPath2Mono(uint8_t path);				// R56(): 2:0bit
int8_t wm8974_MonoMute(uint8_t newState);						// R56(): 6bit
int8_t wm8974_MonoAttn(uint8_t newState);						// R40(): 0bit

// Enabling the outputs
int8_t wm8974_EnableOutput(uint8_t pwrManage1, uint8_t selectOutput);			// R1(): 3:2bit, 8bit, R3(): 3:2bit, 7:5bit
int8_t wm8974_SelectVREF2AnalogueResistance(uint8_t resistaceIdx);				// R49(): 0bit

// Companding
int8_t wm8974_CompandSelcet(uint8_t side, uint8_t compandMethod);					// R5(): 4:1bit

// Audio sample rates
int8_t wm8974_SampleRate(uint8_t sampleRate);					// R7(): 3:1bit

// GPIO configure
int8_t wm8974_GPIOConfig(uint8_t value);							// R8(): 5:0bit

// Power management
int8_t wm8974_OversampleRateSelect(uint8_t side, uint8_t oversampleRate);		// R10(): 3bit, R14(): 3bit
int8_t wm8974_VMIDSelect(uint8_t value);							// R1(): 1:0bit
int8_t wm8974_AnalogueAmpBiasEnable(uint8_t newState);			// R1(): 3bit


#ifdef __cpulspuls
}
#endif

#endif
