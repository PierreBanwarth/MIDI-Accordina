#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <stdlib.h>
#include <Arduino.h>
#include "Wire.h"
#include <PCF8575.h>

class Keyboard
{
    private:
        // replace 0 by value of the pin and add 32
        TwoWire*  _wire;
        uint8_t  _address1;
        uint8_t  _address2;
        // declaration of the PCF8575 objects
        PCF8575 PCF1;
        PCF8575 PCF2;
        const uint8_t pinArrayPCF[36] = {
            4, 0, 0, 
            0, 8, 9, 
            10, 11, 12, 
            13, 14, 15, 
            7, 6, 5, 
            0, 3, 2, 
            1, 0, 16, 
            17, 18, 19, 
            20, 21, 22, 
            31, 23, 30, 
            29, 28, 27, 
            26, 25, 24, 
        };
        const uint8_t pinArrayClassicPin[36] = {
            0, 6, 2, 
            0, 0, 0, 
            0, 0, 0, 
            0, 0, 0, 
            0, 0, 0, 
            4, 0, 0, 
            0, 5, 0, 
            0, 0, 0,
            0, 0, 0,
            0, 0, 0,
            0, 0, 0,
            0, 0, 0,
        };

        uint8_t oldStatePousser[36] = {
            0, 0, 0, 
            0, 0, 0, 
            0, 0, 0, 
            0, 0, 0, 
            0, 0, 0, 
            0, 0, 0, 
            0, 0, 0, 
            0, 0, 0,
            0, 0, 0,
            0, 0, 0,
            0, 0, 0,
            0, 0, 0,
        };
        uint8_t oldStateTirer[36] = {
            0, 0, 0, 
            0, 0, 0, 
            0, 0, 0, 
            0, 0, 0, 
            0, 0, 0, 
            0, 0, 0, 
            0, 0, 0, 
            0, 0, 0,
            0, 0, 0,
            0, 0, 0,
            0, 0, 0,
            0, 0, 0,
        };
    public:
        explicit Keyboard(const uint8_t deviceAddress1 = 0x20, const uint8_t deviceAddress2 = 0x22, TwoWire *wire = &Wire);
        void initKeyboard();
        int getButtonState(uint8_t index);
        int accordion(uint8_t index);
};

#endif