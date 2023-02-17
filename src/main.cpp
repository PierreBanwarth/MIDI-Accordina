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
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>



// GUItool: begin automatically generated code
byte waveformPitch[16][8] = {
{255, 255, 255, 255, 255, 255, 255, 255},   // Default to 255 as an "unused" indicator as it's outside the range of pitch values 0-127
{255, 255, 255, 255, 255, 255, 255, 255},
{255, 255, 255, 255, 255, 255, 255, 255},
{255, 255, 255, 255, 255, 255, 255, 255},
{255, 255, 255, 255, 255, 255, 255, 255},
{255, 255, 255, 255, 255, 255, 255, 255},
{255, 255, 255, 255, 255, 255, 255, 255},
{255, 255, 255, 255, 255, 255, 255, 255},
{255, 255, 255, 255, 255, 255, 255, 255},
{255, 255, 255, 255, 255, 255, 255, 255},
{255, 255, 255, 255, 255, 255, 255, 255},
{255, 255, 255, 255, 255, 255, 255, 255},
{255, 255, 255, 255, 255, 255, 255, 255},
{255, 255, 255, 255, 255, 255, 255, 255},
{255, 255, 255, 255, 255, 255, 255, 255},
{255, 255, 255, 255, 255, 255, 255, 255},
};


