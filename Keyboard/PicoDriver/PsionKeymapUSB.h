/*
 Maps the keys to ASCII symbols as shown here:
 https://www.arduino.cc/reference/cs/language/functions/usb/keyboard/keyboardmodifiers/
 more here: c:\Users\user-name\AppData\Local\Arduino15\packages\rp2040\hardware\rp2040\4.5.2\libraries\HID_Keyboard\src\HID_Keyboard.h
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

#define KEY_SPACE      0x20
#define KEY_HASH       0x23 // #
#define KEY_APOSTROPHE 0x27 // '
#define KEY_COMMA      0x2C // ,
#define KEY_PERIOD     0x2E // .
#define KEY_COLON      0x3A // :
#define KEY_SEMICOLON  0x3B // ;
#define KEY_ANGLE_L    0x3C // <
#define KEY_EQUAL      0x3D // =
#define KEY_ANGLE_R    0x3E // >
#define KEY_AT         0x40 // @
#define KEY_SQUARE_L   0x5B // [
#define KEY_BACK_SLASH 0x5C // \ 
#define KEY_SQUARE_R   0x5D // ]
#define KEY_UNDERSCORE 0x5F // _
#define KEY_TICK       0x60 // `
#define KEY_CURL_L     0x7B // {
#define KEY_PIPE       0x7C // |
#define KEY_CURL_R     0x7D // }
#define KEY_TILDA      0x7E // ~

#define KEY_FN         KEY_RIGHT_ALT   // Mapped as AltGr

static int keyScancode[NROWS][NCOLS] = {
  { 0              , KEY_SPACE        , KEY_UP_ARROW   , KEY_COMMA                , KEY_LEFT_ARROW           , KEY_RIGHT_ARROW , KEY_LEFT_SHIFT  },
  { KEY_Z          , KEY_X            , KEY_C          , KEY_V                    , KEY_B                    , KEY_N           , KEY_RIGHT_SHIFT },
  { KEY_H          , KEY_J            , KEY_K          , KEY_M                    , KEY_PERIOD               , KEY_DOWN_ARROW  , KEY_FN          },
  { KEY_TAB        , KEY_A            , KEY_S          , KEY_D                    , KEY_F                    , KEY_G           , KEY_LEFT_CTRL   },
  { KEY_1          , KEY_2            , KEY_3          , KEY_4                    , KEY_5                    , KEY_6           , 0               },
  { KEY_U          , KEY_I            , KEY_O          , KEY_P                    , KEY_L                    , KEY_RETURN      , KEY_LEFT_ALT    },
  { KEY_Q          , KEY_W            , KEY_E          , KEY_R                    , KEY_T                    , KEY_Y           , KEY_ESC         },
  { KEY_7          , KEY_8            , KEY_9          , KEY_0                    , KEY_BACKSPACE            , KEY_APOSTROPHE  , 0               }
};

static int keyFnScancode[NROWS][NCOLS] = {
  { 0              , KEY_PRINT_SCREEN , KEY_PAGE_UP    , KEY_MENU                 , KEY_HOME                 , KEY_END         , 0               },
  { 0              , 0                , 0              , 0                        , 0                        , 0               , 0               },
  { KEY_PIPE       , KEY_TICK         , KEY_TILDA      , KEY_BRIGHTNESS_DECREMENT , KEY_BRIGHTNESS_INCREMENT , KEY_PAGE_DOWN   , KEY_FN          },
  { KEY_CAPS_LOCK  , 0                , 0              , 0                        , 0                        , 0               , 0               },
  { KEY_UNDERSCORE , KEY_HASH         , KEY_BACK_SLASH , KEY_AT                   , KEY_ANGLE_L              , KEY_ANGLE_R     , 0               },
  { KEY_KP_SLASH   , KEY_KP_PLUS      , KEY_KP_MINUS   , KEY_EQUAL                , KEY_SEMICOLON            , 0               , KEY_LEFT_GUI    },
  { 0              , 0                , 0              , 0                        , 0                        , KEY_KP_ASTERISK , KEY_POWER       },
  { KEY_SQUARE_L   , KEY_SQUARE_R     , KEY_CURL_L     , KEY_CURL_R               , KEY_DELETE               , KEY_COLON       , 0               }
};
