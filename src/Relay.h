/*!
  @file Relay.h
  
  This is part of Chuck Malloch's implementation of firmware 
  for the [OnkartGromt OpenEffects Project hardware](http://openeffectsproject.com/).
  
  Written by Charles B. Malloch, PhD, Department of Electrical and Computer 
  Engineering, UMass Amherst. January 27, 2018
  
  BSD license, all text here must be included in any redistribution.
  
*/

#include <Arduino.h>
#include <Print.h>

#ifndef Relay_h
#define Relay_h

#define Relay_VERSION "0.001.000"

  /*! \brief Wrapper for hardware interface -Relay-.
 
    The relays in the OpenEffects Project hardware select either direct 
    pass-through of the signal ( relay not energized ) or routing the signal 
    through the i2s chip ( relay energized ) where it is available to be 
    modified by the firmware. There is one relay each for the R and L
    channels. The relays are not wired to the foot switches - they are 
    entirely under control of the firmware.

  */

class Relay {

  public:
    
    Relay ();  // constructor
    void init ( int id, int pin );
    void setValue ( int val );
    int getValue ();


  protected:
  
  private:
  
    int _id;
    int _pin;
    int _value;
    unsigned long _lastValueChangeAt_ms;
    
};

#endif