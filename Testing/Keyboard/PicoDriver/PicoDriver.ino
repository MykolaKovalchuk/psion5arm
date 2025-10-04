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
#define MAX_SCAN_RATE 1000

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
        Keyboard.releaseAll(); // Ensure we don't hold anything
      }
    }

    // Remember which keys were pressed so we can release them later
    for (int col = 0; col < NCOLS; col++)
    {
      for (int row = 0; row < NROWS; row++)
      {
        if (keypressArrayPrevious[row][col] == 0 || keypressArrayCurrent[row][col] == 0) // Do not overwrite pressed keys with different scanCodes after Fn press or release
        {
          keypressArrayPrevious[row][col] = keypressArrayCurrent[row][col];
        }
      }
    }

    previousTime = millis();
  }
  else
  {
    delayMicroseconds(100);
  }
}

int scanKeyboard(int keyArray[][NCOLS])
{
  int nKeysPressed = 0;
  bool fnPressed = false;
  bool keyFPressed = false; // Fn + F + 1-0 = F1-F10

  // We need to go by columns first, because columns 7-12 combined on a single contact pin
  for (int col = 0; col < NCOLS; col++)
  {
    // Select a pin to sink current
    pinMode(Cols[col], OUTPUT);
    digitalWrite(Cols[col], LOW);
    delayMicroseconds(100); // Without small delay there are some inconsistencies in keys scanning

    for (int row = 0; row < NROWS; row++)
    {
      if (keyScancode[row][col] != 0)
      {
        if (digitalRead(Rows[row]) == LOW)
        {
          if (keyArray[row][col] == 0) // If no pressed scancode yet stored
          {
            keyArray[row][col] = 1;
          }
          if (keyScancode[row][col] == KEY_FN)
          {
            fnPressed = true;
          }
          if (keyScancode[row][col] == KEY_F)
          {
            keyFPressed = true;
          }

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

  // Store new keys scanCodes with current Fn
  for (int col = 0; col < NCOLS; col++)
  {
    for (int row = 0; row < NROWS; row++)
    {
      if (keyArray[row][col] == 1) // 1 == newly pressed key
      {
        int scanCode = keyScancode[row][col];
        if (fnPressed && keyFPressed && scanCode >= KEY_0 && scanCode <= KEY_9) // Fn + F + 1-0 = F1-F10
        {
          if (scanCode == KEY_0)
          {
            scanCode = KEY_F10;
          }
          else
          {
            scanCode = scanCode - KEY_1 + KEY_F1;
          }
        }
        else if (fnPressed)
        {
          scanCode = keyFnScancode[row][col];
        }

        keyArray[row][col] = scanCode;
      }
    }
  }

  return nKeysPressed;
}

void sendKeys(int pressedArray[][NCOLS], int previousArray[][NCOLS])
{
  for (int row = 0; row < NROWS; row++)
  {
    for (int col = 0; col < NCOLS; col++)
    {
      if (pressedArray[row][col] != KEY_FN && previousArray[row][col] != KEY_FN) // Do not report Fn key itself
      {
        if (pressedArray[row][col] != 0 && previousArray[row][col] == 0) // If a new button is pressed (ignore key scanCode change by Fn press or release)
        {
          Keyboard.press(pressedArray[row][col]);
        }
        else if (pressedArray[row][col] == 0 && previousArray[row][col] != 0) // This handles the release of keys
        {
          Keyboard.release(previousArray[row][col]); // Release previously pressed key (with memory of its Fn state when pressed)
        }
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