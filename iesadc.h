#ifndef IESADC_H
#define IESADC_H

#include <avr/io.h>
#include <stdio.h>
#include "iesusart.h"

// WTF. Why is there no header here? Always seperate declaration,
// documentation, and implementation! Clean this up if you use this!

#define DR_ADC0 DDRC
#define DP_ADC0 DDC0
#define IR_ADC0 PC0
#define IP_ADC0 PC0

#define DR_ADC1 DDRC
#define DP_ADC1 DDC1
#define IR_ADC1 PC1
#define IP_ADC1 PC1

#define DR_ADC2 DDRC
#define DP_ADC2 DDC2
#define IR_ADC2 PC2
#define IP_ADC2 PC2

// The following constants reflect table 23-4 of the ATMega328p-data-
// sheet. These constants
#define ADMUX_CHN_ADC0 0 // 0000 0000
#define ADMUX_CHN_ADC1 1 // 0000 0001
#define ADMUX_CHN_ADC2 2 // 0000 0010
#define ADMUX_CHN_ADC3 3 // 0000 0011
#define ADMUX_CHN_ALL 7 // 0000 1111

// Average some measurements to reduce probable noise.
#define ADC_AVG_WINDOW 20

// Well hmmm understand this by yourself. Become inspired.
#define ADCMSG "ADC0: %5u\tADC1: %5u\tADC2: %5u\n"

/** Initializes the ADC-unit. There is ONE single ADC unit on the
 * microcontroller, but different "channels" (input pins) can be
 * connected to the ADC via a MUX-register. The s4etup of the ADC is
 * done in this method, the MUX is used in the read-function.
 */
void ADC_init(void) ;

/** We have a 10-bit-ADC, so somewhere in memory we have to read that
 * 10 bits.  Due to this, this function returns a 16-bit-value.
 */
uint16_t ADC_read(uint8_t channel) ;

/** Used to read multiple measurements to reduce noise.
 */
uint16_t ADC_read_avg(uint8_t channel, uint8_t nsamples) ;
#endif
