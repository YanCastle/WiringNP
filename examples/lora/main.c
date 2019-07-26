#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#include <wiringPi.h>
#include "lora.h"

bool LoraTest(){

  uint8_t test = 0;
  
  LoraWrite( REG_LR_OPMODE, RFLR_OPMODE_SLEEP );            
  LoraWrite( REG_LR_OPMODE, 0x80|RFLR_OPMODE_SLEEP );       
  LoraWrite( REG_LR_OPMODE, 0x80|RFLR_OPMODE_STANDBY );
  
  LoraWrite( REG_LR_HOPPERIOD,0x91 );
  LoraRead( REG_LR_HOPPERIOD,&test);
  
  if(test!=0x91)
    return false;    
  else
    return true;
}


void main(){
    init();
    if(LoraTest()){
        printf('Test Success')
    }
}
