/*!
  @file Pedal.h
  
  This is part of Chuck Malloch's implementation of firmware 
  for the [OnkartGromt OpenEffects Project hardware](http://openeffectsproject.com/).
  
  Written by Charles B. Malloch, PhD, Department of Electrical and Computer 
  Engineering, UMass Amherst. January 27, 2018
  
  BSD license, all text here must be included in any redistribution.
  
*/

#include <Arduino.h>
#include <Print.h>

#include <Utility.h>

#ifndef Pedal_h
#define Pedal_h

#define Pedal_VERSION "0.001.000"

  /*! \brief Wrapper for hardware interface -Pedal-.
 
    A note on the [handling of potentiometers]
    (http://cbmalloch.umasscreate.net/wp/uncategorized/the-overloading-of-potentiometers/),
    which applies also to the potentiometers used in expression pedals.

  */

class Pedal {

  public:
    
    void setVerbose ( int i );
    
    #define _Pedal_VERBOSE_DEFAULT  2
    
    Pedal ();  // constructor
    void init ( int id, int pin, int verbose = _Pedal_VERBOSE_DEFAULT );
    
    void update ();
    
    bool changed ();
    float getValue ();
    void clearState ();


  protected:
  
  private:
  
    float read ();
    
    // LSB is 1 / ( 172 - 12 )
    const float _hysteresis = 2.5 / ( 172.0 - 12.0 );
    const float _alpha = 0.6;
    // const unsigned long _settlingTime_ms = 2;
    // const int _nReadRepetitions = 10;
    
    int _id;
    int _pin;
    int _verbose;
    float _value, _oldValue;
    unsigned long _lastValueChangeAt_ms;
    bool _changed;
    bool _changeReported = false;
    
};

#endif