// Teensy Audio library configuration (visualizer: https://www.pjrc.com/teensy/gui/index.html)
// 128 waveforms to 128 envelopes (8 note polyphony per channel x 16) routed to 32 mixers to 8 mixers to 2 mixers to 1 mixer to audio out (MQS)
AudioSynthWaveform      waveformCh[16][8];
AudioEffectEnvelope     envelopeCh[16][8];
AudioMixer4             firstMixer[32];
AudioMixer4             secondMixer[8];
AudioMixer4             thirdMixer[2];
AudioMixer4             outMixer;
AudioConnection         ch00WaveformToEnvelope0(waveformCh[0][0], 0, envelopeCh[0][0], 0);
AudioConnection         ch00WaveformToEnvelope1(waveformCh[0][1], 0, envelopeCh[0][1], 0);
AudioConnection         ch00WaveformToEnvelope2(waveformCh[0][2], 0, envelopeCh[0][2], 0);
AudioConnection         ch00WaveformToEnvelope3(waveformCh[0][3], 0, envelopeCh[0][3], 0);
AudioConnection         ch00WaveformToEnvelope4(waveformCh[0][4], 0, envelopeCh[0][4], 0);
AudioConnection         ch00WaveformToEnvelope5(waveformCh[0][5], 0, envelopeCh[0][5], 0);
AudioConnection         ch00WaveformToEnvelope6(waveformCh[0][6], 0, envelopeCh[0][6], 0);
AudioConnection         ch00WaveformToEnvelope7(waveformCh[0][7], 0, envelopeCh[0][7], 0);
AudioConnection         ch01WaveformToEnvelope0(waveformCh[1][0], 0, envelopeCh[1][0], 0);
AudioConnection         ch01WaveformToEnvelope1(waveformCh[1][1], 0, envelopeCh[1][1], 0);
AudioConnection         ch01WaveformToEnvelope2(waveformCh[1][2], 0, envelopeCh[1][2], 0);
AudioConnection         ch01WaveformToEnvelope3(waveformCh[1][3], 0, envelopeCh[1][3], 0);
AudioConnection         ch01WaveformToEnvelope4(waveformCh[1][4], 0, envelopeCh[1][4], 0);
AudioConnection         ch01WaveformToEnvelope5(waveformCh[1][5], 0, envelopeCh[1][5], 0);
AudioConnection         ch01WaveformToEnvelope6(waveformCh[1][6], 0, envelopeCh[1][6], 0);
AudioConnection         ch01WaveformToEnvelope7(waveformCh[1][7], 0, envelopeCh[1][7], 0);
AudioConnection         ch02WaveformToEnvelope0(waveformCh[2][0], 0, envelopeCh[2][0], 0);
AudioConnection         ch02WaveformToEnvelope1(waveformCh[2][1], 0, envelopeCh[2][1], 0);
AudioConnection         ch02WaveformToEnvelope2(waveformCh[2][2], 0, envelopeCh[2][2], 0);
AudioConnection         ch02WaveformToEnvelope3(waveformCh[2][3], 0, envelopeCh[2][3], 0);
AudioConnection         ch02WaveformToEnvelope4(waveformCh[2][4], 0, envelopeCh[2][4], 0);
AudioConnection         ch02WaveformToEnvelope5(waveformCh[2][5], 0, envelopeCh[2][5], 0);
AudioConnection         ch02WaveformToEnvelope6(waveformCh[2][6], 0, envelopeCh[2][6], 0);
AudioConnection         ch02WaveformToEnvelope7(waveformCh[2][7], 0, envelopeCh[2][7], 0);
AudioConnection         ch03WaveformToEnvelope0(waveformCh[3][0], 0, envelopeCh[3][0], 0);
AudioConnection         ch03WaveformToEnvelope1(waveformCh[3][1], 0, envelopeCh[3][1], 0);
AudioConnection         ch03WaveformToEnvelope2(waveformCh[3][2], 0, envelopeCh[3][2], 0);
AudioConnection         ch03WaveformToEnvelope3(waveformCh[3][3], 0, envelopeCh[3][3], 0);
AudioConnection         ch03WaveformToEnvelope4(waveformCh[3][4], 0, envelopeCh[3][4], 0);
AudioConnection         ch03WaveformToEnvelope5(waveformCh[3][5], 0, envelopeCh[3][5], 0);
AudioConnection         ch03WaveformToEnvelope6(waveformCh[3][6], 0, envelopeCh[3][6], 0);
AudioConnection         ch03WaveformToEnvelope7(waveformCh[3][7], 0, envelopeCh[3][7], 0);
AudioConnection         ch04WaveformToEnvelope0(waveformCh[4][0], 0, envelopeCh[4][0], 0);
AudioConnection         ch04WaveformToEnvelope1(waveformCh[4][1], 0, envelopeCh[4][1], 0);
AudioConnection         ch04WaveformToEnvelope2(waveformCh[4][2], 0, envelopeCh[4][2], 0);
AudioConnection         ch04WaveformToEnvelope3(waveformCh[4][3], 0, envelopeCh[4][3], 0);
AudioConnection         ch04WaveformToEnvelope4(waveformCh[4][4], 0, envelopeCh[4][4], 0);
AudioConnection         ch04WaveformToEnvelope5(waveformCh[4][5], 0, envelopeCh[4][5], 0);
AudioConnection         ch04WaveformToEnvelope6(waveformCh[4][6], 0, envelopeCh[4][6], 0);
AudioConnection         ch04WaveformToEnvelope7(waveformCh[4][7], 0, envelopeCh[4][7], 0);
AudioConnection         ch05WaveformToEnvelope0(waveformCh[5][0], 0, envelopeCh[5][0], 0);
AudioConnection         ch05WaveformToEnvelope1(waveformCh[5][1], 0, envelopeCh[5][1], 0);
AudioConnection         ch05WaveformToEnvelope2(waveformCh[5][2], 0, envelopeCh[5][2], 0);
AudioConnection         ch05WaveformToEnvelope3(waveformCh[5][3], 0, envelopeCh[5][3], 0);
AudioConnection         ch05WaveformToEnvelope4(waveformCh[5][4], 0, envelopeCh[5][4], 0);
AudioConnection         ch05WaveformToEnvelope5(waveformCh[5][5], 0, envelopeCh[5][5], 0);
AudioConnection         ch05WaveformToEnvelope6(waveformCh[5][6], 0, envelopeCh[5][6], 0);
AudioConnection         ch05WaveformToEnvelope7(waveformCh[5][7], 0, envelopeCh[5][7], 0);
AudioConnection         ch06WaveformToEnvelope0(waveformCh[6][0], 0, envelopeCh[6][0], 0);
AudioConnection         ch06WaveformToEnvelope1(waveformCh[6][1], 0, envelopeCh[6][1], 0);
AudioConnection         ch06WaveformToEnvelope2(waveformCh[6][2], 0, envelopeCh[6][2], 0);
AudioConnection         ch06WaveformToEnvelope3(waveformCh[6][3], 0, envelopeCh[6][3], 0);
AudioConnection         ch06WaveformToEnvelope4(waveformCh[6][4], 0, envelopeCh[6][4], 0);
AudioConnection         ch06WaveformToEnvelope5(waveformCh[6][5], 0, envelopeCh[6][5], 0);
AudioConnection         ch06WaveformToEnvelope6(waveformCh[6][6], 0, envelopeCh[6][6], 0);
AudioConnection         ch06WaveformToEnvelope7(waveformCh[6][7], 0, envelopeCh[6][7], 0);
AudioConnection         ch07WaveformToEnvelope0(waveformCh[7][0], 0, envelopeCh[7][0], 0);
AudioConnection         ch07WaveformToEnvelope1(waveformCh[7][1], 0, envelopeCh[7][1], 0);
AudioConnection         ch07WaveformToEnvelope2(waveformCh[7][2], 0, envelopeCh[7][2], 0);
AudioConnection         ch07WaveformToEnvelope3(waveformCh[7][3], 0, envelopeCh[7][3], 0);
AudioConnection         ch07WaveformToEnvelope4(waveformCh[7][4], 0, envelopeCh[7][4], 0);
AudioConnection         ch07WaveformToEnvelope5(waveformCh[7][5], 0, envelopeCh[7][5], 0);
AudioConnection         ch07WaveformToEnvelope6(waveformCh[7][6], 0, envelopeCh[7][6], 0);
AudioConnection         ch07WaveformToEnvelope7(waveformCh[7][7], 0, envelopeCh[7][7], 0);
AudioConnection         ch08WaveformToEnvelope0(waveformCh[8][0], 0, envelopeCh[8][0], 0);
AudioConnection         ch08WaveformToEnvelope1(waveformCh[8][1], 0, envelopeCh[8][1], 0);
AudioConnection         ch08WaveformToEnvelope2(waveformCh[8][2], 0, envelopeCh[8][2], 0);
AudioConnection         ch08WaveformToEnvelope3(waveformCh[8][3], 0, envelopeCh[8][3], 0);
AudioConnection         ch08WaveformToEnvelope4(waveformCh[8][4], 0, envelopeCh[8][4], 0);
AudioConnection         ch08WaveformToEnvelope5(waveformCh[8][5], 0, envelopeCh[8][5], 0);
AudioConnection         ch08WaveformToEnvelope6(waveformCh[8][6], 0, envelopeCh[8][6], 0);
AudioConnection         ch08WaveformToEnvelope7(waveformCh[8][7], 0, envelopeCh[8][7], 0);
AudioConnection         ch09WaveformToEnvelope0(waveformCh[9][0], 0, envelopeCh[9][0], 0);
AudioConnection         ch09WaveformToEnvelope1(waveformCh[9][1], 0, envelopeCh[9][1], 0);
AudioConnection         ch09WaveformToEnvelope2(waveformCh[9][2], 0, envelopeCh[9][2], 0);
AudioConnection         ch09WaveformToEnvelope3(waveformCh[9][3], 0, envelopeCh[9][3], 0);
AudioConnection         ch09WaveformToEnvelope4(waveformCh[9][4], 0, envelopeCh[9][4], 0);
AudioConnection         ch09WaveformToEnvelope5(waveformCh[9][5], 0, envelopeCh[9][5], 0);
AudioConnection         ch09WaveformToEnvelope6(waveformCh[9][6], 0, envelopeCh[9][6], 0);
AudioConnection         ch09WaveformToEnvelope7(waveformCh[9][7], 0, envelopeCh[9][7], 0);
AudioConnection         ch10WaveformToEnvelope0(waveformCh[10][0], 0, envelopeCh[10][0], 0);
AudioConnection         ch10WaveformToEnvelope1(waveformCh[10][1], 0, envelopeCh[10][1], 0);
AudioConnection         ch10WaveformToEnvelope2(waveformCh[10][2], 0, envelopeCh[10][2], 0);
AudioConnection         ch10WaveformToEnvelope3(waveformCh[10][3], 0, envelopeCh[10][3], 0);
AudioConnection         ch10WaveformToEnvelope4(waveformCh[10][4], 0, envelopeCh[10][4], 0);
AudioConnection         ch10WaveformToEnvelope5(waveformCh[10][5], 0, envelopeCh[10][5], 0);
AudioConnection         ch10WaveformToEnvelope6(waveformCh[10][6], 0, envelopeCh[10][6], 0);
AudioConnection         ch10WaveformToEnvelope7(waveformCh[10][7], 0, envelopeCh[10][7], 0);
AudioConnection         ch11WaveformToEnvelope0(waveformCh[11][0], 0, envelopeCh[11][0], 0);
AudioConnection         ch11WaveformToEnvelope1(waveformCh[11][1], 0, envelopeCh[11][1], 0);
AudioConnection         ch11WaveformToEnvelope2(waveformCh[11][2], 0, envelopeCh[11][2], 0);
AudioConnection         ch11WaveformToEnvelope3(waveformCh[11][3], 0, envelopeCh[11][3], 0);
AudioConnection         ch11WaveformToEnvelope4(waveformCh[11][4], 0, envelopeCh[11][4], 0);
AudioConnection         ch11WaveformToEnvelope5(waveformCh[11][5], 0, envelopeCh[11][5], 0);
AudioConnection         ch11WaveformToEnvelope6(waveformCh[11][6], 0, envelopeCh[11][6], 0);
AudioConnection         ch11WaveformToEnvelope7(waveformCh[11][7], 0, envelopeCh[11][7], 0);
AudioConnection         ch12WaveformToEnvelope0(waveformCh[12][0], 0, envelopeCh[12][0], 0);
AudioConnection         ch12WaveformToEnvelope1(waveformCh[12][1], 0, envelopeCh[12][1], 0);
AudioConnection         ch12WaveformToEnvelope2(waveformCh[12][2], 0, envelopeCh[12][2], 0);
AudioConnection         ch12WaveformToEnvelope3(waveformCh[12][3], 0, envelopeCh[12][3], 0);
AudioConnection         ch12WaveformToEnvelope4(waveformCh[12][4], 0, envelopeCh[12][4], 0);
AudioConnection         ch12WaveformToEnvelope5(waveformCh[12][5], 0, envelopeCh[12][5], 0);
AudioConnection         ch12WaveformToEnvelope6(waveformCh[12][6], 0, envelopeCh[12][6], 0);
AudioConnection         ch12WaveformToEnvelope7(waveformCh[12][7], 0, envelopeCh[12][7], 0);
AudioConnection         ch13WaveformToEnvelope0(waveformCh[13][0], 0, envelopeCh[13][0], 0);
AudioConnection         ch13WaveformToEnvelope1(waveformCh[13][1], 0, envelopeCh[13][1], 0);
AudioConnection         ch13WaveformToEnvelope2(waveformCh[13][2], 0, envelopeCh[13][2], 0);
AudioConnection         ch13WaveformToEnvelope3(waveformCh[13][3], 0, envelopeCh[13][3], 0);
AudioConnection         ch13WaveformToEnvelope4(waveformCh[13][4], 0, envelopeCh[13][4], 0);
AudioConnection         ch13WaveformToEnvelope5(waveformCh[13][5], 0, envelopeCh[13][5], 0);
AudioConnection         ch13WaveformToEnvelope6(waveformCh[13][6], 0, envelopeCh[13][6], 0);
AudioConnection         ch13WaveformToEnvelope7(waveformCh[13][7], 0, envelopeCh[13][7], 0);
AudioConnection         ch14WaveformToEnvelope0(waveformCh[14][0], 0, envelopeCh[14][0], 0);
AudioConnection         ch14WaveformToEnvelope1(waveformCh[14][1], 0, envelopeCh[14][1], 0);
AudioConnection         ch14WaveformToEnvelope2(waveformCh[14][2], 0, envelopeCh[14][2], 0);
AudioConnection         ch14WaveformToEnvelope3(waveformCh[14][3], 0, envelopeCh[14][3], 0);
AudioConnection         ch14WaveformToEnvelope4(waveformCh[14][4], 0, envelopeCh[14][4], 0);
AudioConnection         ch14WaveformToEnvelope5(waveformCh[14][5], 0, envelopeCh[14][5], 0);
AudioConnection         ch14WaveformToEnvelope6(waveformCh[14][6], 0, envelopeCh[14][6], 0);
AudioConnection         ch14WaveformToEnvelope7(waveformCh[14][7], 0, envelopeCh[14][7], 0);
AudioConnection         ch15WaveformToEnvelope0(waveformCh[15][0], 0, envelopeCh[15][0], 0);
AudioConnection         ch15WaveformToEnvelope1(waveformCh[15][1], 0, envelopeCh[15][1], 0);
AudioConnection         ch15WaveformToEnvelope2(waveformCh[15][2], 0, envelopeCh[15][2], 0);
AudioConnection         ch15WaveformToEnvelope3(waveformCh[15][3], 0, envelopeCh[15][3], 0);
AudioConnection         ch15WaveformToEnvelope4(waveformCh[15][4], 0, envelopeCh[15][4], 0);
AudioConnection         ch15WaveformToEnvelope5(waveformCh[15][5], 0, envelopeCh[15][5], 0);
AudioConnection         ch15WaveformToEnvelope6(waveformCh[15][6], 0, envelopeCh[15][6], 0);
AudioConnection         ch15WaveformToEnvelope7(waveformCh[15][7], 0, envelopeCh[15][7], 0);
AudioConnection         ch00envelopeToMixer0(envelopeCh[0][0], 0, firstMixer[0], 0);
AudioConnection         ch00envelopeToMixer1(envelopeCh[0][1], 0, firstMixer[0], 1);
AudioConnection         ch00envelopeToMixer2(envelopeCh[0][2], 0, firstMixer[0], 2);
AudioConnection         ch00envelopeToMixer3(envelopeCh[0][3], 0, firstMixer[0], 3);
AudioConnection         ch00envelopeToMixer4(envelopeCh[0][4], 0, firstMixer[1], 0);
AudioConnection         ch00envelopeToMixer5(envelopeCh[0][5], 0, firstMixer[1], 1);
AudioConnection         ch00envelopeToMixer6(envelopeCh[0][6], 0, firstMixer[1], 2);
AudioConnection         ch00envelopeToMixer7(envelopeCh[0][7], 0, firstMixer[1], 3);
AudioConnection         ch01envelopeToMixer0(envelopeCh[1][0], 0, firstMixer[2], 0);
AudioConnection         ch01envelopeToMixer1(envelopeCh[1][1], 0, firstMixer[2], 1);
AudioConnection         ch01envelopeToMixer2(envelopeCh[1][2], 0, firstMixer[2], 2);
AudioConnection         ch01envelopeToMixer3(envelopeCh[1][3], 0, firstMixer[2], 3);
AudioConnection         ch01envelopeToMixer4(envelopeCh[1][4], 0, firstMixer[3], 0);
AudioConnection         ch01envelopeToMixer5(envelopeCh[1][5], 0, firstMixer[3], 1);
AudioConnection         ch01envelopeToMixer6(envelopeCh[1][6], 0, firstMixer[3], 2);
AudioConnection         ch01envelopeToMixer7(envelopeCh[1][7], 0, firstMixer[3], 3);
AudioConnection         ch02envelopeToMixer0(envelopeCh[2][0], 0, firstMixer[4], 0);
AudioConnection         ch02envelopeToMixer1(envelopeCh[2][1], 0, firstMixer[4], 1);
AudioConnection         ch02envelopeToMixer2(envelopeCh[2][2], 0, firstMixer[4], 2);
AudioConnection         ch02envelopeToMixer3(envelopeCh[2][3], 0, firstMixer[4], 3);
AudioConnection         ch02envelopeToMixer4(envelopeCh[2][4], 0, firstMixer[5], 0);
AudioConnection         ch02envelopeToMixer5(envelopeCh[2][5], 0, firstMixer[5], 1);
AudioConnection         ch02envelopeToMixer6(envelopeCh[2][6], 0, firstMixer[5], 2);
AudioConnection         ch02envelopeToMixer7(envelopeCh[2][7], 0, firstMixer[5], 3);
AudioConnection         ch03envelopeToMixer0(envelopeCh[3][0], 0, firstMixer[6], 0);
AudioConnection         ch03envelopeToMixer1(envelopeCh[3][1], 0, firstMixer[6], 1);
AudioConnection         ch03envelopeToMixer2(envelopeCh[3][2], 0, firstMixer[6], 2);
AudioConnection         ch03envelopeToMixer3(envelopeCh[3][3], 0, firstMixer[6], 3);
AudioConnection         ch03envelopeToMixer4(envelopeCh[3][4], 0, firstMixer[7], 0);
AudioConnection         ch03envelopeToMixer5(envelopeCh[3][5], 0, firstMixer[7], 1);
AudioConnection         ch03envelopeToMixer6(envelopeCh[3][6], 0, firstMixer[7], 2);
AudioConnection         ch03envelopeToMixer7(envelopeCh[3][7], 0, firstMixer[7], 3);
AudioConnection         ch04envelopeToMixer0(envelopeCh[4][0], 0, firstMixer[8], 0);
AudioConnection         ch04envelopeToMixer1(envelopeCh[4][1], 0, firstMixer[8], 1);
AudioConnection         ch04envelopeToMixer2(envelopeCh[4][2], 0, firstMixer[8], 2);
AudioConnection         ch04envelopeToMixer3(envelopeCh[4][3], 0, firstMixer[8], 3);
AudioConnection         ch04envelopeToMixer4(envelopeCh[4][4], 0, firstMixer[9], 0);
AudioConnection         ch04envelopeToMixer5(envelopeCh[4][5], 0, firstMixer[9], 1);
AudioConnection         ch04envelopeToMixer6(envelopeCh[4][6], 0, firstMixer[9], 2);
AudioConnection         ch04envelopeToMixer7(envelopeCh[4][7], 0, firstMixer[9], 3);
AudioConnection         ch05envelopeToMixer0(envelopeCh[5][0], 0, firstMixer[10], 0);
AudioConnection         ch05envelopeToMixer1(envelopeCh[5][1], 0, firstMixer[10], 1);
AudioConnection         ch05envelopeToMixer2(envelopeCh[5][2], 0, firstMixer[10], 2);
AudioConnection         ch05envelopeToMixer3(envelopeCh[5][3], 0, firstMixer[10], 3);
AudioConnection         ch05envelopeToMixer4(envelopeCh[5][4], 0, firstMixer[11], 0);
AudioConnection         ch05envelopeToMixer5(envelopeCh[5][5], 0, firstMixer[11], 1);
AudioConnection         ch05envelopeToMixer6(envelopeCh[5][6], 0, firstMixer[11], 2);
AudioConnection         ch05envelopeToMixer7(envelopeCh[5][7], 0, firstMixer[11], 3);
AudioConnection         ch06envelopeToMixer0(envelopeCh[6][0], 0, firstMixer[12], 0);
AudioConnection         ch06envelopeToMixer1(envelopeCh[6][1], 0, firstMixer[12], 1);
AudioConnection         ch06envelopeToMixer2(envelopeCh[6][2], 0, firstMixer[12], 2);
AudioConnection         ch06envelopeToMixer3(envelopeCh[6][3], 0, firstMixer[12], 3);
AudioConnection         ch06envelopeToMixer4(envelopeCh[6][4], 0, firstMixer[13], 0);
AudioConnection         ch06envelopeToMixer5(envelopeCh[6][5], 0, firstMixer[13], 1);
AudioConnection         ch06envelopeToMixer6(envelopeCh[6][6], 0, firstMixer[13], 2);
AudioConnection         ch06envelopeToMixer7(envelopeCh[6][7], 0, firstMixer[13], 3);
AudioConnection         ch07envelopeToMixer0(envelopeCh[7][0], 0, firstMixer[14], 0);
AudioConnection         ch07envelopeToMixer1(envelopeCh[7][1], 0, firstMixer[14], 1);
AudioConnection         ch07envelopeToMixer2(envelopeCh[7][2], 0, firstMixer[14], 2);
AudioConnection         ch07envelopeToMixer3(envelopeCh[7][3], 0, firstMixer[14], 3);
AudioConnection         ch07envelopeToMixer4(envelopeCh[7][4], 0, firstMixer[15], 0);
AudioConnection         ch07envelopeToMixer5(envelopeCh[7][5], 0, firstMixer[15], 1);
AudioConnection         ch07envelopeToMixer6(envelopeCh[7][6], 0, firstMixer[15], 2);
AudioConnection         ch07envelopeToMixer7(envelopeCh[7][7], 0, firstMixer[15], 3);
AudioConnection         ch08envelopeToMixer0(envelopeCh[8][0], 0, firstMixer[16], 0);
AudioConnection         ch08envelopeToMixer1(envelopeCh[8][1], 0, firstMixer[16], 1);
AudioConnection         ch08envelopeToMixer2(envelopeCh[8][2], 0, firstMixer[16], 2);
AudioConnection         ch08envelopeToMixer3(envelopeCh[8][3], 0, firstMixer[16], 3);
AudioConnection         ch08envelopeToMixer4(envelopeCh[8][4], 0, firstMixer[17], 0);
AudioConnection         ch08envelopeToMixer5(envelopeCh[8][5], 0, firstMixer[17], 1);
AudioConnection         ch08envelopeToMixer6(envelopeCh[8][6], 0, firstMixer[17], 2);
AudioConnection         ch08envelopeToMixer7(envelopeCh[8][7], 0, firstMixer[17], 3);
AudioConnection         ch09envelopeToMixer0(envelopeCh[9][0], 0, firstMixer[18], 0);
AudioConnection         ch09envelopeToMixer1(envelopeCh[9][1], 0, firstMixer[18], 1);
AudioConnection         ch09envelopeToMixer2(envelopeCh[9][2], 0, firstMixer[18], 2);
AudioConnection         ch09envelopeToMixer3(envelopeCh[9][3], 0, firstMixer[18], 3);
AudioConnection         ch09envelopeToMixer4(envelopeCh[9][4], 0, firstMixer[19], 0);
AudioConnection         ch09envelopeToMixer5(envelopeCh[9][5], 0, firstMixer[19], 1);
AudioConnection         ch09envelopeToMixer6(envelopeCh[9][6], 0, firstMixer[19], 2);
AudioConnection         ch09envelopeToMixer7(envelopeCh[9][7], 0, firstMixer[19], 3);
AudioConnection         ch10envelopeToMixer0(envelopeCh[10][0], 0, firstMixer[20], 0);
AudioConnection         ch10envelopeToMixer1(envelopeCh[10][1], 0, firstMixer[20], 1);
AudioConnection         ch10envelopeToMixer2(envelopeCh[10][2], 0, firstMixer[20], 2);
AudioConnection         ch10envelopeToMixer3(envelopeCh[10][3], 0, firstMixer[20], 3);
AudioConnection         ch10envelopeToMixer4(envelopeCh[10][4], 0, firstMixer[21], 0);
AudioConnection         ch10envelopeToMixer5(envelopeCh[10][5], 0, firstMixer[21], 1);
AudioConnection         ch10envelopeToMixer6(envelopeCh[10][6], 0, firstMixer[21], 2);
AudioConnection         ch10envelopeToMixer7(envelopeCh[10][7], 0, firstMixer[21], 3);
AudioConnection         ch11envelopeToMixer0(envelopeCh[11][0], 0, firstMixer[22], 0);
AudioConnection         ch11envelopeToMixer1(envelopeCh[11][1], 0, firstMixer[22], 1);
AudioConnection         ch11envelopeToMixer2(envelopeCh[11][2], 0, firstMixer[22], 2);
AudioConnection         ch11envelopeToMixer3(envelopeCh[11][3], 0, firstMixer[22], 3);
AudioConnection         ch11envelopeToMixer4(envelopeCh[11][4], 0, firstMixer[23], 0);
AudioConnection         ch11envelopeToMixer5(envelopeCh[11][5], 0, firstMixer[23], 1);
AudioConnection         ch11envelopeToMixer6(envelopeCh[11][6], 0, firstMixer[23], 2);
AudioConnection         ch11envelopeToMixer7(envelopeCh[11][7], 0, firstMixer[23], 3);
AudioConnection         ch12envelopeToMixer0(envelopeCh[12][0], 0, firstMixer[24], 0);
AudioConnection         ch12envelopeToMixer1(envelopeCh[12][1], 0, firstMixer[24], 1);
AudioConnection         ch12envelopeToMixer2(envelopeCh[12][2], 0, firstMixer[24], 2);
AudioConnection         ch12envelopeToMixer3(envelopeCh[12][3], 0, firstMixer[24], 3);
AudioConnection         ch12envelopeToMixer4(envelopeCh[12][4], 0, firstMixer[25], 0);
AudioConnection         ch12envelopeToMixer5(envelopeCh[12][5], 0, firstMixer[25], 1);
AudioConnection         ch12envelopeToMixer6(envelopeCh[12][6], 0, firstMixer[25], 2);
AudioConnection         ch12envelopeToMixer7(envelopeCh[12][7], 0, firstMixer[25], 3);
AudioConnection         ch13envelopeToMixer0(envelopeCh[13][0], 0, firstMixer[26], 0);
AudioConnection         ch13envelopeToMixer1(envelopeCh[13][1], 0, firstMixer[26], 1);
AudioConnection         ch13envelopeToMixer2(envelopeCh[13][2], 0, firstMixer[26], 2);
AudioConnection         ch13envelopeToMixer3(envelopeCh[13][3], 0, firstMixer[26], 3);
AudioConnection         ch13envelopeToMixer4(envelopeCh[13][4], 0, firstMixer[27], 0);
AudioConnection         ch13envelopeToMixer5(envelopeCh[13][5], 0, firstMixer[27], 1);
AudioConnection         ch13envelopeToMixer6(envelopeCh[13][6], 0, firstMixer[27], 2);
AudioConnection         ch13envelopeToMixer7(envelopeCh[13][7], 0, firstMixer[27], 3);
AudioConnection         ch14envelopeToMixer0(envelopeCh[14][0], 0, firstMixer[28], 0);
AudioConnection         ch14envelopeToMixer1(envelopeCh[14][1], 0, firstMixer[28], 1);
AudioConnection         ch14envelopeToMixer2(envelopeCh[14][2], 0, firstMixer[28], 2);
AudioConnection         ch14envelopeToMixer3(envelopeCh[14][3], 0, firstMixer[28], 3);
AudioConnection         ch14envelopeToMixer4(envelopeCh[14][4], 0, firstMixer[29], 0);
AudioConnection         ch14envelopeToMixer5(envelopeCh[14][5], 0, firstMixer[29], 1);
AudioConnection         ch14envelopeToMixer6(envelopeCh[14][6], 0, firstMixer[29], 2);
AudioConnection         ch14envelopeToMixer7(envelopeCh[14][7], 0, firstMixer[29], 3);
AudioConnection         ch15envelopeToMixer0(envelopeCh[15][0], 0, firstMixer[30], 0);
AudioConnection         ch15envelopeToMixer1(envelopeCh[15][1], 0, firstMixer[30], 1);
AudioConnection         ch15envelopeToMixer2(envelopeCh[15][2], 0, firstMixer[30], 2);
AudioConnection         ch15envelopeToMixer3(envelopeCh[15][3], 0, firstMixer[30], 3);
AudioConnection         ch15envelopeToMixer4(envelopeCh[15][4], 0, firstMixer[31], 0);
AudioConnection         ch15envelopeToMixer5(envelopeCh[15][5], 0, firstMixer[31], 1);
AudioConnection         ch15envelopeToMixer6(envelopeCh[15][6], 0, firstMixer[31], 2);
AudioConnection         ch15envelopeToMixer7(envelopeCh[15][7], 0, firstMixer[31], 3);
AudioConnection         firstMixerToSecondMixer00(firstMixer[0], 0, secondMixer[0], 0);
AudioConnection         firstMixerToSecondMixer01(firstMixer[1], 0, secondMixer[0], 1);
AudioConnection         firstMixerToSecondMixer02(firstMixer[2], 0, secondMixer[0], 2);
AudioConnection         firstMixerToSecondMixer03(firstMixer[3], 0, secondMixer[0], 3);
AudioConnection         firstMixerToSecondMixer04(firstMixer[4], 0, secondMixer[1], 0);
AudioConnection         firstMixerToSecondMixer05(firstMixer[5], 0, secondMixer[1], 1);
AudioConnection         firstMixerToSecondMixer06(firstMixer[6], 0, secondMixer[1], 2);
AudioConnection         firstMixerToSecondMixer07(firstMixer[7], 0, secondMixer[1], 3);
AudioConnection         firstMixerToSecondMixer08(firstMixer[8], 0, secondMixer[2], 0);
AudioConnection         firstMixerToSecondMixer09(firstMixer[9], 0, secondMixer[2], 1);
AudioConnection         firstMixerToSecondMixer10(firstMixer[10], 0, secondMixer[2], 2);
AudioConnection         firstMixerToSecondMixer11(firstMixer[11], 0, secondMixer[2], 3);
AudioConnection         firstMixerToSecondMixer12(firstMixer[12], 0, secondMixer[3], 0);
AudioConnection         firstMixerToSecondMixer13(firstMixer[13], 0, secondMixer[3], 1);
AudioConnection         firstMixerToSecondMixer14(firstMixer[14], 0, secondMixer[3], 2);
AudioConnection         firstMixerToSecondMixer15(firstMixer[15], 0, secondMixer[3], 3);
AudioConnection         firstMixerToSecondMixer16(firstMixer[16], 0, secondMixer[4], 0);
AudioConnection         firstMixerToSecondMixer17(firstMixer[17], 0, secondMixer[4], 1);
AudioConnection         firstMixerToSecondMixer18(firstMixer[18], 0, secondMixer[4], 2);
AudioConnection         firstMixerToSecondMixer19(firstMixer[19], 0, secondMixer[4], 3);
AudioConnection         firstMixerToSecondMixer20(firstMixer[20], 0, secondMixer[5], 0);
AudioConnection         firstMixerToSecondMixer21(firstMixer[21], 0, secondMixer[5], 1);
AudioConnection         firstMixerToSecondMixer22(firstMixer[22], 0, secondMixer[5], 2);
AudioConnection         firstMixerToSecondMixer23(firstMixer[23], 0, secondMixer[5], 3);
AudioConnection         firstMixerToSecondMixer24(firstMixer[24], 0, secondMixer[6], 0);
AudioConnection         firstMixerToSecondMixer25(firstMixer[25], 0, secondMixer[6], 1);
AudioConnection         firstMixerToSecondMixer26(firstMixer[26], 0, secondMixer[6], 2);
AudioConnection         firstMixerToSecondMixer27(firstMixer[27], 0, secondMixer[6], 3);
AudioConnection         firstMixerToSecondMixer28(firstMixer[28], 0, secondMixer[7], 0);
AudioConnection         firstMixerToSecondMixer29(firstMixer[29], 0, secondMixer[7], 1);
AudioConnection         firstMixerToSecondMixer30(firstMixer[30], 0, secondMixer[7], 2);
AudioConnection         firstMixerToSecondMixer31(firstMixer[31], 0, secondMixer[7], 3);
AudioConnection         secondMixerToThirdMixer0(secondMixer[0], 0, thirdMixer[0], 0);
AudioConnection         secondMixerToThirdMixer1(secondMixer[1], 0, thirdMixer[0], 1);
AudioConnection         secondMixerToThirdMixer2(secondMixer[2], 0, thirdMixer[0], 2);
AudioConnection         secondMixerToThirdMixer3(secondMixer[3], 0, thirdMixer[0], 3);
AudioConnection         secondMixerToThirdMixer4(secondMixer[4], 0, thirdMixer[1], 0);
AudioConnection         secondMixerToThirdMixer5(secondMixer[5], 0, thirdMixer[1], 1);
AudioConnection         secondMixerToThirdMixer6(secondMixer[6], 0, thirdMixer[1], 2);
AudioConnection         secondMixerToThirdMixer7(secondMixer[7], 0, thirdMixer[1], 3);
AudioConnection         thirdMixerToOutMixer0(thirdMixer[0], 0, outMixer, 0);
AudioConnection         thirdMixerToOutMixer1(thirdMixer[1], 0, outMixer, 1);
AudioAmplifier		amp1;		//xy=324,172
AudioOutputI2S		i2s1;		//xy=538,168
AudioConnection		patchCord1 (outMixer, amp1);
AudioConnection		patchCord2 (amp1, 0, i2s1, 0);
// GUItool: end automatically generated code

