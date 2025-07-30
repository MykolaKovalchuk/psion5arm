/*
 Raspberry Pico USB keyboard driver for Psino Series 5 keyboard.
 Made in Arduino IDE with https://github.com/earlephilhower/arduino-pico/ library (using guide https://randomnerdtutorials.com/programming-raspberry-pi-pico-w-arduino-ide/).

 Keyboard code based on original RasmusB code https://github.com/RasmusB/USB-Keyboard-Adapter and guide https://hackaday.io/project/4042-psio
 Additional guide: https://jbmorley.co.uk/posts/2018-03-11-psion-bluetooth-keyboard/

 Cirque Trackpad code is derived on library and examples from https://github.com/2bndy5/CirquePinnacle
*/

#include <Keyboard.h>
#include <Mouse.h>
#include <CirquePinnacle.h>
#include "board.h"
#include "PsionKeymapUSB.h"

#define MAX_SCAN_RATE 1000 // Max number of scans/second
#define LED LED_BUILTIN

unsigned long previousTime;
unsigned int minDelay;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED, HIGH);

  sleep_ms(1000);

  previousTime = 0;
  minDelay = 1000 / MAX_SCAN_RATE;

  setupKeyboard();
  setupTrackpad();

  digitalWrite(LED, LOW);
}

void loop()
{
  if ((millis() - previousTime) < minDelay)
  {
    delayMicroseconds(100);
    return;
  }

  processKeyboard();
  processTrackpad();

  previousTime = millis();
}
