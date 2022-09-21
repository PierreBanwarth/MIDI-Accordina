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
    Octave (MIDI and Synth)
1. MIDI 
    Classic midi keyboard + 6 drones
    Drum midi keyboard
2. Synth
    Polyphonic keyboard + Envelope for drones (2 oscillators each)
    Waveform for all oscillators
    Octave for all oscillators
    Attack for all oscillators



## Main.cpp
[Main](https://github.com/PierreBanwarth/MIDI-Accordina/blob/main/src/main.cpp)  
TODO : Translate all code in english and cleanup var names

### functions

#### where the magic happen
##### MOZZI 
MOZZI is working with tabs of oscillators value
there is two functions  
 - UpdateAudio who manage sound output
 - UpdateControl who manage control of the sound
 - 
###### Setup
```c++
#define POLYPHONY 4 // Number of sound that can be played at the same time (theme)

// Array of ADSR envelopes matching with 2 array of oscilators
ADSR <CONTROL_RATE, AUDIO_RATE> envelope[POLYPHONY]; 
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> oscil1[POLYPHONY] = Oscil<COS2048_NUM_CELLS, AUDIO_RATE> (COS2048_DATA);
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> oscil2[POLYPHONY] = Oscil<COS2048_NUM_CELLS, AUDIO_RATE> (COS2048_DATA);

// One ADSR envelope matching 2 oscillators for drones  
ADSR <CONTROL_RATE, AUDIO_RATE> envelopeBourdon; 
Oscil <COS2048_NUM_CELLS, AUDIO_RATE> bourdon1(COS2048_DATA);
Oscil <COS2048_NUM_CELLS, AUDIO_RATE> bourdon2(COS2048_DATA);

int notesPlaying[POLYPHONY]; // Tab to count how many notes are playing simultaneously
```

###### Update audio
Some magical byte shifting (MOZZI documentation is not clear about that but this look working)
```c++
int updateAudio(){
  long note = 0;
  for (byte i = 0; i < POLYPHONY; i++){
    long newNote = 0;
    // For each note we compute ( envelope x (oscil1 + oscil2))
    newNote = (long)envelope[i].next() * (oscil1[i].next()+oscil2[i].next());
    note = note + newNote;
  }
  // Magical byte shifting incoming !!!!
  note = note >> (POLYPHONY+7);
  return note;
  // Soon had to add drones
  // int16_t noteBourdon =  (int16_t)envelopeBourdon.next() * (bourdon1.next()+bourdon2.next()) >>8;
  // return (note + noteBourdon)>>2;
}
```

###### Update control
Used to manage envelope noteOn noteOff things.
```
void updateControl();
```

###### Update control
all that stuff is launched by audioHook(); in the main loop


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
#### Display and Menu management
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

#### Presets 

```c++
Configuration conf = newPresets[0];
// Configutation object are usefull to stock some informations and save and load presets
// Configuration(Name octave, tone shift, octaveOsc2, octaveOsc3, octaveOsc4, waveFormOsc1 ,waveFormOsc2 ,waveFormOsc3 ,waveFormOsc4 , attackTheme, attackDrones)
Configuration("Squ Tri",2,11, -1 ,-1 ,-2,-3 ,4,4,2,0 , 250, 250),

static void setPresets(int i){
  conf = newPresets[i]; // all data are stored in conf
  for(byte z = 0; z < POLYPHONY; z++){ // Setting good wave table for all synth
    oscil1[z].setTable(getWaveFromInt(conf.getOsc1()));
    oscil2[z].setTable(getWaveFromInt(conf.getOsc2()));
  }
  // Setting good wave table for drones
  bourdon1.setTable(getWaveFromInt(conf.getBrd1()));
  bourdon2.setTable(getWaveFromInt(conf.getBrd2()));
}


```





## Concertina Library
[Concertina library](https://github.com/PierreBanwarth/MIDI-Accordina/tree/main/include/concertina_lib) TODO rename the lib

 - Configuration manager : goal is to manage presets TODO add reading/writing on the sd card.
 - Display : Custom coded display menu
 - MusicMath : Functions to compute some music stuff (tone shifting, octave shifting) TODO : Maybe add microtonal shifting
 - Concertina.h : Definition of notes Name, Array of notes and pinout.
 



This project is working thanks to :  
Camille MILLET, Tony JEGO, Yannick CHIRON, Nicolas HARRAND, Jean BANWARTH
