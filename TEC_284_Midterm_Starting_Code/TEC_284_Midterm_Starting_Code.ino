// Written by: Alex Robertson and original author of starter code
// Last Edited: 04/17/25
// TEC 284 Magic 8 Ball

//Arduino references can be found at: https://www.arduino.cc/reference/en/

//Necessary library files for the OLED and Accelerometer. Do not edit or delete!

#include <Arduino.h>
#include <U8x8lib.h>
#include "LIS3DHTR.h"

#ifdef SOFTWAREWIRE
    #include <SoftwareWire.h>
    SoftwareWire myWire(3, 2);
    LIS3DHTR<SoftwareWire> LIS; //Software I2C
    #define WIRE myWire
#else
    #include <Wire.h>
    LIS3DHTR<TwoWire> LIS; //Hardware I2C
    #define WIRE Wire
#endif

//Define a structure that holds your variables
struct ball {
  String phrases[10];
  String moods[10];
};

//Assign your 8 Ball answers and info into an array
struct ball magicBall = {{"For Sure", "Yes", "Definitely!", "Maybe", "Not Sure...", 
  "Ask Later", "I'm Tired", "No Way!", "No", "Nope"}, {"Positive", "Positive", "Positive",
  "Neutral", "Neutral", "Neutral", "Neutral", "Negative", "Negative", "Negative"}};


U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE); //do not delete

//----------Messages----------------//
//Don't change the content here, but use this to create variables/array/data structure)

    /*Message#    Message         Mood
      1           For Sure        Positive
      2           Yes             Positive
      3           Definitely!     Positive
      4           Maybe           Neutral
      5           Not Sure...     Neutral
      6           Ask Later       Neutral
      7           I'm Tired       Neutral
      8           No Way!         Negative
      9           No              Negative
      10          Nope            Negative
    */

int getPhrase() {
  int phraseNum = random(10);
  return phraseNum;
}

void setup() {

  LIS.begin(WIRE, 0x19); //I2C init -- do not delete

  Serial.begin(9600);                                     
  u8x8.begin();

  // Welcome message printed to the serial monitor
  Serial.println("Welcome to the Magic 8 Ball! Shake to begin!");
}

void loop() {

  u8x8.setFont(u8x8_font_7x14B_1x2_r); //do not edit or delete
  

  if (LIS.getAccelerationZ() > 2) { //If the Grove board is shaken
    u8x8.setCursor(0,0);
    int phraseNum = getPhrase();
    String output = magicBall.phrases[phraseNum];
    Serial.println(output + " - " + magicBall.moods[phraseNum]); // Print output to Serial Monitor
    u8x8.println(output); // Print output to OLED
    u8x8.println(magicBall.moods[phraseNum]);
    delay(5000);  // Delays for 5 seconds
    u8x8.clearDisplay();
  } 
}