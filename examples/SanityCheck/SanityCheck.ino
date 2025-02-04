/*
 * This sketch demonstrates the ability to set individual channels of 
 * a TLC59116 driver using the setBrightness() function.
 */

#include <TLC59116.h>
#include <Wire.h>

#define RESET_PIN 5

TLC59116 board(0b1100000);

void setup() {
  Wire.begin();

  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, LOW);
  delay(5);
  digitalWrite(RESET_PIN, HIGH);
  
  board.begin();
}

void loop() {
  for (uint8_t channel = 0; channel < NUM_CHANNELS; channel++) {
    board.setBrightness(channel, 255);
    delay(10);
    board.setBrightness(channel, 0);
  }
}
