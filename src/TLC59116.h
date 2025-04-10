/*
	TLC59116.h - Library to interface with Texas Instruments TLC59116
	I2C bus controlled 16-channel LED driver
	https://github.com/alayander/tlc59116
*/

#ifndef TLC59116_h
#define TLC59116_h

#include <Arduino.h>
#include <Wire.h>

#define NUM_CHANNELS 16

#define AUTO_INCREMENT_PATTERN 0b10100010

/* Register Defintions */
#define MODE1 0x00
#define MODE2 0x01
#define PWM0 0x02
#define PWM1 0x03
#define PWM2 0x04
#define PWM3 0x05
#define PWM4 0x06
#define PWM5 0x07
#define PWM6 0x08
#define PWM7 0x09
#define PWM8 0x0A
#define PWM9 0x0B
#define PWM10 0x0C
#define PWM11 0x0D
#define PWM12 0x0E
#define PWM13 0x0F
#define PWM14 0x10
#define PWM15 0x11
#define GRPPWM 0x12
#define GRPFREQ 0x13
#define LEDOUT0 0x14
#define LEDOUT1 0x15
#define LEDOUT2 0x16
#define LEDOUT3 0x17
#define SUBADR1 0x18
#define SUBADR2 0x19
#define SUBADR3 0x1A
#define ALLCALLADR 0x1B
#define IREF 0x1C
#define EFLAG1 0x1D
#define EFLAG2 0x1E

class TLC59116 {
  private:
	uint8_t _addr;
	uint8_t _shadow_registers[16];
	bool _enable_shadow_registers;
	/* Write value to a register */
	void writeToReg(uint8_t reg, uint8_t val);

  public:
	/* Constructors */
	TLC59116(uint8_t addr);
	TLC59116(uint8_t addr, bool _enable_shadow_registers);
	/* Initialize the driver and set all channels to default (0) */
	void begin();
	/* Sets a pattern using auto increment */
	void setPatternAutoIncrement(uint16_t pattern, uint8_t brightness);
	/* Sets a pattern by writing manually to each channel */
	void setPatternPerChannel(uint16_t pattern, uint8_t brightness);
	/* Set brightness value (0-255) for a given channel (0-15) */
	void setBrightness(uint8_t channel, uint8_t brightness);
};

#endif
