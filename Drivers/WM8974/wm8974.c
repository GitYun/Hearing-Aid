

#include "wm8974.h"

#define I2C_HANDLE hi2c1

extern I2C_HandleTypeDef I2C_HANDLE;

/*
uint16_t g_Wm8974RegsDefalutValueArr[] = {
	0x01FF, 0x0000, 0x0000, 0x0000, 0x0050, 0x000, 
	0x0140, 0x0000, 0x0000, 0x0000, 0x00FF, 0x0100,
	0x00FF, 0x012C, 0x002C, 0x002C, 0x002C, 0x002C, 
	0x0032, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
	0x0038, 0x000B, 0x0032, 0x0000, 0x0008, 0x000C, 
	0x0093, 0x00E9, 0x0000, 0x0003, 0x0010, 0x0000, 
	0x0002, 0x0000, 0x0039, 0x0000
};
*/

/*
 * Note: The g_wm8974AllCtrlWordAddr[x].value equal 0xFFFF is reserved register of wm8974
 */
wm89xx_ctrlWord_t g_wm8974AllCtrlWordArr[] = {
	{0x01FF, 0x00}, {0x0000, 0x01}, {0x0000, 0x02}, {0x0000, 0x03}, {0x0050, 0x04}, {0x0000, 0x05}, 
	{0x0140, 0x06}, {0x0000, 0x07}, {0x0000, 0x08}, {0xFFFF, 0x09}, {0x0000, 0x0A}, {0x00FF, 0x0B}, 
	{0xFFFF, 0x0C}, {0xFFFF, 0x0D}, {0x0100, 0x0E}, {0x00FF, 0x0F}, {0xFFFF, 0x10}, {0xFFFF, 0x11},
	{0x012C, 0x12}, {0x002C, 0x13}, {0x002C, 0x14}, {0x002C, 0x15}, {0x002C, 0x16}, {0xFFFF, 0x17},
	{0x0032, 0x18}, {0x0000, 0x19}, {0xFFFF, 0x1A}, {0x0000, 0x1B}, {0x0000, 0x1C}, {0x0000, 0x1D}, 
	{0x0000, 0x1E}, {0xFFFF, 0x1F}, {0x0038, 0x20}, {0x000B, 0x21}, {0x0032, 0x22}, {0x0000, 0x23}, 
	{0x0008, 0x24}, {0x000C, 0x25}, {0x0093, 0x26}, {0x00E9, 0x27}, {0x0000, 0x28}, {0xFFFF, 0x29},
	{0xFFFF, 0x2A}, {0xFFFF, 0x2B}, {0x0003, 0x2C}, {0x0010, 0x2D}, {0xFFFF, 0x2E}, {0x0000, 0x2F}, 
	{0xFFFF, 0x30}, {0x0002, 0x31}, {0x0000, 0x32}, {0xFFFF, 0x33}, {0xFFFF, 0x34}, {0xFFFF, 0x35},
	{0x0039, 0x36}, {0xFFFF, 0x37}, {0x0000, 0x38}
};

