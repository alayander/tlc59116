/*
	TLC59116.cpp - Library to interface with Texas Instruments TLC59116
	I2C bus controlled 16-channel LED driver
	https://github.com/alayander/tlc59116
*/

#include "TLC59116.h"

TLC59116::TLC59116(uint8_t addr) {
	_addr = addr;
	_enable_shadow_registers = true;
}

TLC59116::TLC59116(uint8_t addr, bool enable_shadow_registers) {
	_addr = addr;
	_enable_shadow_registers = enable_shadow_registers;
}

void TLC59116::begin() {
	/* Set MODE1 register to default values except bit [4] (OSC bit) */
	/* According to spec sheet, proper operation requires OSC bit to be set low */
	writeToReg(MODE1, 0x01);
	/* At least 500us delay are required after setting OSC bit */
	delay(1);
	/* Set MODE2 register to default values */
	writeToReg(MODE2, 0x00);
	/* Enable each channel to be driven by individual PWM */
	writeToReg(LEDOUT0, 0xAA);
	writeToReg(LEDOUT1, 0xAA);
	writeToReg(LEDOUT2, 0xAA);
	writeToReg(LEDOUT3, 0xAA);
	/* Initialize all channels to 0 (off) */
	for (uint8_t channel = 0; channel < NUM_CHANNELS; channel++) {
		setBrightness(channel, 0x00);
		_shadow_registers[channel] = 0x00;
	}
}

void TLC59116::setPatternAutoIncrement(uint16_t pattern, uint8_t brightness) {
	Wire.beginTransmission(_addr);
	Wire.write((char)AUTO_INCREMENT_PATTERN);
	for (uint8_t channel = 0; channel < NUM_CHANNELS; channel++) {
		if (pattern & (1 << channel)) {
			Wire.write((char)brightness);
		} else {
			Wire.write((char)0x00);
		}

		if (_enable_shadow_registers) {
			_shadow_registers[channel] = brightness;
		}
	}
	Wire.endTransmission();
}

void TLC59116::setPatternPerChannel(uint16_t pattern, uint8_t brightness) {
	for (uint8_t channel = 0; channel < NUM_CHANNELS; channel++) {
		if (pattern & (1 << channel)) {
			setBrightness(channel, brightness);
		} else {
			setBrightness(channel, 0x00);
		}
	}
}

void TLC59116::setBrightness(uint8_t channel, uint8_t brightness) {
	if (!_enable_shadow_registers || _shadow_registers[channel] != brightness) {
		writeToReg(PWM0 + (channel & 0x0F), brightness);
		_shadow_registers[channel] = brightness;
	}
}

void TLC59116::writeToReg(uint8_t reg, uint8_t val) {
	Wire.beginTransmission(_addr);
	Wire.write((char)reg);
	Wire.write((char)val);
	Wire.endTransmission();
}
