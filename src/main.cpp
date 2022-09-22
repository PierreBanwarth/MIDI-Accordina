#include <Arduino.h>
#include "Wire.h"                                                               // Wire library (Included with Arduino IDE)
#include "SSD1306Ascii.h"                                                       // SSD1306Ascii v1.3.0 library by Bill Greiman
#include "SSD1306AsciiWire.h"                                                   // SSD1306Ascii v1.3.0 library by Bill Greiman
#include "RotaryEncoder.h"

#include <MozziGuts.h>
#include <Oscil.h> // oscillator template

#include "concertina_lib/concertina.h"

#include "concertina_lib/configuration.cpp"
#include "concertina_lib/configuration.h"
#include "concertina_lib/musicMath.h"
#include "concertina_lib/musicMath.cpp"
#include <tables/square_analogue512_int8.h>
#include <tables/triangle_analogue512_int8.h>
#include <tables/sin512_int8.h>
#include <tables/saw_analogue512_int8.h>
#include <mozzi_midi.h>
#include <mozzi_fixmath.h>
#include <mozzi_rand.h>
#include <LowPassFilter.h>
#include <ADSR.h>

#include <tables/cos2048_int8.h>
#include <tables/sin2048_int8.h> //Wavetables for Oscillators
#include <tables/saw2048_int8.h>
#include <tables/triangle2048_int8.h>
#include <tables/square_no_alias_2048_int8.h>
#include <tables/triangle_dist_cubed_2048_int8.h>
// OLED I2C address and library configuration
#define I2C_ADDRESS 0x3C
#define POLYPHONY 4

// #DEFINE MIDI_NAME {'M','e','l', 'o','d','i','c', 'a'}

byte mode = MODE_SYNTH;
byte mode_midi = DRUM;
SSD1306AsciiWire oled;

int countMenu = 0;
ADSR <CONTROL_RATE, AUDIO_RATE> envelopeBourdon; // notre enveloppe
ADSR <CONTROL_RATE, AUDIO_RATE> envelope[POLYPHONY]; // notre enveloppe
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> oscil1[POLYPHONY] = Oscil<COS2048_NUM_CELLS, AUDIO_RATE> (COS2048_DATA);
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> oscil2[POLYPHONY] = Oscil<COS2048_NUM_CELLS, AUDIO_RATE> (COS2048_DATA);

Oscil <COS2048_NUM_CELLS, AUDIO_RATE> bourdon1(COS2048_DATA);
Oscil <COS2048_NUM_CELLS, AUDIO_RATE> bourdon2(COS2048_DATA);
// MOZZI SETUP
int notesPlaying[POLYPHONY];

Configuration conf = newPresets[0];
int wichOsc = 0;
int globalFrequence;
int stateWave = 1;
int bourdonSynthActivated = 0;
int menuActiveItem = MAIN;
byte stateButtonEncoder = HIGH;

int oscillator = 0;
// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);

// use #define for CONTROL_RATE, not a constant
#define CONTROL_RATE 64 // Hz, powers of 2 are most reliable

// ENCODER PART OF THE CODE
// Define proper RST_PIN if required.
#define RST_PIN -1
RotaryEncoder encoder(A1, A0, RotaryEncoder::LatchMode::TWO03);

int state = 0;
int encoderPosition = 0;
byte buttonEncoder = 2;

byte pousserTirer = 1;

void initDisplay(uint8_t i2c_address)
{
  oled.begin(&Adafruit128x64, i2c_address);
  oled.clear();
  oled.setFont(Adafruit5x7);
  oled.print("test");
  Wire.begin();           // Init I2C
  Wire.setClock(400000L); // Fast mode
}

void displayShift(uint8_t i)
{
  oled.print(keyNames[i]);
}

void testOff(uint8_t i)
{
  oled.clear();
  oled.print("Off : ");
  oled.print(i);
  oled.println("");
}

void testOn(uint8_t i)
{
  oled.clear();
  oled.print("On : ");
  oled.print(i);
  oled.println("");
}
void printIndex(uint8_t i)
{
  oled.println(i);
}

void displayOsc(uint8_t i)
{
  oled.print(waveFormNames[i]);
}

