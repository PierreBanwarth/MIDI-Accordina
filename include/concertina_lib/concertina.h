#ifndef __CONCERTINA_H__
#define __CONCERTINA_H__
#include "Arduino.h"
#include <MIDI.h>
//include configutation
#include "configuration.hpp"

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



#define BUTTON_RELEASED 1
#define BUTTON_PRESSED 0

#define SYNTH_SETTINGS 12
#define MIDI_SETTINGS 13

#define DRUM 14
#define THEME 15
#define HALFTONE 16
#define PRESETS 17

#define OCT1_SET 18
#define OCT2_SET 19
#define OCT3_SET 20
#define OCT4_SET 21


#define WAV1_SET 22
#define WAV2_SET 23
#define WAV3_SET 24
#define WAV4_SET 25


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


enum
{
    // DEFINING MIDI notes
    Cn1 = 0,
    Cs1 = 1,
    Dn1 = 2,
    Ds1 = 3,
    En1 = 4,
    Fn1 = 5,
    Fs1 = 6,
    Gn1 = 7,
    Gs1 = 8,
    An1 = 9,
    As1 = 10,
    Bn1 = 11,

    Cn2 = 0 + 12,
    Cs2 = 1 + 12,
    D2 = 2 + 12,
    Ds2 = 3 + 12,
    En2 = 4 + 12,
    Fn2 = 5 + 12,
    Fs2 = 6 + 12,
    Gn2 = 7 + 12,
    Gs2 = 8 + 12,
    An2 = 9 + 12,
    As2 = 10 + 12,
    Bn2 = 11 + 12,

    Cn3 = 0 + 24,
    Cs3 = 1 + 24,
    Dn3 = 2 + 24,
    Ds3 = 3 + 24,
    En3 = 4 + 24,
    Fn3 = 5 + 24,
    Fs3 = 6 + 24,
    Gn3 = 7 + 24,
    Gs3 = 8 + 24,
    An3 = 9 + 24,
    As3 = 10 + 24,
    Bn3 = 11 + 24,

