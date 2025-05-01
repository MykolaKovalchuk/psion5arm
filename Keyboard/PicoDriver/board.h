/*
 This is how the pins are connected to the keyboard.
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

// See the keyboard schematic for row/col mapping
#define NROWS 8
#define NCOLS 7

// Psion keyboard contacts numbered 0-21 left to right when looking on keyboard normally with contact cable placed straight up.
// Contacts 0 and 21 are not used.

// Use GPIO 1-15 - all on one side of RP2040 chip

#define ROW_01  15 // 20
#define ROW_02  14 // 19
#define ROW_03  13 // 18
#define ROW_04  12 // 17
#define ROW_05  11 // 16
#define ROW_06  9  // 14
#define ROW_07  8  // 13
#define ROW_08  7  // 12

#define COL_1   10 // 15
#define COL_2   6  // 11
#define COL_3   5  // 10
#define COL_4   4  // 9
#define COL_5   3  // 8
#define COL_6   2  // 7
#define COL_7   1  // columns 7-12, contacts 1-6, combined together (each column contact just has 1 key mapped)

int Rows [NROWS] = {
  ROW_01,
  ROW_02,
  ROW_03,
  ROW_04,
  ROW_05,
  ROW_06,
  ROW_07,
  ROW_08
};

int Cols [NCOLS] = {
  COL_1,
  COL_2,
  COL_3,
  COL_4,
  COL_5,
  COL_6,
  COL_7
};
