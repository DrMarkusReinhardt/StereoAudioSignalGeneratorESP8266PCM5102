/* A dual channel DDS audio signal generator for the NodeMCU (ESP8266) module with PCM5102 DAC module.
 * 
 * The sine signal generation for left and right channel is based on the DDS principle.
 * Different frequencies for the left and the right channel are allowed.
 * 
 * History: 3rd Feb. 2021, creation
 *          5th Feb. 2021, dual channel processing created
 *          
 * Author: Dr. Markus Reinhardt, 
 * 
 */
#include <Arduino.h>
#include <i2s.h>
#include "ESP8266DDSGenerator.h"
#include "I2SHandler.h"

// create the dual channel DDS sine generator
const uint32_t sampleRate = 48000;
const float frequencyLeft = 1000.0;
const float frequencyRight = 2000.0;
const uint16_t sineTableSize = 4096;
ESP8266DDSGenerator sineGen(sampleRate, frequencyLeft, frequencyRight, sineTableSize);

// create the I2S handler
I2SHandler i2sHandler(sampleRate);

void setup() 
{  
  Serial.begin(115200);

  // setup the DDS sine generator
  sineGen.setup();
  
  // setup the I2S handler
  i2sHandler.setup();
  
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
