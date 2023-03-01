#ifndef __MENU_H__
#define __MENU_H__

#include <stdlib.h>
#include <Arduino.h>
#include "concertina_lib/concertina.h"
#include "concertina_lib/configuration.hpp"
#include "concertina_lib/configuration.cpp"
#include "concertina_lib/display.hpp"
#include "concertina_lib/display.cpp"
#include "SSD1306AsciiWire.h"
#include "RotaryEncoder.h"
class Menu
{
    private:
        // replace 0 by value of the pin and add 32
        int currentState = MAIN;
        int encoderValue = 0;
        int oldButtonState = HIGH;
        int currentMode = MODE_SYNTH;
        int modeMidi = DRUM;
        Display display;
        Configuration configuration = Configuration("main", 1,0,1,2,3,4,0,0,0,0,0,0);
    public:
        explicit Menu(Display d);
        Configuration updateState(uint8_t newEncoderValue, uint8_t buttonPressed,RotaryEncoder encoder);
        void initDisplay(uint8_t initEncoderPosition);
        void displayState();
};  

#endif