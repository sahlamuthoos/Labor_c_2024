/**
 * @file update_hardwareone.h
 */


#ifndef UPDATE_HARDWAREONE_h
#define UPDATE_HARDWAREONE_h

#include <avr/io.h>
#include <stdio.h>

// SR clock
#define DR_SR_CLK  DDRD
#define DP_SR_CLK  DDD4
#define OR_SR_CLK  PORTD
#define OP_SR_CLK  PORTD4

#define DR_SR_DATA DDRB
#define DP_SR_DATA DDB2
#define OR_SR_DATA PORTB
#define OP_SR_DATA PORTB2

#define REGWIDTH 3


typedef unsigned char srr_t;
typedef unsigned char cntv8_t;

/**
 *@brief
 * Clocks the real hardware -- whenever this is called,
 * a rising edge on PD4 is generated.  
 */
void clk();



/**
 *@brief 
 * Writes the in-memory-representation (the "model") of
 * the robot's shift-register to the real hardware. 
 * @param *regmdl This variable helps us use the line follower to make the LEDs blink and indicate the driving direction simultaneously.
 */
void update_hardware(srr_t *regmdl);


#endif
