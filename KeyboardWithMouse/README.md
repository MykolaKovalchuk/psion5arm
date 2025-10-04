# Combined driver for Psions Series 5 keyboard and Cirque trackpad

Firmware with combined driver for Psions Series 5 keyboard (connected with 22-pin FPC cable) and Cirque trackpad (connected with 12-pin FPC cable) for Raspberry Pico.

Code is written to use with Arduino IDE.
It needs Raspberry Pi Pico Arduino core from earlephilhower: https://github.com/earlephilhower/arduino-pico/ (using guide https://randomnerdtutorials.com/programming-raspberry-pi-pico-w-arduino-ide/).

Keyboard code based on original RasmusB code https://github.com/RasmusB/USB-Keyboard-Adapter and guide https://hackaday.io/project/4042-psio

Cirque Trackpad code is derived on library and examples from https://github.com/2bndy5/CirquePinnacle

Folder [PicoKMDriver](./PicoKMDriver/) contains firmware code.

Folder [PCB](./PCB/) contains KiCad scheme and pcb for a board to connect 22-pin FPC and 12-pin FPC to a Raspberry Pico and work with above firmware code.
![PCB preview](/Images/board_v1.jpg)
