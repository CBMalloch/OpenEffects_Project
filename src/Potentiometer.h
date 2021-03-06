/*!
  @file Potentiometer.h
  
  This is part of Chuck Malloch's implementation of firmware 
  for the [OnkartGromt OpenEffects Project hardware](http://openeffectsproject.com/).
  
  Written by Charles B. Malloch, PhD, Department of Electrical and Computer 
  Engineering, UMass Amherst. January 27, 2018
  
  BSD license, all text here must be included in any redistribution.
  
*/

#include <Arduino.h>
#include <Print.h>

#include <Utility.h>

#ifndef Potentiometer_h
#define Potentiometer_h

#define Potentiometer_VERSION "0.001.001"

/*! \brief Wrapper for hardware interface -Potentiometer-.
 
  ## Handling of potentiometers
  Since this design overloads the potentiometers ( for each settings mode, a given
  potentiometer controls some aspect of a different effect module ), I had to think
  long and hard about what should happen when a new mode is selected, since the 
  pot can't move to reflect the ( different ) setting of the ( different )
  parameter of the ( different ) effect module.
  I chose to ignore each pot until it is moved, at which time the related effect module
  setting will ( unfortunately ) jump to the current pot setting. *(Note to Paul -
  consider offering a rotary-encoder option here...)*
  This brings up a *different* gotcha. Reading a voltage several times will often yield
  different values. This will cause the pot value to be perceived as changed. Rats.
  So I had to add a guard band around the current setting, considering any reading 
  within the guard band to be unchanged. I also added an [EWMA smoothing algorithm]
  (https://en.wikipedia.org/wiki/Moving_average) to minimize the required size of 
  the guard band. The larger the guard band, the more one has to move the pot in
  order for the change to be noticed. The longer the averaging period, the more 
  sluggishly the reaction to a change occurs and settles. I had to split the 
  difference.
  I have just added a method: jump. When this is called, it short-circuits the 
  EWMA smoothing of the potentiometer's value towards the pot knob position.
  It is intended that this method be called when the display is about to be 
  changed - i.e. the pots are about to be attached to a new parameter. This need 
  is because a pot change just before a mode change leaves the value changing and
  so indicates an unintended change to the new mode.
  
*/

class Potentiometer {

  public:
    
    #define _Potentiometer_VERBOSE_DEFAULT 12
    
    Potentiometer ();  // constructor
    void init ( int id, int pin, int verbose = _Potentiometer_VERBOSE_DEFAULT );
    void update ();
    
    bool changed ();
    float getValue ();
    void clearState ();
    void jump ();


  protected:
  
  private:
  
    float read ();
    
    // LSB is about 1023 - 5
    const float _hysteresis = 2.5 / ( 1023.0 - 5.0 );
    const float _alpha = 0.6;
    // const unsigned long _settlingTime_ms = 2;
    
    int _id;
    int _pin;
    int _verbose;
    float _value, _oldValue;
    unsigned long _lastValueChangeAt_ms;
    bool _changed;
    bool _changeReported = false;

};

#endif