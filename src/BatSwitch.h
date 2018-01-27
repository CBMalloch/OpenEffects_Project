/*!
  @file BatSwitch.h
  
  This is part of Chuck Malloch's implementation of firmware 
  for the [OnkartGromt OpenEffects Project hardware](http://openeffectsproject.com/).
  
  Written by Charles B. Malloch, PhD, Department of Electrical and Computer 
  Engineering, UMass Amherst. January 27, 2018
  
  BSD license, all text here must be included in any redistribution.
  
*/

#include <Arduino.h>
#include <Print.h>

#ifndef BatSwitch_h
#define BatSwitch_h

#define BatSwitch_VERSION "0.001.000"

/*! \brief Wrapper for hardware interface -BatSwitch-.
 
  The bat switches are 3-position toggles, designated (ON)-OFF-(ON), meaning
  that the switch stays in the center position when it is put there, but 
  it springs back when moved to either side position ( that's what the parentheses
  indicate ). The two side positions are connected to ground through two different 
  valued resistors, so that the voltage is pulled down to a different value with 
  each position of the switch.
  The arrangement is different between the two bat switches provided; see the [table
  provided](@ref OpenEffectsBoxHW.h)

*/

class BatSwitch {

  public:
    
    BatSwitch ();  // constructor
    void init ( int id, int pin );
    void update ();
    
    bool changed ();
    int getValue ();
    void clearState ();


  protected:
  
  private:
  
    const unsigned long _noticePeriod_ms =  50UL;
    const unsigned long _repeatPeriod_ms = 500UL;

    int _id;
    int _pin;
    int _value, _oldValue;
    unsigned long _lastRepeatAt_ms, _lastValueChangeAt_ms, _lastCenteredAt_ms;
    bool _changed;
    
};

#endif

