/*!
  @file Mode0.cpp
  
  This is part of Chuck Malloch's implementation of firmware 
  for the [OnkartGromt OpenEffects Project hardware](http://openeffectsproject.com/).
  
  Written by Charles B. Malloch, PhD, Department of Electrical and Computer 
  Engineering, UMass Amherst. January 27, 2018
  
  BSD license, all text here must be included in any redistribution.
  
*/

#include <Mode0.h>

Mode0::Mode0 () {
  // constructor
}

void Mode0::init ( OpenEffectsBoxHW *oebhw, char * version, float *outputVolume, int verbose ) {
                   
  DisplayableModule::init ( 0, (char *) "Mode0", oebhw, verbose );
  
  _volume = outputVolume;
  setVolume ( * _volume );
  
  if ( _verbose >= 12 ) {
    Serial.print ( "Mode0 " );
    Serial.print ( _id );
    Serial.println ( " initialized" );
  }
  
  strncpy ( _version, version, _versionStrLen );
}

void Mode0::setVolume ( float volume ) {
  * _volume = volume;
  if ( _verbose >= 12 ) {
    Serial.print ( "Mode0 " );
    Serial.print ( _id );
    Serial.print ( " volume: " );
    Serial.print ( * _volume ); 
    Serial.print ( "\n" );\
  }
  _displayIsStale = true;

}

void Mode0::notify ( int channel, float value ) {
  if ( _verbose >= 12 ) {
    Serial.print ( "Mode0 " );
    Serial.print ( _id );
    Serial.print ( " / " );
    Serial.print ( channel );
    Serial.print ( ": " );
    Serial.println ( value );
  }

  if ( channel != 0 ) return;
  setVolume ( value * 1.5 );
}

void Mode0::display ( int mode, int subMode, bool force ) {

  if ( ! force && ! _displayIsStale ) return;
  
  _oebhw->oled.displayCommon ( mode, subMode );
  
  if ( _verbose >= 12 ) {
    Serial.println ( "Mode0 display" );
  }

  _oebhw->oled.setTextSize ( 1 );
  _oebhw->oled.setCursor ( 0, 28 );
  _oebhw->oled.print ( "Vol" );
  
  _oebhw->oled.setTextSize ( 3 );
  _oebhw->oled.setCursor ( 40, 20 );
  _oebhw->oled.print ( * _volume );

  // version bottom
  _oebhw->oled.setTextSize ( 1 );
  _oebhw->oled.setCursor ( 0, 56 );
  _oebhw->oled.print ( _version );

  _oebhw->oled.display();  // note takes about 100ms!!!
  
  _displayIsStale = false;

}