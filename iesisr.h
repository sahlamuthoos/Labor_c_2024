
/**
 * @file iesisr.h
*/

#ifndef IESISR_h
#define IESISR_h


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "iesusart.h"


#define OR_HEARTBEAT PORTB
#define OP_HEARTBEAT PB5
#define DR_HEARTBEAT DDRB
#define DP_HEARTBEAT DDB5


// We want to toggle the LED every 0.5s.
// In every second, 16E6/256=62500 interrupts are fired.
// In every half-second 62500/2=31250 ticks are fired.

/** 
 * Globale varibales 
  */
char counttime;
volatile uint16_t cnt;
volatile uint16_t hZ;
volatile uint16_t newHz;
volatile uint16_t secondsCounter;
volatile uint16_t runTime;
volatile uint16_t second;
volatile uint16_t centi_second;
/**
 * Time measurement
 */ 
ISR(TIMER1_COMPA_vect);

/**
 * @brief 
 * This method is responsible for time measurement
 */ 
void setupTimer01();

enum condition {
	
	START = 1,
	TURN = 2,
	HOLD = 3,
	PAUSE = 4,
	RESET = 5
	
};

#endif
