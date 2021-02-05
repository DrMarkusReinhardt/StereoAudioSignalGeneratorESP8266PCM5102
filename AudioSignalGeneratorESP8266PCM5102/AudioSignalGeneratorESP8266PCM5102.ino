/* A audio signal generator for the ESP32 module with PCM5102 DAC module.
 *  
 * The sine signal generation is based on the DDS principle.
 * 
 * History: 3rd Feb. 2021, creation
 * Author: Dr. Markus Reinhardt, 
 * 
 */
#include <Arduino.h>
#include <i2s.h>
#include "ESP8266DDSGenerator.h"
#include "I2SHandler.h"

// create the DDS signal generator
uint32_t sampleRate = 48000;
float frequency = 1000.0;
const uint16_t sineTableSize = 1024;
ESP8266DDSSignalGenerator sineGen(sampleRate, frequency, sineTableSize);

// create the I2S handler
I2SHandler i2sHandler(sampleRate);

void setup() 
{  
   i2sHandler.setup(); 
}

void loop() 
{
  uint32_t signalSample;
  signalSample = sineGen.getNextSample();
  i2sHandler.write2I2SBuffer(signalSample);
}
