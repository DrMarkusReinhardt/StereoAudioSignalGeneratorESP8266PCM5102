/* ESP8266 Arduino library for a dual channel DDS sine signal generator

   Author: Dr. Markus Reinhardt
   History: 5th Feb. 2021, creation

*/

#include "ESP8266DDSGenerator.h"

ESP8266DDSGenerator::ESP8266DDSGenerator(float initSampleRate, float initfrequencyLeft, float initfrequencyRight, uint16_t initSineTableSize)
 : m_sampleRate(initSampleRate), m_frequencyLeft(initfrequencyLeft), m_frequencyRight(initfrequencyRight), m_sineTableSize(initSineTableSize)
{
	m_samplePeriod = 1.0 / initSampleRate;
	m_phaseIncrementLeft  = m_sineTableSize * m_frequencyLeft  * m_samplePeriod;
  m_phaseIncrementRight = m_sineTableSize * m_frequencyRight * m_samplePeriod;
  m_phaseLeft  = 0.0;
  m_phaseRight = 0.0;
}

void ESP8266DDSGenerator::setup()
{
  createSineTable();
}

void ESP8266DDSGenerator::createSineTable()
{
	float phaseIncrement = 2.0 * M_PI / ((float) m_sineTableSize);
  m_sineTable = new uint16_t [m_sineTableSize];
	for(uint16_t k = 0; k < m_sineTableSize; k++)
	  m_sineTable[k] = (uint16_t)(16383 * (1.0 + sin(phaseIncrement*k)));
}

void ESP8266DDSGenerator::getNextSamples(uint16_t &sampleLeft, uint16_t &sampleRight)
{
	m_phaseLeft += m_phaseIncrementLeft;
	m_tableIndex =  ((uint16_t) floorf(m_phaseLeft)) % m_sineTableSize;
	sampleLeft = m_sineTable[m_tableIndex];
  m_phaseRight += m_phaseIncrementRight;
  m_tableIndex =  ((uint16_t) floorf(m_phaseRight)) % m_sineTableSize;
  sampleRight = m_sineTable[m_tableIndex];
}