wm89xx_ctrlWord_t g_wm8974InitCtrlWordArr[] = {
	/* R6, 
	 * CLKSEL(8bit) = 0(0=MCLK, 1=PLL output), 
	 *
	 * MCLKDIV(7:5bit) = 000h(000h=divide by 1, 001h=divide by 1.5, 010h=divide by 2, 
	 *  011h=divide by 3, 100h=divide by 4, 101h=divide by 6, 110h=divide by 8, 111h=divide by 12), 
	 *
	 * BCLKDIV(4:2bit) = 000h(000h=divide by 1, BCLK=MCLK; 001h=divide by 2, BCLK=MCLK/2; 
	 *  010h=divide by 4, 011h=divide by 8, 100h=divide by 16, 101h=divide by 32, 110h=reserved, 111h=reserved), 
	 *
	 * MS(0bit) = 0(0=BCLK and FRAME clock are inputs, 1=BCLK and FRAME clock are outputs)
	 */
	{0x0000, WM8974_CLOCK_GEN_CTRL},
	
	/* R4, BCP(8bit) = 0(0=BCLK polarity normal, 1=inverted), FRAMEP(7bit) = 0(0=Frame clock polarity normal,
	 * 1=inverted), WL(6:5bit) = 11h(Word length, 00h=16bits, 01h=20bits, 10h=24bits, 11=32bits),
	 * FMT(4:3) = 10h(Data Format, 00h=Right justified, 01h=Left justified, 10h=I2S format,
	 * 11=DSP/PCM mode), DACLRSWAP(2bit)=0, ADCLRSWAP(1bit) = 0
	 */
	{0x0070, WM8974_AUDIO_INTERFACE},
	
	/* R44, MBVSEL(8bit) = 0(0=0.9*AVDD, 1= 0.65*AVDD), AUXMODE(3bit) = 0
	 * AUX2INPPGA(2bit) = 0, MICN2INPPGA(1bit) = 1, MICP2INPPGA(0bit) = 1
	 */
	{0x0003, WM8974_INPUT_CTRL},
	
	// R45, INPPGAVOL=010000h(0dB), INPPGAMUTE = 0(not muted), INPPGAZC = 0(update gain when changes)
	//{0x0010, WM8974_INPUT_PGA_GAIN_CTRL},		// reset default value
	
	/* R47, PGABOOST(8bit) = 0(0=+0dB, 1=+20dB), MICP2BOOSTVOL(6:4bit) = 000h(Path disabled), 
	 * AUX2BOOSTVOL(2:0bit) = 000h(Path disabled)
	*/
	//{0x0000, WM8974_ADC_BOOST_CTRL},		// reset default value
	
	/* R1, BUFDCOPEN(8bit) = 0(0=AVDD/2, 1=1.5xAVDD/2), AUXEN(6bit) = 0, PLLEN(5bit) = 0,
	 * MICBEN(4bit) = 1, BIASEN(3bit) = 1, BUFIOEN(2bit) = 1, VMIDSEL(1:0bit) = 01(50kOhm)
	 */
	{0x001D, WM8974_PWR_MANAGE1},	
	
	// R2, BOOSTEN(4bit) = 0, INPPGAEN(2bit) = 1, ADCEN(0bit) = 1
	{0x0005, WM8974_PWR_MANAGF2},	
	
	/* R14, HPFEN(8bit) = 1, HPAPP(7bit) = 0(0=~3.7Hz, 1=HPFCUT), HPFCUT(6:4bit) = 000h(Table 11),
	 * ADCOSR(3bit) = 0(0=64x, 1=128x), ADCPOL(0bit) = 0(0=normal, 1=inverted), 
	 */
	//{0x0100, WM8974_ADC_CTRL},		// reset default value
	
	/* R15, ADCVOL(7:0bit) = 0xFF(0dB, 0.5dB steps up to -127dB) */
	//{0x00FF, WM8974_ADC_DIGITAL_VOL},	// reset default value
	
	/* R11, DACVOL(7:0bit) = 0xFF(0dB, 0.5dB steps up to -127dB) */
	//{0x00FF, WM8974_DAC_DIGITAL_VOL},	// reset default value
	
	/* R10, DACMU(6bit) = 0(0=DACMU disabled, 1=DACMU enabled), DEEMPH(5:4bit)=00h(No de-emphasis),
	 * DACOSR128(3bit) = 0(DAC oversample rate select, 0=64x, lowest power; 1=128x,best SNR), 
	 * AMUTE(2bit) = 1(0=auto mute disabled, 1=auto mute enabled) 
	 */
	{0x0004, WM8974_DAC_CTRL},
	
	/* R18,  EQMODE(8bit) = 1(0=ADC path, 1=DAC path), EQ1C(6:5bit) = 11h(fcutoff: 00h=80Hz, 
	 * 01h=105Hz, 10h=135Hz, 11h=175Hz), EQ1G(4:0bit) = 00110h(+6dB, Table 35) 
	 */
	{0x0166, WM8974_EQ1_LOW_SHELF},
	
	/* R19, EQ2BW(8bit) = 0(0=narrow bandwidth, 1=wide bandwidth), EQ2C(6:5bit) = 01h(fc=300Hz),
	 * EQ2G(4:0bit) = 01100h(0dB, Table 35)
	 */
	//{0x002C, WM8974_EQ2_PEAK1},	// reset default value
	
	/* R20, EQ3BW(8bit) = 0, EQ3C(6:5bit) = 01h(fc=850Hz), EQ3G(4:0bit) = 01100(0dB, Table 35) */
	//{0x002C, WM8974_EQ3_PEAK2},		// reset default value
	
	/* R21, EQ4BW(8bit) = 0, EQ4C(6:5bit) = 01h(fc=2.4kHz), EQ4G(4:0bit) = 01100(0dB, Table 35) */
	//{0x002C, WM8974_EQ4_PEAK3},		// reset default value
	
	/* R22, EQ5C(6:5bit) = 01h(fcutoff = 6.9kHz), EQ5G(4:0bit) = 10010h(-6dB, Table 35) */
	{0x0032, WM8974_EQ5_HIGH_SHELF},
	
	/* R49, BUFDCOPEN(8bit) = 0, MONOBOOST(3bit) = 0(0=no boost, 1=1.5x gian boost, Table 37), 
	 * SPKBOOST(2bit) = 0(0=no boost, 1=1.5x gian boost, Table 37), 
	 * TSDEN(1bit) = 1(thermal shutdown enabled), VROI(0bit) = 0(0=1kOhm, 1=30kOhm)
	 */
	//{0x0002, WM8974_OUTPUT_CTRL},		// reset default value
	
	/* R50, AUX2SPK(5bit) = 0, BYP2SPK(1bit) = 0, DAC2SPK(0bit) = 1 */
	//{0x0001, WM8974_SPK_MIXER_CTRL},	// reset default value
	
	/* R56, MONOMUTE(6bit) = 1(0=no mute, 1=output muted, During mute the mono output will output
	 *												 VMID which can be used as a DC reference for a headphoneout),
	 * AUX2MONO(2bit) = 0, BYP2MONO(1bit) = 0, DAC2MONO(0bit) = 0
	*/
	{0x0040, WM8974_MONO_MIXER_CTRL},	
	
	/* R54, SPKZC(7bit) = 1(0=change gain immediately, 1=change gian on zero cross only), 
	 * SPKMUTE(6bit) = 0(0=speaker output enabled, 1=speaker output muted),
	* SPKVOL(5:0bit) = 111001h(0dB, 1dB steps)
	 */
	{0x00B9, WM8974_SPK_VOLUME_CTRL},
	
	/* R7, SR(3:1bit) = 000h(Smaple rate, 000h=48kHz, 001h=32kHz), SLOWCLKEN(0bit) = 1(0=slowclock disabled, 1=slow clock enabled) */
	{0x0001, WM8974_ADDITIONAL_CTRL},
	
	// R3, MONOEN(7bit) = 0, SPKNEN(6bit) = 1, SPKPEN(5bit) = 1, MONOMIXEN(3bit) = 0, SPKMIXEN(2bit) = 1, DACEN(0bit) = 1
	{0x0065, WM8974_PWR_MANAGE3}
};

