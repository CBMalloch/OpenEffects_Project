/*!
  @file DC.h
  
  This is part of Chuck Malloch's implementation of firmware 
  for the [OnkartGromt OpenEffects Project hardware](http://openeffectsproject.com/).
  It wraps the [Teensy Audio Design Tool](https://www.pjrc.com/teensy/gui/) module
  of the same name.
  
  Written by Charles B. Malloch, PhD, Department of Electrical and Computer 
  Engineering, UMass Amherst. January 27, 2018
  
  BSD license, all text here must be included in any redistribution.
  
*/

#ifndef DC_h
#define DC_h

#define DC_VERSION "0.000.001"

#include <DisplayableModule.h>

#define DC_VERBOSE_DEFAULT  2
    
/*! \brief Wrapper for Audio Design Tool -DC-.

  See [Paul Stoffregen's Audio Design Tool](https://www.pjrc.com/teensy/gui/)
 
*/

class DC : public DisplayableModule {

  public:
    DC ();  // constructor
    void setVerbose ( int verbose );
    
    void init ( int id, char *name, AudioSynthWaveformDc *dc, OpenEffectsBoxHW *oebhw, int verbose = DC_VERBOSE_DEFAULT );
    void notify ( int channel, float value );
    void display ( int mode, int subMode, bool force = false );
    
    void setLevel ( float level );    
  
  protected:
  
  private:
    
    float _level;
    
    AudioSynthWaveformDc *_dc;
};

#endif