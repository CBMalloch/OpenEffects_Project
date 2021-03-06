/*!
  @file Pedal.cpp
  
  This is part of Chuck Malloch's implementation of firmware 
  for the [OnkartGromt OpenEffects Project hardware](http://openeffectsproject.com/).
  
  Written by Charles B. Malloch, PhD, Department of Electrical and Computer 
  Engineering, UMass Amherst. January 27, 2018
  
  BSD license, all text here must be included in any redistribution.
  
*/

#include <Pedal.h>

Pedal::Pedal () {
}

float Pedal::read () {
  const int nReadRepetitions = 2;
  float value = 0;
  for ( int i = 0; i < nReadRepetitions; i++ ) {
    value += analogRead ( _pin );
    delay ( 1 );
  }
  value /= float ( nReadRepetitions );
  
  // an unplugged pedal should give a value of 0
  if ( value < 12 ) return ( -1.0 );
  return ( Utility::fmapc ( value, 12, 172, 0.0, 1.0 ) );
}

void Pedal::init ( int pedalID, int pin, int verbose ) {

  _id = pedalID;
  _pin = pin;  // *analog* pin
  _verbose = verbose;
  
  _value = read();
  _oldValue = _value;
  _lastValueChangeAt_ms = millis();
    
  if ( _verbose >= 10 ) {
    Serial.print ( "Pedal " ); Serial.print ( _id );
    Serial.print ( " (pin " ); Serial.print ( _pin );
    Serial.println ( ") inited" );
  }
}

void Pedal::update () {

  if ( analogRead ( _pin ) == 0 ) {
    static bool notified = false;
    if ( _verbose >= 18 && ! notified ) {
      Serial.print ( "Pedal " ); Serial.print ( _id );
      Serial.print ( " (pin " ); Serial.print ( _pin );
      Serial.print ( ") value: " );
      Serial.print ( _value );
      Serial.println ( "; must be unplugged!" );
    }
    notified = true;
    return;
  }

  _value = read() * ( 1.0 - _alpha ) + _value * _alpha;
  
  if ( abs ( _value - _oldValue ) > _hysteresis ) {
    if ( _verbose >= 12 ) {
      Serial.print ( "Pedal " ); Serial.print ( _id );
      Serial.print ( " (pin " ); Serial.print ( _pin );
      Serial.print ( ") new value: " );
      Serial.println ( _value );
    }
    _oldValue = _value;
    _lastValueChangeAt_ms = millis();
    _changeReported = false;
//  } else if ( ( millis() - _lastValueChangeAt_ms ) < _settlingTime_ms ) {
 //  } else 
  }
  if ( ! _changeReported ) {
    if ( _verbose >= 12 ) {
      Serial.print ( "Pedal " ); Serial.print ( _id );
      Serial.print ( " (pin " ); Serial.print ( _pin );
      Serial.println ( ") reporting change" );
    }
    _changed = true;
    _changeReported = true;
  }

}

bool Pedal::changed () {
  return ( _changed );
}

float Pedal::getValue () {
  return ( _value );
}

void Pedal::clearState () {
  _changed = false;
}