// 
// AudioSynthWaveform       waveform1[42]; //xy=968.3332138061523,4748.095205307007
// AudioSynthWaveform       waveform2[42]; //xy=970.237922668457,4846.190433502197
// 
// AudioEffectEnvelope      envelope[42];      
// AudioMixer4              mixer[42];         
// AudioMixer4              mixer1;         
// AudioMixer4              mixer2;        
// AudioMixer4              mixer3;
// AudioMixer4              mixer4;
// AudioMixer4              mixer5;         
// AudioMixer4              mixer6;         
// AudioMixer4              mixer7;         
// AudioMixer4              mixer8;        
// AudioMixer4              mixer9;         
// AudioMixer4              mixer10;        
// AudioMixer4              mixer11;         
// AudioMixer4              mixer12;        
// AudioMixer4              mixer13;         
// AudioMixer4              mixer14;         
// AudioMixer4              mixer15;         
// 
// AudioOutputI2S           i2s1;          
// 
// AudioConnection          patchCord1(waveform1[0], 0, mixer[0], 0);
// AudioConnection          patchCord2(waveform2[0], 0, mixer[0], 1);
// 
// AudioConnection          patchCord3(waveform1[1], 0, mixer[1], 0);
// AudioConnection          patchCord4(waveform2[1], 0, mixer[1], 1);
// 
// AudioConnection          patchCord5(waveform1[2], 0, mixer[2], 0);
// AudioConnection          patchCord6(waveform2[2], 0, mixer[2], 1);
// 
// AudioConnection          patchCord7(waveform1[3], 0, mixer[3], 0);
// AudioConnection          patchCord8(waveform2[3], 0, mixer[3], 1);
// 
// AudioConnection          patchCord9(waveform1[4], 0, mixer[4], 0);
// AudioConnection          patchCord0(waveform2[4], 0, mixer[4], 1);
// 
// AudioConnection          patchCord11(waveform1[5], 0, mixer[5], 0);
// AudioConnection          patchCord12(waveform2[5], 0, mixer[5], 1);
// 
// AudioConnection          patchCord13(waveform1[6], 0, mixer[6], 0);
// AudioConnection          patchCord14(waveform2[6], 0, mixer[6], 1);
// 
// AudioConnection          patchCord15(waveform1[7], 0, mixer[7], 0);
// AudioConnection          patchCord16(waveform2[7], 0, mixer[7], 1);
// 
// AudioConnection          patchCord17(waveform1[8], 0, mixer[8], 0);
// AudioConnection          patchCord18(waveform2[8], 0, mixer[8], 1);
// 
// AudioConnection          patchCord19(waveform1[9], 0, mixer[9], 0);
// AudioConnection          patchCord10(waveform2[9], 0, mixer[9], 1);
// 
// AudioConnection          patchCord21(waveform1[10], 0, mixer[10], 0);
// AudioConnection          patchCord22(waveform2[10], 0, mixer[10], 1);
// 
// AudioConnection          patchCord23(waveform1[11], 0, mixer[11], 0);
// AudioConnection          patchCord24(waveform2[11], 0, mixer[11], 1);
// 
// AudioConnection          patchCord25(waveform1[12], 0, mixer[12], 0);
// AudioConnection          patchCord26(waveform2[12], 0, mixer[12], 1);
// 
// AudioConnection          patchCord27(waveform1[13], 0, mixer[13], 0);
// AudioConnection          patchCord28(waveform2[13], 0, mixer[13], 1);
// 
// AudioConnection          patchCord29(waveform1[14], 0, mixer[14], 0);
// AudioConnection          patchCord20(waveform2[14], 0, mixer[14], 1);
// 
// AudioConnection          patchCord31(waveform1[15], 0, mixer[15], 0);
// AudioConnection          patchCord32(waveform2[15], 0, mixer[15], 1);
// 
// AudioConnection          patchCord33(waveform1[16], 0, mixer[16], 0);
// AudioConnection          patchCord34(waveform2[16], 0, mixer[16], 1);
// 
// AudioConnection          patchCord35(waveform1[17], 0, mixer[17], 0);
// AudioConnection          patchCord36(waveform2[17], 0, mixer[17], 1);
// 
// AudioConnection          patchCord37(waveform1[18], 0, mixer[18], 0);
// AudioConnection          patchCord38(waveform2[18], 0, mixer[18], 1);
// 
// AudioConnection          patchCord39(waveform1[19], 0, mixer[19], 0);
// AudioConnection          patchCord30(waveform2[19], 0, mixer[19], 1);
// 
// AudioConnection          patchCord41(waveform1[20], 0, mixer[20], 0);
// AudioConnection          patchCord42(waveform2[20], 0, mixer[20], 1);
// 
// AudioConnection          patchCord43(waveform1[21], 0, mixer[21], 0);
// AudioConnection          patchCord44(waveform2[21], 0, mixer[21], 1);
// 
// AudioConnection          patchCord45(waveform1[22], 0, mixer[22], 0);
// AudioConnection          patchCord46(waveform2[22], 0, mixer[22], 1);
// 
// AudioConnection          patchCord47(waveform1[23], 0, mixer[23], 0);
// AudioConnection          patchCord48(waveform2[23], 0, mixer[23], 1);
// 
// AudioConnection          patchCord49(waveform1[24], 0, mixer[24], 0);
// AudioConnection          patchCord40(waveform2[24], 0, mixer[24], 1);
// 
// AudioConnection          patchCord51(waveform1[25], 0, mixer[25], 0);
// AudioConnection          patchCord52(waveform2[25], 0, mixer[25], 1);
// 
// AudioConnection          patchCord53(waveform1[26], 0, mixer[26], 0);
// AudioConnection          patchCord54(waveform2[26], 0, mixer[26], 1);
// 
// AudioConnection          patchCord55(waveform1[27], 0, mixer[27], 0);
// AudioConnection          patchCord56(waveform2[27], 0, mixer[27], 1);
// 
// AudioConnection          patchCord57(waveform1[28], 0, mixer[28], 0);
// AudioConnection          patchCord58(waveform2[28], 0, mixer[28], 1);
// 
// AudioConnection          patchCord59(waveform1[29], 0, mixer[29], 0);
// AudioConnection          patchCord50(waveform2[29], 0, mixer[29], 1);
// 
// AudioConnection          patchCord61(waveform1[30], 0, mixer[30], 0);
// AudioConnection          patchCord62(waveform2[30], 0, mixer[30], 1);
// 
// AudioConnection          patchCord63(waveform1[31], 0, mixer[31], 0);
// AudioConnection          patchCord64(waveform2[31], 0, mixer[31], 1);
// 
// AudioConnection          patchCord65(waveform1[32], 0, mixer[32], 0);
// AudioConnection          patchCord66(waveform2[32], 0, mixer[32], 1);
// 
// AudioConnection          patchCord67(waveform1[33], 0, mixer[33], 0);
// AudioConnection          patchCord68(waveform2[33], 0, mixer[33], 1);
// 
// AudioConnection          patchCord69(waveform1[34], 0, mixer[34], 0);
// AudioConnection          patchCord60(waveform2[34], 0, mixer[34], 1);
// 
// AudioConnection          patchCord71(waveform1[35], 0, mixer[35], 0);
// AudioConnection          patchCord72(waveform2[35], 0, mixer[35], 1);
// 
// AudioConnection          patchCord73(waveform1[36], 0, mixer[36], 0);
// AudioConnection          patchCord74(waveform2[36], 0, mixer[36], 1);
// 
// AudioConnection          patchCord75(waveform1[37], 0, mixer[37], 0);
// AudioConnection          patchCord76(waveform2[37], 0, mixer[37], 1);
// 
// AudioConnection          patchCord77(waveform1[38], 0, mixer[38], 0);
// AudioConnection          patchCord78(waveform2[38], 0, mixer[38], 1);
// 
// AudioConnection          patchCord79(waveform1[39], 0, mixer[39], 0);
// AudioConnection          patchCord70(waveform2[39], 0, mixer[39], 1);
// 
// AudioConnection          patchCord81(waveform1[40], 0, mixer[40], 0);
// AudioConnection          patchCord82(waveform2[40], 0, mixer[40], 1);
// 
// AudioConnection          patchCord83(waveform1[41], 0, mixer[41], 0);
// AudioConnection          patchCord84(waveform2[41], 0, mixer[41], 1);
// 
// 
// AudioConnection          patchCord100(mixer[0], 0, envelope[0], 0);
// AudioConnection          patchCord101(mixer[1], 0, envelope[1], 0);
// AudioConnection          patchCord102(mixer[2], 0, envelope[2], 0);
// AudioConnection          patchCord103(mixer[3], 0, envelope[3], 0);
// AudioConnection          patchCord104(mixer[4], 0, envelope[4], 0);
// AudioConnection          patchCord105(mixer[5], 0, envelope[5], 0);
// AudioConnection          patchCord106(mixer[6], 0, envelope[6], 0);
// AudioConnection          patchCord107(mixer[7], 0, envelope[7], 0);
// AudioConnection          patchCord108(mixer[8], 0, envelope[8], 0);
// AudioConnection          patchCord109(mixer[9], 0, envelope[9], 0);
// AudioConnection          patchCord110(mixer[10], 0, envelope[10], 0);
// AudioConnection          patchCord111(mixer[11], 0, envelope[11], 0);
// AudioConnection          patchCord112(mixer[12], 0, envelope[12], 0);
// AudioConnection          patchCord113(mixer[13], 0, envelope[13], 0);
// AudioConnection          patchCord114(mixer[14], 0, envelope[14], 0);
// AudioConnection          patchCord115(mixer[15], 0, envelope[15], 0);
// AudioConnection          patchCord116(mixer[16], 0, envelope[16], 0);
// AudioConnection          patchCord117(mixer[17], 0, envelope[17], 0);
// AudioConnection          patchCord118(mixer[18], 0, envelope[18], 0);
// AudioConnection          patchCord119(mixer[19], 0, envelope[19], 0);
// AudioConnection          patchCord120(mixer[20], 0, envelope[20], 0);
// AudioConnection          patchCord121(mixer[21], 0, envelope[21], 0);
// AudioConnection          patchCord122(mixer[22], 0, envelope[22], 0);
// AudioConnection          patchCord123(mixer[23], 0, envelope[23], 0);
// AudioConnection          patchCord124(mixer[24], 0, envelope[24], 0);
// AudioConnection          patchCord125(mixer[25], 0, envelope[25], 0);
// AudioConnection          patchCord126(mixer[26], 0, envelope[26], 0);
// AudioConnection          patchCord127(mixer[27], 0, envelope[27], 0);
// AudioConnection          patchCord128(mixer[28], 0, envelope[28], 0);
// AudioConnection          patchCord129(mixer[29], 0, envelope[29], 0);
// AudioConnection          patchCord130(mixer[30], 0, envelope[30], 0);
// AudioConnection          patchCord131(mixer[31], 0, envelope[31], 0);
// AudioConnection          patchCord132(mixer[32], 0, envelope[32], 0);
// AudioConnection          patchCord133(mixer[33], 0, envelope[33], 0);
// AudioConnection          patchCord134(mixer[34], 0, envelope[34], 0);
// AudioConnection          patchCord135(mixer[35], 0, envelope[35], 0);
// AudioConnection          patchCord136(mixer[36], 0, envelope[36], 0);
// AudioConnection          patchCord137(mixer[37], 0, envelope[37], 0);
// AudioConnection          patchCord138(mixer[38], 0, envelope[38], 0);
// AudioConnection          patchCord139(mixer[39], 0, envelope[39], 0);
// AudioConnection          patchCord140(mixer[40], 0, envelope[40], 0);
// AudioConnection          patchCord141(mixer[41], 0, envelope[41], 0);
// 
// AudioConnection          patchCord150(envelope[0], 0, mixer1, 0);
// AudioConnection          patchCord151(envelope[1], 0, mixer1, 1);
// AudioConnection          patchCord152(envelope[2], 0, mixer1, 2);
// AudioConnection          patchCord153(envelope[3], 0, mixer1, 3);
// 
// AudioConnection          patchCord154(envelope[4], 0, mixer2, 0);
// AudioConnection          patchCord155(envelope[5], 0, mixer2, 1);
// AudioConnection          patchCord156(envelope[6], 0, mixer2, 2);
// AudioConnection          patchCord157(envelope[7], 0, mixer2, 3);
// 
// AudioConnection          patchCord158(envelope[8], 0, mixer3, 0);
// AudioConnection          patchCord159(envelope[9], 0, mixer3, 1);
// AudioConnection          patchCord160(envelope[10], 0, mixer3, 2);
// AudioConnection          patchCord161(envelope[11], 0, mixer3, 3);
// 
// AudioConnection          patchCord162(envelope[12], 0, mixer4, 0);
// AudioConnection          patchCord163(envelope[13], 0, mixer4, 1);
// AudioConnection          patchCord164(envelope[14], 0, mixer4, 2);
// AudioConnection          patchCord165(envelope[15], 0, mixer4, 3);
// 
// AudioConnection          patchCord166(envelope[16], 0, mixer5, 0);
// AudioConnection          patchCord167(envelope[17], 0, mixer5, 1);
// AudioConnection          patchCord168(envelope[18], 0, mixer5, 2);
// AudioConnection          patchCord169(envelope[19], 0, mixer5, 3);
// 
// AudioConnection          patchCord170(envelope[20], 0, mixer6, 0);
// AudioConnection          patchCord171(envelope[21], 0, mixer6, 1);
// AudioConnection          patchCord172(envelope[22], 0, mixer6, 2);
// AudioConnection          patchCord173(envelope[23], 0, mixer6, 3);
// 
// AudioConnection          patchCord174(envelope[24], 0, mixer7, 0);
// AudioConnection          patchCord175(envelope[25], 0, mixer7, 1);
// AudioConnection          patchCord176(envelope[26], 0, mixer7, 2);
// AudioConnection          patchCord177(envelope[27], 0, mixer7, 3);
// 
// AudioConnection          patchCord178(envelope[28], 0, mixer8, 0);
// AudioConnection          patchCord179(envelope[29], 0, mixer8, 1);
// AudioConnection          patchCord180(envelope[30], 0, mixer8, 2);
// AudioConnection          patchCord181(envelope[31], 0, mixer8, 3);
// 
// AudioConnection          patchCord182(envelope[32], 0, mixer9, 0);
// AudioConnection          patchCord183(envelope[33], 0, mixer9, 1);
// AudioConnection          patchCord184(envelope[34], 0, mixer9, 2);
// AudioConnection          patchCord185(envelope[35], 0, mixer9, 3);
// 
// AudioConnection          patchCord186(envelope[36], 0, mixer10, 0);
// AudioConnection          patchCord187(envelope[37], 0, mixer10, 1);
// AudioConnection          patchCord188(envelope[38], 0, mixer10, 2);
// AudioConnection          patchCord189(envelope[39], 0, mixer10, 3);
// 
// AudioConnection          patchCord190(envelope[40], 0, mixer11, 0);
// AudioConnection          patchCord191(envelope[41], 0, mixer11, 1);
// 
// 
// 
// AudioConnection          patchCord200(mixer1, 0, mixer12, 0);
// AudioConnection          patchCord201(mixer2, 0, mixer12, 1);
// AudioConnection          patchCord202(mixer3, 0, mixer12, 2);
// AudioConnection          patchCord203(mixer4, 0, mixer12, 3);
// 
// AudioConnection          patchCord204(mixer5, 0, mixer13, 0);
// AudioConnection          patchCord205(mixer6, 0, mixer13, 1);
// AudioConnection          patchCord206(mixer7, 0, mixer13, 2);
// AudioConnection          patchCord207(mixer8, 0, mixer13, 3);
// 
// AudioConnection          patchCord208(mixer9, 0, mixer14, 0);
// AudioConnection          patchCord209(mixer10, 0, mixer14, 1);
// AudioConnection          patchCord210(mixer11, 0, mixer14, 2);
// 
// AudioConnection          patchCord211(mixer12, 0, mixer15, 0);
// AudioConnection          patchCord212(mixer13, 0, mixer15, 1);
// AudioConnection          patchCord213(mixer14, 0, mixer15, 2);
// 
// AudioConnection          patchCord214(mixer15, 0, i2s1, 0);
// AudioConnection          patchCord215(mixer15, 0, i2s1, 1);
// 
// AudioControlSGTL5000     sgtl5000_1;   
// 
// // GUItool: end automatically generated code
// 
// 
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
  0, 0, 0, 
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
  Wire1.setClock(400000L); 
  Wire1.begin();           // Init I2C for PCF8575 (keyboard)

  // screen settings init
  //Wire.setClock(400000L); // Fast mode
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
      oled.print("Found : ");
      oled.println(address);
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
  delay(2000);
  PCF1.setButtonMask(0xFFFF);
  PCF2.setButtonMask(0xFFFF);

  AudioMemory(20);
  amp1.gain(0.5);

  // waveform1.begin(WAVEFORM_SINE);
  // waveform1.amplitude(0.5);
  // waveform1.frequency(50);
  // waveform1.pulseWidth(0.15);


  // envelope1.attack(10);
  // envelope1.hold(10);
  // envelope1.decay(25);
  // envelope1.sustain(0.4);
  // envelope1.release(70);
  // audio library init
  //  AudioMemory(20);
  //  sgtl5000_1.enable();
  //  sgtl5000_1.volume(0.05);
  //
  //
  //  // for i in envelope
  //
  //  for(int i=0; i<42; i++){
  //
  //    waveform1[i].begin(WAVEFORM_SINE);
  //    waveform1[i].amplitude(0.75);
  //    waveform1[i].frequency(50);
  //    waveform1[i].pulseWidth(0.60);
  //
  //    waveform2[i].begin(WAVEFORM_TRIANGLE);
  //    waveform2[i].amplitude(0.75);
  //    waveform2[i].frequency(50);
  //    waveform2[i].pulseWidth(0.60);
  //    mixer[i].gain(0, 0.15);
  //    mixer[i].gain(1, 0.15);
  //    mixer[i].gain(2, 0.15);
  //    mixer[i].gain(3, 0.15);
  //    envelope[i].attack(10);
  //    envelope[i].hold(10);
  //    envelope[i].decay(25);
  //    envelope[i].sustain(0.4);
  //    envelope[i].release(70);
  //  }
  oled.clear();
}

