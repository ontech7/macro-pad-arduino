# Macro Pad - Arduino
Macro pad configurable directly via Arduino  

# Hardware used
1x Arduino Pro Micro clone (ATmega32u4) - KeeYees PRO Micro  
1x OLED 0.96" 128x64  
4x 6x6x6 buttons  
4x 10k Ohm resistors  
Cables, tin, matrix board  

# How it works
It's possible to setup all the macros directly via Arduino, using the script available in the repo.  

ATmega32u4-based boards allow to emulate keyboard/mouse, so after setupping the macros, you can emulate multiple keys using the 4 buttons.  

In the menu, when you click "Set macros", you can select one of the button to configure.  
After that, it's possible to select from 1 to 3 keys for that macro. You can choose among "Modifiers", "Alphabet" and/or "Numbers".  

When you click "Reset macros", you can reset one of the button already configured.

In the end, when you click "START", they macro attached to the buttons will activate.

Feel free to add support for EEPROM, to save macros even after turning off and turning on, and to add Mouse modifiers as well.

# Images
![Macro Pad - Front](https://i.imgur.com/JXZ0cWf.jpg)  

![Macro Pad - Rear](https://i.imgur.com/xK9TXbX.jpg)  

![Macro Pad - Macro setup](https://i.imgur.com/TpPFj7B.jpg)  

# Credits
$ [Andrea Losavio](https://www.linkedin.com/in/andrea-losavio-a60246107/)
