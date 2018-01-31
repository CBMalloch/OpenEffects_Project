/*!
  @file Filter.h
  
  This is part of Chuck Malloch's implementation of firmware 
  for the [OnkartGromt OpenEffects Project hardware](http://openeffectsproject.com/).
  It wraps the [Teensy Audio Design Tool](https://www.pjrc.com/teensy/gui/) module
  of the same name.
  
  Written by Charles B. Malloch, PhD, Department of Electrical and Computer 
  Engineering, UMass Amherst. January 27, 2018
  
  BSD license, all text here must be included in any redistribution.
  
*/

#ifndef Filter_h
#define Filter_h

#define Filter_VERSION "0.000.001"

#include <DisplayableModule.h>

#define Filter_VERBOSE_DEFAULT  2
    
/*! \brief Wrapper for Audio Design Tool -Filter-.

  See [Paul Stoffregen's Audio Design Tool](https://www.pjrc.com/teensy/gui/)
 
  Also see the Wikipedia article on [Wah-wah pedals](https://en.wikipedia.org/wiki/Wah-wah_pedal)
  I am trying to create a wah-wah pedal using an expression pedal routed to control
  the base frequency of this filter.
  
*/

 
 class Filter : public DisplayableModule {

  public:
    Filter ();  // constructor
    void setVerbose ( int verbose );
    
    void init ( int id, char *name, AudioFilterStateVariable *filter, OpenEffectsBoxHW *oebhw, int verbose = Filter_VERBOSE_DEFAULT );
    void notify ( int channel, float value );
    void display ( int mode, int subMode, bool force = false );
    
    void setFrequency ( float frequency );    
    void setResonance ( float resonance );    
    void setOctaveControl ( float octaveControl );    
  
  protected:
  
  private:
    
    float _frequency;
    float _resonance;
    float _octaveControl;
    
    AudioFilterStateVariable *_filter;
};

#endif