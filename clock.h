
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


  
  


void setupTimer01() ;




