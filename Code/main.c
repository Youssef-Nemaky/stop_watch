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
    /* External Interrupts Settings */
   
    /* External Interrupt 0
     * This will enable external interrupt 0 to work on falling edge with internal pull
     * resistor ON 
     */
    EX_INT_enable(EXTERNAL_INTERRUPT_0_ID, EXT_INT_FALLING_EDGE_TRIGGER_INTERNAL_PULL_UP);
    
   
    /* External Interrupt 1
     * This will enable external interrupt 1 to work on rising edge with internal pull
     * resistor OFF 
     */
    EX_INT_enable(EXTERNAL_INTERRUPT_1_ID, EXT_INT_RISING_EDGE_TRIGGER);
    
    /* External Interrupt 2
     * This will enable external interrupt 2 to work on rising edge with internal pull
     * resistor OFF 
     */
    EX_INT_enable(EXTERNAL_INTERRUPT_2_ID, EXT_INT_FALLING_EDGE_TRIGGER_INTERNAL_PULL_UP);

    
    /* Button 0 
     * This button is connected to INT0 pin which will trigger the external interrupt 0
     */

    button_config_t button0 = {PORTD_ID, PIN2_ID, BUTTON_PULLUP_CONNECTION,
    GPIO_INTERNAL_PULLUP_ENABLED};

    BUTTON_init(button0);
    
    /* Button 1
     * This button is connected to INT1 pin which will trigger the external interrupt 1
     */

    button_config_t button1 = {PORTD_ID, PIN3_ID, BUTTON_PULLDOWN_CONNECTION,
    GPIO_INTERNAL_RESISTOR_DISABLED};

    BUTTON_init(button1);

    /* Timer Settings */
    /*
     * By setting the config structure with these settings the timer1 will work on
     * 1) CTC(compare) mode
     * 2) Pre-scaler of 64
     * 3) initialValue of 0
     * 4) compareValue of 15625 (1 second)
     * 5) OC1A and OC1B both disconnected
     * 6) number of ticks is 1 as we want to fire an interrupt every 1 second
     */
    timer1_config_t timer1 = {TIMER_CTC_MODE, T1_F_CPU_64, INITIAL_VALUE_TIMER1, 
    COMPARE_VALUE_TIMER1, LOW, OC1_DISCONNECTED, OC1_DISCONNECTED, 1, LOW};
    
    /* Set TIMER1 callback function */
    TIMER1_setCallBack(increaseTime);
    
    /* Initialize the timer with the configurational structure */
    TIMER1_init(&timer1);

    /* SUPER LOOP */
    while(1){

    }
}