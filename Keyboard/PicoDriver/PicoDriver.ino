/*
 Raspberry Pico USB keyboard driver for Psino Series 5 keyboard.
 Made in Arduino IDE with https://github.com/earlephilhower/arduino-pico/ library (using guide https://randomnerdtutorials.com/programming-raspberry-pi-pico-w-arduino-ide/).

 Code based on original RasmusB code https://github.com/RasmusB/USB-Keyboard-Adapter and guide https://hackaday.io/project/4042-psio
 Additional guide: https://jbmorley.co.uk/posts/2018-03-11-psion-bluetooth-keyboard/
*/

#include "board.h"
#include "Keyboard.h"
#include "PsionKeymapUSB.h"

#define KEYBOARD_ENABLED true

// Max number of scans/second
#define MAX_SCAN_RATE 100

int keypressArrayCurrent[NROWS][NCOLS];
int keypressArrayPrevious[NROWS][NCOLS];

unsigned long previousTime;
unsigned int minDelay;

void setup()
{
  previousTime = 0;
  minDelay = 1000 / MAX_SCAN_RATE;

  if (KEYBOARD_ENABLED)
  {
    Keyboard.begin();
    Keyboard.onLED(ledCB);
  }

  pinMode(LED_BUILTIN, OUTPUT);

  for (int i = 0; i < NCOLS; i++)
  {
    pinMode(Cols[i], INPUT);
  }

  for (int i = 0; i < NROWS; i++)
  {
    pinMode(Rows[i], INPUT_PULLUP);
  }
}

void loop()
{
  if ((millis() - previousTime) >= minDelay)
  {
    // Scan the keyboard matrix
    int nKeysPressed = scanKeyboard(keypressArrayCurrent);

    // Send the keypresses over USB
    if (KEYBOARD_ENABLED)
    {
      sendKeys(keypressArrayCurrent, keypressArrayPrevious);
      if (nKeysPressed == 0)
      {
        // Ensure we don't hold anything
        Keyboard.releaseAll();
      }
    }

    // Remember which keys were pressed so we can release them later
    memcpy(keypressArrayPrevious, keypressArrayCurrent, sizeof(keypressArrayCurrent));
    previousTime = millis();
  }
  else
  {
    delay(1);
  }
}

int scanKeyboard(int keyArray[][NCOLS])
{
  int nKeysPressed = 0;

  for (int col = 0; col < NCOLS; col++)
  {
    // Select a pin to sink current
    pinMode(Cols[col], OUTPUT);
    digitalWrite(Cols[col], LOW);
    delay(1);

    for (int row = 0; row < NROWS; row++)
    {
      if (keyScancode[row][col] != 0)
      {
        if (digitalRead(Rows[row]) == LOW)
        {
          keyArray[row][col] = 1;
          nKeysPressed++;
        }
        else
        {
          keyArray[row][col] = 0;
        }
      }
    }

    pinMode(Cols[col], INPUT);
  }

  return nKeysPressed;
}

void sendKeys(int pressedArray[][NCOLS], int previousArray[][NCOLS])
{
  for (int row = 0; row < NROWS; row++)
  {
    for (int col = 0; col < NCOLS; col++)
    {
      // If a new button is pressed
      if (pressedArray[row][col] > previousArray[row][col])
      {
        Keyboard.press(keyScancode[row][col]);
      }
      // This handles the release of keys
      else if (pressedArray[row][col] < previousArray[row][col])
      {
        Keyboard.release(keyScancode[row][col]);
      }
    }
  }
}

void ledCB(bool numlock, bool capslock, bool scrolllock, bool compose, bool kana, void *cbData)
{
  (void) numlock;
  (void) scrolllock;
  (void) compose;
  (void) kana;
  (void) cbData;
  digitalWrite(LED_BUILTIN, capslock ? HIGH : LOW);
}
