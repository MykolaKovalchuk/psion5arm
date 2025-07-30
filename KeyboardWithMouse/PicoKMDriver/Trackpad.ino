/*
 Cirque Trackpad code is derived on library and examples from https://github.com/2bndy5/CirquePinnacle
*/

PinnacleTouchSPI trackpad(DR_PIN, SS_PIN);

RelativeReport trackpadData; // An object to hold data reported by the Cirque trackpad

void setupTrackpad()
{
  if (!trackpad.begin())
  {
    while (true)
    {
      // Hold program in infinite loop
    }
  }

  // By default, the trackpad is configured to use relative mode with tap detection enabled.
  // This config fits nicely with Mouse HID reports!
  trackpad.setDataMode(PINNACLE_RELATIVE); // Ensure mouse mode is enabled

  // Tell the Pinnacle ASIC to rotate the orientation of the axis data by +90 degrees
  trackpad.relativeModeConfig(true, true); // (enable taps, rotate90)
}

void processTrackpad()
{
  if (trackpad.available()) // Is there new data?
  {
    // Save buttons previous state before getting updates
    uint8_t prevButtonStates = trackpadData.buttons;

    trackpad.read(&trackpadData);

    uint8_t buttonsChanged = prevButtonStates ^ trackpadData.buttons;
    if (buttonsChanged)
    {
      uint8_t toggledOff = buttonsChanged ^ (trackpadData.buttons & buttonsChanged);
      uint8_t toggledOn = buttonsChanged ^ toggledOff;
      if (toggledOn)
      {
        Mouse.press(toggledOn);
      }
      if (toggledOff)
      {
        Mouse.release(toggledOff);
      }
    }

    if (trackpadData.x || trackpadData.y || trackpadData.scroll)
    {
      // Invert the x-axis, use the others as is
      Mouse.move(trackpadData.x * -1, trackpadData.y, trackpadData.scroll);
    }
  }
}
