/*!
  @file Oled.cpp
  
  This is part of Chuck Malloch's implementation of firmware 
  for the [OnkartGromt OpenEffects Project hardware](http://openeffectsproject.com/).
  
  Written by Charles B. Malloch, PhD, Department of Electrical and Computer 
  Engineering, UMass Amherst. January 27, 2018
  
  BSD license, all text here must be included in any redistribution.
  
*/

#include <Oled.h>

// OLED screen
// #define OLED_RESET 4
///*

// Adafruit_SSD1306 _oled_hw ( 4 );
    
Oled::Oled () {
  // constructor
}

//   */

void Oled::init ( int verbose ) {

  _verbose = verbose;
  
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  // initialize with the I2C addr 0x3D (for the 128x64)
  // 0x3c on Open Effects box
  
  const byte addI2C = 0x3c;
  begin ( SSD1306_SWITCHCAPVCC, addI2C );  
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display ();
  delay ( 500 );

  // Clear the buffer.
  clearDisplay ();
  display ();
    
  displaySplash ();
  
  if ( _verbose >= 12 ) {
    Serial.println ( "OLED initialized" );
  }
  
}




/*
void Oled::clearDisplay() {
  if ( _verbose >= 12 ) {
    Serial.println ( "OLED about to clear display" );
  }

  _oled_hw.clearDisplay ();
}

void Oled::setTextColor ( unsigned long color ) {
  _oled_hw.setTextColor ( color );
}

void Oled::setTextSize ( int textSize ) {
  _oled_hw.setTextSize ( textSize );
}

void Oled::setCursor ( int col, int row ) {
  _oled_hw.setCursor ( col, row );
}

void Oled::print ( const char *str ) {
  _oled_hw.print ( str );
}

void Oled::display () {
  _oled_hw.display();
}


*/


void Oled::displayCommon ( int mode, int subMode ) {
  // 128h x 64v
  
  if ( _verbose >= 12 ) {
    Serial.print ( "OLED displayCommon: " );
    Serial.print ( mode );
    Serial.print ( "." );
    Serial.println ( subMode );
  }

  
  clearDisplay();
  setTextColor ( WHITE );
    
  // large numbers are the bat switch positions

  setTextSize ( 1 );  // 6x8
  setCursor ( 96, 56 );
  print ( mode );
  print ( "." );
  print ( subMode );

}

void Oled::displaySplash () {

  clearDisplay();
  setTextColor ( WHITE );
    
  // large numbers are the bat switch positions

  setTextSize ( 1 );
  setCursor ( 96, 56 );
  print ( "hello" );
  print ( "." );
  print ( "world" );
  
  display();
  
  if ( _verbose >= 12 ) {
    Serial.println ( "OLED splashed" );
  }

}