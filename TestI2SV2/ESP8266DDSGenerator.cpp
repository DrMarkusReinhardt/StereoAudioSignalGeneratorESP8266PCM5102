/* ESP8266 Arduino library for a DDS signal generator

   Author: Dr. Markus Reinhardt
   History: 5th Feb. 2021, creation

*/

#include "ESP8266DDSGenerator.h"

ESP8266DDSGenerator::ESP8266DDSGenerator(float initSampleRate, float initFrequency, uint16_t initSineTableSize)
 : m_sampleRate(initSampleRate), m_frequency(initFrequency), m_sineTableSize(initSineTableSize)
{
	m_samplePeriod = 1.0 / initSampleRate;
	m_phaseIncrement = m_sineTableSize * m_frequency * m_samplePeriod;
	m_phase = 0.0;
}
void ESP8266DDSGenerator::setup()
{
  createSineTable();
}

void ESP8266DDSGenerator::createSineTable()
{
	float phaseIncrement = 2.0 * M_PI / ((float) m_sineTableSize);
  m_sineTable = new float [m_sineTableSize];
	for(uint16_t k = 0; k < m_sineTableSize; k++)
	    m_sineTable[k] = sin(phaseIncrement*k);
}

float ESP8266DDSGenerator::getNextSample()
{
	float sample_f;
  uint32_t sample_i;
	m_phase += m_phaseIncrement;
	m_tableIndex =  ((uint16_t) floorf(m_phase)) % m_sineTableSize;
	sample_f = m_sineTable[m_tableIndex];
  return sample_f;
}
