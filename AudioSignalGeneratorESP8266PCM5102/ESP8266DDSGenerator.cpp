/* ESP8266 Arduino library for a DDS signal generator

   Author: Dr. Markus Reinhardt
   History: 5th Feb. 2021, creation

*/

#include "ESP8266DDSGenerator.h"

ESP8266DDSSignalGenerator::ESP8266DDSSignalGenerator(float initSampleRate, float initFrequency, uint16_t initSineTableSize=1024)
 : m_sampleRate(initSampleRate), m_frequency(initFrequency), m_sineTableSize(initSineTableSize)
{
	m_samplePeriod = 1.0 / initSampleRate;
	m_phaseIncrement = m_sineTableSize * m_frequency * m_samplePeriod;
	m_phase = 0.0;
	createSineTable();
}

void ESP8266DDSSignalGenerator::createSineTable()
{
	float phaseIncrement = 2.0 * M_PI / ((float) m_sineTableSize);
	for(uint16_t k = 0; k < m_sineTableSize; k++)
	    m_sineTable[k] = sin(phaseIncrement*k);
}

uint32_t ESP8266DDSSignalGenerator::getNextSample()
{
	float sample_f;
  uint32_t sample_i;
	m_phase += m_phaseIncrement;
	m_tableIndex =  ((uint16_t) floorf(m_phase)) % m_sineTableSize;
	sample_f = m_sineTable[m_tableIndex];
  sample_i = (uint32_t) ((2>>30) * (sample_f+1.0));  // note the offset to get positive values
  return sample_i;
}