    Cn4 = 0 + 36,
    Cs4 = 1 + 36,
    Dn4 = 2 + 36,
    Ds4 = 3 + 36,
    En4 = 4 + 36,
    Fn4 = 5 + 36,
    Fs4 = 6 + 36,
    Gn4 = 7 + 36,
    Gs4 = 8 + 36,
    An4 = 9 + 36,
    As4 = 10 + 36,
    Bn4 = 11 + 36,
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
const float midiPitchFrequencyMap[] = {
     8.176,     8.662,     9.177,     9.723,    10.301,    10.913,    11.562,    12.250,    12.978,    13.750,    14.568,    15.434,        // C-1 to B-1
    16.352,    17.324,    18.354,    19.445,    20.602,    21.827,    23.125,    24.500,    25.957,    27.500,    29.135,    30.868,        //  C0 to B0
    32.703,    34.648,    36.708,    38.891,    41.203,    43.654,    46.249,    48.999,    51.913,    55.000,    58.270,    61.735,        //  C1 to B1
    65.406,    69.296,    73.416,    77.782,    82.407,    87.307,    92.499,    97.999,   103.826,   110.000,   116.541,   123.471,        //  C2 to B2
   130.813,   138.591,   146.832,   155.563,   164.814,   174.614,   184.997,   195.998,   207.652,   220.000,   233.082,   246.942,        //  C3 to B3
   261.626,   277.183,   293.665,   311.127,   329.628,   349.228,   369.994,   391.995,   415.305,   440.000,   466.164,   493.883,        //  C4 to B4
   523.251,   554.365,   587.330,   622.254,   659.255,   698.456,   739.989,   783.991,   830.609,   880.000,   932.328,   987.767,        //  C5 to B5
  1046.502,  1108.731,  1174.659,  1244.508,  1318.510,  1396.913,  1479.978,  1567.982,  1661.219,  1760.000,  1864.655,  1975.533,        //  C6 to B6
  2093.005,  2217.461,  2349.318,  2489.016,  2637.020,  2793.826,  2959.955,  3135.963,  3322.438,  3520.000,  3729.310,  3951.066,        //  C7 to B7
  4186.009,  4434.922,  4698.636,  4978.032,  5274.041,  5587.652,  5919.911,  6271.927,  6644.875,  7040.000,  7458.620,  7902.133,        //  C8 to B8
  8372.018,  8869.844,  9397.273,  9956.063, 10548.082, 11175.303, 11839.822, 12543.854,                                                    //  C9 to G9
};

uint8_t oldStatePousser[] = {
  1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1,
};
uint8_t oldStateTirer[] = {
  1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1,
};


//
//const byte pousser[36] = {
//  F2, G2, An2, 
//  Bb3, B3, Fs3, 
//  Eb3, D3, An3, 
//  G3, F4, C4, 
//  Bb4, An4, E4, 
//  0, B4, Gs4, 
//  0, Gs4, C4, 
//  Cs4, B4, Fs4, 
//  Eb4, D4, An4, 
//  G4, F4, C4, 
//  Bb4, An4, E4, 
//  D4, B4, F4, 
//};
//
//const byte tirer[36] = {
//  E2, C2, B2, 
//  An2, G2, D2, 
//  Cs2, C2, G2,
//  An2, E2, B3, 
//  Gs3, G3, D3,
//  0, Bb3, Fs3,
//  0, Fs3, D3,
//  Eb3, C4, G4,
//  Cs4, E4, B4, 
//  Gs4, G4, D4,
//  Cs4, C4, G4,
//  An4, E4, Bb4,
//};


const byte pousser[] = {
// 0  1    2  3   4    5 
  Bn4, Gn4, Fn4, 0, Cn4, Cs4,
// 6   7   8   9   10  11 
  Dn4, Gs3, Gn3, Bn3, En3, An3,
//12  13  14   15   16 17 
  Gn3, Cn3, Cs3, En4, 0, 0,
//18  19  20  21   22  23
  Cn1, En1, B1, An1, Gn1, D2,
//24   25  26  27  28  29
  Cs2, Cn2, Gn2, An2, En2, Bn2,
//30   31  32  33 34 35
  Gs2, Gn2, Dn3, 0, 0, 0,
};

const byte tirer[] = {
// 0    1    2  3  4  5 
  Fs4, En4, An4, 0, An3, Ds4,
// 6   7   8   9   10  11 
  Cn4, Bb3, Fn3, An3, Bn3, Gn3,
// 12  13  14   15  16 17 
  Fs3, Bn2, Ds3, Bn3, 0, 0,
//18  19  20  21   22  23
  Gn1, Fn1, D2, Bb1, Dn1, Fs2,
//24   25  26  27  28  29
  Ds2, D2, An2, Gn2, Fn2, Cn3,
//30   31  32  33 34 35
  Bb2, An2, En3, 0, 0, 0
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

const byte pinBourdon[6] = {
  39, 34, 35, 
  36, 37, 38, 
};

const byte noteBourdon[6] = {
  2,4,5,
  7,9,11,
};

Configuration newPresets[6] = {
  Configuration("base", 1,0,4,3,2,1,0,0,0,0,0,0),
  Configuration("test1", 1,0,4,3,2,1,1,1,2,2,0,0),
  Configuration("test2", 1,0,4,3,2,1,2,2,3,3,0,0),
  Configuration("test3", 1,0,4,3,2,1,3,3,4,4,0,0),
  Configuration("test4", 1,0,4,3,2,1,1,2,3,4,0,0),
  Configuration("test5", 1,0,4,3,2,1,1,2,3,4,0,0),
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
  "Fa#/Si"
};

String waveFormNames[5] = {
  "Sin",
  "Cos",
  "Tri",
  "Saw",
  "Square",
};




#endif
