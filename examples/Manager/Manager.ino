/*
 * This sketch demonstrates the ability of using the manager class
 * to set a pattern across three drivers.
 */

#include <TLC59116.h>
#include <TLC59116Manager.h>
#include <Wire.h>

#define RESET_PIN 5

TLC59116 board1(0b1100011, false);
TLC59116 board2(0b1100100, false);
TLC59116 board3(0b1100101, false);
TLC59116Manager manager;

void setup() {
  Wire.begin();
  Wire.setClock(400000);

  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, LOW);
  delay(5);
  digitalWrite(RESET_PIN, HIGH);

  if (!manager.add(&board1))
    Serial.println("Failed to add board1");
  if (!manager.add(&board2))
    Serial.println("Failed to add board2");
  if (!manager.add(&board3))
    Serial.println("Failed to add board3");

  manager.begin();
}

void loop() {
  manager.setPattern(0x5555555555555555, 200);
  delay(100);
  manager.setPattern(0xAAAAAAAAAAAAAAAA, 200);
  delay(100);
}
