#ifndef __CONCERTINA_H__
#define __CONCERTINA_H__
#include "Arduino.h"
#include <MIDI.h>
#include "concertina_lib/configuration.h"
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
  Configuration("Squ Tri",2,11, -1 ,-1 ,-2,-3 ,4,4,2,0 , 250, 250),
  Configuration("Bass",   4,11, -1, -2, -2,-3, 0,4,2,0 , 200, 200),
  Configuration("Squ Tri",1,11, -3 ,-2 ,-2,-3 ,4,4,2,0 , 200, 200),
  Configuration("Squ Tri",1,11, -3 ,-2 ,-2,-3 ,4,4,2,0 , 200, 200),
  Configuration("Squ Tri",1,11, -3 ,-2 ,-2,-3 ,4,4,2,0 , 200, 200),
  Configuration("Squ Tri",1,11, -3 ,-2 ,-2,-3 ,4,4,2,0 , 200, 200),
  Configuration("Squ Tri",1,11, -3 ,-2 ,-2,-3 ,4,4,2,0 , 200, 200)

};

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
    Dn2 = 2 + 12,
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

int MatriceNote[72] = {
  // 0         1         2          3        4         5         6         7         8        9         10       11
  NOTE_C1,  NOTE_CS1, NOTE_D1,  NOTE_DS1, NOTE_E1,  NOTE_F1,  NOTE_FS1, NOTE_G1,  NOTE_GS1, NOTE_A1,  NOTE_AS1, NOTE_B1,
  // 12        13        14         15       16       17        18        19        20       21         22       23
  NOTE_C2,  NOTE_CS2, NOTE_D2,  NOTE_DS2, NOTE_E2,  NOTE_F2,  NOTE_FS2, NOTE_G2,  NOTE_GS2, NOTE_A2,  NOTE_AS2, NOTE_B2,
  // 24        25        26         27       28       29        30        31        32       33         34       35
  NOTE_C3,  NOTE_CS3, NOTE_D3,  NOTE_DS3, NOTE_E3,  NOTE_F3,  NOTE_FS3, NOTE_G3,  NOTE_GS3, NOTE_A3,  NOTE_AS3, NOTE_B3,
  // 36        37        38         39       40       41        42        43        44       45         46       47
  NOTE_C4,  NOTE_CS4, NOTE_D4,  NOTE_DS4, NOTE_E4,  NOTE_F4,  NOTE_FS4, NOTE_G4,  NOTE_GS4, NOTE_A4,  NOTE_AS4, NOTE_B4,
  // 48        49        50         51       52       53        54        55        56       57         58       59
  NOTE_C5,  NOTE_CS5, NOTE_D5,  NOTE_DS5, NOTE_E5,  NOTE_F5,  NOTE_FS5, NOTE_G5,  NOTE_GS5, NOTE_A5,  NOTE_AS5, NOTE_B5,
  // 60        61        62         63       64       65        66        67        68       69         70       71
  NOTE_C6,  NOTE_CS6, NOTE_D6,  NOTE_DS6, NOTE_E6,  NOTE_F6,  NOTE_FS6, NOTE_G6,  NOTE_GS6, NOTE_A6,  NOTE_AS6, NOTE_B6,
};

// int pousserSynthNew[] = {
//   33, 31, 37, 36, 32, 35,
//   28, 31, 24, 25, 19, 26,
//   23, 21, 16, 12, 12, 38,
//   23, 14, 53, 21, 59, 52,
//   55, 48, 49, 50, 43, 42,
//   47, 40, 45, 43, 16, 19,
// };
// int tirerSynthNew[] = {
//   31, 33, 39, 35, 34, 36,
//   29, 33, 26, 30, 23, 30,
//   26, 22, 17, 19, 43, 40,
//   36, 40, 57, 47, 54, 47,
//   52, 45, 51, 48, 41, 46,
//   45, 38, 43, 42, 38, 33
// };

int drum[] = {
  Cs2, An1, 0,   0,   Cn2, Bn1,
  As1, Gs1, Gn1, Fs1, En1, Fn1,
  Dn1, Ds1, Cn1, Cs1, 0,   Dn2,
  0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0
};

int pousser[] = {
  Dn3, Gn3, Cn3, Bn4, En4, Fn4, //5
  Gn4, En4, Cn4, Dn4, Gn3, Cs2, //11
  Cn2, Gn1, Dn2, Gs3, Bn3, En3, //17
  An3, Gn3, Cn3, Cs3, An2, Cn1, //23
  En3, Dn3, Gn2, Gs2, Bn2, En2, //29
  An3, Gn2, Bn2, Gn2, An5, Gn2, //17
};
int tirer[] = {
  0,   0,   0, Fs4, Bn3, An4,
  En4, Ds4, An3, Cn4, Fn3, Ds2,
  Dn2, Bn1, Fs2, As3, An3, Dn3,
  Gn3, Fs3, Bn2, Ds3, Gn2, Gn1,
  En3, En3, An2, As2, Cn3, Fn2,
  Gn2, An2, An2, 0,   0,   0,
};

int pinButton[] = {
  0,  3,  4,  5,  6,  7,
  8,  9,  10, 11, 12, 16,
  17, 20, 21, 24, 25, 26,
  27, 28, 29, 30, 31, 32,
  33, 34, 35, 36, 37, 38,
  39, 40, 41, 50, 52, 48,
};
//
// int tirerSynth[] = {
//   0, 0, 0, NOTE_B4, NOTE_E4, NOTE_F4,
//   NOTE_G4, NOTE_E4, NOTE_C4, NOTE_D4, NOTE_G3, NOTE_CS2,
//   NOTE_C2, NOTE_G1, NOTE_D2, NOTE_GS3, NOTE_B3, NOTE_E3,
//   NOTE_A3, NOTE_G3, NOTE_C3, NOTE_CS3, NOTE_A2, NOTE_C1,
//   0, NOTE_D3, NOTE_G2, NOTE_GS2, NOTE_B2, NOTE_E2,
//   NOTE_A3, NOTE_G2, NOTE_B2, 0, 0, 0,
// };
// int pousserSynth[] = {
//   0, 0, 0, NOTE_FS4, NOTE_B3, NOTE_A4,
//   NOTE_E4, NOTE_DS4, NOTE_A3, NOTE_C4, NOTE_F3, NOTE_DS2,
//   NOTE_D2, NOTE_B1, NOTE_FS2, NOTE_AS3, NOTE_A3, NOTE_D3,
//   NOTE_G3, NOTE_FS3, NOTE_B2, NOTE_DS3, NOTE_G2, NOTE_G1,
//   0  , NOTE_E3, NOTE_A2, NOTE_AS2, NOTE_C3, NOTE_F2,
//   NOTE_G2, NOTE_A2, NOTE_A2, 0, 0, 0,
// };

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
