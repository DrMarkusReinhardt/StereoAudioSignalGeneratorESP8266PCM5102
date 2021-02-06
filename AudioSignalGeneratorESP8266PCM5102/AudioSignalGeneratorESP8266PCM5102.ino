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
  char stringBuffer[20];

  // setup the DDS sine generator
  sineGen.setup();
  
  // setup the I2S handler
  i2sHandler.setup();

  // show the left channel frequency value
  u8g2.begin();
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2.setDrawColor(1);
  String frequencyLeftStr = String(frequencyLeft,1); 
  u8g2.drawStr(0,8,"Frequency");
  u8g2.drawStr(0,24,"Left Chan.:");
  frequencyLeftStr.toCharArray(stringBuffer,10);
  u8g2.drawStr(0,40,stringBuffer);
  u8g2.drawStr(36,40,"Hz");

  // line between the display sections
  u8g2.drawVLine(64,0,64);
    
  // show the right channel frequency value
  String frequencyRightStr = String(frequencyRight,1); 
  u8g2.drawStr(68,8,"Frequency");
  u8g2.drawStr(68,24,"Right Chan.: ");
  frequencyRightStr.toCharArray(stringBuffer,10);
  u8g2.drawStr(68,40,stringBuffer);
  u8g2.drawStr(102,40,"Hz");

  
  /*
  u8g2.setFont(u8g2_font_fub20_tf);
  u8g2.setDrawColor(2);
  u8g2.drawStr(0,60,"Hi Markus");
  u8g2.setDrawColor(3);
  u8g2.drawLine(0, 0, 127, 63);
  u8g2.drawLine(0,63,127,0);
  u8g2.drawEllipse(32,32,10,20);
  */
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay(1000); 
  
  delay(1000);
  Serial.println("");
  Serial.println("Setup done");
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
