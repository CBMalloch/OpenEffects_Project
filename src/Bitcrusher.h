/*!
  @file Bitcrusher.h
  
  This is part of Chuck Malloch's implementation of firmware 
  for the [OnkartGromt OpenEffects Project hardware](http://openeffectsproject.com/).
  It wraps the [Teensy Audio Design Tool](https://www.pjrc.com/teensy/gui/) module
  of the same name.
  
  Written by Charles B. Malloch, PhD, Department of Electrical and Computer 
  Engineering, UMass Amherst. January 27, 2018
  
  BSD license, all text here must be included in any redistribution.
  
*/

#ifndef Bitcrusher_h
#define Bitcrusher_h

#define Bitcrusher_VERSION "0.001.000"

#include <DisplayableModule.h>

#define Bitcrusher_VERBOSE_DEFAULT 12
    
/*! \brief Wrapper for Audio Design Tool -Bitcrusher-.

  See [Paul Stoffregen's Audio Design Tool](https://www.pjrc.com/teensy/gui/)
 
*/

class Bitcrusher : public DisplayableModule {

  public:
    Bitcrusher ();  // constructor
    void setVerbose ( int verbose );
    
    void init ( int id, char *name, AudioEffectBitcrusher *_bitcrusher, OpenEffectsBoxHW *oebhw, int verbose = Bitcrusher_VERBOSE_DEFAULT );

    void notify ( int channel, float value );
    void display ( int mode, int subMode, bool force = false );
    
    void setNBits ( int nBits );
    void setSampleRate ( unsigned int sampleRate );
  
  protected:
  
  private:
  /*
    int _verbose;
    int _id;
    #define nameStrLen 8
    char _name [ nameStrLen ];
    OpenEffectsBoxHW *_oebhw;
  */
    
    static const int nChannels = 2;
    int _nBits;
    unsigned int _sampleRate;
    
    AudioEffectBitcrusher *_bitcrusher;
};

#endif