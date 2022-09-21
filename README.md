<img src="https://user-images.githubusercontent.com/7162775/191379148-af449447-4c98-4340-b313-ac48eb72af3b.png"  width="250">


# AccordinaMIDI
[Journal de developpement ici](https://github.com/PierreBanwarth/MIDI-Accordina/blob/main/journal.md)
[Dev Journal in french here](https://github.com/PierreBanwarth/MIDI-Accordina/blob/main/journal.md)

# Presentation

This project is the last version (V5) of my Accordion Mechanical Keyboard  

Powered by a teensy 4.1.  

We use MIDI protocol and [MOZZI library](https://sensorium.github.io/Mozzi/learn/output/)  
Most of the code is a reuse of my [previous version of Accordion Mechanical Keyboard](https://github.com/PierreBanwarth/MIDI-Melodica)  

This version is very faster than the previous one thanks to the teensy.  
I have tested it with 5 envelopes at the same time (work only with three with the arduino MEGA)  

# Goal

This project is a mechanical keyboard simulating a concertina keyboard.    
Working both as a Synth and in MIDI.  
Polyphonic (5 sound at a time now)  

# Electronic  
TODO : Post a tutorial to make your own PCB  
this project work with :  
 - 37 mechanical keyboards switchs (36 on the keyboard and one for the push/pull) 
 - 128*64 Oled screen 
 - Encoder 
 - jack 3.5 input
 - micro usb input

# Code 
## Menu

1. General
⋅⋅* Octave (MIDI and Synth)
1. MIDI
⋅⋅* Classic midi keyboard + 6 drones
⋅⋅* Drum midi keyboard
2. Synth
⋅⋅* Polyphonic keyboard + Envelope for drones (2 oscillators each)
⋅⋅* Waveform for all oscillators
⋅⋅* Octave for all oscillators
⋅⋅* Attack for all oscillators



## Main.cpp
[Main](https://github.com/PierreBanwarth/MIDI-Accordina/blob/main/src/main.cpp)  
TODO : Translate all code in english and cleanup var names

### functions
#### functions that emulate expected behaviors:   

```c++
// Synth
static int noteSynthBourdon(uint8_t sens_soufflet, uint8_t index, Configuration conf);
static int noteSynth(uint8_t sens_soufflet, uint8_t index, Configuration conf);
// MIDI
static void noteMidiBourdon(uint8_t index, Configuration conf, int velocity);
static void noteMidi(uint8_t sens_soufflet, uint8_t index, Configuration conf, int velocity);
static void noteMidiDrum(uint8_t index, int velocity);
```
#### function to play notes 
```c++
// Synth
static void noteOnSynth(int frequence, Configuration conf);
static void noteOffSynth(int frequence);
static void noteOnBourdonSynth(int frequence, Configuration conf);
// MIDI
static void noteOn(int noteToPlay, Configuration conf, int velocity, int index);
static void noteOff(int noteToShutdown, Configuration conf);
```
#### Menu management
```c++
Display display = Display(I2C_ADDRESS); // Instanciate a Display object, used to display everything

display.maindisplay(0, mode, mode_midi, menuActiveItem, conf); // in setup to initialize display

static void menuSelector(Display d){
  encoder.tick();
  int newPosition = abs(encoder.getPosition());
  int state = digitalRead(buttonEncoder);
  if (encoderPosition != newPosition)
  {
    d.maindisplay(newPosition, mode, mode_midi, menuActiveItem, conf);// Update display when encoder is rotating
    encoderPosition = newPosition;
  }
  if(state == HIGH && state != stateButtonEncoder){
    menuActiveItem = menuSelectorSwitch(newPosition, menuActiveItem);
    d.maindisplay(newPosition, mode, mode_midi, menuActiveItem, conf);// Update display when encoder is clicked
  }
  stateButtonEncoder = state;
}

static int menuSelectorSwitch(int newPos, int menuActiveItem); // Automata that manage menuing
```







## Concertina Library
[Concertina library](https://github.com/PierreBanwarth/MIDI-Accordina/tree/main/include/concertina_lib) TODO rename the lib

 - Configuration manager : goal is to manage presets TODO add reading/writing on the sd card.
 - Display : Custom coded display menu
 - MusicMath : Functions to compute some music stuff (tone shifting, octave shifting) TODO : Maybe add microtonal shifting
 - Concertina.h : Definition of notes Name, Array of notes and pinout.
 



This project is working thanks to :  
Camille MILLET, Tony JEGO, Yannick CHIRON, Nicolas HARRAND, Jean BANWARTH