/**
* @breif			Get the total count of @ref g_wm8974InitCtrlWordArr array object
* @param			None 
* @retval		array object total count
* @note			None
 */
uint16_t getCtrlWordArrSize(void)
{
	return (uint16_t)(sizeof(g_wm8974InitCtrlWordArr)/sizeof(g_wm8974InitCtrlWordArr[0]));
}

 
/**
 * @breif		Configuare WM8974's interface with MCU include that clcok and audio interface. 
 * @param		wm89xx_clockConfig_t - clock interface structure with MCU
 * @param		wm89xx_auidoInterface_t - audio interace structure with MCU
 * @retval		0 - success, 1 - failed.
 * @note			R6(): 0bit, 8:2bit, R4(): 8:1bit
 */
int8_t wm8974_DigitalAudioInterface(wm89xx_clockConfig_t clock, wm89xx_audioInterface_t audioInterface)
{
	uint16_t value = (uint16_t)(clock.mode | (clock.bclkDiv<<2) | (clock.mclkDiv<<5) | (clock.clkSel<<8));
	if ( 1 == wm89xx_WriteOneRegister(&I2C_HANDLE, WM8974_I2C_ADDR, value, WM8974_CLOCK_GEN_CTRL))
		return 1;
	
	value = (uint16_t)((audioInterface.adcLRSwap<<1) | (audioInterface.dacLRSwap<<2) | (audioInterface.format << 3) |
					(audioInterface.wordLen<<5) | (audioInterface.framePolarity<<7) | (audioInterface.bclkPolarity<<8));
	if ( 1 == wm89xx_WriteOneRegister(&I2C_HANDLE, WM8974_I2C_ADDR, value, WM8974_AUDIO_INTERFACE))
		return 1;
	
	return 0;
}

