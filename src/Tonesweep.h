/*!
  @file Tonesweep.h
  
  This is part of Chuck Malloch's implementation of firmware 
  for the [OnkartGromt OpenEffects Project hardware](http://openeffectsproject.com/).
  It wraps the [Teensy Audio Design Tool](https://www.pjrc.com/teensy/gui/) module
  of the same name.
  
  Written by Charles B. Malloch, PhD, Department of Electrical and Computer 
  Engineering, UMass Amherst. January 27, 2018
  
  BSD license, all text here must be included in any redistribution.
  
*/

#ifndef Tonesweep_h
#define Tonesweep_h

#define Tonesweep_VERSION "0.000.001"

#include <DisplayableModule.h>

#define Tonesweep_VERBOSE_DEFAULT 12
    
/*! \brief Wrapper for Audio Design Tool -Tonesweep-.

  See [Paul Stoffregen's Audio Design Tool](https://www.pjrc.com/teensy/gui/)
 
*/
class Tonesweep : public DisplayableModule {

  public:
    Tonesweep ();  // constructor
    void setVerbose ( int verbose );
    
    void init ( int id, char *name, AudioSynthToneSweep *sine, OpenEffectsBoxHW *oebhw, int verbose = Tonesweep_VERBOSE_DEFAULT );
    void notify ( int channel, float value );
    void display ( int mode, int subMode, bool force = false );
    
    void setLFrequency ( float frequency );
    void setHFrequency ( float frequency );
    void setSweepTime ( float sweep_time );
    void tickle ();
  
  protected:
  
  private:
    
    float _lFrequency;
    float _hFrequency;
    float _sweepTime;
    
    AudioSynthToneSweep *_tonesweep;
};

#endif