# Macro Pad - Arduino
Macro pad configurable directly via Arduino  

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
It's possible to setup all the macros directly via Arduino, using the script available in the repo.  
ATmega32u4-based boards allow to emulate keyboard/mouse, so after setupping the macros, you can emulate multiple keys using the 4 buttons.  

## Guide

- In the menu, button 1 is "**Up**", button 2 is "**Down**", button 3 is "**Confirm/Enter**" and button 4 is "**Cancel/Back**".
- Selected "**Set macros**", you can select one of the button to configure.  
After that, it's possible to select from 1 to 3 keys for that macro. You can choose among "**Modifiers**", "**Alphabet**" and/or "**Numbers**".  
- Selected "**Reset macros**", you can reset one of the button already configured.  
- Selected "**START**", the macro attached to the buttons will activate.
- To **go back** after you started the macro listener, you can click simultaneously button 1 (**Up**), button 2 (**Down**) and button 4 (**Cancel/Back**).

Feel free to add support for EEPROM, to save macros even after turning off and turning on, and to add Mouse modifiers as well.

## Images
![Macro Pad - 3D Printed cover](https://i.imgur.com/5l0VHF7.jpeg)

![Macro Pad - Front](https://i.imgur.com/JXZ0cWf.jpg)  

![Macro Pad - Rear](https://i.imgur.com/xK9TXbX.jpg)  

![Macro Pad - Macro setup](https://i.imgur.com/TpPFj7B.jpg)  

## 3D Printed Cover

You can find the **STLs**, **.blend** and **.3mf** projects on [this link](https://drive.google.com/drive/folders/1iDR6E4x4kF29GcKFQsr7bH7N1tLRjrTk?usp=sharing)

## Credits
$ [Andrea Losavio](https://www.linkedin.com/in/andrea-losavio-a60246107/)
