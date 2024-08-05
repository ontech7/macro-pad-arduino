# Macro Pad - Arduino
The macros can be configured directly on the macro pad, so there's no need to modify and re-flash the code on the Arduino every time you want to change a macro.

## Summary
1) [Hardware used](#hardware-used)
2) [How it works](#how-it-works)
3) [Guide](#guide)
4) [Images](#images)
5) [3D Printed Cover](#3d-printed-cover)
6) [Credits](#credits)

## Hardware used
1x **Arduino Pro Micro clone** (ATmega32u4) - KeeYees PRO Micro  
1x **OLED 0.96" 128x64**  
4x **6x6x6 buttons**  
4x **10k Ohm resistors**  
Cables, tin, matrix board  

## How it works
You can set up all macros directly via Arduino using the script available in this repository. Boards based on the ATmega32u4 allow keyboard/mouse emulation, enabling you to emulate multiple key presses using the four buttons after configuring the macros.

## Guide

- In the menu, button 1 is "Up", button 2 is "Down", button 3 is "Confirm/Enter", and button 4 is "Cancel/Back".
- To configure a button:
  - Select "Set macros".
  - Choose one of the buttons to configure.
- Select up to three keys for that macro from "Modifiers", "Alphabet", and/or "Numbers".
- To reset a configured button:
  - Select "Reset macros".
  - Choose the button to reset.
- To activate the macros:
  - Select "START".
- To return to the menu after starting the macro listener, simultaneously press button 1 (Up), button 2 (Down), and button 4 (Cancel/Back).

Feel free to add support for EEPROM to save macros even after powering off and to include Mouse modifiers.

## Images
![Macro Pad - 3D Printed cover](https://i.imgur.com/5l0VHF7.jpeg)

![Macro Pad - Front](https://i.imgur.com/JXZ0cWf.jpg)  

![Macro Pad - Rear](https://i.imgur.com/xK9TXbX.jpg)  

![Macro Pad - Macro setup](https://i.imgur.com/TpPFj7B.jpg)  

## 3D Printed Cover

You can find the **STLs**, **.blend** and **.3mf** projects on [this link](https://drive.google.com/drive/folders/1iDR6E4x4kF29GcKFQsr7bH7N1tLRjrTk?usp=sharing)

## Credits
[Andrea Losavio](https://www.linkedin.com/in/andrea-losavio-a60246107/)  

Feel free to reach out with any questions or suggestions!  
