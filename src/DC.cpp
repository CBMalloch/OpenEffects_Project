/*!
  @file DC.cpp
  
  This is part of Chuck Malloch's implementation of firmware 
  for the [OnkartGromt OpenEffects Project hardware](http://openeffectsproject.com/).
  It wraps the [Teensy Audio Design Tool](https://www.pjrc.com/teensy/gui/) module
  of the same name.
  
  Written by Charles B. Malloch, PhD, Department of Electrical and Computer 
  Engineering, UMass Amherst. January 27, 2018
  
  BSD license, all text here must be included in any redistribution.
  
*/

#include <DC.h>

DC::DC () {
  // constructor
}

void DC::init ( int id, char *name, AudioSynthWaveformDc *dc, OpenEffectsBoxHW *oebhw, int verbose ) {
                   
                   
  DisplayableModule::init ( id, name, oebhw, verbose );
  
  _dc = dc;
  _level = 0.2;
  setLevel ( _level );
  
  if ( _verbose >= 12 ) {
    Serial.print ( "DC " );
    Serial.print ( _id );
    Serial.println ( " initialized" );
  }
}

void DC::setLevel ( float level ) {
  _level = level;
  if ( _verbose >= 12 ) {
    Serial.print ( "DC " );
    Serial.print ( _id );
    Serial.print ( " level: " );
    Serial.print ( _level ); 
    Serial.print ( "\n" );\
  }
  _dc->amplitude ( _level );
  _displayIsStale = true;

}

void DC::notify ( int channel, float value ) {
  if ( _verbose >= 12 ) {
    Serial.print ( "DC " );
    Serial.print ( _id );
    Serial.print ( " / " );
    Serial.print ( channel );
    Serial.print ( ": " );
    Serial.println ( value );
  }

  if ( channel != 0 ) return;
  
  setLevel ( value * 1.5 );
}

void DC::display ( int mode, int subMode, bool force ) {

  if ( ! force && ! _displayIsStale ) return;
  
  _oebhw->oled.displayCommon ( mode, subMode );

  
  if ( _verbose >= 12 ) {
    Serial.print ( "DC " );
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
  _oebhw->oled.print ( "DC" );
  
  _oebhw->oled.setTextSize ( 2 );
  _oebhw->oled.setCursor ( 30, 16 );
  _oebhw->oled.print ( _level );
  _oebhw->oled.setTextSize ( 1 );

  _oebhw->oled.display();  // note takes about 100ms!!!
  
  _displayIsStale = false;
}