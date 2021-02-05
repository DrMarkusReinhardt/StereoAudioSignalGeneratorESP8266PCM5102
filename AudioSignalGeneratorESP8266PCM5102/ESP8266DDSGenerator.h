/* ESP8266 Arduino library for a dual channel DDS sine signal generator

   Author: Dr. Markus Reinhardt
   History: 5th Feb. 2021, creation

*/
#pragma once

#include <Arduino.h>

class ESP8266DDSGenerator
{
  public:
    ESP8266DDSGenerator(float initSampleRate, float initfrequencyLeft, float initfrequencyRight, uint16_t initSineTableSize);
    void setup();
    void getNextSamples(uint16_t &sampleLeft, uint16_t &sampleRight);

  private:
     void createSineTable();
    
  private:
    float m_sampleRate;
    float m_samplePeriod;
    float m_frequencyLeft;
    float m_frequencyRight;
    float m_phaseIncrementLeft;
    float m_phaseLeft;
    float m_phaseIncrementRight;
    float m_phaseRight;
    uint16_t m_tableIndex;
    uint16_t m_sineTableSize;
    uint16_t *m_sineTable;
};
