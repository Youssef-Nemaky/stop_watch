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

#endif /* STOP_WATCH_H_ */
