/*
    TLC59116.cpp - Library to interface with Texas Instruments TLC59116
    I2C bus controlled 16-channel LED driver
    https://github.com/alayander/tlc59116
*/

#include "TLC59116.h"

TLC59116::TLC59116(uint8_t addr) { _addr = addr; }

void TLC59116::begin() {
    Wire.begin();
    /* Set MODE1 register to default values except bit [4] */
    /* According to spec sheet, proper operation requires bit [4] to be set low */
    writeToReg(MODE1, 0x01);
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
    }
}

void TLC59116::setBrightness(uint8_t channel, uint8_t brightness) {
    writeToReg(PWM0 + (channel & 0x0F), brightness);
}

void TLC59116::writeToReg(uint8_t reg, uint8_t val) {
    Wire.beginTransmission(_addr);
    Wire.write((char) reg);
    Wire.write((char) val);
    Wire.endTransmission();
}
