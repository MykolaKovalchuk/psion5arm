/*
 This is how the pins are connected to the keyboard and trackpad.
*/

// This disables the RX and TX LEDs that are not on this PCB
#undef TXLED0
#undef RXLED0
#undef TXLED1
#undef RXLED1
#undef TX_RX_LED_INIT

#undef LED_BUILTIN_RX
#undef LED_BUILTIN_TX

#define TXLED0 0
#define RXLED0 0 
#define TXLED1 0
#define RXLED1 0
#define TX_RX_LED_INIT 0

#define LED_BUILTIN_RX 0
#define LED_BUILTIN_TX 0

#define LED 28 // Use GPIO 28 instead of LED_BUILTIN

// See the keyboard schematic for row/col mapping
#define NROWS 8
#define NCOLS 7

// Psion keyboard contacts numbered 1-22 left to right when looking on keyboard normally with contact cable placed straight up.
// Contacts 1 and 22 are not used.
// Use GPIO 1-15 - all on one side of RP2040 chip.

#define ROW_01  15 // 21
#define ROW_02  14 // 20
#define ROW_03  13 // 19
#define ROW_04  12 // 18
#define ROW_05  11 // 17
#define ROW_06  9  // 15
#define ROW_07  8  // 14
#define ROW_08  7  // 13

#define COL_1   10 // 16
#define COL_2   6  // 12
#define COL_3   5  // 11
#define COL_4   4  // 10
#define COL_5   3  // 9
#define COL_6   2  // 8
#define COL_7   1  // columns 7-12, contacts 2-7, combined together (each column contact just has 1 key mapped)

int Rows[NROWS] = {
  ROW_01,
  ROW_02,
  ROW_03,
  ROW_04,
  ROW_05,
  ROW_06,
  ROW_07,
  ROW_08
};

int Cols[NCOLS] = {
  COL_1,
  COL_2,
  COL_3,
  COL_4,
  COL_5,
  COL_6,
  COL_7
};

// Cirque trackpad connected with 12 contacts FPC cable (1-12), see https://github.com/2bndy5/CirquePinnacle
// Following Pico pins are used for Cirque contacts.
// Using SPI0 of Raspberry Pico.

// Contact 1  - SCK - pin 24 / GP18 / SPI0 SCK
// Contact 2  - SO  - pin 21 / GP16 / SPI0 RX
#define SS_PIN 20 // Contact 3  - SS  - pin 26 / GP20
#define DR_PIN 21 // Contact 4  - DR  - pin 27 / GP21
// Contact 5  - SI  - pin 25 / GP19 / SPI0 TX
// Contact 11 - GND - pin 28 / GND
// Contact 12 - VDD - pin 36 / 3V3(OUT)
