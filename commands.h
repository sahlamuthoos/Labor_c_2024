/**
 * @file commands.h

*/

#ifndef COMMANDS_h
#define COMMANDS_h

#include <avr/io.h>
#include <stdio.h>
#include "motors.h"
#include "iesusart.h"
#include "iesisr.h"
//#include "driveone.h"
#include "iesadc.h"
#include "iesmotors.h"
#include <avr/wdt.h>
#include <util/delay.h>

#include <util/delay.h>
typedef unsigned char srr_t;
typedef unsigned char cntv8_t;
srr_t *regmdl;
srr_t last_model_state;
srr_t lastSeen;   
srr_t *onOffLight;

/**
 *@brief 
 * If the command "S" is pressed, then the robot should start moving.
 * @param roundCounter This variable counts how many times the robot drive over the start field.
 * @param *currentcommand This variable let the last received current command work.
 * @param *last_model_state This variable saves the last state of the line followers.
  */

void commandS(short *roundCounter, enum condition currentCommand, srr_t *regmdl, srr_t *lastSeen, srr_t *last_model_state);


/**
 *@brief 
 * If the command "P" is pressed, all motors will come to a halt.  
 * @param *currentcommand This variable let the last received current command work.
  */

void commandP1 (enum condition *currentCommand);

oid commandT(enum condition *currentCommand) ;
	

 void commandH(enum condition *currentCommand;
/**
 *@brief 
 * If the command "T" is pressed, then the robot will turn left and rotate in a circle.
 * @param *currentcommand This variable let the last received current command work.
  */

//void commandT(enum condition *currentCommand);


/**
 *@brief 
 * If the command "H" is pressed, then it will stop rotating in a circle and come to a halt.
 * @param *currentcommand This variable let the last received current command work.
  */



/**
 *@brief 
 *If no command is printed, then the motors do not move. Instead, only the lights blink, 
 * and they wait until a command is printed.
 * @param *roundCounter This variable counts how many times the robot drive over the start field.
 * @param *currentcommand This variable let the last received current command work.
 * @param *lastSeen This variable saves the last seen light.
 * @param *last_model_state This variable saves the last state of the line followers.
 * @param *regmdl This variable helps us use the line follower to make the LEDs blink and indicate the driving direction simultaneously.
 * @param *onOffLight This variable is for the LEDs to make them blink until the robot starts to drive.
 * @param *startField This variable is where the robot starts to drive.
 
  */
void command0(enum condition *currentCommand, srr_t *regmdl, char *startField, short *roundCounter,  srr_t *onOffLight, srr_t *lastSeen, srr_t *last_model_state);


/**
 *@brief 
 * The method ensures that the robot resets after completing all three rounds.
 */
void commandReset();



#endif
