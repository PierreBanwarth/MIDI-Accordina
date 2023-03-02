#include <SSD1306Ascii.h>
#include "Wire.h" // Wire library (Included with Arduino IDE)
#include "menu.hpp"
#include "concertina_lib/concertina.h"
#include "concertina_lib/display.hpp"
#include "concertina_lib/configuration.hpp"
#include "RotaryEncoder.h"

Menu::Menu(Display disp){
  display = disp;
}

void Menu::initDisplay(uint8_t initEncoderPosition){
    display.clear();
    display.displayMainMenu(MODE_SYNTH, 0);
    encoderValue = initEncoderPosition;
}
void Menu::displayState(){
    display.clear();
    if(currentState == MAIN){
        display.displayMainMenu(MODE_SYNTH, encoderValue);
    }
    else if(currentState == OCTAVE){
        display.displayOctaveMenu(encoderValue, configuration);
    }else if(currentState==HALFTONE){
        display.displayHalfTone(configuration, encoderValue);
    }
    else if(currentState == PRESETS){
        display.displayPresetsMenu(encoderValue);
    }else if(currentState == CHOOSE_OCTAVE){
        display.displayOctaveMenu(encoderValue,configuration);
    }else if(currentState == MIDI_SETTINGS){
        display.displayMidiSettings(modeMidi, encoderValue);
    }else if(currentState == SYNTH_SETTINGS){
        display.displaySynthSettingsFirstMenu(encoderValue, configuration, currentState);
    }else if(currentState >= OCT1_SET && currentState <= WAV4_SET){
        display.displaySynthSettingsFirstMenu(encoderValue, configuration, currentState);

    }else if(currentState == DISPLAY_STATE){
        display.displayState(configuration);
    }
    else if (currentState == MENU_ATTACK){
        display.displayMenuAttack(configuration, encoderValue);
    }else if (currentState == OCT_OSC || currentState == WAVE){
        display.displayOctOrWave(
            currentState,
            encoderValue,
            configuration
        );
    }else if (currentState == OSCILLATOR){
        display.displayOscillatorChoice(encoderValue, configuration);
    }
}