// function of menuing with the encoder
// Five menu items
int getButtonState(uint8_t index){
  // if value is 0 in PCF array then classic reading
  if(pinArrayPCF[index] != 0){    
    if(pinArrayPCF[index] < 16){
      //return PCF1.read16();
      return 1;
    }
    
    else if(pinArrayPCF[index] < 32){
      // return PCF2.readButton(pinArrayPCF[index]-16);
      return 1;

    }
    if (pinArrayPCF[index] == 55)
    {
      //return PCF1.readButton(0);
      return 1;

      // return PCF1.readButton(0);
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
    //buttonStates[p] = PCF1.readButton(p);
  }
  for (uint8_t p = 0; p < 16; p++)
  {
    //buttonStates[p+16] = PCF2.readButton(p);
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

void printKey(int index)
{
  oled.clear();
  oled.print("Index");
  if (index >= 36)
  {
    oled.print("Drone : ");
    oled.println(index);
  }
  else
  {
    oled.print("Key : ");
    oled.println(index);
    // print all data in integer array that are larger than 36ole

    if (pinArrayPCF[index] == 0)
    {
      oled.print("Teensy : ");
      oled.println(pinArrayClassicPin[index]);
    }
    else if (pinArrayPCF[index] == 55)
    {
      oled.print("PCF1 : ");
      oled.println(pinArrayPCF[index]);
    }
    else if (pinArrayPCF[index] < 16)
    {
      oled.print("PCF1 : ");
      oled.println(pinArrayPCF[index]);
    }
    else
    {
      oled.print("PCF2 : ");
      oled.println(pinArrayPCF[index]-16);
    }
    oled.print("Pousser : ");
    oled.println(pousser[index]);

    oled.print("Tirer : ");
    oled.println(tirer[index]);
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
// Mapping function for floats
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void synthNoteOn(byte synthChannel, byte pitch, byte velocity)
{
  for (byte myWaveform = 0; myWaveform < 8; myWaveform++)
  {
    if (waveformPitch[synthChannel][myWaveform] == 255)                                        // Find the first available waveform in the 16 waveform array.  255 used as indicator.
    {
        waveformPitch[synthChannel][myWaveform] = pitch;
        waveformCh[synthChannel][myWaveform].amplitude(0.5);
        waveformCh[synthChannel][myWaveform].frequency(midiPitchFrequencyMap[pitch]);
        envelopeCh[synthChannel][myWaveform].noteOn();
        break;
    }
  }
}

void synthNoteOff(byte synthChannel, byte pitch, byte velocity)
{
  for (byte myWaveform = 0; myWaveform < 8; myWaveform++)
  {
    if (waveformPitch[synthChannel][myWaveform] == pitch)                                        // Find matching waveform in the 16 waveform array, mark as available and send noteOff
    {
        waveformPitch[synthChannel][myWaveform] = 255;
        envelopeCh[synthChannel][myWaveform].noteOff();

        break;
    }
  }
}



void noteOff(int note, Configuration conf){
  synthNoteOff(0,note+36,127);
}
void noteOn(int note, int index, Configuration conf){
  synthNoteOn(0,note+36,127);
}




static void noteMidi(uint8_t sens_soufflet, uint8_t index, Configuration conf, int velocity){
   //, uint8_t oldStatePousser, uint8_t oldStateTirer
  uint8_t bouton = buttonStates[index];
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
            noteOff(noteSynthTirer, conf);
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
            noteOff(noteSynthPousser, conf);
            oldStatePousser[index] = BUTTON_RELEASED;
          }
        }
      }
    }
    else
    {
      if (oldStatePousser[index] == BUTTON_PRESSED)
      {
        noteOff(noteSynthPousser, conf);
        oldStatePousser[index] = BUTTON_RELEASED;
      }
      if (oldStateTirer[index] == BUTTON_PRESSED)
      {
        // on appuie pas sur le bouton ma
        noteOff(noteSynthTirer, conf);
        oldStateTirer[index] = BUTTON_RELEASED;
      }
    }
  }

}




void playNotes(Configuration conf, int sens_soufflet ){
  for(indexArrayScan = 0; indexArrayScan < 36; indexArrayScan++){
    if(indexArrayScan != 31 && indexArrayScan != 8){
      noteMidi(sens_soufflet,indexArrayScan,conf, 127);
    }
  }
}

Configuration conf = Configuration("Squ Tri",2,11);
int count = 0;
void loop()
{
  // https://forum.pjrc.com/search.php?searchid=7853170

  int sens_soufflet = digitalRead(SOUFFLET_PIN);
  for (int i = 0; i < 36; i++)
  {
    buttonStates[i] = getButtonState(i);
  }
  
  // if(count==50){
  //   int test = PCF1.read16();
  //   int test2 = PCF2.read16();   
  //   count = 0;
  // }
  // count++;
  playNotes(conf, sens_soufflet);
  

}