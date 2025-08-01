#include <Mouse.h>
#include <CirquePinnacle.h>

#define SS_PIN 20
#define DR_PIN 21
#define LED LED_BUILTIN

PinnacleTouchSPI trackpad(DR_PIN, SS_PIN);
// If using I2C, then use the following line (not the line above)
// PinnacleTouchI2C trackpad(DR_PIN);

// an object to hold data reported by the Cirque trackpad
RelativeReport data;

const uint32_t interval = 750;  // milliseconds used to blink LED
uint32_t lastLedChange = 0;     // millis() since last digitalWrite()
bool ledState = false;          // last state sent to digitalWrite()

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);

  sleep_ms(1000);

  if (!trackpad.begin()) {
    while (true) {
      // hold program in infinite loop
    }
  }
  // By default, the trackpad is configured to use relative mode with
  // tap detection enabled. This config fits nicely with Mouse HID reports!

  trackpad.setDataMode(PINNACLE_RELATIVE);  // ensure mouse mode is enabled
  // tell the Pinnacle ASIC to rotate the orientation of the axis data by +90 degrees
  trackpad.relativeModeConfig(true, true);  // (enable taps, rotate90)


  digitalWrite(LED, LOW);
  lastLedChange = millis();
}

void loop() {

  if (trackpad.available()) {  // is there new data?

    // save buttons' previous state before getting updates
    uint8_t prevButtonStates = data.buttons;  // for edge detection

    trackpad.read(&data);  // get new data

    // edge detection for binary button data
    uint8_t buttonsChanged = prevButtonStates ^ data.buttons;
    if (buttonsChanged) {
      uint8_t toggledOff = buttonsChanged ^ (data.buttons & buttonsChanged);
      uint8_t toggledOn = buttonsChanged ^ toggledOff;
      if (toggledOn) {
        Mouse.press(toggledOn);
      }
      if (toggledOff) {
        Mouse.release(toggledOff);
      }
    }

    if (data.x || data.y || data.scroll) {
      // invert the x-axis, use the others as is
      Mouse.move(data.x * -1, data.y, data.scroll);
    }
  }  // end if trackpad.available()

  if (millis() - lastLedChange > interval) {
    lastLedChange = millis();
    ledState = !ledState;
    digitalWrite(LED, ledState);
  }
}