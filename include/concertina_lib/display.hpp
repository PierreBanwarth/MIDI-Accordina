#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "SSD1306AsciiWire.h"
#include "concertina_lib/concertina.h"
#include "concertina_lib/configuration.hpp"

 class Display
 {
 private:
  SSD1306AsciiWire* _oled;
  uint8_t  _address;
  TwoWire*  _wire;

public:
  //explicit PCF8575(const uint8_t deviceAddress = 0x20, TwoWire *wire = &Wire);
  explicit Display();
  explicit Display(SSD1306AsciiWire *oled, const uint8_t deviceAddress, TwoWire *wire);
  void initDisplay();
  void printIndex(uint8_t  i);
  void displayOsc(uint8_t i);
  void testOff(uint8_t  i);
  void testOn(uint8_t  i);
  void displayShift(uint8_t i);
  void displayMainTitle();
  void displayAttack(Configuration conf);
  void printOscWave(Configuration conf);
  void displayOscillatorChoice(uint8_t newPos, Configuration conf);
  void displayOctave(Configuration conf, uint8_t newPos);
  void displayHalfTone(Configuration conf, uint8_t newPos);
  void displayPresetsMenu(uint8_t newPos);
  void displayMainMenu(uint8_t mode, uint8_t newPos);
  void displayMidiSettings(uint8_t mode, uint8_t newPos);
  void displaySynthSettingsFirstMenu(uint8_t newPos);
  void displayMenuAttack(Configuration conf, uint8_t newPos);
  void printOscOct(Configuration conf);
  void displayOctaveMenu(uint8_t newPos, Configuration conf);
  void displayAttackSwitch(uint8_t attack, uint8_t newPos);
  void displayState(Configuration conf);
  void maindisplay(uint8_t newPos, uint8_t mode, uint8_t mode_midi, uint8_t menuActiveItem, Configuration conf);
  void displayOctOrWave(
     uint8_t menuActiveItem,
     uint8_t newPos,
     Configuration conf
  );
  void clear();
  String keyNames[23] = {
    "Sol#/Do#",
    "La/Re",
    "Sib/Re#",
    "Si/Mi",
    "Do/Fa",
    "Do#/Fa#",
    "Re/Sol",
    "Re#/Sol#",
    "Mi/La",
    "Fa/Sib",
    "Fa#/Si",
    "Sol/Do",
    "Sol#/Do#",
    "La/Re",
    "Sib/Re#",
    "Si/Mi",
    "Do/Fa",
    "Do#/Fa#",
    "Re/Sol",
    "Re#/Sol#",
    "Mi/La",
    "Fa/Sib",
    "Fa#/Si"
  };
  String waveFormNames[5] = {
    "Sin",
    "Cos",
    "Tri",
    "Saw",
    "Square",
  };

 };

#endif