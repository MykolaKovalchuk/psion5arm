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

  if (KEYBOARD_ENABLED) Keyboard.begin();

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

    //digitalWrite(LED_BUILTIN, keypressArrayCurrent[0][1]);
    digitalWrite(LED_BUILTIN, nKeysPressed == 0 ? LOW : HIGH);

    // Send the keypresses over USB
    if (KEYBOARD_ENABLED)
    {
      sendKeys(keypressArrayCurrent, keypressArrayPrevious);
    }

    // Remember which keys were pressed so we can release them later
    memcpy(keypressArrayPrevious, keypressArrayCurrent, sizeof(keypressArrayCurrent));
    previousTime = millis();
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
    //digitalWrite(Cols[col], LOW);
  }

  return nKeysPressed;
}

void sendKeys(int pressedArray[][NCOLS], int previousArray[][NCOLS])
{
  for (int row = 0; row < NROWS; row++)
  {
    for (int col = 0; col < NCOLS; col++)
    {
      // Only scan mapped buttons
      if (keyScancode[row][col] != 0)
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
}

/*
void sendKeys(int pressedArray[][NCOLS], int previousArray[][NCOLS])
{
  for (int row = 0; row < NROWS; row++)
  {
    for (int col = 0; col < NCOLS; col++)
    {
      // Only scan mapped buttons
      if (keyScancode[row][col] != 0)
      {
        // If a new button is pressed
        if (pressedArray[row][col] > previousArray[row][col])
        {
          // Ugly hack to fix the Delete Key under Windows
          // Is the backspace key pressed?
          if ( row == 2 && col == 4)
          {
            // Is any of the shift keys pressed?
            if (pressedArray[0][6] > 0 || pressedArray[7][7] > 0)
            {
              // Shift is pressed, send DELETE
              Keyboard.press(KEY_DELETE);
            }
            else
            {
              // No Shift key pressed, send BACKSPACE
              Keyboard.press(KEY_BACKSPACE);
            }
          }
          else if ((row == 0 && col == 6) || (row == 7 && col == 7))
          {
            // Special handling of the SHIFT keys
            // Since we need to press SHIFT to send the KEY_DELETE, we need
            // to make sure that we don't send the shift key as well unless
            // BOTH shift keys are pressed...
            if (pressedArray[2][4] > 0)
            {
              // BACKSPACE/DELETE key is pressed
              if ((pressedArray[0][6] > 0) && (pressedArray[7][7] > 0))
              {
                // Both shift keys are pressed, send the SHIFT keys
                Keyboard.press(keyScancode[row][col]);
              } // If only one was pressed, we don't want to send SHIFT.
            }
            else {
              // Backspace / delete is not pressed
              // Send the shift keys as usual
              Keyboard.press(keyScancode[row][col]);
            }
          }
          else {
            // "Normal" keypress, just send as is
            Keyboard.press(keyScancode[row][col]);
          }
        }
        // This handles the release of keys
        else if (pressedArray[row][col] < previousArray[row][col])
        {
          // Make sure we release either BACKSPACE or DELETE; whatever was pressed
          if (row == 2 && col == 4)
          {
            Keyboard.release(KEY_DELETE);
            Keyboard.release(KEY_BACKSPACE);
          }
          else
          {
            Keyboard.release(keyScancode[row][col]);
          }
        }
      }
    }
  }
}
//*/
