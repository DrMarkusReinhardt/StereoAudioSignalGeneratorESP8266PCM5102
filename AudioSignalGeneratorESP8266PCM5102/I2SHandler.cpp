/*  Class I2SHandler
 *  
 *  Author: Dr. Markus Reinhardt
 *  History:  5th Feb. 2021, creation
 * 
 */
#include "I2SHandler.h"

#define write_sample(sample) while (i2s_write_sample_nb(sample)==0)

I2SHandler::I2SHandler(uint32_t initSampleRate) : m_sampleRate(initSampleRate)
{
  
}

void I2SHandler::setup()
{
  /*
  // i2s configuration 
  int i2s_num = 0; // i2s port number
  
  i2s_config_t i2s_config = 
  {
       .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
       .sample_rate = 48000,
       .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
       .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
       .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
       .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1, // high interrupt priority
       .dma_buf_count = 8,
       .dma_buf_len = 64,   // Interrupt level 1
       .use_apll = false,
       .tx_desc_auto_clear = false,
       .fixed_mclk = 0
      };
      
  i2s_pin_config_t pin_config = 
  {
      .bck_io_num = 26,   // this is BCK pin
      .ws_io_num = 25,    // this is LRCK pin
      .data_out_num = 22, // this is DATA output pin
      .data_in_num = -1   // Not used
  };
  
  */   
  /*
  // initialize i2s with configurations
  i2s_driver_install((i2s_port_t)i2s_num, &i2s_config, 0, NULL);
  i2s_set_pin((i2s_port_t)i2s_num, &pin_config);
  //set sample rates of i2s to a given sample rate
  i2s_set_sample_rates((i2s_port_t)i2s_num, sampleRate);
  */
  
  i2s_begin();
  i2s_set_rate(m_sampleRate);
}

void I2SHandler::write2I2SBuffer(uint32_t sample)
{
  write_sample(sample);
}