Configuration Menu::updateState(uint8_t newEncoderValue, uint8_t buttonPressed, RotaryEncoder *encoder){
    //  else if(currentState == ATTACK_MAIN){
    //    displayAttackSwitch(configuration.attackTheme, encoderValue);
    //  }else if(currentState == ATTACK_DRONE){
    //    displayAttackSwitch(configuration.attackBourdon, encoderValue);
    //  }
    if(encoderValue != newEncoderValue){
        encoderValue = newEncoderValue;
        displayState();
    }
    
    if(oldButtonState != buttonPressed && buttonPressed == LOW){


        if(currentState==OCTAVE){
            configuration.octave = (encoderValue)%6;
            currentState = MAIN;
            encoder->setPosition(1);

        }else if(currentState==HALFTONE){
            configuration.shiftHalfTone = (encoderValue%23);
            currentState = MAIN;
            encoder->setPosition(2);

        }else if(currentState==ATTACK_MAIN){
            configuration.attackTheme = (configuration.attackTheme+(5*encoderValue))%255;
            currentState = MENU_ATTACK;
            encoder->setPosition(0);
        }
        else if(currentState==ATTACK_DRONE){
            configuration.attackBourdon = (configuration.attackBourdon+(5*encoderValue))%255;
            currentState = MENU_ATTACK;
            encoder->setPosition(1);
        }else if(currentState==DISPLAY_STATE){
            currentState = MAIN;
            encoder->setPosition(4);
        }else if(currentState == MIDI_SETTINGS){
            if(encoderValue%2 == 0){
                if(modeMidi == DRUM){
                    modeMidi=THEME;
                }
                else if(modeMidi == THEME){
                    modeMidi=DRUM;
                }
            }else if(encoderValue%2==1){
                currentState = MAIN;
            }
        }else if(currentState==MAIN){
            if(encoderValue%6 == 0){
            if(currentMode == MODE_SYNTH){
                currentMode=MODE_MIDI;
            }
            else if(currentMode == MODE_MIDI){
                currentMode=MODE_SYNTH;
            }
            }
            else if(encoderValue%6 == 1){
                currentState = OCTAVE;
                encoder->setPosition(configuration.octave);
            }
            else if(encoderValue%6 == 2){
                currentState = HALFTONE;
                encoder->setPosition(configuration.shiftHalfTone);
            }
            else if(encoderValue%6 == 3){
                if(currentMode == MODE_MIDI){
                    currentState = MIDI_SETTINGS;
                }else if(currentMode == MODE_SYNTH){
                    currentState = SYNTH_SETTINGS;
                }
                encoder->setPosition(0);
            }
            else if(encoderValue%6 == 4){
                currentState = DISPLAY_STATE;
            }
            else if(encoderValue%6 == 5){
                currentState = PRESETS;
                encoder->setPosition(0);
            }
        }else if(currentState==PRESETS){
            //if(encoderValue%6 == 0){
            if(encoderValue%8==7){
                currentState = MAIN;
            }
            else{
                configuration = newPresets[encoderValue];
            }
            // encoder->setPosition(5);
        }
        else if(currentState==MENU_ATTACK){
            if(encoderValue%3 == 0){
                currentState = ATTACK_MAIN;
            }
            else if(encoderValue%3 == 1){
                currentState = ATTACK_DRONE;
            }
            else if(encoderValue%3 == 2){
                currentState = SYNTH_SETTINGS;
            }
            encoder->setPosition(1);
        }else if(currentState==SYNTH_SETTINGS){

            if(encoderValue%9 == 0){
                currentState=WAV1_SET;
            }
            if(encoderValue%9 == 1){
                currentState=WAV2_SET;
            }
            if(encoderValue%9 == 2){
                currentState=WAV3_SET;
            }
            if(encoderValue%9 == 3){
                currentState=WAV4_SET;
            }
            if(encoderValue%9 == 4){
                currentState=OCT1_SET;
            }
            if(encoderValue%9 == 5){
                currentState=OCT2_SET;
            }
            if(encoderValue%9 == 6){
                currentState=OCT3_SET;
            }
            if(encoderValue%9 == 7){
                currentState=OCT4_SET;
            }
            if(encoderValue%9 == 8){
                currentState = MAIN;        
                encoder->setPosition(0);
            }
        }else if(currentState == WAV1_SET ){
            configuration.activeOsc1 = encoderValue%5;
            currentState = SYNTH_SETTINGS;
            encoder->setPosition(0);
        }else if(currentState == WAV2_SET ){
            configuration.activeOsc2 = encoderValue%5;
            currentState = SYNTH_SETTINGS;
            encoder->setPosition(1);
        }else if(currentState == WAV3_SET ){
            configuration.activeBrd1 = encoderValue%5;
            currentState = SYNTH_SETTINGS;
            encoder->setPosition(2);

        }else if(currentState == WAV4_SET ){
            configuration.activeBrd2 = encoderValue%5;
            currentState = SYNTH_SETTINGS;
            encoder->setPosition(3);
        
        }else if(currentState == OCT1_SET ){
            configuration.setOscOct(1, (encoderValue%6)-3);
            currentState = SYNTH_SETTINGS;
            encoder->setPosition(4);

        }else if(currentState == OCT2_SET ){
            configuration.setOscOct(2, (encoderValue%6)-3);
            currentState = SYNTH_SETTINGS;
            encoder->setPosition(5);

        }else if(currentState == OCT3_SET ){
            configuration.setOscOct(3, (encoderValue%6)-3);
            currentState = SYNTH_SETTINGS;
            encoder->setPosition(6);

        }else if(currentState == OCT4_SET ){
            configuration.setOscOct(4, (encoderValue%6)-3);
            currentState = SYNTH_SETTINGS;
            encoder->setPosition(7);
        }
        else if(currentState==CHOOSE_OCTAVE){
            int newOctave = (encoderValue%6)-3;
            configuration.setOscOct(wichOsc, newOctave);
            encoder->setPosition(wichOsc-1);
            currentState = OCT_OSC;

        }else if(currentState==OCT_OSC){
            if(encoderValue%6 == 5){
                currentState = SYNTH_SETTINGS;
                encoder->setPosition(2);
            }else{
                currentState = CHOOSE_OCTAVE;
                wichOsc = (encoderValue%6)+1;
            }
        }else if (currentState == WAVE){
            if (encoderValue % 6 == 5)
            {
                currentState = SYNTH_SETTINGS;
                encoder->setPosition(0);
            }else{
                currentState = OSCILLATOR;
                encoder->setPosition(0);
                oscillator = (encoderValue % 6)+1;
            }
        }else if(currentState==OSCILLATOR){
            if(encoderValue%6 != 5){
                if(oscillator == 1){
                    configuration.activeOsc1 = encoderValue%6;
                }else if(oscillator == 2){
                    configuration.activeOsc2 = encoderValue%6;
                }else if(oscillator == 3){
                    configuration.activeBrd1 = encoderValue%6;
                }else if (oscillator == 4){
                    configuration.activeBrd2 = encoderValue%6;
                }else if (oscillator == 5){
                    configuration.setAllOsc(encoderValue%6);
                }
            }else if(encoderValue%6 == 5){
                currentState = WAVE;
                encoder->setPosition(oscillator-1);
                oscillator = 0;
            }
        }
        displayState();
    }
    oldButtonState = buttonPressed; 

    return configuration;
}
