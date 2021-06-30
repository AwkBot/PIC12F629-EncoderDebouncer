/*
 * File:   encoder.c
 * Author: Carlos
 *
 * Created on June 20, 2021, 2:35 PM
 */


#include "encoder.h"

uint8_t old_AB = 0x00;
const   int8_t  enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

int8_t read_encoder(void) {
   uint8_t tmpValue = 0x00;
  
  // Read Encoder Clock Value
  if(encCK)
    tmpValue |= 0x02;
  
  // Read Encoder Data Value
  if(encDT)
    tmpValue |= 0x01;
  
  old_AB <<= 2;  //Save Previous Value
  old_AB |= tmpValue;
  tmpValue = (old_AB & 0x0f);
  return (enc_states[tmpValue]);
}
