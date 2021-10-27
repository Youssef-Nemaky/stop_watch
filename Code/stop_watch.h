/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 25/10/2021
* Name: stop_watch.h
==============================================================================
*/

#ifndef STOP_WATCH_H_
#define STOP_WATCH_H_

/*
==============================================================================
*                            Include Files
==============================================================================
*/
/* HAL Drivers */
#include "button.h"
#include "seven_segment.h"
/* MCAL Drivers */
#include "timer.h"
#include "MCAL/Gpio_Driver/gpio.h"
#include "external_interrupt.h"


/*
==============================================================================
*                               External Variables
==============================================================================
*/
extern uint8 g_time[TIME_ARR_LENGTH];

/*
==============================================================================
*                               Definitions
==============================================================================
*/

#define INITIAL_VALUE_TIMER1 (0u)
#define COMPARE_VALUE_TIMER1 (15625u)
#define TIME_ARR_LENGTH 3
#define TIME_SECONDS_INDEX 0
#define TIME_MINUTES_INDEX 1
#define TIME_HOURS_INDEX 2
#define MAX_SECONDS_COUNTER 60
#define MAX_MINUTES_COUNTER 60
#define SEVEN_SEG_CONTROL_PINS 6
#define SEVEN_SEG_CONTROL_PORT PORTC_ID
/*
==============================================================================
*                            Functions Prototypes
==============================================================================
*/

/* This function gets called to increase the time 
 * It increases the seconds and if overflow occurs (second reaches 60), seconds 
 * become zero (overflow) and it increases minutes. if minutes becomes 60, overflow occurs
 * minutes become zero and hours variable is increased if hours become 255 (max value of uint8), 
 * overflow occurs and hours becomes zero and the stop watch starts again
 */
void increaseTime(void);

/* 
 * This function gets called to display the time on the seven segments display
 */
void displayTime(const SEVENSEGMENT_config_t * seven_segment_configPtr);

#endif /* STOP_WATCH_H_ */
