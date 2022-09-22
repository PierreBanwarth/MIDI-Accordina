#include "SSD1306Ascii.h"
#include "Wire.h" // Wire library (Included with Arduino IDE)

#include "display.hpp"
#include "concertina_lib/concertina.h"
#include "concertina_lib/configuration.h"


Display::Display(uint8_t i2c_address) {
  oled.begin(&Adafruit128x64, i2c_address);
  oled.clear();
  oled.setFont(Adafruit5x7);
  oled.print("test");
  Wire.begin();           // Init I2C
  Wire.setClock(400000L); // Fast mode
}

void Display::displayShift(uint8_t  i){
  oled.print(keyNames[i]);
}

void Display::testOff(uint8_t  i){
  oled.clear();
  oled.print("Off : ");
  oled.print(i);
  oled.println("");

}

void Display::testOn(uint8_t  i){
  oled.clear();
  oled.print("On : ");
  oled.print(i);
  oled.println("");
}
void Display::printIndex(uint8_t  i){
  oled.println(i);
}

void Display::displayOsc(uint8_t i){
  oled.print(waveFormNames[i]);
}

void Display::displayMainTitle(){
  oled.println("Melodica MIDI");
  oled.println("V 2.0.0.0");
}
void Display::displayAttack(Configuration conf){
  oled.print("VOsc: ");
  oled.print(conf.attackTheme);
  oled.print(" VBrd: ");
  oled.println(conf.attackBourdon);
}

void Display::printOscWave(Configuration conf){
  displayOsc(conf.activeOsc1);
  oled.print(" ");
  displayOsc(conf.activeOsc2);
  oled.print(" ");
  displayOsc(conf.activeBrd1);
  oled.print(" ");
  displayOsc(conf.activeBrd2);
  oled.println("");
}
void Display::printOscOct(Configuration conf){
  oled.print("Oct: ");
  oled.print(conf.octaveOsc1);
  oled.print("   ");
  oled.print(conf.octaveOsc2);
  oled.print("   ");
  oled.print(conf.octaveBourdon1);
  oled.print("  ");
  oled.print(conf.octaveBourdon2);
  oled.println("");
}
void Display::displayOctave(Configuration conf, uint8_t newPos){
  oled.print("Octave : ");
  oled.println(conf.octave);
  oled.print("Oct : ");
  oled.println((newPos)%6);
  oled.print(" ");
}
void Display::displayHalfTone(Configuration conf, uint8_t  newPos){
  oled.print("Actual ");
  displayShift(conf.shiftHalfTone);
  oled.println("");
  oled.print("New : ");
  displayShift(newPos);
  oled.print(" ");
}
void Display::displayAttackSwitch(uint8_t attack, uint8_t newPos){
  oled.print("Volume Main : ");
  oled.println(attack);
  oled.println(" ");
  oled.print("Volume : ");
  oled.print((attack+(5*newPos))%255);
  oled.print(" ");
}
void Display::displayPresetsMenu(uint8_t newPos){
  for(int i=0; i<7; i++){
    oled.print(" ");
    String name = newPresets[i].getName();
    oled.println(name);
  }
  oled.println("  Back");
  oled.setCursor(0, (newPos%8));
  oled.print(">");
}

void Display::displayMainMenu(uint8_t mode, uint8_t newPos){
  displayMainTitle();
  oled.print("  Mode : ");
  if(mode == MODE_MIDI){
    oled.println("MIDI");

  }else if(mode == MODE_SYNTH){
    oled.println("Synth");
  }
  oled.println("  Octave");
  oled.println("  HalfTone");
  if(mode == MODE_MIDI){
    oled.println("  MIDI setup");

  }else if(mode == MODE_SYNTH){
    oled.println("  SYNTH setup");
  }
  oled.println("  State");
  oled.println("  Presets");
  oled.setCursor(0, (newPos%6)+2);
  oled.print(">");
}
void Display::displayMidiSettings(uint8_t mode_midi, uint8_t newPos){

  oled.println("MIDI settings");
  oled.println(" ");
  oled.print("  Mode : ");
  if(mode_midi == DRUM){
    oled.println("DRUM !!!");
  }else if(mode_midi == THEME){
    oled.println("Theme");
  }
  oled.println("  Back");
  oled.setCursor(0, (newPos%2)+2);
  oled.print(">");

}
void Display::displayMenuAttack(Configuration conf, uint8_t newPos){
  oled.println("Volume :");
  displayAttack(conf);
  oled.println("  Theme");
  oled.println("  Drone");
  oled.println("  Back");
  oled.setCursor(0, (newPos%3)+2);
  oled.print(">");

}
void Display::displaySynthSettingsFirstMenu(uint8_t newPos){
  oled.println("Synth");
  oled.println("");
  oled.println("  Waveform");
  oled.println("  Volume");
  oled.println("  Osc Oct");
  oled.println("  Back");
  oled.setCursor(0, (newPos%4)+2);
  oled.print(">");
}

void Display::displayState(Configuration conf){
  displayMainTitle();
  oled.print("Oct: ");
  oled.print(conf.octave);
  oled.print(" ");
  displayShift(conf.shiftHalfTone);
  oled.println("");

  displayAttack(conf);
  oled.println("  -------------------");
  oled.println("  Osc1 Osc2 Brd1 Brd2");
  printOscOct(conf);
  printOscWave(conf);

}
void Display::displayOscillatorChoice(uint8_t newPos, Configuration conf){
  oled.println("Wave Form :");
  printOscWave(conf);
  oled.println("  Sin");
  oled.println("  Cos");
  oled.println("  Tri");
  oled.println("  Saw");
  oled.println("  Square");
  oled.println("  Back");
  oled.setCursor(0, (newPos%6)+2);
  oled.print(">");
}


void Display::displayOctOrWave(
  uint8_t menuActiveItem,
  uint8_t newPos,
  Configuration conf
){
  if(menuActiveItem == OCT_OSC){
    oled.println("Oct osc :");
    printOscOct(conf);
  }else{
    oled.println("Wave :");
    printOscWave(conf);
  }
  oled.println("  Osc1 ");
  oled.println("  Osc2 ");
  oled.println("  Drone1");
  oled.println("  Drone2 ");
  oled.println("  All ");
  oled.println("  Back ");
  oled.setCursor(0, (newPos%6)+2);
  oled.print(">");
}
void Display::printOctaveMenu(uint8_t newPos, Configuration conf){
  printOscOct(conf);
  oled.println("");
  oled.print(newPos%6 -3);
  oled.print(" ");
}

void Display::maindisplay(uint8_t newPos, uint8_t mode, uint8_t mode_midi, uint8_t menuActiveItem, Configuration conf){
  oled.clear();
  if(menuActiveItem==OCTAVE){
    displayOctave(conf, newPos);
  }else if(menuActiveItem==HALFTONE){
    displayHalfTone(conf, newPos);
  }else if(menuActiveItem == ATTACK_MAIN){
    displayAttackSwitch(conf.attackTheme, newPos);
  }else if(menuActiveItem == ATTACK_DRONE){
    displayAttackSwitch(conf.attackBourdon, newPos);
  }else if(menuActiveItem == PRESETS){
    displayPresetsMenu(newPos);
  }else if(menuActiveItem == CHOOSE_OCTAVE){
    printOctaveMenu(newPos,conf);
  }else if(menuActiveItem == MAIN){
    displayMainMenu(mode, newPos);
  }else if(menuActiveItem == MIDI_SETTINGS){
    displayMidiSettings(mode_midi, newPos);
  }else if(menuActiveItem == SYNTH_SETTINGS){
    displaySynthSettingsFirstMenu(newPos);
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
