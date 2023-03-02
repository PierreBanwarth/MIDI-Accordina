// Created: 2021-03-01 15:00:00

#include "concertina_lib/concertina.h"

#include "concertina_lib/configuration.hpp"
#include "concertina_lib/keyboard.hpp"
#include "concertina_lib/display.hpp"
#include "concertina_lib/menu.hpp"
#include "concertina_lib/menu.cpp"

#include "concertina_lib/musicMath.h"

#include <PCF8575.h>
#include <stdlib.h>
#include <Arduino.h>
#include <MIDI.h>
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include "RotaryEncoder.h" // RotaryEncoder v1.5.0 library by Matthais Hertel
#include <math.h> //<cmath> in case of c++

#include <Audio.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: end automatically generated code


AudioSynthWaveform       waveform1[6]; //xy=968.3332138061523,4748.095205307007
AudioSynthWaveform       waveform2[6]; //xy=970.237922668457,4846.190433502197

AudioEffectEnvelope      envelope[6];
AudioMixer4              mixer[6];

AudioMixer4              mixer1;
AudioMixer4              mixer2;
AudioMixer4              mixer3;
AudioOutputI2S           i2s1;

AudioConnection          patchCord1(waveform1[0], 0, mixer[0], 0);
AudioConnection          patchCord2(waveform2[0], 0, mixer[0], 1);

AudioConnection          patchCord3(waveform1[1], 0, mixer[1], 0);
AudioConnection          patchCord4(waveform2[1], 0, mixer[1], 1);

AudioConnection          patchCord5(waveform1[2], 0, mixer[2], 0);
AudioConnection          patchCord6(waveform2[2], 0, mixer[2], 1);

AudioConnection          patchCord7(waveform1[3], 0, mixer[3], 0);
AudioConnection          patchCord8(waveform2[3], 0, mixer[3], 1);

AudioConnection          patchCord9(waveform1[4], 0, mixer[4], 0);
AudioConnection          patchCord0(waveform2[4], 0, mixer[4], 1);

AudioConnection          patchCord11(waveform1[5], 0, mixer[5], 0);
AudioConnection          patchCord12(waveform2[5], 0, mixer[5], 1);


AudioConnection          patchCord100(mixer[0], 0, envelope[0], 0);
AudioConnection          patchCord101(mixer[1], 0, envelope[1], 0);
AudioConnection          patchCord102(mixer[2], 0, envelope[2], 0);
AudioConnection          patchCord103(mixer[3], 0, envelope[3], 0);
AudioConnection          patchCord104(mixer[4], 0, envelope[4], 0);
AudioConnection          patchCord105(mixer[5], 0, envelope[5], 0);


AudioConnection          patchCord150(envelope[0], 0, mixer1, 0);
AudioConnection          patchCord151(envelope[1], 0, mixer1, 1);
AudioConnection          patchCord152(envelope[2], 0, mixer1, 2);
AudioConnection          patchCord153(envelope[3], 0, mixer1, 3);

AudioConnection          patchCord154(envelope[4], 0, mixer2, 0);
AudioConnection          patchCord155(envelope[5], 0, mixer2, 1);


AudioConnection          patchCord190(mixer1, 0, mixer3, 0);
AudioConnection          patchCord191(mixer2, 0, mixer3, 1);


AudioAmplifier amp1; // xy=623.25,378.25

// AudioConnection patchCord300(mixer3, bitcrusher1);

AudioConnection patchCord301(mixer3, amp1);
AudioConnection patchCord303(amp1, 0, i2s1, 0);

AudioControlSGTL5000     sgtl5000_1;

// // GUItool: end automatically generated code

int waveform_type = WAVEFORM_SAWTOOTH;
int mixer1_setting = 0;
int mixer2_setting = 0;
elapsedMillis timeout = 0;
bool mixer2_envelope = false;

#define SOUFFLET_PIN 1
#define PRESSED 0
#define RELEASED 1

