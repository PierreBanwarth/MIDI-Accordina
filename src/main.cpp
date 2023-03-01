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


AudioSynthWaveform       waveform1[42]; //xy=968.3332138061523,4748.095205307007
AudioSynthWaveform       waveform2[42]; //xy=970.237922668457,4846.190433502197

AudioEffectEnvelope      envelope[42];
AudioMixer4              mixer[42];

AudioMixer4              mixer1;
AudioMixer4              mixer2;
AudioMixer4              mixer3;
AudioMixer4              mixer4;
AudioMixer4              mixer5;
AudioMixer4              mixer6;
AudioMixer4              mixer7;
AudioMixer4              mixer8;
AudioMixer4              mixer9;
AudioMixer4              mixer10;
AudioMixer4              mixer11;
AudioMixer4              mixer12;
AudioMixer4              mixer13;
AudioMixer4              mixer14;
AudioMixer4              mixer15;

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

AudioConnection          patchCord13(waveform1[6], 0, mixer[6], 0);
AudioConnection          patchCord14(waveform2[6], 0, mixer[6], 1);

AudioConnection          patchCord15(waveform1[7], 0, mixer[7], 0);
AudioConnection          patchCord16(waveform2[7], 0, mixer[7], 1);

AudioConnection          patchCord17(waveform1[8], 0, mixer[8], 0);
AudioConnection          patchCord18(waveform2[8], 0, mixer[8], 1);

AudioConnection          patchCord19(waveform1[9], 0, mixer[9], 0);
AudioConnection          patchCord10(waveform2[9], 0, mixer[9], 1);

AudioConnection          patchCord21(waveform1[10], 0, mixer[10], 0);
AudioConnection          patchCord22(waveform2[10], 0, mixer[10], 1);

AudioConnection          patchCord23(waveform1[11], 0, mixer[11], 0);
AudioConnection          patchCord24(waveform2[11], 0, mixer[11], 1);

AudioConnection          patchCord25(waveform1[12], 0, mixer[12], 0);
AudioConnection          patchCord26(waveform2[12], 0, mixer[12], 1);

AudioConnection          patchCord27(waveform1[13], 0, mixer[13], 0);
AudioConnection          patchCord28(waveform2[13], 0, mixer[13], 1);

AudioConnection          patchCord29(waveform1[14], 0, mixer[14], 0);
AudioConnection          patchCord20(waveform2[14], 0, mixer[14], 1);

AudioConnection          patchCord31(waveform1[15], 0, mixer[15], 0);
AudioConnection          patchCord32(waveform2[15], 0, mixer[15], 1);

AudioConnection          patchCord33(waveform1[16], 0, mixer[16], 0);
AudioConnection          patchCord34(waveform2[16], 0, mixer[16], 1);

AudioConnection          patchCord35(waveform1[17], 0, mixer[17], 0);
AudioConnection          patchCord36(waveform2[17], 0, mixer[17], 1);

AudioConnection          patchCord37(waveform1[18], 0, mixer[18], 0);
AudioConnection          patchCord38(waveform2[18], 0, mixer[18], 1);

AudioConnection          patchCord39(waveform1[19], 0, mixer[19], 0);
AudioConnection          patchCord30(waveform2[19], 0, mixer[19], 1);

AudioConnection          patchCord41(waveform1[20], 0, mixer[20], 0);
AudioConnection          patchCord42(waveform2[20], 0, mixer[20], 1);

AudioConnection          patchCord43(waveform1[21], 0, mixer[21], 0);
AudioConnection          patchCord44(waveform2[21], 0, mixer[21], 1);

AudioConnection          patchCord45(waveform1[22], 0, mixer[22], 0);
AudioConnection          patchCord46(waveform2[22], 0, mixer[22], 1);

AudioConnection          patchCord47(waveform1[23], 0, mixer[23], 0);
AudioConnection          patchCord48(waveform2[23], 0, mixer[23], 1);

AudioConnection          patchCord49(waveform1[24], 0, mixer[24], 0);
AudioConnection          patchCord40(waveform2[24], 0, mixer[24], 1);

AudioConnection          patchCord51(waveform1[25], 0, mixer[25], 0);
AudioConnection          patchCord52(waveform2[25], 0, mixer[25], 1);

AudioConnection          patchCord53(waveform1[26], 0, mixer[26], 0);
AudioConnection          patchCord54(waveform2[26], 0, mixer[26], 1);

AudioConnection          patchCord55(waveform1[27], 0, mixer[27], 0);
AudioConnection          patchCord56(waveform2[27], 0, mixer[27], 1);

AudioConnection          patchCord57(waveform1[28], 0, mixer[28], 0);
AudioConnection          patchCord58(waveform2[28], 0, mixer[28], 1);

