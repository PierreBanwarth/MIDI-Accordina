#ifndef __CONCERTINA_H__
#define __CONCERTINA_H__
#include "Arduino.h"
#include <MIDI.h>
//include configutation
#include "configuration.h"

#define OCTAVE 1
#define MODE 2
#define DISPLAY_STATE 3
#define MENU_ATTACK 4
#define ATTACK_MAIN 5
#define ATTACK_DRONE 6
#define OCT_OSC 7
#define MAIN 8
#define CHOOSE_OCTAVE 9
#define OSCILLATOR 10
#define WAVE 11

#define BUTTON_RELEASED 0
#define BUTTON_PRESSED 1

#define SYNTH_SETTINGS 12
#define MIDI_SETTINGS 13

#define DRUM 14
#define THEME 15
#define HALFTONE 16

#define PRESETS 17


#define MODE_MIDI 0
#define MODE_SYNTH 1

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

enum waveform { SIN = 1, COS = 2, TRI = 3, SAW = 4, SQUARE = 5};

Configuration newPresets[] = {
  Configuration("Squ Tri",2,11),
  Configuration("Squ Tri",4,11),
  Configuration("Squ Tri",1,11),
  Configuration("Squ Tri",1,11),
  Configuration("Squ Tri",1,11),
  Configuration("Squ Tri",1,11),
  Configuration("Squ Tri",1,11)

};

enum
{
    // DEFINING MIDI notes
    C1 = 0,
    Cs1 = 1,
    D1 = 2,
    Ds1 = 3,
    E1 = 4,
    F1 = 5,
    Fs1 = 6,
    G1 = 7,
    Gs1 = 8,
    An1 = 9,
    As1 = 10,
    Bn1 = 11,

    C2 = 0 + 12,
    Cs2 = 1 + 12,
    D2 = 2 + 12,
    Ds2 = 3 + 12,
    E2 = 4 + 12,
    F2 = 5 + 12,
    Fs2 = 6 + 12,
    G2 = 7 + 12,
    Gs2 = 8 + 12,
    An2 = 9 + 12,
    As2 = 10 + 12,
    B2 = 11 + 12,

    C3 = 0 + 24,
    Cs3 = 1 + 24,
    D3 = 2 + 24,
    Ds3 = 3 + 24,
    E3 = 4 + 24,
    F3 = 5 + 24,
    Fs3 = 6 + 24,
    G3 = 7 + 24,
    Gs3 = 8 + 24,
    An3 = 9 + 24,
    As3 = 10 + 24,
    B3 = 11 + 24,

    C4 = 0 + 36,
    Cs4 = 1 + 36,
    D4 = 2 + 36,
    Ds4 = 3 + 36,
    E4 = 4 + 36,
    F4 = 5 + 36,
    Fs4 = 6 + 36,
    G4 = 7 + 36,
    Gs4 = 8 + 36,
    An4 = 9 + 36,
    As4 = 10 + 36,
    B4 = 11 + 36,
    An5 = 9 + 48,
    Eb1 = As1,
    Bb1 = Ds1,
    Eb2 = As2,
    Bb2 = Ds2,
    Eb3 = As3,
    Bb3 = Ds3,
    Eb4 = As4,
    Bb4 = Ds4,

};


uint8_t oldStatePousser[] = {
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
};
uint8_t oldStateTirer[] = {
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
};

uint8_t bourdonActif[] = {
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
};

const byte pousser[36] = {
  F2, G2, An2, 
  Bb3, B3, Fs3, 
  Eb3, D3, An3, 
  G3, F4, C4, 
  Bb4, An4, E4, 
  0, B4, Gs4, 
  0, Gs4, C4, 
  Cs4, B4, Fs4, 
  Eb4, D4, An4, 
  G4, F4, C4, 
  Bb4, An4, E4, 
  D4, B4, F4, 
};

const byte tirer[36] = {
  E2, C2, B2, 
  An2, G2, D2, 
  Cs2, C2, G2,
  An2, E2, B3, 
  Gs3, G3, D3,
  0, Bb3, Fs3,
  0, Fs3, D3,
  Eb3, C4, G4,
  Cs4, E4, B4, 
  Gs4, G4, D4,
  Cs4, C4, G4,
  An4, E4, Bb4,
};


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
    "Fa#/Si"};

String waveFormNames[5] = {
    "Sin",
    "Cos",
    "Tri",
    "Saw",
    "Square",
};
#endif
