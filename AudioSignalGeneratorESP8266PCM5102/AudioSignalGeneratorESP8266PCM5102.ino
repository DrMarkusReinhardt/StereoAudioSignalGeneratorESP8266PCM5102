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
uint32_t sampleRate = 44100;
float frequency = 2000.0;
const uint16_t sineTableSize = 1024;
ESP8266DDSGenerator sineGen(sampleRate, frequency, sineTableSize);

// create the I2S handler
I2SHandler i2sHandler(sampleRate);

void setup() 
{  
  Serial.begin(115200);
  sineGen.setup();
  i2sHandler.setup();
  delay(1000);
  Serial.println("");
  Serial.println("Setup done");
}

void loop() 
{
  float signalSample_f;
  uint32_t signalSample_i;
  int16_t signalSample_L;
  int16_t signalSample_R;

  uint8_t state=0;
  for (int i=0; i<10*sampleRate;i++) 
  { 
    signalSample_f = sineGen.getNextSample();
    signalSample_L = (int16_t) (16383 * (signalSample_f+1.0));  // note the offset to get positive values
    signalSample_R = signalSample_L;
    i2sHandler.write2I2SBufferLR(signalSample_L, signalSample_R);
    if ((i % 10000) == 0)
      yield(); // without this get WDT resets
  }
}
