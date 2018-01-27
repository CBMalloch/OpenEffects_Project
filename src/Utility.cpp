/*!
  @file Utility.cpp
  
  This is part of Chuck Malloch's implementation of firmware 
  for the [OnkartGromt OpenEffects Project hardware](http://openeffectsproject.com/).
  It contains useful common utility functions.
  
  Written by Charles B. Malloch, PhD, Department of Electrical and Computer 
  Engineering, UMass Amherst. January 27, 2018
  
  BSD license, all text here must be included in any redistribution.
  
*/

#include <Utility.h>

Utility::Utility () {
  // constructor
}

void Utility::setVerbose ( int verbose ) {
  _verbose = verbose;
  Serial.print ( "Utility VERBOSE: " );
  Serial.println ( _verbose );
}

float Utility::fmap ( float n, float n0, float n9, float y1, float y9 ) {
  float p = ( n - n0 ) / ( n9 - n0 );
  return ( y1 + ( y9 - y1 ) * p );
}

float Utility::fconstrain ( float x, float y1, float y9 ) {
  bool inverse = y9 > y1;
  if ( ( x < y1 ) == inverse) return ( y1 );
  if ( ( x > y9 ) == inverse ) return ( y9 );
  return ( x );
}

float Utility::fmapc ( float n, float n0, float n9, float y1, float y9 ) {
  return fconstrain ( fmap ( n, n0, n9, y1, y9 ), y1, y9 );
}

/**************************************************************************/
/*!
    @brief Simulates the action of an audio-taper pot.
            A regular potentiometer, also called a linear-taper potentiometer,
            is typically used as a voltage divider.
            With the end terminals connected one to a known fixed voltage and 
            the other to ground, the middle terminal provides a variable voltage
            that changes linearly with the rotation of the shaft.
            This isn't very good when used as a volume control, since what 
            we perceive as a doubling of volume is actually the result of 
            quadrupling the amplitude. 
            Similarly, a linear variation isn't very good used to control 
            frequency, since the pitch we perceive varies with the log of 
            the frequency - one octave involves doubling the frequency.
            Therefore, potentiometers are built in a variant called "audio taper",
            which varies the divided voltage in a way intended to be exponential.
            This function simulates the action of an audio-taper pot.
    @param  x
            The voltage received from a linear-taper pot, scaled to the range [0, 1].
    @param  fifty_pct_value
            The value we'd like to see at 50% of the pot's rotation ( centered ).
            This works best between 0 and about 0.4.
    @return The value, between 0 and 1, that we'd get from the pot if it were
            in fact an audio-taper pot.
*/
/**************************************************************************/

float Utility::expmap ( float x, float fifty_pct_value ) {
  // 0 -> small num; 0.5 -> fifty_pct_value; 1 -> 1
  // good for values of fifty_pct_value from >0 to about 0.4
  float scale = 1 / ( fifty_pct_value * fifty_pct_value );
  float base = log ( scale );  // log is natural log
  return ( exp ( x * base ) / scale );
}

