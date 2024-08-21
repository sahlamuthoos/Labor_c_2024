#include "iesmotors.h"
#include <util/delay.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "iesusart.h"
#include "iesadc.h"
#include "iesisr.h"
#include "motors.h"
#include "commands.h"
#include "driveone.h"
#include "update_hardwareone.h"

#include <avr/wdt.h>
#include <stdio.h>
#define DEBUG 0

/**
 * @brief 
 * Robot function/peripheral RIGHT LF.
 **/
#define DR_LF_R DDRC
#define DP_LF_R DDC0
#define IR_LF_R PINC
#define IP_LF_R PINC0

/**
 * @brief 
 * Robot function/peripheral MIDDLE LF.
 */
#define DR_LF_M DDRC
#define DP_LF_M DDC1
#define IR_LF_M PINC
#define IP_LF_M PINC1

/**
 * @brief 
 * Robot function/peripheral LEFT LF.
 */

#define DR_LF_L DDRC
#define DP_LF_L DDC2
#define IR_LF_L PINC
#define IP_LF_L PINC2

void setUp () {
		
    // Delete everything on ports B and D
    PORTD = 0;
    PORTB = 0;

    // Set PD5 and PD6 as output (EN[A|B]!)
    DDRD |= (1 << MOTOR_LEFT) | (1 << MOTOR_RIGHT);

    // Set PD7 as output (IN1)
    DDRD |= (1 << LEFT_INFRONT_OUTPUT);

    // Make PWM work on PD[5|6]
    setupTimer0();

    // Set PB0, PB1, and PB3 as output (IN[2|3|4])
    DDRB |= (1 << LEFT_BEHIND_OUTPUT) | (1 << RIGHT_INFRONT_OUTPUT) | (1 << RIGHT_BEHIND_OUTPUT);	
}


typedef unsigned char srr_t;
typedef unsigned char cntv8_t;

/**
 * @brief
 * Clears the in-memory-representation (the "model") of
 * the robot's shift-register.
*/
void clear(srr_t *regmdl) {
	
    *regmdl = 0;
    update_hardware(regmdl);
}


/**
 * @brief
 * Sets data directions.
*/
void setup_ddr_all() {
    // Set Data Direction Register B2 as output.
    DR_SR_DATA |= 1 << DP_SR_DATA;

    // Set Data Direction Register D4 as output. To D4,
    // the CLK-line of the robot's shift-register is connected.
    DR_SR_CLK |= 1 << DP_SR_CLK;

    // Set Data Direction Register C[0|1|2] as input. To these pins,
    // the robot's line-infrared-reflection-sensors are attached.
    DR_LF_L &= ~(1 << DP_LF_L);
    DR_LF_R &= ~(1 << DP_LF_R);
    DR_LF_M &= ~(1 << DP_LF_M);
}


int main(void) {
	
	setUp();
    // Set the duty cycles for PD5/PD6
    setDutyCycle(PD5, 155);
    setDutyCycle(PD6, 155);
    
    // Setup everything
    setup_ddr_all();
    USART_init(UBRR_SETTING);

    // Allocate 1 byte in memory/on heap for a representation (model)
    // of the register and clear the contents directly, and update
    // everything accordingly.
    srr_t *regmdl = malloc(sizeof(srr_t)); 
    srr_t last_model_state = *regmdl;
    srr_t lastSeen = *regmdl;
    clear(regmdl);
    ADC_init();
    
     cnt = 0;
	short roundCounter = 0;
	char startField = 1;
	setupTimer01();
	unsigned char command = 0;  
	short pauseCnt = 0;
	char lightCnt = 0;
	enum condition currentCommand = 0;
	enum condition lastCommand = 0;
	srr_t onOffLight = 0;
	char lengthOfTime[110];
	unsigned char startOnce = 0;
	
    while (1) {
			
	if (UCSR0A & (1 << RXC0)) {
		command = USART_receiveByte();
		lastCommand = currentCommand;	
		if (command == 'S') {
			update_model(regmdl, &startField, &roundCounter, 1);
			if (*regmdl == 7){
				USART_print("anything here\n");
				currentCommand = 'S';
			}			
		currentCommand = command;	
		} else if (command == 'P') { 
			
			if (lastCommand == 'P') { 
				currentCommand = 'S';
			} else {
				commandP1(&currentCommand);
			}				
		} else if (command == 'T') {		
			commandT(&currentCommand);
		} else if (command == 'H') {
			commandH(&currentCommand);
		
		} else if (command == 'E') {
			bothSidesBackward();
			hardTurnLeft();
			_delay_ms(3000);
			bothSidesStop();
			USART_print("Slay babes\n");	
		} 			
	 }	
	if (currentCommand == 0) {
		command0(&currentCommand, regmdl, &startField, &roundCounter, &onOffLight, &lastSeen, &last_model_state);
		
	} else if (currentCommand == 'S') {
		update_model(regmdl, &startField, &roundCounter, 1);
		drive(regmdl, lastSeen);
		commandS(&roundCounter, currentCommand, regmdl, &lastSeen, &last_model_state);
		/**
		 * @brief
		 * @param pauseCnt This variable controls the timing for the output of the message.
		 * @param lightCnt This varible is for the LEDs, which one should be on or off.
		 */ 		
	} else if (currentCommand == 'P') {
		if (hZ >= 1) {
					pauseCnt++;
					lightCnt++;
					hZ = 0;
					if (pauseCnt >= 2){
						USART_print("Pause ... zzzzzZZZzzz...wake me up with P again \n");
					}
				switch (lightCnt) {
					case 1:
						*regmdl = 1;
						update_hardware(regmdl);
						break;
					
					case 2: 
						*regmdl = 2;
						update_hardware(regmdl);
						break;
						
					case 3:
						*regmdl = 4;
						update_hardware(regmdl);
						break;
						
					case 4:
						*regmdl = 2;
						update_hardware(regmdl);
						lightCnt = 0;
						break;
				}
			}  
	}
		
	if (roundCounter > 3) {
		currentCommand == RESET;
		commandReset();
		break;
	} 
}
return 0; 	
}

