/*
    TLC59116Manager.cpp - Library to manage multiple
    Texas Instruments TLC59116 I2C bus controlled 16-channel LED driver
    https://github.com/alayander/tlc59116
*/

#include "TLC59116Manager.h"

TLC59116Manager::TLC59116Manager() {
    _count = 0;
}

bool TLC59116Manager::add(TLC59116* driver) {
    if (_count < 4) {
        _drivers[_count++] = driver;
        return true;
    }

    return false;
}

void TLC59116Manager::begin() {
    for (size_t i = 0; i < _count; i++) {
        _drivers[i]->begin();
    }
}

void TLC59116Manager::setPattern(uint64_t pattern, uint8_t brightness) {
    for (size_t i = 0; i < _count; i++) {
        uint16_t subpattern = (pattern >> (i * 16)) & 0xFFFF;
        _drivers[i]->setPattern(subpattern, brightness);
    }
}
