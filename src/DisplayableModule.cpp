/*!
  @file DisplayableModule.cpp
  
  This is part of Chuck Malloch's implementation of firmware 
  for the [OnkartGromt OpenEffects Project hardware](http://openeffectsproject.com/).
  It is the base class for all the wrappers I've written for the 
  [Teensy Audio Design Tool](https://www.pjrc.com/teensy/gui/) module. Having 
  them all be subclasses of this base class allows me to assign any one of them
  to a pointer in the OpenEffectsBox master class, so it can call the active one 
  whenever it wants without having to have a big ugly case statement.
  
  Written by Charles B. Malloch, PhD, Department of Electrical and Computer 
  Engineering, UMass Amherst. January 27, 2018
  
  BSD license, all text here must be included in any redistribution.
  
*/

#include <DisplayableModule.h>

DisplayableModule::DisplayableModule () {
  // constructor
}

void DisplayableModule::setVerbose ( int verbose ) {
  _verbose = verbose;
  Serial.print ( "DisplayableModule VERBOSE: " );
  Serial.println ( _verbose );
}

void DisplayableModule::init ( int id, char *name, OpenEffectsBoxHW *oebhw, int verbose ) {

  _id = id;
  strncpy ( _name, name, nameStrLen );
  setVerbose ( verbose );
  _oebhw = oebhw;
  _isActive = false;
  _displayIsStale = true;
}

bool DisplayableModule::isActive () {
  return ( _isActive );
}

void DisplayableModule::activate ( bool val ) {
  _isActive = val;
}

// void DisplayableModule::notify ( int channel, int value ) {
// }
    
void DisplayableModule::notify ( int channel, float value ) {
}
    
void DisplayableModule::display ( int mode, int subMode, bool force ) {
}
