/*!
  @file Mode0.h
  
  This is part of Chuck Malloch's implementation of firmware 
  for the [OnkartGromt OpenEffects Project hardware](http://openeffectsproject.com/).
  
  Written by Charles B. Malloch, PhD, Department of Electrical and Computer 
  Engineering, UMass Amherst. January 27, 2018
  
  BSD license, all text here must be included in any redistribution.
  
*/

#ifndef Mode0_h
#define Mode0_h

#define Mode0_VERSION "0.000.001"

#include <DisplayableModule.h>

#define Mode0_VERBOSE_DEFAULT  112
    
/*! \brief Class to instantiate the mode-0 screen.

  Wherein is set the output volume. Alternatively, the volume can be set by an effects 
  pedal plugged into Exp1.
 
*/

class Mode0 : public DisplayableModule {

  public:
    Mode0 ();  // constructor
    // void setVerbose ( int verbose );
    
    void init ( OpenEffectsBoxHW *oebhw, char * version, float *outputVolume, int verbose = Mode0_VERBOSE_DEFAULT );
    void notify ( int channel, float value );
    void display ( int mode, int subMode, bool force = false );
    
    void setVolume ( float volume );
  
  protected:
  
  private:
    #define _versionStrLen 20
    char _version [ _versionStrLen ];
    
    float *_volume;  // set in OpenEffectsBox.cpp; only recorded here for display

};

#endif