AudioConnection          patchCord59(waveform1[29], 0, mixer[29], 0);
AudioConnection          patchCord50(waveform2[29], 0, mixer[29], 1);

AudioConnection          patchCord61(waveform1[30], 0, mixer[30], 0);
AudioConnection          patchCord62(waveform2[30], 0, mixer[30], 1);

AudioConnection          patchCord63(waveform1[31], 0, mixer[31], 0);
AudioConnection          patchCord64(waveform2[31], 0, mixer[31], 1);

AudioConnection          patchCord65(waveform1[32], 0, mixer[32], 0);
AudioConnection          patchCord66(waveform2[32], 0, mixer[32], 1);

AudioConnection          patchCord67(waveform1[33], 0, mixer[33], 0);
AudioConnection          patchCord68(waveform2[33], 0, mixer[33], 1);

AudioConnection          patchCord69(waveform1[34], 0, mixer[34], 0);
AudioConnection          patchCord60(waveform2[34], 0, mixer[34], 1);

AudioConnection          patchCord71(waveform1[35], 0, mixer[35], 0);
AudioConnection          patchCord72(waveform2[35], 0, mixer[35], 1);

AudioConnection          patchCord73(waveform1[36], 0, mixer[36], 0);
AudioConnection          patchCord74(waveform2[36], 0, mixer[36], 1);

AudioConnection          patchCord75(waveform1[37], 0, mixer[37], 0);
AudioConnection          patchCord76(waveform2[37], 0, mixer[37], 1);

AudioConnection          patchCord77(waveform1[38], 0, mixer[38], 0);
AudioConnection          patchCord78(waveform2[38], 0, mixer[38], 1);

AudioConnection          patchCord79(waveform1[39], 0, mixer[39], 0);
AudioConnection          patchCord70(waveform2[39], 0, mixer[39], 1);

AudioConnection          patchCord81(waveform1[40], 0, mixer[40], 0);
AudioConnection          patchCord82(waveform2[40], 0, mixer[40], 1);

AudioConnection          patchCord83(waveform1[41], 0, mixer[41], 0);
AudioConnection          patchCord84(waveform2[41], 0, mixer[41], 1);


AudioConnection          patchCord100(mixer[0], 0, envelope[0], 0);
AudioConnection          patchCord101(mixer[1], 0, envelope[1], 0);
AudioConnection          patchCord102(mixer[2], 0, envelope[2], 0);
AudioConnection          patchCord103(mixer[3], 0, envelope[3], 0);
AudioConnection          patchCord104(mixer[4], 0, envelope[4], 0);
AudioConnection          patchCord105(mixer[5], 0, envelope[5], 0);
AudioConnection          patchCord106(mixer[6], 0, envelope[6], 0);
AudioConnection          patchCord107(mixer[7], 0, envelope[7], 0);
AudioConnection          patchCord108(mixer[8], 0, envelope[8], 0);
AudioConnection          patchCord109(mixer[9], 0, envelope[9], 0);
AudioConnection          patchCord110(mixer[10], 0, envelope[10], 0);
AudioConnection          patchCord111(mixer[11], 0, envelope[11], 0);
AudioConnection          patchCord112(mixer[12], 0, envelope[12], 0);
AudioConnection          patchCord113(mixer[13], 0, envelope[13], 0);
AudioConnection          patchCord114(mixer[14], 0, envelope[14], 0);
AudioConnection          patchCord115(mixer[15], 0, envelope[15], 0);
AudioConnection          patchCord116(mixer[16], 0, envelope[16], 0);
AudioConnection          patchCord117(mixer[17], 0, envelope[17], 0);
AudioConnection          patchCord118(mixer[18], 0, envelope[18], 0);
AudioConnection          patchCord119(mixer[19], 0, envelope[19], 0);
AudioConnection          patchCord120(mixer[20], 0, envelope[20], 0);
AudioConnection          patchCord121(mixer[21], 0, envelope[21], 0);
AudioConnection          patchCord122(mixer[22], 0, envelope[22], 0);
AudioConnection          patchCord123(mixer[23], 0, envelope[23], 0);
AudioConnection          patchCord124(mixer[24], 0, envelope[24], 0);
AudioConnection          patchCord125(mixer[25], 0, envelope[25], 0);
AudioConnection          patchCord126(mixer[26], 0, envelope[26], 0);
AudioConnection          patchCord127(mixer[27], 0, envelope[27], 0);
AudioConnection          patchCord128(mixer[28], 0, envelope[28], 0);
AudioConnection          patchCord129(mixer[29], 0, envelope[29], 0);
AudioConnection          patchCord130(mixer[30], 0, envelope[30], 0);
AudioConnection          patchCord131(mixer[31], 0, envelope[31], 0);
AudioConnection          patchCord132(mixer[32], 0, envelope[32], 0);
AudioConnection          patchCord133(mixer[33], 0, envelope[33], 0);
AudioConnection          patchCord134(mixer[34], 0, envelope[34], 0);
AudioConnection          patchCord135(mixer[35], 0, envelope[35], 0);
AudioConnection          patchCord136(mixer[36], 0, envelope[36], 0);
AudioConnection          patchCord137(mixer[37], 0, envelope[37], 0);
AudioConnection          patchCord138(mixer[38], 0, envelope[38], 0);
AudioConnection          patchCord139(mixer[39], 0, envelope[39], 0);
AudioConnection          patchCord140(mixer[40], 0, envelope[40], 0);
AudioConnection          patchCord141(mixer[41], 0, envelope[41], 0);

