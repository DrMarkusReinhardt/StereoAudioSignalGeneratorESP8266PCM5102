/*  Class I2SHandler
 *  
 *  Author: Dr. Markus Reinhardt
 *  History:  5th Feb. 2021, creation
 * 
 */
#pragma once

#include <stdint.h>
#include <i2s.h>
#include <i2s_reg.h>

class I2SHandler
{
  public:
    I2SHandler(uint32_t initSampleRate);
    void setup();
    void write2I2SBuffer(uint32_t sample);
    
  private:
    uint32_t m_sampleRate;
};
