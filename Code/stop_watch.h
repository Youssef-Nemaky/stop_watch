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
*                               Definitions
==============================================================================
*/

#define INITIAL_VALUE_TIMER1 (0u)
#define COMPARE_VALUE_TIMER1 (15625u)

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


#endif /* STOP_WATCH_H_ */
