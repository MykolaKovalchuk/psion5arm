# psion5arm
Psion Series 5 upgrade with ARM-based SBC

![Modified Psion 5](/Images/PXL_20250928_071642151.jpg)

Used components:
- Non-working Psion Series 5 for parts;
- New Single Board Computer : Khadas Edge2;
- Screen: Khadas TS050 - 5" full HD (1920x1080) touchscreen;
- Khadas Edge2 IO board - for internal USB for keyboard, SD card reader, and amplifier with speakers contacts;
- Cirque GlidePoint Circle Trackpad, 23mm version - small trackpad;
- Raspberry Pi Pico - keyboard and trackpad controller;
- Small power bank with 12V 2A power delivery - tested with two different 5,000mAh 22.5W power banks (output 5V3A, 9V2.22A, 12V1.67A, 10V2.25A, 22.5W Max), works at least without heavy load;

Folder [KeyboardWithMouse](/KeyboardWithMouse/) contains:
- Firmware for Raspberry Pico Pi to control Psion keyboard and Cirque trackpad;
- KiCad files for PCB to connect Raspberry Pi with keyboard and trackpad via 22-pin and 12-pin flat cables.
Code files for keyboard and trackpad (identified as mouse) contain links to original code, libraries, and guaide, which I have used to prepare my version of this controller.

Internal components (during testing):
![Internal Components](/Images/PXL_20250809_113856536.jpg)

Components placement:
![Assembly 1](/Images/assembly1.jpg)
All components connected with lots of FPC flat cables and FPC extension boards (22pin for keyboard, 12pin for trackpad, 40pin for display+touchpad, 2 x 30pin for IO board).
Except Raspberry Pi connected to Khadas IO board via 4 wire USB interface (V, D+, D-, G).

Actual assembly:
![Assembly 2](/Images/PXL_20250928_035612955.jpg)

3D models for new panels: https://www.printables.com/@MykolaKovalc_3575424/collections/2704362
