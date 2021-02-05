/* ESP8266 Arduino library for a DDS signal generator

   Author: Dr. Markus Reinhardt
   History: 5th Feb. 2021, creation

*/
#include <Arduino.h>

class ESP8266DDSSignalGenerator
{
public:
    ESP8266DDSSignalGenerator(float initSampleRate, float initFrequency, uint16_t initSineTableSize);
    uint32_t getNextSample();

private:
     void createSineTable();
    
private:
    float m_sampleRate;
    float m_samplePeriod;
    float m_frequency;
    float m_phaseIncrement;
    float m_phase;
    uint16_t m_tableIndex;
    uint16_t m_sineTableSize;
    float m_sineTable[];
};
