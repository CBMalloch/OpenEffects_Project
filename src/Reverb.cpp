/*!
  @file Reverb.cpp
  
  This is part of Chuck Malloch's implementation of firmware 
  for the [OnkartGromt OpenEffects Project hardware](http://openeffectsproject.com/).
  It wraps the [Teensy Audio Design Tool](https://www.pjrc.com/teensy/gui/) module
  of the same name.
  
  Written by Charles B. Malloch, PhD, Department of Electrical and Computer 
  Engineering, UMass Amherst. January 27, 2018
  
  BSD license, all text here must be included in any redistribution.
  
*/

#include <Reverb.h>

Reverb::Reverb () {
  // constructor
}

void Reverb::init ( int id, char *name, AudioEffectReverb *reverb, OpenEffectsBoxHW *oebhw, int verbose ) {
                   
                   
  DisplayableModule::init ( id, name, oebhw, verbose );
  
  _reverb = reverb;
  setReverbTime ( 0 );
  
  if ( _verbose >= 12 ) {
    Serial.print ( "Reverb " );
    Serial.print ( _id );
    Serial.println ( " initialized" );
  }
}

void Reverb::setReverbTime ( float reverbTime_s ) {
  // HACK! reverb time of 0 is ignored!
  _reverbTime_s = reverbTime_s + 1e-6;
  if ( _verbose >= 12 ) {
    Serial.print ( "Reverb " );
    Serial.print ( _id );
    Serial.print ( "; time: " );
    Serial.print ( _reverbTime_s ); 
    Serial.print ( "\n" );\
  }
  _reverb->reverbTime ( _reverbTime_s );
  _displayIsStale = true;
}

void Reverb::notify ( int channel, float value ) {
  if ( _verbose >= 12 ) {
    Serial.print ( "Reverb " );
    Serial.print ( _id );
    Serial.print ( ": " );
    Serial.println ( value );
  }
  
  if ( channel != 0 ) return;
  
  setReverbTime ( Utility::fmapc ( value, 0.0, 1.0, 0.0, 8.0 ) );

}

void Reverb::display ( int mode, int subMode, bool force ) {

  if ( ! force && ! _displayIsStale ) return;
  
  _oebhw->oled.displayCommon ( mode, subMode );

  
  if ( _verbose >= 12 ) {
    Serial.print ( "Reverb " );
    Serial.print ( _id );
    Serial.print ( " (" );
    Serial.print ( _name );
    Serial.println ( ") display" );
  }

  _oebhw->oled.setTextSize ( 2 );
  _oebhw->oled.setCursor ( 0, 0 );
  if ( strlen ( _name ) > 0 ) {
    _oebhw->oled.print ( _name );
    _oebhw->oled.print ( " " );
  }
  _oebhw->oled.print ( "reverb" );
    
  _oebhw->oled.setTextSize ( 2 );
  _oebhw->oled.setCursor ( 30, 16 );
  _oebhw->oled.print ( _reverbTime_s );
  _oebhw->oled.setTextSize ( 1 );
  _oebhw->oled.setCursor ( 0, 20 );
  _oebhw->oled.print ( "s" );

  _oebhw->oled.display();  // note takes about 100ms!!!
  
  _displayIsStale = false;
}