void displayMainTitle()
{
  oled.println("Melodica MIDI");
  oled.println("V 2.0.0.0");
}
void displayAttack(Configuration conf)
{
  oled.print("VOsc: ");
  oled.print(conf.attackTheme);
  oled.print(" VBrd: ");
  oled.println(conf.attackBourdon);
}

void printOscWave(Configuration conf)
{
  displayOsc(conf.activeOsc1);
  oled.print(" ");
  displayOsc(conf.activeOsc2);
  oled.print(" ");
  displayOsc(conf.activeBrd1);
  oled.print(" ");
  displayOsc(conf.activeBrd2);
  oled.println("");
}
void printOscOct(Configuration conf)
{
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
void displayOctave(Configuration conf, uint8_t newPos)
{
  oled.print("Octave : ");
  oled.println(conf.octave);
  oled.print("Oct : ");
  oled.println((newPos) % 6);
  oled.print(" ");
}
void displayHalfTone(Configuration conf, uint8_t newPos)
{
  oled.print("Actual ");
  displayShift(conf.shiftHalfTone);
  oled.println("");
  oled.print("New : ");
  displayShift(newPos);
  oled.print(" ");
}
void displayAttackSwitch(uint8_t attack, uint8_t newPos)
{
  oled.print("Volume Main : ");
  oled.println(attack);
  oled.println(" ");
  oled.print("Volume : ");
  oled.print((attack + (5 * newPos)) % 255);
  oled.print(" ");
}
void displayPresetsMenu(uint8_t newPos)
{
  for (int i = 0; i < 7; i++)
  {
    oled.print(" ");
    String name = newPresets[i].getName();
    oled.println(name);
  }
  oled.println("  Back");
  oled.setCursor(0, (newPos % 8));
  oled.print(">");
}

void displayMainMenu(uint8_t mode, uint8_t newPos)
{
  displayMainTitle();
  oled.print("  Mode : ");
  if (mode == MODE_MIDI)
  {
    oled.println("MIDI");
  }
  else if (mode == MODE_SYNTH)
  {
    oled.println("Synth");
  }
  oled.println("  Octave");
  oled.println("  HalfTone");
  if (mode == MODE_MIDI)
  {
    oled.println("  MIDI setup");
  }
  else if (mode == MODE_SYNTH)
  {
    oled.println("  SYNTH setup");
  }
  oled.println("  State");
  oled.println("  Presets");
  oled.setCursor(0, (newPos % 6) + 2);
  oled.print(">");
}
void displayMidiSettings(uint8_t mode_midi, uint8_t newPos)
{

  oled.println("MIDI settings");
  oled.println(" ");
  oled.print("  Mode : ");
  if (mode_midi == DRUM)
  {
    oled.println("DRUM !!!");
  }
  else if (mode_midi == THEME)
  {
    oled.println("Theme");
  }
  oled.println("  Back");
  oled.setCursor(0, (newPos % 2) + 2);
  oled.print(">");
}
void displayMenuAttack(Configuration conf, uint8_t newPos)
{
  oled.println("Volume :");
  displayAttack(conf);
  oled.println("  Theme");
  oled.println("  Drone");
  oled.println("  Back");
  oled.setCursor(0, (newPos % 3) + 2);
  oled.print(">");
}
void displaySynthSettingsFirstMenu(uint8_t newPos)
{
  oled.println("Synth");
  oled.println("");
  oled.println("  Waveform");
  oled.println("  Volume");
  oled.println("  Osc Oct");
  oled.println("  Back");
  oled.setCursor(0, (newPos % 4) + 2);
  oled.print(">");
}

void displayState(Configuration conf)
{
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
void displayOscillatorChoice(uint8_t newPos, Configuration conf)
{
  oled.println("Wave Form :");
  printOscWave(conf);
  oled.println("  Sin");
  oled.println("  Cos");
  oled.println("  Tri");
  oled.println("  Saw");
  oled.println("  Square");
  oled.println("  Back");
  oled.setCursor(0, (newPos % 6) + 2);
  oled.print(">");
}

void displayOctOrWave(
    uint8_t menuActiveItem,
    uint8_t newPos,
    Configuration conf)
{
  if (menuActiveItem == OCT_OSC)
  {
    oled.println("Oct osc :");
    printOscOct(conf);
  }
  else
  {
    oled.println("Wave :");
    printOscWave(conf);
  }
  oled.println("  Osc1 ");
  oled.println("  Osc2 ");
  oled.println("  Drone1");
  oled.println("  Drone2 ");
  oled.println("  All ");
  oled.println("  Back ");
  oled.setCursor(0, (newPos % 6) + 2);
  oled.print(">");
}
void printOctaveMenu(uint8_t newPos, Configuration conf)
{
  printOscOct(conf);
  oled.println("");
  oled.print(newPos % 6 - 3);
  oled.print(" ");
}

void maindisplay(uint8_t newPos, uint8_t mode, uint8_t mode_midi, uint8_t menuActiveItem, Configuration conf)
{
  oled.clear();
  if (menuActiveItem == OCTAVE)
  {
    displayOctave(conf, newPos);
  }
  else if (menuActiveItem == HALFTONE)
  {
    displayHalfTone(conf, newPos);
  }
  else if (menuActiveItem == ATTACK_MAIN)
  {
    displayAttackSwitch(conf.attackTheme, newPos);
  }
  else if (menuActiveItem == ATTACK_DRONE)
  {
    displayAttackSwitch(conf.attackBourdon, newPos);
  }
  else if (menuActiveItem == PRESETS)
  {
    displayPresetsMenu(newPos);
  }
  else if (menuActiveItem == CHOOSE_OCTAVE)
  {
    printOctaveMenu(newPos, conf);
  }
  else if (menuActiveItem == MAIN)
  {
    displayMainMenu(mode, newPos);
  }
  else if (menuActiveItem == MIDI_SETTINGS)
  {
    displayMidiSettings(mode_midi, newPos);
  }
  else if (menuActiveItem == SYNTH_SETTINGS)
  {
    displaySynthSettingsFirstMenu(newPos);
  }
  else if (menuActiveItem == DISPLAY_STATE)
  {
    displayState(
        conf);
  }
  else if (menuActiveItem == MENU_ATTACK)
  {
    displayMenuAttack(conf, newPos);
  }
  else if (menuActiveItem == OCT_OSC || menuActiveItem == WAVE)
  {
    displayOctOrWave(
        menuActiveItem,
        newPos,
        conf);
  }
  else if (menuActiveItem == OSCILLATOR)
  {
    displayOscillatorChoice(newPos, conf);
  }
}

// technical stuff to play put everything in a library
static void noteOn(int noteToPlay, Configuration conf, int velocity, int index){
  usbMIDI.sendNoteOn(noteToPlay + 12*conf.octave, velocity, 1);

}
static void noteOff(int noteToShutdown, Configuration conf){
  usbMIDI.sendNoteOff(noteToShutdown + 12*conf.octave, 0, 1);
}

static void noteMidiDrum(uint8_t index, int velocity){
  uint8_t note = drum[index]+36;
  digitalWrite(pinButton[index], HIGH);
  uint8_t bouton = digitalRead(pinButton[index]);
  if (bouton == LOW)
  {
    // on pousse sur le bouton et sur le soufflet
    if(oldStatePousser[index] == BUTTON_RELEASED){
      oldStatePousser[index] = BUTTON_PRESSED;
      noteOn(note, conf, 127, index);
    }

  }else{
    noteOff(note, conf);
    oldStatePousser[index] = BUTTON_RELEASED;
  }
}
static void noteMidi(uint8_t sens_soufflet, uint8_t index, Configuration conf, int velocity){
   //, uint8_t oldStatePousser, uint8_t oldStateTirer
  // velocity = 127;
  digitalWrite(pinButton[index], HIGH);
  uint8_t bouton = digitalRead(pinButton[index]);
  // digitalWrite(pinButton[index], LOW);
  uint8_t noteA = pousser[index] + getShift(conf.shiftHalfTone);
  uint8_t noteB = tirer[index] + getShift(conf.shiftHalfTone);
  if (pousser[index] != 0 || tirer[index] != 0)
  {
    // higher velocity usually makes MIDI instruments louder
    if (bouton == LOW)
    {
      if (sens_soufflet == LOW)
      {
        // on pousse sur le bouton et sur le soufflet
        if (oldStatePousser[index] == BUTTON_RELEASED)
        {
          noteOn(noteA, conf, velocity, index);
          oldStatePousser[index] = BUTTON_PRESSED;
          if (oldStateTirer[index] == BUTTON_PRESSED)
          {
            noteOff(noteB, conf);
            oldStateTirer[index] = BUTTON_RELEASED;
          }
        }
      }
      else
      { // on tire sur le soufflet et on appuie sur le bouton
        if (oldStateTirer[index] == 0)
        {

          noteOn(noteB, conf, velocity, index);
          oldStateTirer[index] = BUTTON_PRESSED;
          if (oldStatePousser[index] == BUTTON_PRESSED)
          {
            noteOff(noteA, conf);
            oldStatePousser[index] = BUTTON_RELEASED;
          }
        }
      }
    }
    else
    {
      if (oldStatePousser[index] == BUTTON_PRESSED)
      {
        noteOff(noteA, conf);
        oldStatePousser[index] = BUTTON_RELEASED;
      }
      if (oldStateTirer[index] == BUTTON_PRESSED)
      {
        // on appuie pas sur le bouton ma
        noteOff(noteB, conf);
        oldStateTirer[index] = BUTTON_RELEASED;
      }
    }
  }

}
static void noteMidiBourdon(uint8_t index, Configuration conf, int velocity){
  //, uint8_t oldStatePousser, uint8_t oldStateTirer
  // velocity = 127;
  digitalWrite(pinButton[index], HIGH);
  uint8_t bouton = digitalRead(pinButton[index]);
  // digitalWrite(pinButton[index], LOW);
  uint8_t note = pousser[index]+getShift(conf.shiftHalfTone);
  if (bouton == LOW)
  {

    // on pousse sur le bouton et sur le soufflet
    if(oldStatePousser[index] == BUTTON_RELEASED){
      oldStatePousser[index] = BUTTON_PRESSED;
      if(bourdonActif[index] == 1){
        noteOff(note, conf);
        bourdonActif[index] = 0;
      }else{
        noteOn(note, conf, velocity/2, index);
        bourdonActif[index] = 1;
      }
    }

  }else{
    oldStatePousser[index] = BUTTON_RELEASED;
  }
}
static void noteOnSynth(int frequence, Configuration conf){
  byte found = 0;
  for(byte i=0; i<POLYPHONY; i++){
    if (notesPlaying[i] == 0 && found == 0){
      notesPlaying[i] = frequence;
      oscil1[i].setFreq(getOctaveValueToMultiplyForOsc(conf.octaveOsc1, frequence, conf.octave));
      oscil2[i].setFreq(getOctaveValueToMultiplyForOsc(conf.octaveOsc2, frequence, conf.octave));
      envelope[i].noteOn(); // on joue la note
      found = 1;
    }else if(notesPlaying[i] == frequence){
      found = 1;
    }
  }
}

static void noteOffSynth(int frequence){
  // Searching if notes is played
  for(byte i=0; i<POLYPHONY; i++){
    if (notesPlaying[i] == frequence){
      // Erasing it from table
      notesPlaying[i] = 0;
      envelope[i].noteOff();
    }
  }
}

static void noteOnBourdonSynth(int frequence, Configuration conf){
  bourdon1.setFreq(getOctaveValueToMultiplyForOsc(conf.octaveBourdon1, frequence, conf.octave));
  bourdon2.setFreq(getOctaveValueToMultiplyForOsc(conf.octaveBourdon2, frequence, conf.octave));
  envelopeBourdon.noteOn(); // on joue la note
}

static int noteSynth(uint8_t sens_soufflet, uint8_t index, Configuration conf){
  digitalWrite(pinButton[index], HIGH);
  uint8_t bouton = digitalRead(pinButton[index]);

  int noteSynthA = MatriceNote[pousser[index]+getShift(conf.shiftHalfTone)];
  int noteSynthB = MatriceNote[tirer[index]+getShift(conf.shiftHalfTone)];
  if (pousser[index] != 0 || tirer[index] != 0)
  {
    if (bouton == LOW)
    {
      if (sens_soufflet == LOW)
      {
        // on pousse sur le bouton et sur le soufflet
        if (oldStatePousser[index] == BUTTON_RELEASED)
        {
          // play note
          if (oldStateTirer[index] == BUTTON_PRESSED)
          {
            noteOffSynth(noteSynthB);
            oldStateTirer[index] = BUTTON_RELEASED;
          }
          noteOnSynth(noteSynthA, conf);
          oldStatePousser[index] = BUTTON_PRESSED;
        }
      }
      else
      { // on tire sur le soufflet et on appuie sur le bouton
        if (oldStateTirer[index] == BUTTON_RELEASED)
        {
          if (oldStatePousser[index] == BUTTON_PRESSED)
          {
            noteOffSynth(noteSynthA);
            oldStatePousser[index] = BUTTON_RELEASED;
          }
          noteOnSynth(noteSynthB, conf);
          oldStateTirer[index] = BUTTON_PRESSED;

        }
      }
      return 1;
    }
    else
    {
      if (oldStatePousser[index] == BUTTON_PRESSED)
      {
        noteOffSynth(noteSynthA);
        oldStatePousser[index] = BUTTON_RELEASED;
      }
      if (oldStateTirer[index] == BUTTON_PRESSED)
      {
        noteOffSynth(noteSynthB);
        oldStateTirer[index] = BUTTON_RELEASED;
      }
      return 0;
    }
  }
  return 0;
}

static void setPresets(int i){
  conf = newPresets[i];
  for(byte z = 0; z < POLYPHONY; z++){
    oscil1[z].setTable(getWaveFromInt(conf.getOsc1()));
    oscil2[z].setTable(getWaveFromInt(conf.getOsc2()));
  }
  bourdon1.setTable(getWaveFromInt(conf.getBrd1()));
  bourdon2.setTable(getWaveFromInt(conf.getBrd2()));
}

static int menuSelectorSwitch(int newPos, int menuActiveItem){

  if(menuActiveItem==OCTAVE){
    conf.octave = (newPos)%6;
    menuActiveItem = MAIN;
    encoder.setPosition(1);

  }else if(menuActiveItem==HALFTONE){
    conf.shiftHalfTone = (newPos%23);
    menuActiveItem = MAIN;
    encoder.setPosition(2);

  }else if(menuActiveItem==ATTACK_MAIN){
    conf.attackTheme = (conf.attackTheme+(5*newPos))%255;
    menuActiveItem = MENU_ATTACK;
    encoder.setPosition(0);
  }
  else if(menuActiveItem==ATTACK_DRONE){
    conf.attackBourdon = (conf.attackBourdon+(5*newPos))%255;
    menuActiveItem = MENU_ATTACK;
    encoder.setPosition(1);
  }else if(menuActiveItem==DISPLAY_STATE){
    menuActiveItem = MAIN;
    encoder.setPosition(4);
  }else if(menuActiveItem == MIDI_SETTINGS){
    if(newPos%2 == 0){
      if(mode_midi == DRUM){
        mode_midi=THEME;
      }
      else if(mode_midi == THEME){
        mode_midi=DRUM;
      }
    }else if(newPos%2==1){
      menuActiveItem = MAIN;
    }
  }else if(menuActiveItem==MAIN){
    if(newPos%6 == 0){
      if(mode == MODE_SYNTH){
        mode=MODE_MIDI;
      }
      else if(mode == MODE_MIDI){
        mode=MODE_SYNTH;
      }
    }
    else if(newPos%6 == 1){
      menuActiveItem = OCTAVE;
      encoder.setPosition(conf.octave);
    }
    else if(newPos%6 == 2){
      menuActiveItem = HALFTONE;
      encoder.setPosition(conf.shiftHalfTone);
    }
    else if(newPos%6 == 3){
      if(mode == MODE_MIDI){
        menuActiveItem = MIDI_SETTINGS;
      }else if(mode == MODE_SYNTH){
        menuActiveItem = SYNTH_SETTINGS;
      }
      encoder.setPosition(0);
    }
    else if(newPos%6 == 4){
      menuActiveItem = DISPLAY_STATE;
    }
    else if(newPos%6 == 5){
      menuActiveItem = PRESETS;
      encoder.setPosition(0);
    }
  }else if(menuActiveItem==PRESETS){
      //if(newPos%6 == 0){
      if(newPos%8==7){
        menuActiveItem = MAIN;
      }
      else{
        setPresets(newPos);
      }
      encoder.setPosition(5);
  }
  else if(menuActiveItem==MENU_ATTACK){
    if(newPos%3 == 0){
      menuActiveItem = ATTACK_MAIN;
    }
    else if(newPos%3 == 1){
      menuActiveItem = ATTACK_DRONE;
    }
    else if(newPos%3 == 2){
      menuActiveItem = SYNTH_SETTINGS;
    }
    encoder.setPosition(1);
  }else if(menuActiveItem==SYNTH_SETTINGS){
    if(newPos%4 == 0){
      menuActiveItem = WAVE;
    }
    else if(newPos%4 == 1){
      menuActiveItem = MENU_ATTACK;
    }
    else if(newPos%4 == 2){
      menuActiveItem = OCT_OSC;
    }
    else if (newPos%4 == 3)
    {
      menuActiveItem = MAIN;
    }
    encoder.setPosition(0);
  }else if(menuActiveItem==CHOOSE_OCTAVE){
      int newOctave = (newPos%6)-3;
      conf.setOscOct(wichOsc, newOctave);
      encoder.setPosition(wichOsc-1);
      menuActiveItem = OCT_OSC;

  }else if(menuActiveItem==OCT_OSC){
    if(newPos%6 == 5){
      menuActiveItem = SYNTH_SETTINGS;
      encoder.setPosition(2);
    }else{
      menuActiveItem = CHOOSE_OCTAVE;
      wichOsc = (newPos%6)+1;
    }

  }else if (menuActiveItem == WAVE){
    if (newPos % 6 == 5)
    {
      menuActiveItem = SYNTH_SETTINGS;
      encoder.setPosition(0);
    }else{
      menuActiveItem = OSCILLATOR;
      encoder.setPosition(0);
      oscillator = (newPos % 6)+1;
    }
  }else if(menuActiveItem==OSCILLATOR){
    if(newPos%6 != 5){
      if(oscillator == 1){
        for(byte z = 0; z < POLYPHONY; z++){
          oscil1[z].setTable(getWaveFromInt(newPos%6));
        }
        conf.activeOsc1 = newPos%6;

      }else if(oscillator == 2){
        for(byte z = 0; z < POLYPHONY; z++){
          oscil2[z].setTable(getWaveFromInt(newPos%6));
        }
        conf.activeOsc2 = newPos%6;

      }else if(oscillator == 3){
        bourdon1.setTable(getWaveFromInt(newPos%6));
        conf.activeBrd1 = newPos%6;

      }else if (oscillator == 4){
        bourdon2.setTable(getWaveFromInt(newPos%6));
        conf.activeBrd2 = newPos%6;

      }else if (oscillator == 5){
        conf.setAllOsc(newPos%6);
        for(byte z = 0; z < POLYPHONY; z++){
          oscil1[z].setTable(getWaveFromInt(newPos%6));
          oscil2[z].setTable(getWaveFromInt(newPos%6));
        }
        bourdon1.setTable(getWaveFromInt(newPos%6));
        bourdon2.setTable(getWaveFromInt(newPos%6));
      }
    }else if(newPos%6 == 5){
      menuActiveItem = WAVE;
      encoder.setPosition(oscillator-1);
      oscillator = 0;
    }
  }
  return menuActiveItem;
}

static void bourdonSetup(){
  byte attack_level = conf.attackBourdon;
  byte decay_level = 255;

  envelopeBourdon.setReleaseLevel(0);
  envelopeBourdon.setADLevels(attack_level,decay_level);
  envelopeBourdon.setTimes(0,0,0,0);
  envelopeBourdon.noteOn();
}

static void menuSelector(){
  encoder.tick();

  int newPosition = abs(encoder.getPosition());
  int state = digitalRead(buttonEncoder);

  if (encoderPosition != newPosition)

  {
    maindisplay(newPosition, mode, mode_midi, menuActiveItem, conf);
    encoderPosition = newPosition;
  }
  if(state == HIGH && state != stateButtonEncoder){
    menuActiveItem = menuSelectorSwitch(newPosition, menuActiveItem);
    maindisplay(newPosition, mode, mode_midi, menuActiveItem, conf);
  }
  stateButtonEncoder = state;

}

int updateAudio(){
  long note = 0;
  for (byte i = 0; i < POLYPHONY; i++){
    long newNote = 0;
    //        1     +       7 + 8 + 1
    newNote = (long)envelope[i].next() * (oscil1[i].next()+oscil2[i].next());
    note = note + newNote;
  }
  long noteBourdon =  (long)envelopeBourdon.next() * (bourdon1.next()+bourdon2.next());
  note = note + noteBourdon;
  note = note >> (POLYPHONY+8);
  return note;
}


static int noteSynthBourdon(uint8_t sens_soufflet, uint8_t index, Configuration conf){
  //, uint8_t oldStatePousser, uint8_t oldStateTirer
  digitalWrite(pinButton[index], HIGH);
  uint8_t bouton = digitalRead(pinButton[index]);
  uint8_t noteA = MatriceNote[pousser[index]+getShift(conf.shiftHalfTone)];
  // On
  if (bouton == LOW)
  {
    // Ancien etat = on a pas appuye
    if(oldStatePousser[index] == BUTTON_RELEASED){
        // le bourdon n'etait pas en jeu
      if(bourdonActif[index] == 0){

        noteOnBourdonSynth(noteA, conf);
        for(byte index=0; index<36; index++){
          bourdonActif[index] = 0;
        }
        bourdonActif[index] = 1;
      }
      // le bourdon etait en jeu
      else{
        bourdonActif[index] = 0;
      }
    }
    oldStatePousser[index] = BUTTON_PRESSED;
  }
  // le bouton n'est pas pressé
  else{
    oldStatePousser[index] = BUTTON_RELEASED;
  }
  return bourdonActif[index];
}

void setup() {
  usbMIDI.begin();
  initDisplay(I2C_ADDRESS);

  // Call oled.setI2cClock(frequency) to change from the default frequency.
  startMozzi(CONTROL_RATE); // :)
  aSin.setFreq(440); // set the frequency

  pinMode(buttonEncoder, INPUT_PULLUP);

  pinMode(pousserTirer, INPUT);
  digitalWrite(pousserTirer, HIGH);
  // SETUP BUTTONS PIN
  for (uint8_t pin = 0; pin < 36; pin++) {
    pinMode(pinButton[pin],INPUT_PULLUP);
  }
  maindisplay(0, mode, mode_midi, menuActiveItem, conf);
}

void updateControl(){

  byte attack_level = conf.attackTheme;
  byte decay_level = 255;

  uint8_t attack = 0;
  uint8_t decay = 0;
  uint8_t release_ms = 0; // times for the attack, decay, and release of envelope
  uint8_t sustain  = 0; //sustain time set to zero so notes can be played as long as key is presssed without being effect by previus touch
  byte pousserTirerState = 0;


  for (byte z = 0; z < POLYPHONY; z++)
  {
    envelope[z].setReleaseLevel(0);
    envelope[z].setADLevels(attack_level,decay_level);
    envelope[z].setTimes(attack,decay,sustain,release_ms);
  }
  bourdonSetup();
  uint8_t onOffSynth = 0;
  uint8_t onOffBourdon = 0;
  pousserTirerState = digitalRead(pousserTirer);
  for (int i = 0; i < 36; i++)
  {
    if( i == 35 ||  i == 0 ||  i == 1 ||  i == 2 ||  i == 34 ){
      onOffBourdon += noteSynthBourdon(pousserTirerState, i, conf);
      noteMidiBourdon(i, conf, 127);
    }else{
      onOffSynth += noteSynth(pousserTirerState, i, conf);
      noteMidi(pousserTirerState, i, conf, 127);
    }
  }
  if(onOffBourdon == 0){
    envelopeBourdon.noteOff();
  }
}



void loop() {
  if(countMenu == 200){
    menuSelector();
    countMenu = 0;
  }
  countMenu++;
  audioHook();
}
