
//KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_MINUS
 
#include <Keypad.h>

const byte ROWS = 16; //sixteen rows
const byte COLS = 16; //twelve columns

char keys[ROWS][COLS] = {
  { '1', MODIFIERKEY_GUI, '1', '2', KEY_SYSTEM_SLEEP, '1', KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN},
  { KEY_MINUS, KEY_0, KEY_9, KEY_8, KEY_7, KEY_6, KEY_5, KEY_4,KEY_3, KEY_2, KEY_1, '1'},
  { '1', KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_EQUAL},
  { MODIFIERKEY_CTRL, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_QUOTE},
  { '1', KEY_CAPS_LOCK, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_COMMA, KEY_PERIOD, KEY_SLASH},
  { MODIFIERKEY_SHIFT, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, '1', KEY_SPACE, KEY_ENTER, KEY_BACKSPACE, '1'}
  
};
byte rowPins[ROWS] = {12,14,15,16,17,18,19,20}; //connect to the row pinouts of the keypad    //flipping the pins for rows and cols doesnt work  // adding the shared cols pins to the rows breaks it
byte colPins[COLS] = {1,2,3,4,5,6,7,8,9,10,11,13}; //connect to the column pinouts of the keypad     


// still need to figure out how to only send 1 keypress at a time instead of 5 char for one press

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

unsigned long loopCount;
unsigned long startTime;
String msg;
int x = 0;

void setup() {
    Serial.begin(9600);
    loopCount = 0;
    startTime = millis();
    msg = "";
}


void loop() {
    loopCount++;
    //char key = kpd.getKey();
    if ( (millis()-startTime)>5000 ) {
        Serial.print("Average loops per second = ");
        Serial.println(loopCount/5);
        startTime = millis();
        loopCount = 0;
    }
    
    
    // Fills kpd.key[ ] array with up-to 10 active keys.
    // Returns true if there are ANY active keys.
    if (kpd.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
            {
                switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:
                    msg = " PRESSED.";

                    
                    
                    Serial.print("Key ");
                Serial.print(kpd.key[i].kchar);
                Serial.println(msg);
                // release all the keys at the same instant
                 Keyboard.set_key1(kpd.key[i].kchar);
                Keyboard.send_now();
               
                //Keyboard.set_key1(0);
                //Keyboard.send_now();
                if (kpd.key[i].kchar == char(KEY_LEFT_SHIFT)) {
                  Serial.print("Shift ");
                  Keyboard.set_modifier(MODIFIERKEY_SHIFT);
                  Keyboard.send_now();
                  x=1;
             
        }
        
                break;
                 
                    case HOLD:
                    msg = " HOLD.";
                    //Keyboard.set_modifier(MODIFIERKEY_SHIFT);
                    //Keyboard.send_now();
                    
                    Keyboard.set_key1(kpd.key[i].kchar);
                Keyboard.send_now();
                    
                break;
                    case RELEASED:
                    msg = " RELEASED.";
                    Serial.println(msg);
                    Keyboard.set_key1(0);
                Keyboard.send_now();
                if (kpd.key[i].kchar == char(KEY_LEFT_SHIFT)) {
                  Serial.print("Shift Released ");
                  Keyboard.set_modifier(0);
                  Keyboard.send_now();
                  x=0;
                }
               
                break;
                    case IDLE:
                    msg = " IDLE.";
                    
                }
                
            }
        }
    }
}  // End 
