/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 25/10/2021
* Name: main.c 
==============================================================================
*/

/*
==============================================================================
*                            Include Files
==============================================================================
*/
#include "stop_watch.h"

void main(void){
    /* Timer Settings */
    timer1_config_t timer1 = {TIMER_CTC_MODE, T1_F_CPU_64, INITIAL_VALUE_TIMER1, 
    COMPARE_VALUE_TIMER1, LOW, OC1_DISCONNECTED, OC1_DISCONNECTED, 1, LOW};
    
    
    /* SUPER LOOP */
    while(1){

    }
}