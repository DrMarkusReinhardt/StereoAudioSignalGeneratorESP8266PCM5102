#include <i2s.h>
#include <i2s_reg.h>
#include "ESP8266DDSGenerator.h"

#define write_sample(data) while (i2s_write_sample_nb(data)==0)

// create the DDS signal generator
const uint32_t sampleRate = 10000;
const float frequency = 1000.0;
const uint16_t sineTableSize = 1024;
ESP8266DDSGenerator sineGen(sampleRate, frequency, sineTableSize);

void setup()
{
    Serial.begin(115200);
    delay(2000);
    pinMode(3, OUTPUT); // Override default Serial initiation
    digitalWrite(3,0); // Set pin low

    // setup the sine generator
    sineGen.setup();
    
    Serial.println(" ");
    Serial.println("Setup done");
}

void loop()
{
    static unsigned long last = millis();
    if (millis() - last > 3000) {
      outputDMA();
      last = millis();
    }
}

void outputDMA(void)
{
   i2s_begin();
   i2s_set_rate(10000);

   uint8_t state=0;
   for (int i=0; i<50000;i++) 
   {
    state = (i >> 12)%2; // Toggle every 4096 double-words
    if (state)
      write_sample(0xffffffff);
    else
      write_sample(0x00000000);
      
    if ((i % 1000) == 0) yield(); // without this get WDT resets
   }
   Serial.println(".");
   i2s_end();
}