AudioConnection          patchCord150(envelope[0], 0, mixer1, 0);
AudioConnection          patchCord151(envelope[1], 0, mixer1, 1);
AudioConnection          patchCord152(envelope[2], 0, mixer1, 2);
AudioConnection          patchCord153(envelope[3], 0, mixer1, 3);

AudioConnection          patchCord154(envelope[4], 0, mixer2, 0);
AudioConnection          patchCord155(envelope[5], 0, mixer2, 1);
AudioConnection          patchCord156(envelope[6], 0, mixer2, 2);
AudioConnection          patchCord157(envelope[7], 0, mixer2, 3);

AudioConnection          patchCord158(envelope[8], 0, mixer3, 0);
AudioConnection          patchCord159(envelope[9], 0, mixer3, 1);
AudioConnection          patchCord160(envelope[10], 0, mixer3, 2);
AudioConnection          patchCord161(envelope[11], 0, mixer3, 3);

AudioConnection          patchCord162(envelope[12], 0, mixer4, 0);
AudioConnection          patchCord163(envelope[13], 0, mixer4, 1);
AudioConnection          patchCord164(envelope[14], 0, mixer4, 2);
AudioConnection          patchCord165(envelope[15], 0, mixer4, 3);

AudioConnection          patchCord166(envelope[16], 0, mixer5, 0);
AudioConnection          patchCord167(envelope[17], 0, mixer5, 1);
AudioConnection          patchCord168(envelope[18], 0, mixer5, 2);
AudioConnection          patchCord169(envelope[19], 0, mixer5, 3);

AudioConnection          patchCord170(envelope[20], 0, mixer6, 0);
AudioConnection          patchCord171(envelope[21], 0, mixer6, 1);
AudioConnection          patchCord172(envelope[22], 0, mixer6, 2);
AudioConnection          patchCord173(envelope[23], 0, mixer6, 3);

AudioConnection          patchCord174(envelope[24], 0, mixer7, 0);
AudioConnection          patchCord175(envelope[25], 0, mixer7, 1);
AudioConnection          patchCord176(envelope[26], 0, mixer7, 2);
AudioConnection          patchCord177(envelope[27], 0, mixer7, 3);

AudioConnection          patchCord178(envelope[28], 0, mixer8, 0);
AudioConnection          patchCord179(envelope[29], 0, mixer8, 1);
AudioConnection          patchCord180(envelope[30], 0, mixer8, 2);
AudioConnection          patchCord181(envelope[31], 0, mixer8, 3);

AudioConnection          patchCord182(envelope[32], 0, mixer9, 0);
AudioConnection          patchCord183(envelope[33], 0, mixer9, 1);
AudioConnection          patchCord184(envelope[34], 0, mixer9, 2);
AudioConnection          patchCord185(envelope[35], 0, mixer9, 3);

AudioConnection          patchCord186(envelope[36], 0, mixer10, 0);
AudioConnection          patchCord187(envelope[37], 0, mixer10, 1);
AudioConnection          patchCord188(envelope[38], 0, mixer10, 2);
AudioConnection          patchCord189(envelope[39], 0, mixer10, 3);

AudioConnection          patchCord190(envelope[40], 0, mixer11, 0);
AudioConnection          patchCord191(envelope[41], 0, mixer11, 1);



AudioConnection          patchCord200(mixer1, 0, mixer12, 0);
AudioConnection          patchCord201(mixer2, 0, mixer12, 1);
AudioConnection          patchCord202(mixer3, 0, mixer12, 2);
AudioConnection          patchCord203(mixer4, 0, mixer12, 3);

AudioConnection          patchCord204(mixer5, 0, mixer13, 0);
AudioConnection          patchCord205(mixer6, 0, mixer13, 1);
AudioConnection          patchCord206(mixer7, 0, mixer13, 2);
AudioConnection          patchCord207(mixer8, 0, mixer13, 3);

