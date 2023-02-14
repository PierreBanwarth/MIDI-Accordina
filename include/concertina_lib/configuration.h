#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include <Arduino.h>



class Configuration {
public:
  // add getter and setters
  
  Configuration(String configurationName,int octave, int shiftHalfTone);

  uint8_t getOctave();
  void setOctave(uint8_t octave);
  
  uint8_t getShiftHalfTone();
  void setShiftHalfTone(uint8_t shiftHalfTone);
  
  String getName();
  void setName(String configurationName);

private:
  // add private variables shiftHalfTone and octave and name
  uint8_t octave;
  uint8_t shiftHalfTone;
  String configurationName;
};

#endif
