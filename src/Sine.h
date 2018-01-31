/*!
  @file Mixer.h
  
  This is part of Chuck Malloch's implementation of firmware 
  for the [OnkartGromt OpenEffects Project hardware](http://openeffectsproject.com/).
  It wraps the [Teensy Audio Design Tool](https://www.pjrc.com/teensy/gui/) module
  of the same name.
  
  Written by Charles B. Malloch, PhD, Department of Electrical and Computer 
  Engineering, UMass Amherst. January 27, 2018
  
  BSD license, all text here must be included in any redistribution.
  
*/

#ifndef Sine_h
#define Sine_h

#define Sine_VERSION "0.000.001"

#include <DisplayableModule.h>

#define Sine_VERBOSE_DEFAULT  2
    
/*! \brief Wrapper for Audio Design Tool -Sine-.

  See [Paul Stoffregen's Audio Design Tool](https://www.pjrc.com/teensy/gui/)
 
*/
class Sine : public DisplayableModule {

  public:
    Sine ();  // constructor
    void setVerbose ( int verbose );
    
    void init ( int id, char *name, AudioSynthWaveformSine *sine, OpenEffectsBoxHW *oebhw, int verbose = Sine_VERBOSE_DEFAULT );
    void notify ( int channel, float value );
    void display ( int mode, int subMode, bool force = false );
    
    void setFrequency ( float frequency );    
  
  protected:
  
  private:
    
    float _frequency;
    
    AudioSynthWaveformSine *_sine;
};

#endif