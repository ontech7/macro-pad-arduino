#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keyboard.h>
#include <EEPROM.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// On an arduino LEONARDO:   2(SDA),  3(SCL)
#define OLED_RESET     4
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

uint8_t macroModifiers[27] = {KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_SHIFT, 0xE0 /* ENTER */, KEY_LEFT_ALT, KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, KEY_RIGHT_ARROW, KEY_BACKSPACE, KEY_TAB, KEY_ESC, KEY_INSERT, KEY_DELETE, KEY_PAGE_UP, KEY_PAGE_DOWN, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12};
String macroModifiersNames[27] = {"Ctrl", "Cmd", "Shift", "Enter", "Alt", "Up", "Down", "Left", "Right", "Bksp", "Tab", "Esc", "Ins", "Del", "PgUp", "PgDw", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12"};
uint8_t macroAlphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
uint8_t macroNumbers[10] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

const uint8_t buttonPin0 = 7;
const uint8_t buttonPin1 = 6;
const uint8_t buttonPin2 = 5;
const uint8_t buttonPin3 = 4;

uint8_t btn_prev0;
uint8_t btn_prev1;
uint8_t btn_prev2;
uint8_t btn_prev3;

int btn_selected = 0;
uint8_t macros[3][4] = {{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0}};
uint8_t macroNamesIndex[3][4] = {{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0}};
uint8_t numMacros[4] = {0, 0, 0, 0};
uint8_t macroType[3][4] = {{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0}};

int selected_option = 0;
int max_options = 0;
int page = 0;

int last_submenu_levels[5] = {0,0,0,0,0};
int current_menu_level = 0;
int current_submenu_level = 0;
int current_macro_num = 0;

bool macroStarted = false;
bool set = false;
bool reset = false;

void setup() {
  Serial.begin(19200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  pinMode(buttonPin0, INPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);

  btn_prev0 = digitalRead(buttonPin0);
  btn_prev1 = digitalRead(buttonPin1);
  btn_prev2 = digitalRead(buttonPin2);
  btn_prev3 = digitalRead(buttonPin3);

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  /*EEPROM.get(0, macros[0][0]);
  EEPROM.get(8, macros[0][1]);
  EEPROM.get(16, macros[0][2]);
  EEPROM.get(24, macros[0][3]);
  EEPROM.get(32, macroNamesIndex[0][0]);
  EEPROM.get(40, macroNamesIndex[0][1]);
  EEPROM.get(48, macroNamesIndex[0][2]);
  EEPROM.get(56, macroNamesIndex[0][3]);*/

  setMenuLevel();
}

void loop() {
  // read the state of the pushbutton value:
  uint8_t btn0 = digitalRead(buttonPin0);
  uint8_t btn1 = digitalRead(buttonPin1);
  uint8_t btn2 = digitalRead(buttonPin2);
  uint8_t btn3 = digitalRead(buttonPin3);

  if (!macroStarted) {
    if (btn3 == LOW && btn_prev3 == HIGH) {
      goBack();
      setMenuLevel();
    }
  
    if (btn2 == LOW && btn_prev2 == HIGH) {
      if (!set && !reset) {
        goAhead();
      } else if (set) {
        if (current_macro_num < numMacros[btn_selected]) {
          if (macroType[current_macro_num][btn_selected] == 0) {
            macros[current_macro_num][btn_selected] = macroModifiers[selected_option];
          } else if (macroType[current_macro_num][btn_selected] == 1) {
            macros[current_macro_num][btn_selected] = macroAlphabet[selected_option];
          } else if (macroType[current_macro_num][btn_selected] == 2) {
            macros[current_macro_num][btn_selected] = macroNumbers[selected_option];
          }
          macroNamesIndex[current_macro_num][btn_selected] = selected_option;
          //EEPROM.put(btn_selected*8, macroModifiers[selected_option]);
          //EEPROM.put(btn_selected*8+32, selected_option);
          current_macro_num++;
          goBack();
        }
        
        if (current_macro_num == numMacros[btn_selected]) {
          current_macro_num = 0;
          goBack();
          goBack();
        }
      } else if (reset) {
        macros[0][btn_selected] = 0;
        macros[1][btn_selected] = 0;
        macros[2][btn_selected] = 0;
        macroNamesIndex[0][btn_selected] = 0;
        macroNamesIndex[1][btn_selected] = 0;
        macroNamesIndex[2][btn_selected] = 0;
        macroType[0][btn_selected] = 0;
        macroType[1][btn_selected] = 0;
        macroType[2][btn_selected] = 0;
        numMacros[btn_selected] = 0;
        //EEPROM.put(btn_selected*8, macroModifiers[selected_option]);
        //EEPROM.put(btn_selected*8+32, selected_option);
        goBack();
      }
      setMenuLevel();
    }
  
    if (btn1 == LOW && btn_prev1 == HIGH) {
      selected_option++;
      setMenuLevel();
    }
  
    if (btn0 == LOW && btn_prev0 == HIGH) {
      selected_option--;
      setMenuLevel();
    }
  } else {
    if (btn0 != btn_prev0) {
      if (btn0 == HIGH) {
        for (int i = 0; i < numMacros[btn_selected]; i++) {
          Keyboard.press(macros[i][0]);
        }
      } else {
        for (int i = 0; i < numMacros[btn_selected]; i++) {
          Keyboard.release(macros[i][0]);
        }
      }
    }

    if (btn1 != btn_prev1) {
      if (btn1 == HIGH) {
        for (int i = 0; i < numMacros[btn_selected]; i++) {
          Keyboard.press(macros[i][1]);
        }
      } else {
        for (int i = 0; i < numMacros[btn_selected]; i++) {
          Keyboard.release(macros[i][1]);
        }
      }
    }

    if (btn2 != btn_prev2) {
      if (btn2 == HIGH) {
        for (int i = 0; i < numMacros[btn_selected]; i++) {
          Keyboard.press(macros[i][2]);
        }
      } else {
        for (int i = 0; i < numMacros[btn_selected]; i++) {
          Keyboard.release(macros[i][2]);
        }
      }
    }

    if (btn3 != btn_prev3) {
      if (btn3 == HIGH) {
        for (int i = 0; i < numMacros[btn_selected]; i++) {
          Keyboard.press(macros[i][3]);
        }
      } else {
        for (int i = 0; i < numMacros[btn_selected]; i++) {
          Keyboard.release(macros[i][3]);
        }
      }
    }
  }

  if (!macroStarted) {
    btn_prev0 = digitalRead(buttonPin0);
    btn_prev1 = digitalRead(buttonPin1);
    btn_prev2 = digitalRead(buttonPin2);
    btn_prev3 = digitalRead(buttonPin3);
  } else {
    btn_prev0 = btn0;
    btn_prev1 = btn1;
    btn_prev2 = btn2;
    btn_prev3 = btn3;
  }

  delay(80);
}

void setMenuLevel() {
  display.clearDisplay();

  set = false;
  reset = false;
  macroStarted = false;
  
  if (current_menu_level == 0 && current_submenu_level == 0) {
    max_options = 2;
    page = 0;
    display.setCursor(10,0);
    display.print("START");
    display.setCursor(10,10);
    display.print("Set macros");
    display.setCursor(10,20);
    display.print("Reset macros");
    setOptionCursor();
  } else if (current_menu_level == 1 && current_submenu_level == 0) {
    macroStarted = true;
    max_options = 0;
    page = 0;
    display.setCursor(15,0);
    display.print("=== STARTED ===");
    display.setCursor(0,20);
    display.print("B1:");
    for (int i = 0; i < numMacros[0]; i++) {
      if (macroType[i][0] == 0) {
        display.print(macroModifiersNames[macroNamesIndex[i][0]]);
      } else if (macroType[i][0] == 1) {
        display.print(char(macroAlphabet[macroNamesIndex[i][0]]));
      } else if (macroType[i][0] == 2) {
        display.print(char(macroNumbers[macroNamesIndex[i][0]]));
      }
      if(i < numMacros[0] - 1) {
        display.print("+");
      }
    }
    display.setCursor(0,30);
    display.print("B2:");
    for (int i = 0; i < numMacros[1]; i++) {
      if (macroType[i][1] == 0) {
        display.print(macroModifiersNames[macroNamesIndex[i][1]]);
      } else if (macroType[i][1] == 1) {
        display.print(char(macroAlphabet[macroNamesIndex[i][1]]));
      } else if (macroType[i][1] == 2) {
        display.print(char(macroNumbers[macroNamesIndex[i][1]]));
      }
      if(i < numMacros[1] - 1) {
        display.print("+");
      }
    }
    display.setCursor(0,40);
    display.print("B3:");
    for (int i = 0; i < numMacros[2]; i++) {
      if (macroType[i][2] == 0) {
        display.print(macroModifiersNames[macroNamesIndex[i][2]]);
      } else if (macroType[i][2] == 1) {
        display.print(char(macroAlphabet[macroNamesIndex[i][2]]));
      } else if (macroType[i][2] == 2) {
        display.print(char(macroNumbers[macroNamesIndex[i][2]]));
      }
      if(i < numMacros[2] - 1) {
        display.print("+");
      }
    }
    display.setCursor(0,50);
    display.print("B4:");
    for (int i = 0; i < numMacros[3]; i++) {
      if (macroType[i][3] == 0) {
        display.print(macroModifiersNames[macroNamesIndex[i][3]]);
      } else if (macroType[i][3] == 1) {
        display.print(char(macroAlphabet[macroNamesIndex[i][3]]));
      } else if (macroType[i][3] == 2) {
        display.print(char(macroNumbers[macroNamesIndex[i][3]]));
      }
      if(i < numMacros[3] - 1) {
        display.print("+");
      }
    }
    display.display();
  } else if (current_menu_level == 1 && current_submenu_level == 1) {
    max_options = 3;
    btn_selected = selected_option;
    page = 0;
    display.setCursor(10,0);
    display.print("Button 1");
    display.setCursor(10,10);
    display.print("Button 2");
    display.setCursor(10,20);
    display.print("Button 3");
    display.setCursor(10,30);
    display.print("Button 4");
    setOptionCursor();
  } else if (current_menu_level == 1 && current_submenu_level == 2) {
    max_options = 3;
    page = 0;
    reset = true;
    display.setCursor(10,0);
    display.print("Button 1");
    display.setCursor(10,10);
    display.print("Button 2");
    display.setCursor(10,20);
    display.print("Button 3");
    display.setCursor(10,30);
    display.print("Button 4");
    setOptionCursor();
  } else if (current_menu_level == 2) {
    max_options = 2;
    numMacros[btn_selected] = selected_option + 1;
    page = 0;
    display.setCursor(60,0);
    display.print("N. Macro");
    display.setCursor(10,0);
    display.print("1");
    display.setCursor(10,10);
    display.print("2");
    display.setCursor(10,20);
    display.print("3");
    setOptionCursor();
  } else if (current_menu_level == 3) {
    max_options = 2;
    macroType[current_macro_num][btn_selected] = selected_option;
    page = 0;
    display.setCursor(80,0);
    display.print("Type");
    display.setCursor(10,0);
    display.print("Modifiers");
    display.setCursor(10,10);
    display.print("Alphabet");
    display.setCursor(10,20);
    display.print("Numbers");
    setOptionCursor();
  } else if (current_menu_level == 4) {
    if (macroType[current_macro_num][btn_selected] == 0) {
      max_options = 26;
    } else if (macroType[current_macro_num][btn_selected] == 1) {
      max_options = 25;
    } else if (macroType[current_macro_num][btn_selected] == 2) {
      max_options = 9;
    }
    set = true;
    setOptionCursor();
    for (int i = 6*page; i <= max_options; i++) {
      display.setCursor(10, 10*i - 60*page);
      if (macroType[current_macro_num][btn_selected] == 0) {
        display.print(macroModifiersNames[i]);
      } else if (macroType[current_macro_num][btn_selected] == 1) {
        display.print(char(macroAlphabet[i]));
      } else if (macroType[current_macro_num][btn_selected] == 2) {
        display.print(char(macroNumbers[i]));
      }
    }
    display.display();
  } 
}

void setOptionCursor() {
  if (selected_option < 0) {
    selected_option = max_options;
  } else if (selected_option > max_options) {
    selected_option = 0;
  }
  page = selected_option/6;
  display.setCursor(0, 10*selected_option - 60*page);
  display.print(">");
  display.display();
}

void goAhead() {
  current_menu_level++;
  last_submenu_levels[current_menu_level] = selected_option;
  current_submenu_level = selected_option;
  selected_option = 0;
}

void goBack() {
  current_menu_level--;

  if (current_menu_level < 0) {
    current_menu_level = 0;
    current_submenu_level = 0;
    selected_option = 0;
  } else {
    current_submenu_level = last_submenu_levels[current_menu_level];
    selected_option = last_submenu_levels[current_menu_level+1];
  }
}