// declaration of the screen object SSD1306AsciiWire oled on first i2c bus (SDA=21, SCL=22)
SSD1306AsciiWire oled; // I2C address 0x3C for 128x64
// declaration of the PCF8575 objects
PCF8575 PCF1(0x20, &Wire);
PCF8575 PCF2(0x22, &Wire);

// declaration of the encoder object RotaryEncoder encoder(2, 3);
RotaryEncoder encoder(15, 14, RotaryEncoder::LatchMode::TWO03);

uint8_t encoderPosition = 0;
uint8_t buttonEncoder = 8;

Configuration configuration;

// declaration of a display object
// TODO TEST DISPLAY AND KEYBOARD
// Display display(&oled, 0x3C, &Wire);
// Keyboard keyboard(0x20, 0x22, &Wire); 
uint8_t topPotPin = 26;
uint8_t bottomPotPin = 27;
uint8_t previousTopPotValue = 0;
uint8_t previousBottomPotValue = 0;

// declaration of the PCF8575 objects


// declaration of the button states array
uint8_t buttonStates[36];

// add constants for pressed an released buttons

const uint8_t buttonPressed = 0;
const uint8_t buttonReleased = 1;
// declare each value of an 36 buttons array
// values of each pin sorted by rows
byte noteFree[6] = {
  0, 0, 0, 
  0, 0, 0, 
};

byte bourdonActif[6] = {
  0,0,0,
  0,0,0,
};

byte oldStateBourdon[6] = {
  0,0,0,0,0,0,
};

uint8_t noteIsOn[36];
uint8_t indexArrayScan = 0;
Display display = Display(&oled, 0x3C, &Wire);
Menu menu = Menu(display);

void setup(){
  // Serial.begin(115200);

  // initialize tab values
  for(int i = 0; i < 36; i++){
    buttonStates[i] = 1;
  }
  
  // set all pins to input with pull-up
  pinMode(buttonEncoder, INPUT);
  digitalWrite(buttonEncoder, HIGH);

  // init pinmod for the keyboard
  for (uint8_t pin = 0; pin < 7; pin++)
  {
    pinMode(pin, INPUT_PULLUP);
    digitalWrite(pin, HIGH);
  }
  for (uint8_t pin = 0; pin < 36; pin++)
  {
    if(pinArrayPCF[pin]==0){
      pinMode(pinArrayClassicPin[pin], INPUT_PULLUP);
      digitalWrite(pinArrayClassicPin[pin], HIGH);
    }
  }

  // init pinmod for the pots
  pinMode(topPotPin, INPUT);
  pinMode(bottomPotPin, INPUT);

  // Init I2C connections 
  Wire.begin();
  oled.begin(&Adafruit128x64, 0x3C);
  oled.clear();
  oled.setFont(Adafruit5x7);

  display.displayMainTitle();

  int error;
  int found = 0;
  //I2C Address scanner
  for (int address = 1; address < 127; address++)
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    { 
      oled.print("Found : ");
      oled.println(address);
      if(address !=60){
        if (found == 0)
        {
          PCF1.setAddress(address);
          found++;
        }
        else if (found == 1)
        {
          PCF2.setAddress(address);
        }
      }
      
    }
  }
  delay(2000);
  // Checking if the PCF8575 are connected
  if (!PCF1.begin())
  {
    oled.println("could not initialize...");
  }
  if (!PCF1.isConnected())
  {
    oled.println("=> not connected");
  }
  else
  {
    oled.println("=> connected!!");
  }
  if (!PCF2.begin())
  {
    oled.println("could not initialize...");
  }
  if (!PCF2.isConnected())
  {
    oled.println("=> not connected");
  }
  else
  {
    oled.println("=> connected!!");
  }
  // set the button mask to 0xFFFF to read all buttons
  delay(1000);
  PCF1.setButtonMask(0xFFFF);
  PCF2.setButtonMask(0xFFFF);

  AudioMemory(80);
  // freeverb1.roomsize(0.1);
  amp1.gain(0.5);
  sgtl5000_1.enable();

  encoder.tick();
  uint8_t newValue = encoder.getPosition();
  menu.initDisplay(newValue);
  for(int i=0; i<6; i++){
    waveform1[i].amplitude(0.2);
    waveform2[i].amplitude(0.2);
  }
}

