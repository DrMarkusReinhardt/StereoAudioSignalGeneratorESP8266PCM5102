/*  Class I2SHandler
 *  
 *  Author: Dr. Markus Reinhardt
 *  History:  5th Feb. 2021, creation
 * 
 */
#include "I2SHandler.h"

I2SHandler::I2SHandler(uint32_t initSampleRate) : m_sampleRate(initSampleRate)
{
}

void I2SHandler::setup()
{
  i2s_begin();
  i2s_set_rate(m_sampleRate);
}

void I2SHandler::write2I2SBufferLR(int16_t left, int16_t right)
{
  int sample = right & 0xFFFF;
  sample = sample << 16;
  sample |= left & 0xFFFF;
  while (i2s_write_sample_nb(sample)==0);
}

void I2SHandler::write2I2SBuffer(uint32_t sample)
{
  while (i2s_write_sample_nb(sample)==0);
}