int8_t wm8974_SoftwareReset(void)		// R44(00h):
{
	if (1 == wm89xx_WriteOneRegister(&I2C_HANDLE, WM8974_I2C_ADDR, 0x01FF, WM8974_SOFTWARE_RESET))
		return 1;
	return 0;
}

// Input PGA configure function prototype
int8_t wm8974_InputPGAEnable(uint8_t newState)		// R2(): 2bit 
{
	uint16_t regVal;
	if (newState > 1)
		return 1;
	
	g_wm8974AllCtrlWordArr[WM8974_PWR_MANAGF2].value |= (newState << 2);
	regVal = g_wm8974AllCtrlWordArr[WM8974_PWR_MANAGF2].value;
	wm89xx_WriteOneRegister(&I2C_HANDLE, WM8974_I2C_ADDR, regVal, g_wm8974AllCtrlWordArr[WM8974_PWR_MANAGF2].reg);
	
	return 0;
}

/**
 * @breif		Configurating Input PGA, named 'intput PGA volume control' register, 
 *					gain from -12dB to +35.25dB with 0.75dB step.
 *
 * @param		volume
 *						INPPAGVOL value of 'input PGA volume control' register.
 *
 * @retval		0 - set success, 1 - failed.
 *
 * @note			None
 */
int8_t wm8974_InputPGAVolumeCtrl(uint8_t volume)	// R45(): 5:0bit
{
	uint16_t regVal = 0;
	
	if (volume > 0x3F)
		volume = 0x3F;
	
	regVal = (g_wm8974AllCtrlWordArr[WM8974_INPUT_PGA_GAIN_CTRL].value & (~0x003F)) | (uint16_t)volume;
	if (0 == wm89xx_WriteOneRegister(&I2C_HANDLE, WM8974_I2C_ADDR, regVal, g_wm8974AllCtrlWordArr[WM8974_INPUT_PGA_GAIN_CTRL].reg))
        g_wm8974AllCtrlWordArr[WM8974_INPUT_PGA_GAIN_CTRL].value = regVal;
	
	return 0;
}

//#define wm8974_InputPGAMuteCtrl(newState)		wm8974_InputPGAVolumeCtrl(newState)			// R45(): 6bit
//#define wm8974_InputPGAZeroCrossCtrl(newState)	wm8974_InputPGAVolumeCtrl(newState)	// R45(): 7bit

int8_t wm8974_ALCEnable(uint8_t newState)				// R32(): 8bit
{
	uint16_t regVal;
	
	if (newState > 1)
		return 1;
	
	g_wm8974AllCtrlWordArr[WM8974_ALC_CTRL1].value |= (newState << 8);
	regVal = g_wm8974AllCtrlWordArr[WM8974_ALC_CTRL1].value;
	wm89xx_WriteOneRegister(&I2C_HANDLE, WM8974_I2C_ADDR, regVal, g_wm8974AllCtrlWordArr[WM8974_ALC_CTRL1].reg);
	return 0;
}

// Auxiliary input configure
//#define wm8974_AuxInputPGA(newState)	wm8974_InputPGAVolumeCtrl(newState)		// R44(): 2bit

int8_t wm8974_AuxEnable(uint8_t newState)		// R1(): 5bit
{
	return 0;
}

int8_t wm8974_AuxMode(uint8_t newState)			// R44(): 3bit
{
	return 0;
}

// Input boost stage configure
int8_t wm8974_BoostEnable(uint8_t newState)	// R2(): 4bit
{
	return 0;
}

int8_t wm8974_PGABoost(uint8_t newState)			// R47(): 8bit
{
	return 0;
}

int8_t wm8974_AuxBoostVol(uint8_t gain)			// R47(): 2:0bit
{
	return 0;
}

int8_t wm8974_MICPBoostVol(uint8_t gain)			// R47(): 6:4bit
{
	return 0;
}

// Microphone bias circuit configure
int8_t wm8974_MicBiasEnable(uint8_t newState)	// R1(): 4bit
{
	return 0;
}

int8_t wm8974_MicBiasVoltage(uint8_t voltage)	// R44(): 8bit
{
	return 0;
}

