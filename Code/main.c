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

/*
==============================================================================
*                              Global Variables
==============================================================================
*/
/* An Array that contains the time where:
 * g_time[0] -> seconds
 * g_time[1] -> minutes
 * g_time[2] -> hours
 */
uint8 g_time[TIME_ARR_LENGTH] = {0};

void main(void){
    /* Timer Settings */
    timer1_config_t timer1 = {TIMER_CTC_MODE, T1_F_CPU_64, INITIAL_VALUE_TIMER1, 
    COMPARE_VALUE_TIMER1, LOW, OC1_DISCONNECTED, OC1_DISCONNECTED, 1, LOW};
    
    TIMER1_setCallBack(increaseTime);
    
    /* SUPER LOOP */
    while(1){

    }
}