// function of menuing with the encoder
// Five menu items
int getButtonState(uint8_t index){
  // if value is 0 in PCF array then classic reading
  int returnValue = 1;
  if(pinArrayPCF[index] != 0){
    if(pinArrayPCF[index] < 16){
      returnValue = PCF1.readButton(pinArrayPCF[index]);
    }
    else if(pinArrayPCF[index] < 32){
      returnValue = PCF2.readButton(pinArrayPCF[index] - 16);
    }
    if (pinArrayPCF[index] == 55)
    {
      returnValue = PCF1.readButton(0);
    }
  }
  else{
    returnValue = digitalRead(pinArrayClassicPin[index]);
  }
  return returnValue;

}




Configuration menuManagement(){
  encoder.tick();
  uint8_t newValue = encoder.getPosition();
  uint8_t newPressed = digitalRead(buttonEncoder);
  return menu.updateState(newValue, newPressed, &encoder);
}

void analogPots()
{
  //uint8_t topPotValue = map(analogRead(topPotPin), 0, 1023, 0, 127);
  //uint8_t bottomPotValue = map(analogRead(bottomPotPin), 0, 1023, 0, 127); 
  uint8_t topPotValue = analogRead(topPotPin);
  uint8_t bottomPotValue = analogRead(bottomPotPin);
  
  if (topPotValue != previousTopPotValue) // No deadzone on this, as tiny random changes are inconsequential, maybe even desireable?
  {
    previousTopPotValue = topPotValue;
    Serial.print("Top Pot Value: ");
    Serial.println(topPotValue);
  }
  // same for bottom pot
  if (bottomPotValue != previousBottomPotValue)// No deadzone on this, as tiny random changes are inconsequential, maybe even desireable?
  {
    previousBottomPotValue = bottomPotValue;
    Serial.print("Bottom Pot Value: ");
    Serial.println(bottomPotValue);
  }
}

void printKey(int index)
{
  oled.clear();
  oled.print("Index");
  if (index >= 36)
  {
    oled.print("Drone : ");
    oled.println(index);
  }
  else
  {
    oled.print("Key : ");
    oled.println(index);
    // print all data in integer array that are larger than 36ole

    if (pinArrayPCF[index] == 0)
    {
      oled.print("Teensy : ");
      oled.println(pinArrayClassicPin[index]);
    }
    else if (pinArrayPCF[index] == 55)
    {
      oled.print("PCF1 : ");
      oled.println(pinArrayPCF[index]);
    }
    else if (pinArrayPCF[index] < 16)
    {
      oled.print("PCF1 : ");
      oled.println(pinArrayPCF[index]);
    }
    else
    {
      oled.print("PCF2 : ");
      oled.println(pinArrayPCF[index]-16);
    }
    oled.print("Pousser : ");
    oled.println(pousser[index]%12);

    oled.print("Tirer : ");
    oled.println(tirer[index] % 12);
  }

}

float noteToFreq(int note) {
  return midiPitchFrequencyMap[note];
}

// Mapping function for floats
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void synthNoteOn(byte note, byte isDrone)
{
  if (isDrone == 1)
    {

      waveform1[5].frequency(midiPitchFrequencyMap[(note+configuration.shiftHalfTone) + 12*(configuration.octaveBourdon1+configuration.octave)]);
      waveform2[5].frequency(midiPitchFrequencyMap[(note+configuration.shiftHalfTone) + 12*(configuration.octaveBourdon2+configuration.octave)]);
      envelope[5].noteOn();
      noteFree[5] = note;
    }else{
      for(int i =0; i<5; i++){
        if(noteFree[i] == 0){

          waveform1[i].frequency(midiPitchFrequencyMap[(note+configuration.shiftHalfTone) + 12*(configuration.octaveOsc1+configuration.octave)]);
          waveform2[i].frequency(midiPitchFrequencyMap[(note+configuration.shiftHalfTone) + 12*(configuration.octaveOsc2+configuration.octave)]);
          envelope[i].noteOn();
          noteFree[i] = note;
          break;
        }
      }
  }

  

}

