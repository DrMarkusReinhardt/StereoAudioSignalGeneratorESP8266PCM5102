/* A dual channel DDS audio signal generator for the NodeMCU (ESP8266) module with PCM5102 DAC module.
 * 
 * The sine signal generation for left and right channel is based on the DDS principle.
 * Different frequencies for the left and the right channel are allowed.
 * 
 * History: 3rd Feb. 2021, creation
 *          5th Feb. 2021, dual channel processing created
 *          
 * Author: Dr. Markus Reinhardt
 * 
 */
#include <Arduino.h>
#include <U8g2lib.h>
#include <i2s.h>
#include "ESP8266DDSGenerator.h"
#include "I2SHandler.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


// create the dual channel DDS sine generator
const uint32_t sampleRate = 48000;
const float frequencyLeft = 1000.0;
const float frequencyRight = 2000.0;
const uint16_t sineTableSize = 4096;
ESP8266DDSGenerator sineGen(sampleRate, frequencyLeft, frequencyRight, sineTableSize);

// create the I2S handler
I2SHandler i2sHandler(sampleRate);

// create the display handler
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() 
{  
  Serial.begin(115200);

  // setup the DDS sine generator
  sineGen.setup();
  
  // setup the I2S handler
  i2sHandler.setup();

  // start the display driver
  displaySetup();
  
  delay(1000);
  Serial.println("");
  Serial.println("Setup done");
}

void displaySetup()
{
  char stringBuffer[20];

  u8g2.begin();
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2.setDrawColor(1);

  // head line
  u8g2.drawStr(0,8,"Dual Chan. Signal Gen.");
  u8g2.drawHLine(0,10,128);
  
  // show the left channel frequency value
  String frequencyLeftStr = String(frequencyLeft,1); 
  u8g2.drawStr(0,24,"Frequency");
  u8g2.drawStr(0,40,"Left Chan.");
  frequencyLeftStr.toCharArray(stringBuffer,10);
  u8g2.drawStr(0,56,stringBuffer);
  u8g2.drawStr(36,56,"Hz");

  // line between the display sections
  u8g2.drawVLine(61,10,64);
    
  // show the right channel frequency value
  String frequencyRightStr = String(frequencyRight,1); 
  u8g2.drawStr(65,24,"Frequency");
  u8g2.drawStr(65,40,"Right Chan.");
  frequencyRightStr.toCharArray(stringBuffer,10);
  u8g2.drawStr(65,56,stringBuffer);
  u8g2.drawStr(102,56,"Hz");

  u8g2.sendBuffer();          // transfer internal memory to the display

}


void loop() 
{
  uint16_t signalSampleLeft;
  uint16_t signalSampleRight;

  for (int i=0; i<sampleRate; i++) 
  { 
    // get next samples for left and right channel
    sineGen.getNextSamples(signalSampleLeft, signalSampleRight);
    
    // write samples for left and right channel to the I2S buffer
    i2sHandler.write2I2SBufferLR(signalSampleLeft, signalSampleRight);
  }
  yield(); // allow other tasks to run, without this get WDT resets
}
