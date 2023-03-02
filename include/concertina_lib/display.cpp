#include <SSD1306Ascii.h>
#include "Wire.h" // Wire library (Included with Arduino IDE)

#include "display.hpp"
#include "concertina_lib/concertina.h"
#include "concertina_lib/configuration.hpp"

Display::Display() {
  _address = 0x3c;
  _wire = &Wire;
}
Display::Display(SSD1306AsciiWire *oled, const uint8_t deviceAddress, TwoWire *wire) {
  _address = deviceAddress;
  _wire = &Wire;
  _oled = oled;
 
}
void Display::initDisplay(){
  _oled->begin(&Adafruit128x64, _address);
  _oled->setFont(Adafruit5x7);
  _wire->begin();           // Init I2C
  _wire->setClock(400000L); // Fast mode
}
void Display::displayShift(uint8_t  i){
  _oled->print(keyNames[i]);
}

void Display::clear(){
  _oled->clear();
}

void Display::testOff(uint8_t  i){
  _oled->clear();
  _oled->print("Off : ");
  _oled->print(i);
  _oled->println("");
}

void Display::testOn(uint8_t  i){
  _oled->clear();
  _oled->print("On : ");
  _oled->print(i);
  _oled->println("");
}
void Display::printIndex(uint8_t  i){
  _oled->println(i);
}

void Display::displayOsc(uint8_t i){
  _oled->print(waveFormNames[i]);
}

void Display::displayMainTitle(){
  _oled->println("Accordina MIDI");
  _oled->println("V 3.0.1.2");
}
void Display::displayAttack(Configuration conf){
 _oled->print("VOsc: ");
 _oled->print(conf.attackTheme);
 _oled->print(" VBrd: ");
 _oled->println(conf.attackBourdon);
}

void Display::printOscWave(Configuration conf){
 displayOsc(conf.activeOsc1);
 _oled->print(" ");
 displayOsc(conf.activeOsc2);
 _oled->print(" ");
 displayOsc(conf.activeBrd1);
 _oled->print(" ");
 displayOsc(conf.activeBrd2);
 _oled->println("");
}
void Display::printOscOct(Configuration conf){
 _oled->print("Oct: ");
 _oled->print(conf.octaveOsc1);
 _oled->print("   ");
 _oled->print(conf.octaveOsc2);
 _oled->print("   ");
 _oled->print(conf.octaveBourdon1);
 _oled->print("  ");
 _oled->print(conf.octaveBourdon2);
 _oled->println("");
}
void Display::displayOctave(Configuration conf, uint8_t newPos){
  _oled->print("Octave : ");
//   _oled->println(conf.getOctave());
  _oled->print("Oct : ");
  _oled->println((newPos)%6);
  _oled->print(" ");
}
void Display::displayHalfTone(Configuration conf, uint8_t  newPos){
  _oled->print("Actual ");
//   displayShift(conf.getShiftHalfTone());
  _oled->println("");
  _oled->print("New : ");
  displayShift(newPos);
  _oled->print(" ");
}
void Display::displayAttackSwitch(uint8_t attack, uint8_t newPos){
  _oled->print("Volume Main : ");
  _oled->println(attack);
  _oled->println(" ");
  _oled->print("Volume : ");
  _oled->print((attack+(5*newPos))%255);
  _oled->print(" ");
}
void Display::displayPresetsMenu(uint8_t newPos){
  for(int i=0; i<6; i++){
    _oled->print(" ");
    String name = newPresets[i].getName();
    _oled->println(name);
  }
  _oled->println("  Back");
  _oled->setCursor(0, (newPos%8));
  _oled->print(">");
}

