/*!
  @file Utility.h
  
  This is part of Chuck Malloch's implementation of firmware 
  for the [OnkartGromt OpenEffects Project hardware](http://openeffectsproject.com/).
  It contains useful common utility functions.
  
  Written by Charles B. Malloch, PhD, Department of Electrical and Computer 
  Engineering, UMass Amherst. January 27, 2018
  
  BSD license, all text here must be included in any redistribution.
  
*/

#ifndef Utility_h
#define Utility_h

#define Utility_VERSION "0.001.001"

#include <Arduino.h>
#include <Print.h>

#define Utility_VERBOSE_DEFAULT 2

/*! \brief Utility subroutines.

*/

class Utility {

  public:
    Utility ();  // constructor
    void setVerbose ( int verbose );
    
    static float fmap ( float n, float n0, float n9, float y1, float y9 );
    static float fconstrain ( float x, float y1, float y9 );
    static float fmapc ( float n, float n0, float n9, float y1, float y9 );
    static float expmap ( float x, float fifty_pct_value = 0.2 );

  protected:
      
  private:
    int _verbose;

};

#endif