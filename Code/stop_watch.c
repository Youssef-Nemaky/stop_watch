/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 25/10/2021
* Name: stop_watch.c 
==============================================================================
*/

#include "stop_watch.h"

/*
==============================================================================
*                            Static Functions Prototypes
==============================================================================
*/
static void disableDisplays();

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


/* 
 * This function gets called to display the time on the seven segments display
 */
void displayTime(const SEVENSEGMENT_config_t * seven_segment_configPtr){
    uint8 seven_seg_ctrl_counter = 0;
    for(seven_seg_ctrl_counter = 0; seven_seg_ctrl_counter < SEVEN_SEG_CONTROL_PINS; seven_seg_ctrl_counter++){
        disableDisplays();
        GPIO_writePin(SEVEN_SEG_CONTROL_PORT, seven_seg_ctrl_counter, HIGH);
        if(seven_seg_ctrl_counter % 2 == 0){
            SEVENSEGMENT_displayNumber(seven_segment_configPtr, g_time[(seven_seg_ctrl_counter / 2)] % 10);
        } else {
            SEVENSEGMENT_displayNumber(seven_segment_configPtr, g_time[(seven_seg_ctrl_counter / 2)] / 10);
        }
        _delay_ms(3);
    }
}

/* 
 * This function gets called to reset the time array
 */
void resetTime(void){
    uint8 counter;
    for(counter = 0; counter < TIME_ARR_LENGTH; counter++){
        g_time[counter] = 0;
    }
}

/* 
 * This function gets called to pause the timer
 */
void pauseTime(void){
    TIMER1_stop();
}
static void disableDisplays(){
    uint8 counter;
    for(counter = 0; counter < SEVEN_SEG_CONTROL_PINS; counter++){
        GPIO_writePin(SEVEN_SEG_CONTROL_PORT, counter, LOW);
    }
}