void Display::displayMainMenu(uint8_t mode, uint8_t newPos){
  displayMainTitle();
  _oled->print("  Mode : ");
  if(mode == MODE_MIDI){
    _oled->println("MIDI");

  }else if(mode == MODE_SYNTH){
    _oled->println("Synth");
  }
  _oled->println("  Octave");
  _oled->println("  HalfTone");
  if(mode == MODE_MIDI){
    _oled->println("  MIDI setup");

  }else if(mode == MODE_SYNTH){
    _oled->println("  SYNTH setup");
  }
  _oled->println("  State");
  _oled->println("  Presets");
  _oled->setCursor(0, (newPos%6)+2);
  _oled->print(">");
}
void Display::displayMidiSettings(uint8_t mode_midi, uint8_t newPos){

  _oled->println("MIDI settings");
  _oled->println(" ");
  _oled->print("  Mode : ");
  if(mode_midi == DRUM){
    _oled->println("DRUM !!!");
  }else if(mode_midi == THEME){
    _oled->println("Theme");
  }
  _oled->println("  Back");
  _oled->setCursor(0, (newPos%2)+2);
  _oled->print(">");

}
void Display::displayMenuAttack(Configuration conf, uint8_t newPos){
  _oled->println("Volume :");
  displayAttack(conf);
  _oled->println("  Theme");
  _oled->println("  Drone");
  _oled->println("  Back");
  _oled->setCursor(0, (newPos%3)+2);
  _oled->print(">");

}
void Display::displaySynthSettingsFirstMenu(uint8_t newPos, Configuration conf, int state){
  // _oled->println("Synth");
  // _oled->println("");
  // _oled->println("  Waveform");
  // _oled->println("  Osc Oct");
  // _oled->println("  Back");
  // _oled->setCursor(0, (newPos%3)+2);
  // #define OCT1_SET 12
  // #define OCT2_SET 13
  // #define OCT3_SET 14
  // #define OCT4_SET 15


  // #define WAV1_SET 16
  // #define WAV2_SET 17
  // #define WAV3_SET 18
  // #define WAV4_SET 19

  // _oled->print(">");
  displayMainTitle();
  _oled->println(" Osc1 Osc2 Brd1 Brd2");
  _oled->print(" ");
  if(state != WAV1_SET){
    displayOsc(conf.activeOsc1);
  }else{
    _oled->print("<");
    displayOscByInt(newPos);
  }
  _oled->print("  ");
  if(state != WAV2_SET){
    displayOsc(conf.activeOsc2);
  }else{
    _oled->print("<");
    displayOscByInt(newPos);
  }
  _oled->print("  ");
  if(state != WAV3_SET){
    displayOsc(conf.activeBrd1);
  }else{
    _oled->print("<");
    displayOscByInt(newPos);
  }
  _oled->print("  ");
  if(state != WAV4_SET){
    displayOsc(conf.activeBrd2);
  }else{
    _oled->print("<");
    displayOscByInt(newPos);
  }
  _oled->println("");
  _oled->print("  ");
  if(state != OCT1_SET){
    _oled->print(conf.octaveOsc1);    
  }else{
    _oled->print("<");
    displayOctByInt(newPos);
  }
  _oled->print("    ");
  if(state != OCT2_SET){
    _oled->print(conf.octaveOsc2);
  }else{
    _oled->print("<");
    displayOctByInt(newPos);
  }
  _oled->print("    ");
  if(state != OCT3_SET){
    _oled->print(conf.octaveBourdon1);
  }else{
    _oled->print("<");
    displayOctByInt(newPos);
  }
  _oled->print("    ");
  if(state != OCT4_SET){
    _oled->print(conf.octaveBourdon2);
  }else{
    _oled->print("<");
    displayOctByInt(newPos);
  }
  _oled->println("");
  _oled->print(" Back");
  
  byte space = 30;
  if(state == SYNTH_SETTINGS){
    if(newPos%9 == 0){
      _oled->setCursor(0,3);
    }
    if(newPos%9 == 1){
      _oled->setCursor(space,3);
    }
    if(newPos%9 == 2){
      _oled->setCursor(2*space,3);
    }
    if(newPos%9 == 3){
      _oled->setCursor(3*space,3);
    }
    if(newPos%9 == 4){
      _oled->setCursor(0,4);
    }
    if(newPos%9 == 5){
      _oled->setCursor(space,4);
    }
    if(newPos%9 == 6){
      _oled->setCursor(2*space,4);
    }
    if(newPos%9 == 7){
      _oled->setCursor(3*space,4);
    }
    if(newPos%9 == 8){
      _oled->setCursor(0,5);
    }
    _oled->print(">");
  }
}

