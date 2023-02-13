// Created: 2021-03-01 15:00:00

#include "concertina_lib/concertina.h"

#include <Wire.h>
#include <PCF8575.h>
#include <stdlib.h>
#include <Arduino.h>
#include <MIDI.h>
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include "RotaryEncoder.h" // RotaryEncoder v1.5.0 library by Matthais Hertel


/* Example for 8 input buttons that are connected from the GPIO expander pins to ground.
 * Note the buttons must be connected with the other side of the switch to GROUND. There is
 * a built in pull-up 'resistor' on each input, but no pull-down resistor capability.
 */
// Info pin 33 seems to be broken

// todo add midi
// todo add sounds
// todo add encoder
// todo add display
// try everything

// declaration of the screen object SSD1306AsciiWire oled on second i2c bus (SDA=21, SCL=22) 
SSD1306AsciiWire oled; // I2C address 0x3C for 128x64


// declaration of the encoder object RotaryEncoder encoder(2, 3);
RotaryEncoder encoder(2, 3);



// declaration of the PCF8575 objects


PCF8575 PCF1(0x20, &Wire);
PCF8575 PCF2(0x22, &Wire);
// declaration of the button states array
uint8_t buttonStates[36];
// adding an old state array to keep in memory the last state of the keyboard
uint8_t oldButtonStates[36];
// add constants for pressed an released buttons
const uint8_t buttonPressed = 0;
const uint8_t buttonReleased = 1;
// declare each value of an 36 buttons array
// values of each pin sorted by rows
const byte pousser[36] = {
  F2, G2, An2, 
  Bb3, B3, Fs3, 
  Eb3, D3, An3, 
  G3, F4, C4, 
  Bb4, An4, E4, 
  0, B4, Gs4, 
  0, Gs4, C4, 
  Cs4, B4, Fs4, 
  Eb4, D4, An4, 
  G4, F4, C4, 
  Bb4, An4, E4, 
  D4, B4, F4, 
};

const byte tirer[36] = {
  E2, C2, B2, 
  An2, G2, D2, 
  Cs2, C2, G2,
  An2, E2, B3, 
  Gs3, G3, D3,
  0, Bb3, Fs3,
  0, Fs3, D3,
  Eb3, C4, G4,
  Cs4, E4, B4, 
  Gs4, G4, D4,
  Cs4, C4, G4,
  An4, E4, Bb4,
};
// replace 0 by value of the pin and add 32
const byte pinArrayPCF[36] = {
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

const byte pinArrayClassicPin[36] = {
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
int indexArrayScan = 0;

void setup(){
  indexArrayScan = 0;
  // initialize screen 
  oled.begin(&Adafruit128x64, 0x3C);
  oled.setFont(Adafruit5x7);
  oled.clear();
  oled.set1X();
  oled.println("Hello World!");
  oled.println("I'm a 128x64");
  oled.println("OLED display!");

  // initialize tab values
  for(int i = 0; i < 36; i++){
    buttonStates[i] = 1;
    oldButtonStates[i] = 1;
  }

  // set all pins to input with pull-up
  for (uint8_t pin = 0; pin < 7; pin++)
  {
    pinMode(pin, INPUT_PULLUP);
  }

  while (!Serial)
  {
    delay(10);
  }
  Serial.begin(115200);
  Serial.print("PCF8575_LIB_VERSION:\t");
  Serial.println(PCF8575_LIB_VERSION);

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
// function of menuing with the encoder
// Five menu items
int getButtonState(uint8_t index){
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


// a function that get from PCF1 and PCF2 return an array of the buttons states
void getButtonStates(uint8_t buttonStates[36]){
  for (uint8_t p = 0; p < 16; p++)
  {
    buttonStates[p] = PCF1.readButton(p);
  }
  for (uint8_t p = 0; p < 16; p++)
  {
    buttonStates[p+16] = PCF2.readButton(p);
  }
  for(int i= 0;i<7;i++){
    buttonStates[i+32] = digitalRead(i);
  }
}


// display in line of all array of button states not pressed yet
// keep in memory the last state of the keyboard and display only the new pressed buttons
void displayButtonPressed(uint8_t buttonStates[36]){
  for(int i = 0; i < 36; i++){
    if(buttonStates[i] == 0){
      if(pinArrayPCF[i] != 0){    
        if(pinArrayPCF[i] < 16){
          // pretty display of the button pressed
          Serial.print("PCF1 : ");
          Serial.print(pinArrayPCF[i]);
         
        }
        else if(pinArrayPCF[i] < 32){
          Serial.print("PCF2 : ");
          Serial.print(pinArrayPCF[i]);
        }
          }
      else{
        Serial.print("Other : ");
        Serial.print(pinArrayClassicPin[i]);
      }
    }
    
  }
  Serial.println();
}



void loop()
{
  if(indexArrayScan >= 36){
    indexArrayScan = 0;
  }
  buttonStates[indexArrayScan] = getButtonState(indexArrayScan);
  // display buttonStates in one line
  displayButtonPressed(buttonStates);
  indexArrayScan++;

}