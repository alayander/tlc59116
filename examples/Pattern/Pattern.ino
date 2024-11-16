/*
 * This sketch demonstrates the ability to set all channels of 
 * a TLC59116 driver simultaneously using the setPattern() function.
 */

#include <TLC59116.h>

#define RESET_PIN D5

TLC59116 board(0b1100000);

void setup() {
  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, LOW);
  delay(5);
  digitalWrite(RESET_PIN, HIGH);
  
  board.begin();
}

void loop() {
  board.setPattern(0xAAAA, 255);
  delay(1000);
  board.setPattern(0x5555, 255);
  delay(1000);
}