AudioConnection          patchCord208(mixer9, 0, mixer14, 0);
AudioConnection          patchCord209(mixer10, 0, mixer14, 1);
AudioConnection          patchCord210(mixer11, 0, mixer14, 2);

AudioConnection          patchCord211(mixer12, 0, mixer15, 0);
AudioConnection          patchCord212(mixer13, 0, mixer15, 1);
AudioConnection          patchCord213(mixer14, 0, mixer15, 2);

AudioAmplifier amp1; // xy=623.25,378.25

AudioConnection patchCord300(mixer15, amp1);
AudioConnection patchCord301(amp1, 0, i2s1, 0);

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
RotaryEncoder encoder(14, 15);

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

const byte pinBourdon[6] = {
  39, 34, 35, 
  36, 37, 38, 
};
const byte noteBourdon[6] = {
  2,4,5,
  7,9,11,
};
byte bourdonActif[6] = {
  0,0,0,
  0,0,0,
};

byte oldStateBourdon[6] = {
  0,0,0,0,0,0,
};

// replace 0 by value of the pin and add 32
const byte pinArrayPCF[36] = {
  4, 0, 0, 
  0, 8, 9, 
  10, 11, 0, 
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
  0, 6, 5, 
  0, 0, 0, 
  0, 0, 33, 
  0, 0, 0, 
  0, 0, 0, 
  4, 0, 0, 
  0, 0, 0, 
  0, 0, 0,
  0, 0, 0,
  0, 0, 0,
  0, 0, 0,
  0, 0, 0,
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
  delay(3000);
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
  amp1.gain(0.5);
  sgtl5000_1.enable();
  encoder.tick();
  uint8_t newValue = encoder.getPosition();
  menu.initDisplay(newValue);
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
  return menu.updateState(newValue, newPressed, encoder);
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

// AudioSynthWaveform waveform1[42]; // xy=968.3332138061523,4748.095205307007
// AudioSynthWaveform waveform2[42]; // xy=970.237922668457,4846.190433502197

// AudioEffectEnvelope envelope[42];
void synthNoteOn(byte synthChannel, byte pitch, byte velocity)
{
  waveform1[synthChannel].amplitude(0.5);
  waveform2[synthChannel].amplitude(0.5);
  waveform1[synthChannel].frequency(midiPitchFrequencyMap[pitch]);
  waveform2[synthChannel].frequency(midiPitchFrequencyMap[pitch - 12]);
  envelope[synthChannel].noteOn();
}

void synthNoteOff(byte synthChannel, byte pitch, byte velocity)
{
  envelope[synthChannel].noteOff();
}

void noteOff(int note, int index){
  synthNoteOff(index, note + 36, 127);
  
}
void noteOn(int note, int index){
  // printKey(index);
  synthNoteOn(index, note + 36, 127);
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
        noteOn(noteSynthPousser,index);
        oldStatePousser[index] = BUTTON_PRESSED;
        if (oldStateTirer[index] == BUTTON_PRESSED)
        {
          noteOff(noteSynthTirer, index);
          oldStateTirer[index] = BUTTON_RELEASED;
        }
      }
    }
    else
    { // on tire sur le soufflet et on appuie sur le bouton
      if (oldStateTirer[index] == BUTTON_RELEASED)
      {

        noteOn(noteSynthTirer, index);
        oldStateTirer[index] = BUTTON_PRESSED;
        if (oldStatePousser[index] == BUTTON_PRESSED)
        {
          noteOff(noteSynthPousser, index);
          oldStatePousser[index] = BUTTON_RELEASED;
        }
      }
    }
  }
  else
  {
    if (oldStatePousser[index] == BUTTON_PRESSED)
    {
      noteOff(noteSynthPousser, index);
      oldStatePousser[index] = BUTTON_RELEASED;
    }
    if (oldStateTirer[index] == BUTTON_PRESSED)
    {
      // on appuie pas sur le bouton ma
      noteOff(noteSynthTirer, index);
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
        noteOff(note, index + 36);
        bourdonActif[index] = 0;
      }
      else
      {
        noteOn(note, index + 36);
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
int state = 0;
void loop()
{
  if(state >= 36){
    state = 0;
  }
  sens_soufflet = digitalRead(SOUFFLET_PIN);
  // https://forum.pjrc.com/search.php?searchid=7853170
  buttonStates[state] = getButtonState(state);

  accordion(sens_soufflet, state);
  state++;

  for(int i=0; i<6;i++){
    noteSynthBourdon(i);
  }
  configuration = menuManagement();
}