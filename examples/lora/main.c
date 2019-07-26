#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#include <wiringPi.h>
#include "lora.h"



void main(){
    init();
    if(LoraTest()==1){
        printf("Test Success");
    }
    print("Test Finsh");
    return;
}