void synthNoteOff(byte note, byte isDrone)
{
  if(isDrone == 1){
    envelope[5].noteOff();
    noteFree[5] = 0;
  }
  for(int i =0; i<5; i++){
    if(noteFree[i] == note){
      envelope[i].noteOff();
      noteFree[i] = 0;
      break;
    }
  }
}

static void accordion(uint8_t sens_soufflet, uint8_t index){
   //, uint8_t oldStatePousser, uint8_t oldStateTirer
  uint8_t bouton = buttonStates[index];

  int noteSynthPousser = pousser[index];
  int noteSynthTirer = tirer[index];
  // higher velocity usually makes MIDI instruments louder
  if (bouton == BUTTON_PRESSED)
  {
    if (sens_soufflet == BUTTON_PRESSED)
    {
      // on pousse sur le bouton et sur le soufflet
      if (oldStatePousser[index] == BUTTON_RELEASED)
      {
        synthNoteOn(noteSynthPousser, 0);
        oldStatePousser[index] = BUTTON_PRESSED;
        if (oldStateTirer[index] == BUTTON_PRESSED)
        {
          synthNoteOff(noteSynthTirer, 0);
          oldStateTirer[index] = BUTTON_RELEASED;
        }
      }
    }
    else
    { // on tire sur le soufflet et on appuie sur le bouton
      if (oldStateTirer[index] == BUTTON_RELEASED)
      {

        synthNoteOn(noteSynthTirer, index);
        oldStateTirer[index] = BUTTON_PRESSED;
        if (oldStatePousser[index] == BUTTON_PRESSED)
        {
          synthNoteOff(noteSynthPousser, index);
          oldStatePousser[index] = BUTTON_RELEASED;
        }
      }
    }
  }
  else
  {
    if (oldStatePousser[index] == BUTTON_PRESSED)
    {
      synthNoteOff(noteSynthPousser, 0);
      oldStatePousser[index] = BUTTON_RELEASED;
    }
    if (oldStateTirer[index] == BUTTON_PRESSED)
    {
      // on appuie pas sur le bouton ma
      synthNoteOff(noteSynthTirer, 0);
      oldStateTirer[index] = BUTTON_RELEASED;
    }
  }
}

static void noteSynthBourdon(uint8_t index)
{
  digitalWrite(pinBourdon[index], HIGH);
  uint8_t bouton = digitalRead(pinBourdon[index]);
  uint8_t note = noteBourdon[index];
  if (bouton == LOW)
  {
    if(oldStateBourdon[index] == BUTTON_RELEASED){
      oldStateBourdon[index] = BUTTON_PRESSED;

      if (bourdonActif[index] == 1)
      {
        synthNoteOff(note, 1);
        bourdonActif[index] = 0;
      }
      else
      {
        synthNoteOn(note, 1);
        bourdonActif[index] = 1;
      }
    }
  }
  else
  {
    oldStateBourdon[index] = BUTTON_RELEASED;
  }
}

void testButtons(){
  int test = 0;
  for (int i = 0; i < 16; i++)
  {
    test = PCF1.read(i);
    if (test == 0)
    {
      Serial.print("PCF1 ");
      Serial.print(i);
      Serial.print(" ");
      Serial.print(" pin ");
      Serial.print(pinArrayPCF[i]);
      Serial.print(" ");
    }
  }

  for (int i = 0; i < 16; i++)
  {
    test = PCF2.read(i);
    if (test == 0)
    {
      Serial.print("PCF2 ");
      Serial.print(i);
      Serial.print(" ");
      Serial.print(" pin ");
      Serial.print(pinArrayPCF[i + 16]);
      Serial.print(" ");
    }
  }
  for (int i = 0; i < 36; i++)
  {
    test = 1;
    if (pinArrayPCF[i] == 0)
    {
      test = digitalRead(pinArrayClassicPin[i]);
    }
    if (test == 0)
    {
      Serial.print("Teensy ");
      Serial.print(i);
      Serial.print(" pin ");
      Serial.print(pinArrayClassicPin[i]);
      Serial.print(" ");
    }
  }

  Serial.println("");
}

