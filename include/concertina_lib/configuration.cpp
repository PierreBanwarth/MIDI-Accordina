#include <Arduino.h>

// create a cpp class named configuration
// this class got two settings shiftHalfTone and octave
// add a constructor getter and setters for this class
// add a constructor to the class
Configuration::Configuration(
  String s,int o, int shift
){
  configurationName = s;
  octave = o;
  shiftHalfTone = shift;
 
}
// add a getter and setter for octave
uint8_t Configuration::getOctave(){
  return octave;
}
void Configuration::setOctave(uint8_t o){
  octave = o;
}
// add a getter and setter for shiftHalfTone
uint8_t Configuration::getShiftHalfTone(){
  return shiftHalfTone;
}
void Configuration::setShiftHalfTone(uint8_t s){
  shiftHalfTone = s;
}
// getter and setter for the name
String Configuration::getName(){
  return configurationName;
}
void Configuration::setName(String s){
  configurationName = s;
}
