/*
 Maps the keys to ASCII symbols as shown here:
 https://www.arduino.cc/reference/cs/language/functions/usb/keyboard/keyboardmodifiers/
 more here: file://c:\Users\mykol\AppData\Local\Arduino15\packages\rp2040\hardware\rp2040\4.5.2\libraries\HID_Keyboard\src\HID_Keyboard.h
*/

#define KEY_A          0x61
#define KEY_B          0x62
#define KEY_C          0x63
#define KEY_D          0x64
#define KEY_E          0x65
#define KEY_F          0x66
#define KEY_G          0x67
#define KEY_H          0x68
#define KEY_I          0x69
#define KEY_J          0x6A
#define KEY_K          0x6B
#define KEY_L          0x6C
#define KEY_M          0x6D
#define KEY_N          0x6E
#define KEY_O          0x6F
#define KEY_P          0x70
#define KEY_Q          0x71
#define KEY_R          0x72
#define KEY_S          0x73
#define KEY_T          0x74
#define KEY_U          0x75
#define KEY_V          0x76
#define KEY_W          0x77
#define KEY_X          0x78
#define KEY_Y          0x79
#define KEY_Z          0x7A

#define KEY_0          0x30
#define KEY_1          0x31
#define KEY_2          0x32
#define KEY_3          0x33
#define KEY_4          0x34
#define KEY_5          0x35
#define KEY_6          0x36
#define KEY_7          0x37
#define KEY_8          0x38
#define KEY_9          0x39

#define KEY_ENTER      0xB0
#define KEY_ESC        0xB1
#define KEY_BACKSPACE  0xB2
#define KEY_TAB        0xB3
#define KEY_SPACE      0x20
#define KEY_APOSTROPHE 0x27
#define KEY_COMMA      0x2C
#define KEY_PERIOD     0x2E
#define KEY_RIGHT      0xD7
#define KEY_LEFT       0xD8
#define KEY_DOWN       0xD9
#define KEY_UP         0xDA
#define KEY_CTRL       0x80   // Left CTRL
#define KEY_LSHIFT     0x81
//#define KEY_ALT_MENU   KEY_MENU   // Context Menu
#define KEY_ALT_MENU   0x82   // Mapped as Left Alt
#define KEY_RSHIFT     0x85
//#define KEY_FN         KEY_RIGHT_ALT   // Mapped as AltGr
#define KEY_FN         KEY_LEFT_GUI   // Windows Key - press and release

static int keyScancode [NROWS] [NCOLS] = {
  { 0       , KEY_SPACE , KEY_UP , KEY_COMMA , KEY_LEFT      , KEY_RIGHT      , KEY_LSHIFT   },
  { KEY_Z   , KEY_X     , KEY_C  , KEY_V     , KEY_B         , KEY_N          , KEY_RSHIFT   },
  { KEY_H   , KEY_J     , KEY_K  , KEY_M     , KEY_PERIOD    , KEY_DOWN       , KEY_FN       },
  { KEY_TAB , KEY_A     , KEY_S  , KEY_D     , KEY_F         , KEY_G          , KEY_CTRL     },
  { KEY_1   , KEY_2     , KEY_3  , KEY_4     , KEY_5         , KEY_6          , 0            },
  { KEY_U   , KEY_I     , KEY_O  , KEY_P     , KEY_L         , KEY_ENTER      , KEY_ALT_MENU },
  { KEY_Q   , KEY_W     , KEY_E  , KEY_R     , KEY_T         , KEY_Y          , KEY_ESC      },
  { KEY_7   , KEY_8     , KEY_9  , KEY_0     , KEY_BACKSPACE , KEY_APOSTROPHE , 0            }
};
