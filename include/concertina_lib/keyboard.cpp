#include "Wire.h" // Wire library (Included with Arduino IDE)

#include "keyboard.hpp"
#include "concertina_lib/concertina.h"
#include <PCF8575.h>

#define SOUFFLET_PIN 1

Keyboard::Keyboard(const uint8_t deviceAddress1 = 0x20, const uint8_t deviceAddress2 = 0x22, TwoWire *wire = &Wire) {
  _address1 = deviceAddress1;
  _address2 = deviceAddress2;
  _wire = &Wire;
}

//create function init keyboard that initialize to PCF
void Keyboard::initKeyboard(){
    PCF8575 PCF1(_address1, &Wire);
    PCF8575 PCF2(_address2, &Wire);
    
    if (!PCF1.begin())
    {
        Serial.println("could not initialize...");
    }
    if (!PCF1.isConnected())
    {
        Serial.println("=> not connected");
    }
    else
    {
        Serial.println("=> connected!!");
    }
    if (!PCF2.begin())
    {
        Serial.println("could not initialize...");
    }
    if (!PCF2.isConnected())
    {
        Serial.println("=> not connected");
    }
    else
    {
        Serial.println("=> connected!!");
    }
    PCF1.setButtonMask(0xFFFF);
    PCF2.setButtonMask(0xFFFF);

}

// Function to get a button state value
// need to dispatch between pcf and physical pin
// use pinArrayPCF
// use pinArrayClassicPin
// return the value for the pin
int Keyboard::getButtonState(uint8_t index){
  // if value is 0 in PCF array then classic reading
  if(pinArrayPCF[index] != 0){    
    if(pinArrayPCF[index] < 16){
      return PCF1.readButton(pinArrayPCF[index]);
    }
    else if(pinArrayPCF[index] < 32){
      return PCF2.readButton(pinArrayPCF[index]-16);
    }
  }
  else{
    return digitalRead(pinArrayClassicPin[index]);
  }
}


int Keyboard::accordion(uint8_t index){
  uint8_t buttonState = getButtonState(index);
  // same algo that noteSynth
  if (buttonState == BUTTON_PRESSED)
  {
    // if soufflet is low
    uint8_t sens_soufflet = digitalRead(SOUFFLET_PIN);
    // same bloc in a if that integrate soufflet
    if( sens_soufflet == BUTTON_PRESSED){
      // On pousse sur le soufflet
      // si oldStateTirer = Pressed set it to released
      if (oldStateTirer[index] == BUTTON_PRESSED){
        oldStateTirer[index] = BUTTON_RELEASED;
      }
      if (oldStatePousser[index] == BUTTON_RELEASED){
        oldStatePousser[index] = BUTTON_PRESSED;
        return pousser[index];
      }
    }
    else{
      // si oldstatePousser = pressed set it to released  
      if (oldStatePousser[index] == BUTTON_PRESSED){
        oldStatePousser[index] = BUTTON_RELEASED;
      }
      // On tire sur le soufflet
      if (oldStateTirer[index] == BUTTON_RELEASED){
        oldStateTirer[index] = BUTTON_PRESSED;
        return tirer[index];
      }
      
    }
  }
  else
  {
    if (oldStatePousser[index] == BUTTON_PRESSED)
    {
      oldStatePousser[index] = BUTTON_RELEASED;
      return 0;
    }
    // same thing for oldStateTirer
    if (oldStateTirer[index] == BUTTON_PRESSED)
    {
      oldStateTirer[index] = BUTTON_RELEASED;
      return 0;
    }
  }
}