void Display::displayOctByInt(int value){
  _oled->print((value%6)-3);
}

void Display::displayOscByInt(int value){
  if(value % 5 == 0){
    _oled->print("Sin");
  }
  if(value % 5 == 1){
    _oled->print("Saw");
  }
  if(value % 5 == 2){
    _oled->print("Squ");
  }
  if(value % 5 == 3){
    _oled->print("tri");
  }
  if(value % 5 == 4){
    _oled->print("pul");
  }

}
void Display::displayState(Configuration conf){
  displayMainTitle();
  _oled->print("Oct: ");
//   _oled->print(conf.getOctave());
  _oled->print(" ");
//   displayShift(conf.getShiftHalfTone());
  _oled->println("");
  displayAttack(conf);
  _oled->println("  -------------------");
  _oled->println("  Osc1 Osc2 Brd1 Brd2");
  printOscOct(conf);
  printOscWave(conf);

}
void Display::displayOscillatorChoice(uint8_t newPos, Configuration conf){
  _oled->println("Wave Form :");
  printOscWave(conf);
  _oled->println("  Sin");
  _oled->println("  Saw");
  _oled->println("  Square");
  _oled->println("  tri");
  _oled->println("  pulse");
  _oled->println("  Back");
  _oled->setCursor(0, (newPos%6)+2);
  _oled->print(">");
}


void Display::displayOctOrWave(
  uint8_t menuActiveItem,
  uint8_t newPos,
  Configuration conf
){
  if(menuActiveItem == OCT_OSC){
    _oled->println("Oct osc :");
    printOscOct(conf);
  }else{
    _oled->println("Wave :");
    printOscWave(conf);
  }
  _oled->println("  Osc1 ");
  _oled->println("  Osc2 ");
  _oled->println("  Drone1");
  _oled->println("  Drone2 ");
  _oled->println("  All ");
  _oled->println("  Back ");
  _oled->setCursor(0, (newPos%6)+2);
  _oled->print(">");
}
void Display::displayOctaveMenu(uint8_t newPos, Configuration conf){
  printOscOct(conf);
  _oled->println("");
  _oled->print(newPos%6 -3);
  _oled->print(" ");
}

void Display::maindisplay(uint8_t newPos, uint8_t mode, uint8_t mode_midi, uint8_t menuActiveItem, Configuration conf){
  if(menuActiveItem==OCTAVE){
    displayOctave(conf, newPos);
  }else if(menuActiveItem==HALFTONE){
    displayHalfTone(conf, newPos);
  }else if(menuActiveItem == ATTACK_MAIN){
    displayAttackSwitch(conf.attackTheme, newPos);
  }else if(menuActiveItem == ATTACK_DRONE){
    displayAttackSwitch(conf.attackBourdon, newPos);
  }
  else if(menuActiveItem == PRESETS){
    displayPresetsMenu(newPos);
  }else if(menuActiveItem == CHOOSE_OCTAVE){
    displayOctaveMenu(newPos,conf);
  }else if(menuActiveItem == MAIN){
    displayMainMenu(mode, newPos);
  }else if(menuActiveItem == MIDI_SETTINGS){
    displayMidiSettings(mode_midi, newPos);
  }else if(menuActiveItem == SYNTH_SETTINGS){
    displaySynthSettingsFirstMenu(newPos, conf, menuActiveItem);
  }else if(menuActiveItem == DISPLAY_STATE){
    displayState(
      conf
    );
  }
  else if (menuActiveItem == MENU_ATTACK){
    displayMenuAttack(conf, newPos);
  }else if (menuActiveItem == OCT_OSC || menuActiveItem == WAVE){
    displayOctOrWave(
      menuActiveItem,
      newPos,
      conf
    );
  }else if (menuActiveItem == OSCILLATOR){
    displayOscillatorChoice(newPos, conf);
  }
}