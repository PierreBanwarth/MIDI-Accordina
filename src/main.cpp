// Created: 2021-03-01 15:00:00

#include "concertina_lib/concertina.h"

#include "concertina_lib/display.hpp"
#include "concertina_lib/display.cpp"

#include "concertina_lib/configuration.h"
#include "concertina_lib/configuration.cpp"
#include "concertina_lib/keyboard.hpp"
#include "concertina_lib/keyboard.cpp"
#include "concertina_lib/musicMath.h"

#include <Audio.h>
#include <Wire.h>
#include <PCF8575.h>
#include <stdlib.h>
#include <Arduino.h>
#include <MIDI.h>
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include "RotaryEncoder.h" // RotaryEncoder v1.5.0 library by Matthais Hertel

// GUItool: begin automatically generated code
AudioSynthSimpleDrum drum2; // xy=399,244
AudioSynthSimpleDrum drum3; // xy=424,310
AudioSynthSimpleDrum drum1; // xy=431,197
AudioSynthSimpleDrum drum4; // xy=464,374
AudioMixer4 mixer1;         // xy=737,265
AudioOutputI2S i2s1;        // xy=979,214
AudioConnection patchCord1(drum2, 0, mixer1, 1);
AudioConnection patchCord2(drum3, 0, mixer1, 2);
AudioConnection patchCord3(drum1, 0, mixer1, 0);
AudioConnection patchCord4(drum4, 0, mixer1, 3);
AudioConnection patchCord5(mixer1, 0, i2s1, 0);
AudioConnection patchCord6(mixer1, 0, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1; // xy=930,518
// GUItool: end automatically generated code

static uint32_t next;

#define PRESSED 0
#define RELEASED 1

    // Info pin 33 seems to be broken

// declaration of the screen object SSD1306AsciiWire oled on second i2c bus (SDA=21, SCL=22)


SSD1306AsciiWire oled; // I2C address 0x3C for 128x64


// declaration of the encoder object RotaryEncoder encoder(2, 3);
RotaryEncoder encoder(14, 15);
uint8_t encoderPosition = 0;
uint8_t buttonEncoder = 8;

// declaration of a display object
// TODO TEST DISPLAY AND KEYBOARD
Display display(&oled, 0x3C, &Wire);
// Keyboard keyboard(0x20, 0x22, &Wire);

uint8_t topPotPin = 0;
uint8_t bottomPotPin = 0;
uint8_t previousTopPotValue = 0;
uint8_t previousBottomPotValue = 0;

// declaration of the PCF8575 objects
PCF8575 PCF1(0x20, &Wire1);
PCF8575 PCF2(0x22, &Wire1);

// declaration of the button states array
uint8_t buttonStates[36];

// adding an old state array to keep in memory the last state of the keyboard
uint8_t oldButtonStates[36];
// add constants for pressed an released buttons

const uint8_t buttonPressed = 0;
const uint8_t buttonReleased = 1;
// declare each value of an 36 buttons array
// values of each pin sorted by rows

const byte pinMenu[6] = {
  0, 1, 2, 
  3, 4, 5, 
};


// replace 0 by value of the pin and add 32
const byte pinArrayPCF[36] = {
  4, 0, 0, 
  0, 8, 9, 
  10, 11, 12, 
  13, 14, 15, 
  7, 6, 5, 
  0, 3, 2, 
  1, 55, 16, 
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

uint8_t indexArrayScan = 0;

void setup(){
  pinMode(buttonEncoder, INPUT);
  digitalWrite(buttonEncoder, HIGH);

  Wire.begin();           // Init I2C
  Wire.setClock(400000L); // Fast mode
//
  oled.begin(&Adafruit128x64, 0x3C);
  oled.clear();
  oled.setFont(Adafruit5x7);
  
  oled.print("bonjour");
  indexArrayScan = 0;
  // initialize screen
  // TODO : TEST DISPLAY AND KEYBOARD
  //display.initDisplay();
  //display.displayMainTitle();

  Serial.begin(115200);
  // audio library init
  AudioMemory(15);

  next = millis() + 1000;

  AudioNoInterrupts();

  drum1.frequency(60);
  drum1.length(1500);
  drum1.secondMix(0.0);
  drum1.pitchMod(0.55);

  drum2.frequency(60);
  drum2.length(300);
  drum2.secondMix(0.0);
  drum2.pitchMod(1.0);

  drum3.frequency(550);
  drum3.length(400);
  drum3.secondMix(1.0);
  drum3.pitchMod(0.5);

  drum4.frequency(1200);
  drum4.length(150);
  drum4.secondMix(0.0);
  drum4.pitchMod(0.0);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  AudioInterrupts();

  // initialize tab values
  for(int i = 0; i < 36; i++){
    buttonStates[i] = 1;
    oldButtonStates[i] = 1;
  }

  // set all pins to input with pull-up
  for (uint8_t pin = 0; pin < 7; pin++)
  {
    pinMode(pin, INPUT_PULLUP);
    digitalWrite(pin, HIGH);
  }

  while (!Serial)
  {
    delay(10);
  }
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
    if (pinArrayPCF[index] == 55)
    {
      return PCF1.readButton(0);
    }
  }
  else{
    return digitalRead(pinArrayClassicPin[index]);
  }
  return 0;

}
int getSouffletState(){
  return digitalRead(SOUFFLET_PIN);
}

int getOldState(uint8_t index){
  return oldButtonStates[index];
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
        // if pin array = 55
        if (pinArrayPCF[i] == 55)
        {
          // pretty display of the button pressed
          Serial.print("PCF1 : 0");
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

void displayMenuButtonStates(){
  for(int i = 0; i < 6; i++){
    if(digitalRead(pinMenu[i]) == 0){
      Serial.print(pinMenu[i]);
      Serial.print(" ");
    }
  }
  Serial.println();
}

void testEncoder(){
  encoder.tick();
  uint8_t newValue = encoder.getPosition();
  uint8_t newPressed = digitalRead(8);

  if(encoderPosition != newValue){
    encoderPosition = newValue;
    Serial.print("Encoder : ");
    Serial.println(encoderPosition);
  }
  // if encoderButtonState is Pressed and was not pressed before
  if(newPressed == PRESSED){
    Serial.println("Encoder Button Pressed");
  }
}
void analogPots()
{
  uint8_t topPotValue = map(analogRead(topPotPin), 0, 1023, 0, 127);
  uint8_t bottomPotValue = map(analogRead(bottomPotPin), 0, 1023, 0, 127); 
  
  if (topPotValue != previousTopPotValue)                                                 // No deadzone on this, as tiny random changes are inconsequential, maybe even desireable?
  {
    previousTopPotValue = topPotValue;
    Serial.print("Top Pot Value: ");
    Serial.print(topPotValue);
  }
  // same for bottom pot
  if (bottomPotValue != previousBottomPotValue)                                                 // No deadzone on this, as tiny random changes are inconsequential, maybe even desireable?
  {
    previousBottomPotValue = bottomPotValue;
    Serial.print("Bottom Pot Value: ");
    Serial.print(bottomPotValue);
  }
}

void testHardware(){
  oled.println("test");
  if(indexArrayScan >= 36){
    indexArrayScan = 0;
  }
  buttonStates[indexArrayScan] = getButtonState(indexArrayScan);
  //// display buttonStates in one line
  displayButtonPressed(buttonStates);
  //displayMenuButtonStates();
  //analogPots();
  indexArrayScan++;
}


void loop()
{
  // TODO : Test keyboard
  // uint8_t noteToPlay = keyboard.accordion(indexArrayScan);
  testHardware();

  if (millis() == next){
    next = millis() + 1000;
    drum2.noteOn();
    Serial.print("Diagnostics: ");
    Serial.print(AudioProcessorUsageMax());
    Serial.print(" ");
    Serial.println(AudioMemoryUsageMax());
    AudioProcessorUsageMaxReset();
  }
}
