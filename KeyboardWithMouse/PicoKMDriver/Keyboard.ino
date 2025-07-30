/*
 Keyboard code based on original RasmusB code https://github.com/RasmusB/USB-Keyboard-Adapter and guide https://hackaday.io/project/4042-psio
 Additional guide: https://jbmorley.co.uk/posts/2018-03-11-psion-bluetooth-keyboard/
*/

#define SWITCH_DELAY 50 // Microseconds to wait after setting output LOW before scannnig keys

int keypressArrayCurrent[NROWS][NCOLS];
int keypressArrayPrevious[NROWS][NCOLS];

bool fnPressed;
bool keyFModifierPressed; // Fn + F1_F10_Modifier + 1-0 = F1-F10

void setupKeyboard()
{
  Keyboard.begin();
  Keyboard.onLED(ledCB);

  for (int i = 0; i < NCOLS; i++)
  {
    pinMode(Cols[i], INPUT);
  }

  for (int i = 0; i < NROWS; i++)
  {
    pinMode(Rows[i], INPUT_PULLUP);
  }
}

void ledCB(bool numlock, bool capslock, bool scrolllock, bool compose, bool kana, void *cbData)
{
  (void) numlock;
  (void) scrolllock;
  (void) compose;
  (void) kana;
  (void) cbData;
  digitalWrite(LED, capslock ? HIGH : LOW);
}

void processKeyboard()
{
  int nKeysPressed = scanKeyboard(keypressArrayCurrent);

  sendKeys(keypressArrayCurrent, keypressArrayPrevious);
  if (nKeysPressed == 0)
  {
    Keyboard.releaseAll(); // Ensure we don't hold anything
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
}

int scanKeyboard(int keyArray[][NCOLS])
{
  int nKeysPressed = 0;
  fnPressed = false;
  keyFModifierPressed = false;

  // We need to go by columns first, because columns 7-12 combined on a single contact pin
  for (int col = 0; col < NCOLS; col++)
  {
    // Select a pin to sink current
    pinMode(Cols[col], OUTPUT);
    digitalWrite(Cols[col], LOW);
    delayMicroseconds(SWITCH_DELAY); // Without small delay there are some inconsistencies in keys scanning

    for (int row = 0; row < NROWS; row++)
    {
      int scanCode = keyScancode[row][col];

      if (scanCode != 0)
      {
        if (digitalRead(Rows[row]) == LOW)
        {
          if (keyArray[row][col] == 0) // If no pressed scancode yet stored
          {
            keyArray[row][col] = 1;
          }
          if (scanCode == KEY_FN)
          {
            fnPressed = true;
          }
          if (scanCode == KEY_F1_F10)
          {
            keyFModifierPressed = true;
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

  translateScanCodes(keyArray);

  return nKeysPressed;
}

void translateScanCodes(int keyArray[][NCOLS])
{
  for (int col = 0; col < NCOLS; col++)
  {
    for (int row = 0; row < NROWS; row++)
    {
      if (keyArray[row][col] == 1) // 1 == newly pressed key
      {
        int scanCode = keyScancode[row][col];
        if (fnPressed && keyFModifierPressed && scanCode >= KEY_0 && scanCode <= KEY_9) // Fn + F1_F10_Modifier + 1-0 = F1-F10
        {
          if (scanCode == KEY_0)
          {
            scanCode = KEY_F10;
          }
          else
          {
            scanCode = scanCode - KEY_1 + KEY_F1; // Translate 1-9 to F1-F9
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
}

void sendKeys(int pressedArray[][NCOLS], int previousArray[][NCOLS])
{
  bool mouseMoved = false;

  for (int row = 0; row < NROWS; row++)
  {
    for (int col = 0; col < NCOLS; col++)
    {
      int newKey = pressedArray[row][col];
      int oldKey = previousArray[row][col];

      if (newKey != KEY_FN && oldKey != KEY_FN) // Do not report Fn key itself
      {
        if (newKey != 0 && oldKey == 0) // If a new button is pressed (ignore key scanCode change by Fn press or release)
        {
          Keyboard.press(newKey);
        }
        else if (newKey == 0 && oldKey != 0) // This handles the release of keys
        {
          Keyboard.release(oldKey); // Release previously pressed key (with memory of its Fn state when pressed)
        }
      }
    }
  }
}