int sens_soufflet =1;

Configuration newConfiguration = Configuration();

void deltaConfig(Configuration conf1, Configuration conf2){
  if(conf1.activeOsc1 != conf2.activeOsc1){
    for(int i=0; i<5; i++){
      // SINE
      if(conf2.activeOsc1 == 0){
        waveform1[i].begin(WAVEFORM_SINE);
      }
      if(conf2.activeOsc1 == 1){
        waveform1[i].begin(WAVEFORM_SAWTOOTH);
      }
      if(conf2.activeOsc1 == 2){
        waveform1[i].begin(WAVEFORM_SQUARE);
      }
      if(conf2.activeOsc1 == 3){
        waveform1[i].begin(WAVEFORM_TRIANGLE);
      }
      if(conf2.activeOsc1 == 4){
        waveform1[i].begin(WAVEFORM_PULSE);
      }
    }
  }
  if(conf1.activeOsc2 != conf2.activeOsc2){
    for(int i=0; i<5; i++){
      // SINE
      if(conf2.activeOsc1 == 0){
        waveform2[i].begin(WAVEFORM_SINE);
      }
      if(conf2.activeOsc1 == 1){
        waveform2[i].begin(WAVEFORM_SAWTOOTH);
      }
      if(conf2.activeOsc1 == 2){
        waveform2[i].begin(WAVEFORM_SQUARE);
      }
      if(conf2.activeOsc1 == 3){
        waveform2[i].begin(WAVEFORM_TRIANGLE);
      }
      if(conf2.activeOsc1 == 4){
        waveform2[i].begin(WAVEFORM_PULSE);
      }
    }
  }
  if(conf1.activeBrd1 != conf2.activeBrd1){
    if(conf2.activeOsc1 == 0){
      waveform1[5].begin(WAVEFORM_SINE);
    }
    if(conf2.activeOsc1 == 1){
      waveform1[5].begin(WAVEFORM_SAWTOOTH);
    }
    if(conf2.activeOsc1 == 2){
      waveform1[5].begin(WAVEFORM_SQUARE);
    }
    if(conf2.activeOsc1 == 3){
      waveform1[5].begin(WAVEFORM_TRIANGLE);
    }
    if(conf2.activeOsc1 == 4){
      waveform1[5].begin(WAVEFORM_PULSE);
    }
  }
  if(conf1.activeBrd2 != conf2.activeBrd2){
    if(conf2.activeOsc1 == 0){
      waveform2[5].begin(WAVEFORM_SINE);
    }
    if(conf2.activeOsc1 == 1){
      waveform2[5].begin(WAVEFORM_SAWTOOTH);
    }
    if(conf2.activeOsc1 == 2){
      waveform2[5].begin(WAVEFORM_SQUARE);
    }
    if(conf2.activeOsc1 == 3){
      waveform2[5].begin(WAVEFORM_TRIANGLE);
    }
    if(conf2.activeOsc1 == 4){
      waveform2[5].begin(WAVEFORM_PULSE);
    }
  }
}
void loop()
{

  sens_soufflet = digitalRead(SOUFFLET_PIN);

  for(int i = 0; i<36; i++){
    buttonStates[i] = getButtonState(i);

    accordion(sens_soufflet, i);
  }
  for(int i=0; i<6;i++){
    noteSynthBourdon(i);
  }
  newConfiguration = menuManagement();
  deltaConfig(configuration, newConfiguration);
  configuration = newConfiguration;

}