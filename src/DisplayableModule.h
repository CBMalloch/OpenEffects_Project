/*!
  @file DisplayableModule.h
  
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

#ifndef DisplayableModule_h
#define DisplayableModule_h

#define DisplayableModule_VERSION "0.001.000"

#include <Arduino.h>
#include <Print.h>

#include <Audio.h>

#include <OpenEffectsBoxHW.h>
#include <Utility.h>

#define DisplayableModule_VERBOSE_DEFAULT  2

/*! \brief Base class for any class using the OLED display.

  In order to limit the delays involved in calling display() to the OLED,
  we want to re-render the display only when something changes that is reflected
  on the current display. This base class provides the instance variables to 
  keep track of that.

*/

class DisplayableModule {

  public:
    DisplayableModule ();  // constructor
    void setVerbose ( int verbose );
    
    void init ( int id, char *name, OpenEffectsBoxHW *oebhw, int verbose = DisplayableModule_VERBOSE_DEFAULT );
    bool isActive ();
    void activate ( bool val );  // these just query and control the _isActive flag
    
    #define _DisplayableModule_VERBOSE_DEFAULT 2
    
    virtual void notify ( int channel, float value );
    virtual void display ( int mode, int subMode, bool force = false );
    
    void identify ();
  
  protected:
  
    volatile int _verbose;
    int _id;
    #define nameStrLen 16
    char _name [ nameStrLen ];
    OpenEffectsBoxHW *_oebhw;
    
    bool _isActive;
    bool _displayIsStale;
    
  private:
    // since this is a base class, mostly everything needs to be "protected" rather than "private"
};

#endif