// ADC configure
int8_t wm8974_ADCEnable(uint8_t newState)					// R2(): 0bit
{
	return 0;
}

int8_t wm8974_ADCOverSampleRate(uint8_t newState)	// R14(): 3bit
{
	return 0;
}

int8_t wm8974_ADCPolarity(uint8_t newState)				// R14(): 0bit
{
	return 0;
}

int8_t wm8974_HighPassFilter(uint8_t value)				// R14(): 8:4bit
{
	return 0;
}

int8_t wm8974_NotchFilter(uint8_t a0, uint8_t a1)	// R27(), R28(), R29(), R30()
{
	return 0;
}

// Digital ADC volume control
int8_t wm8974_ADCDigitalVolume(uint8_t adcVolume)	// R15(): 7:0bit
{
	return 0;
}

int8_t wm8974_DACEnable(uint8_t newState)					// R3(): 0bit
{
	return 0;
}

// DAC digital Hi-Fi volume control
int8_t wm8974_DACDigitalVolume(uint8_t dacVolume)	// R11(): 7:0bit
{
	return 0;
}

// Hi-Fi DAC
int8_t wm8974_DACDeEmphasis(uint8_t newState)			// R10(): 5:4bit
{
	return 0;
}

// DAC mute
int8_t wm8974_DACSoftMute(uint8_t newState)				// R10(): 6bit
{
	return 0;
}
int8_t wm8974_DACAnalogueMute(uint8_t newState)		// R10(): 2bit
{
	return 0;
}

// 5-band graphic EQ
int8_t wm8974_EQMode(uint16_t mode)								// R18(): 8bit
{
	return 0;
}
int8_t wm8974_EQConfig(uint8_t mode, uint8_t bandIndex, uint16_t value)	// R18(), R19(), R20(), R21(), R22()
{
	return 0;
}

// Analogue outputs
int8_t wm8974_SpeakerBoost(uint8_t newState)				// R49(): 2bit
{
	return 0;
}

int8_t wm8974_MonoBoost(uint8_t newState)					// R48(): 3bit
{
	return 0;
}

int8_t wm8974_BufferDCLevelShiftEnable(uint16_t newState)		// R1(): 8bit
{
	return 0;
}

// Speaker output
int8_t wm8974_SelectPath2Speaker(uint8_t path)			// R50(): 1:0bit, 5bit
{
	return 0;
}

int8_t wm8974_SpeakerAttn(uint8_t newState)				// R40(): 1bit
{
	return 0;
}

int8_t wm8974_SpeakerVolume(uint8_t volume)				// R54(): 7:0bit
{
	return 0;
}

// Zero cross timeout
int8_t wm8974_SlowClkEnable(uint8_t newState)			// R7(): 0bit
{
	return 0;
}

// Mono output
int8_t wm8974_SelectPath2Mono(uint8_t path)				// R56(): 2:0bit
{
	return 0;
}

int8_t wm8974_MonoMute(uint8_t newState)						// R56(): 6bit
{
	return 0;
}

int8_t wm8974_MonoAttn(uint8_t newState)						// R40(): 0bit
{
	return 0;
}

// Enabling the outputs
int8_t wm8974_EnableOutput(uint8_t pwrManage1, uint8_t selectOutput)			// R1(): 3:2bit, 8bit, R3(): 3:2bit, 7:5bit
{
	return 0;
}

int8_t wm8974_SelectVREF2AnalogueResistance(uint8_t resistaceIdx)				// R49(): 0bit
{
	return 0;
}

// Companding
int8_t wm8974_CompandSelcet(uint8_t side, uint8_t compandMethod)					// R5(): 4:1bit
{
	return 0;
}

// Audio sample rates
int8_t wm8974_SampleRate(uint8_t sampleRate)					// R7(): 3:1bit
{
	return 0;
}

// GPIO configure
int8_t wm8974_GPIOConfig(uint8_t value)							// R8(): 5:0bit
{
	return 0;
}

// Power management
int8_t wm8974_OversampleRateSelect(uint8_t side, uint8_t oversampleRate)		// R10(): 3bit, R14(): 3bit
{
	return 0;
}

int8_t wm8974_VMIDSelect(uint8_t value)							// R1(): 1:0bit
{
	return 0;
}

int8_t wm8974_AnalogueAmpBiasEnable(uint8_t newState)			// R1(): 3bit
{
	return 0;
}
