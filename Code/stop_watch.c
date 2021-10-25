/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 25/10/2021
* Name: stop_watch.c 
==============================================================================
*/

#include "stop_watch.h"


/* This function gets called to increase the time 
 * It increases the seconds and if overflow occurs (second reaches 60), seconds 
 * become zero (overflow) and it increases minutes. if minutes becomes 60, overflow occurs
 * minutes become zero and hours variable is increased if hours become 255 (max value of uint8), 
 * overflow occurs and hours becomes zero and the stop watch starts again
 */
void increaseTime(void){
    g_time[TIME_SECONDS_INDEX]++;
    if(g_time[TIME_SECONDS_INDEX] >= MAX_SECONDS_COUNTER){
        g_time[TIME_SECONDS_INDEX] = LOW;
        g_time[TIME_MINUTES_INDEX]++;
        if(g_time[TIME_MINUTES_INDEX] >= MAX_MINUTES_COUNTER){
            g_time[TIME_MINUTES_INDEX] = LOW;
            g_time[TIME_HOURS_INDEX]++;
        }
    }
}
