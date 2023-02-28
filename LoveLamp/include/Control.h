#include <Arduino.h>
#include <Storage.h>

#define INPUT_BUTTON_PIN 10
#define LONG_PRESS_TIME 3000

void(* resetFunc) (void) = 0;

namespace Control{
    int curr_state;
    int last_state  = LOW;
    unsigned long pressedTime  = 0;
    unsigned long releasedTime = 0;


    void setup(){
        Serial.begin(9600);
        pinMode(INPUT_BUTTON_PIN, INPUT_PULLUP);
    }

    void reset(){

    }

    void detect_button(){
        curr_state = digitalRead(INPUT_BUTTON_PIN);

        if(last_state == LOW && curr_state == HIGH){
            pressedTime = millis();
        }
        else if(curr_state == LOW && last_state == HIGH){
            releasedTime = millis();
        }

        if(releasedTime - pressedTime > LONG_PRESS_TIME){
            Storage::deleteCredentials();
            resetFunc();
        }

        last_state = curr_state;
    }
}