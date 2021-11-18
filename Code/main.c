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
/* HAL Drivers */
#include "HAL/Button_Driver/button.h"
#include "HAL/Seven_Segment_Driver/seven_segment.h"
/* MCAL Drivers */
#include "MCAL/Timer_Driver/timer.h"
#include "MCAL/Gpio_Driver/gpio.h"
#include "MCAL/External_Interrupt_Driver/external_interrupt.h"

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
#define TIMER1_TICK_NUM 1

/*
==============================================================================
*                           Functions Prototypes
==============================================================================
*/
static void disableDisplays();
static void buttons_init();
static void SS_init();
static void timer_init();
static void external_interrupts_init();
static void set_ss_ctrl_pins_direction();
static void increaseTime(void);
static void displayTime(const SEVENSEGMENT_config_t * seven_segment_configPtr);
static void resetTime(void);
static void pauseTime(void);
static void resumeTime(void);
static void systemInit(void);
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

/* Structures */
static button_config_t button0;
static button_config_t button1;
static button_config_t button2;
static SEVENSEGMENT_config_t time_display;
static timer1_config_t timer1;

int main(void){
    /* Enable Global Interrupts */
    SREG |= (1<<7);

    systemInit();

    /* SUPER LOOP */
    while(1){
        displayTime(&time_display);
    }
    return 0;
}



void systemInit(void){
    external_interrupts_init();

    buttons_init();

    SS_init();

    timer_init();
    
}

void external_interrupts_init(void){
    /* External Interrupt 0 Initialization */
    EX_INT_enable(EXTERNAL_INTERRUPT_0_ID, EXT_INT_FALLING_EDGE_TRIGGER_INTERNAL_PULL_UP);
    EX_INT_setCallBack(resetTime, EXTERNAL_INTERRUPT_0_ID);

    /* External Interrupt 1 Initialization */
    EX_INT_enable(EXTERNAL_INTERRUPT_1_ID, EXT_INT_RISING_EDGE_TRIGGER);
    EX_INT_setCallBack(pauseTime, EXTERNAL_INTERRUPT_1_ID);

    /* External Interrupt 2 Initialization */
    EX_INT_enable(EXTERNAL_INTERRUPT_2_ID, EXT_INT_FALLING_EDGE_TRIGGER_INTERNAL_PULL_UP);
    EX_INT_setCallBack(resumeTime, EXTERNAL_INTERRUPT_2_ID);
}

void buttons_init(void){
    /* Button 0 Settings */
	button0.port_number = PORTD_ID;
    button0.pin_number  = PIN2_ID;
    button0.button_connection = BUTTON_PULLUP_CONNECTION;
    button0.internal_resistor = GPIO_INTERNAL_PULLUP_ENABLED;

    /* Button 1 Settings */
    button1.port_number = PORTD_ID;
    button1.pin_number = PIN3_ID;
    button1.button_connection = BUTTON_PULLDOWN_CONNECTION;
    button1.internal_resistor = GPIO_INTERNAL_RESISTOR_DISABLED;

    /* Button 2 Settings */
    button2.port_number = PORTB_ID;
    button2.pin_number = PIN2_ID;
    button2.button_connection = BUTTON_PULLUP_CONNECTION;
    button2.internal_resistor = GPIO_INTERNAL_PULLUP_ENABLED;

    BUTTON_init(&button0);
    BUTTON_init(&button1);
    BUTTON_init(&button2);

}

void SS_init(void){
    time_display.portNumber = PORTA_ID;
    time_display.portHalf = GPIO_FIRST_HALF;
    SEVENSEGMENT_init(&time_display);
    set_ss_ctrl_pins_direction();
}

void timer_init(void){
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
    timer1.timerMode = TIMER_CTC_MODE;
    timer1.timer_prescaler = T1_F_CPU_64;
    timer1.timer_initialValue = INITIAL_VALUE_TIMER1;
    timer1.timer_compareValueA = COMPARE_VALUE_TIMER1;
    timer1.timer_compareValueB = LOW;
    timer1.OC1APinMode = OC1_DISCONNECTED;
    timer1.OC1BPinMode = OC1_DISCONNECTED;
    timer1.channelA_ticks = TIMER1_TICK_NUM;
    timer1.channelB_ticks = LOW;

    /* Set TIMER1 callback function */
    TIMER1_setCallBack(increaseTime);

    TIMER1_init(&timer1);
}

static void set_ss_ctrl_pins_direction(){
    uint8 seven_seg_ctrl_pins_counter;
    /* Set the control pins of the 7-segment */
    for(seven_seg_ctrl_pins_counter = 0; seven_seg_ctrl_pins_counter < SEVEN_SEG_CONTROL_PINS; seven_seg_ctrl_pins_counter++){
        GPIO_setPinDirection(SEVEN_SEG_CONTROL_PORT,seven_seg_ctrl_pins_counter,PIN_OUTPUT);
    }
}
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
            if(g_time[TIME_HOURS_INDEX] > 99){
                g_time[TIME_HOURS_INDEX] = 0;
            }
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
    TIMER1_deInit();
    TIMER1_init(&timer1);
    TIMER1_stop();
}

/* 
 * This function gets called to pause the timer
 */
void pauseTime(void){
    TIMER1_stop();
}

/* 
 * This function gets called to resume the timer
 */
void resumeTime(void){
    TIMER1_start(&timer1);
}


static void disableDisplays(){
    uint8 counter;
    for(counter = 0; counter < SEVEN_SEG_CONTROL_PINS; counter++){
        GPIO_writePin(SEVEN_SEG_CONTROL_PORT, counter, LOW);
    }
}
