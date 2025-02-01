/*
	TLC59116Manager.h - Library to manage multiple
	Texas Instruments TLC59116 I2C bus controlled 16-channel LED driver
	https://github.com/alayander/tlc59116
*/

#ifndef TLC59116Manager_h
#define TLC59116Manager_h

#include <Arduino.h>
#include <TLC59116.h>
#include <Wire.h>

class TLC59116Manager {
  private:
	TLC59116 *_drivers[4];
	size_t _count;

  public:
	/* Constructor */
	TLC59116Manager();
	/* Add driver to manager */
	bool add(TLC59116 *driver);
	/* Initialize all drivers and set all channels to default (0) */
	void begin();
	/* Set bits given by binary pattern to brightness value (0-255) */
	void setPattern(uint64_t pattern, uint8_t brightness);
};

#endif
