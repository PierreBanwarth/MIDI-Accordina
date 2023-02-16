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
#include <math.h> //<cmath> in case of c++

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code

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

AudioConnection          patchCord214(mixer15, 0, i2s1, 0);
AudioConnection          patchCord215(mixer15, 0, i2s1, 1);

AudioControlSGTL5000     sgtl5000_1;   

// GUItool: end automatically generated code


int waveform_type = WAVEFORM_SAWTOOTH;
int mixer1_setting = 0;
int mixer2_setting = 0;
elapsedMillis timeout = 0;
bool mixer2_envelope = false;



#define SOUFFLET_PIN 1
#define PRESSED 0
#define RELEASED 1

// Info pin 33 seems to be broken
// declaration of the screen object SSD1306AsciiWire oled on second i2c bus (SDA=21, SCL=22)


SSD1306AsciiWire oled; // I2C address 0x3C for 128x64
// declaration of the PCF8575 objects
PCF8575 PCF1(0x20, &Wire1);
PCF8575 PCF2(0x22, &Wire1);

// declaration of the encoder object RotaryEncoder encoder(2, 3);
RotaryEncoder encoder(14, 15);

uint8_t encoderPosition = 0;
uint8_t buttonEncoder = 8;

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

const byte pinMenu[6] = {
  39, 34, 35, 
  36, 37, 38, 
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
  5, 6, 2, 
  3, 0, 0, 
  0, 0, 0, 
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

uint8_t indexArrayScan = 0;

void setup(){
  Serial.begin(115200);

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
  // init pinmod for the menu keyboard
  for (uint8_t pin = 0; pin < 6; pin++)
  {
    pinMode(pinMenu[pin], INPUT_PULLUP);
    digitalWrite(pinMenu[pin], HIGH);
  }
  // init pinmod for the pots
  pinMode(topPotPin, INPUT);
  pinMode(bottomPotPin, INPUT);

  // Init I2C connections 
  Wire.begin();           // Init I2C for the screen
  Wire1.begin();           // Init I2C for PCF8575 (keyboard)

  // screen settings init
  Wire.setClock(400000L); // Fast mode
  oled.begin(&Adafruit128x64, 0x3C);
  oled.clear();
  oled.setFont(Adafruit5x7);

  oled.println("Accordina MIDI");
  int error;
  int found = 0;
  // I2C Address scanner
  for (int address = 1; address < 127; address++)
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire1.beginTransmission(address);
    error = Wire1.endTransmission();
    if (error == 0)
    {
      if(found == 0){
        PCF1.setAddress(address);
        found++;
      }else if(found == 1){
        PCF2.setAddress(address);
      }
    }
  }
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
  PCF1.setButtonMask(0xFFFF);
  PCF2.setButtonMask(0xFFFF);

    // audio library init
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.05);

 
  // for i in envelope 

  for(int i=0; i<42; i++){

    waveform1[i].begin(WAVEFORM_SINE);
    waveform1[i].amplitude(0.75);
    waveform1[i].frequency(50);
    waveform1[i].pulseWidth(0.60);

    waveform2[i].begin(WAVEFORM_TRIANGLE);
    waveform2[i].amplitude(0.75);
    waveform2[i].frequency(50);
    waveform2[i].pulseWidth(0.60);
    mixer[i].gain(0, 0.15);
    mixer[i].gain(1, 0.15);
    mixer[i].gain(2, 0.15);
    mixer[i].gain(3, 0.15);
    envelope[i].attack(10);
    envelope[i].hold(10);
    envelope[i].decay(25);
    envelope[i].sustain(0.4);
    envelope[i].release(70);
  }
  oled.clear();
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
void displaySouffletState(){
  if(digitalRead(SOUFFLET_PIN) == 0){
    Serial.println("Soufflet Pressed");
  }
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


float noteToFreq(int note) {
  return midiPitchFrequencyMap[note];
}


void noteOnSynth(int note){
  oled.print("Note : ");
  oled.println(note);
  oled.clear();
}
void noteOff(int note, int index, Configuration conf){
 
  envelope[index].noteOff();
}
void noteOn(int note, int index, Configuration conf){
  oled.clear();
  oled.print(index);
  oled.print(" ");

  waveform1[index].frequency(noteToFreq(note+36));
  waveform2[index].frequency(noteToFreq(note+24));
  envelope[index].noteOn();
}


static void noteMidi(uint8_t sens_soufflet, uint8_t index, Configuration conf, int velocity){
   //, uint8_t oldStatePousser, uint8_t oldStateTirer
  uint8_t bouton = getButtonState(index);

  int noteSynthPousser = pousser[index];
  int noteSynthTirer = tirer[index];


  {
    // higher velocity usually makes MIDI instruments louder
    if (bouton == BUTTON_PRESSED)
    {
      if (sens_soufflet == BUTTON_PRESSED)
      {
        // on pousse sur le bouton et sur le soufflet
        if (oldStatePousser[index] == BUTTON_RELEASED)
        {
          noteOn(noteSynthPousser,index, conf);
          oldStatePousser[index] = BUTTON_PRESSED;
          if (oldStateTirer[index] == BUTTON_PRESSED)
          {
            noteOff(noteSynthTirer, index, conf);
            oldStateTirer[index] = BUTTON_RELEASED;
          }
        }
      }
      else
      { // on tire sur le soufflet et on appuie sur le bouton
        if (oldStateTirer[index] == BUTTON_RELEASED)
        {

          noteOn(noteSynthTirer, index, conf);
          oldStateTirer[index] = BUTTON_PRESSED;
          if (oldStatePousser[index] == BUTTON_PRESSED)
          {
            noteOff(noteSynthPousser, index, conf);
            oldStatePousser[index] = BUTTON_RELEASED;
          }
        }
      }
    }
    else
    {
      if (oldStatePousser[index] == BUTTON_PRESSED)
      {
        noteOff(noteSynthPousser, index, conf);
        oldStatePousser[index] = BUTTON_RELEASED;
      }
      if (oldStateTirer[index] == BUTTON_PRESSED)
      {
        // on appuie pas sur le bouton ma
        noteOff(noteSynthTirer, index, conf);
        oldStateTirer[index] = BUTTON_RELEASED;
      }
    }
  }

}



// intégration de la fonction de lecture des boutons
//static int noteSynth(uint8_t sens_soufflet, uint8_t index){
//
//  uint8_t bouton = getButtonState(index);
//
//  int noteSynthPousser = pousser[index];
//  int noteSynthTirer = tirer[index];
//
//  noteSynthPousser = index;
//  noteSynthTirer = index;
//
//  if (pousser[index] != 0 || tirer[index] != 0)
//  {
//    if (bouton == BUTTON_PRESSED)
//    {
//      if (sens_soufflet == BUTTON_PRESSED)
//      {
//        // on pousse sur le bouton et sur le soufflet
//        if (oldStatePousser[index] == BUTTON_RELEASED)
//        {
//          // play note
//          oldStatePousser[index] = BUTTON_PRESSED;
//          if (oldStateTirer[index] == BUTTON_PRESSED)
//          {
//            oldStateTirer[index] = BUTTON_RELEASED;
//          }
//        }
//        noteOnSynth(noteSynthPousser);
//      }
//      else
//      { // on tire sur le soufflet et on appuie sur le bouton
//        if (oldStateTirer[index] == BUTTON_RELEASED)
//        {
//          oldStateTirer[index] = BUTTON_PRESSED;
//          if (oldStatePousser[index] == BUTTON_PRESSED)
//          {
//            oldStatePousser[index] = BUTTON_RELEASED;
//          }
//        }
//        noteOnSynth(noteSynthTirer);
//      }
//      return 1;
//    }
//    else
//    {
//      if (oldStatePousser[index] == BUTTON_PRESSED)
//      {
//        oldStatePousser[index] = BUTTON_RELEASED;
//      }
//      if (oldStateTirer[index] == BUTTON_PRESSED)
//      {
//        oldStateTirer[index] = BUTTON_RELEASED;
//      }
//      return 0;
//    }
//  }
//  return 0;
//}


void testHardware(Configuration conf){
  if(indexArrayScan >= 36){
    indexArrayScan = 0;
  }
  if(indexArrayScan != 31){
    // noteSynth(digitalRead(SOUFFLET_PIN), indexArrayScan);
    noteMidi(digitalRead(SOUFFLET_PIN), indexArrayScan, conf, 127);
  }
  indexArrayScan++;
}

Configuration conf = Configuration("Squ Tri",2,11);

void loop()
{

  // TODO : Test keyboard
  // uint8_t noteToPlay = keyboard.accordion(indexArrayScan);
  
  //getButtonStates(buttonStates);
  //displayButtonPressed(buttonStates);
  testHardware(conf);
  //testHardware();
  //displaySouffletState();
  //displayMenuButtonStates();
  //drum1.noteOn();
  AudioProcessorUsageMaxReset();
}