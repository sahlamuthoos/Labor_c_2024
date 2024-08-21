
/**
 * @file motors.h
*/


#ifndef MOTORS_h
#define MOTORS_h


#include <avr/io.h>
#include <stdio.h>
#include "iesmotors.h"


#define MOTOR_LEFT DD5
#define MOTOR_RIGHT DD6
#define LEFT_INFRONT_OUTPUT DD7
#define LEFT_BEHIND_OUTPUT DD0
#define RIGHT_INFRONT_OUTPUT DD1
#define RIGHT_BEHIND_OUTPUT DD3
#define RIGHT_TIRE_FRONT PD7
#define RIGHT_TIRE_BEHIND PB0
#define LEFT_TIRE_FRONT PB3
#define LEFT_TIRE_BEHIND PB1 

#define NORMAL_SPEED 170
#define TURN_SPEED 200


/**
 *@brief 
 * Left motor drives forward
 * 
  */

void leftMotorForward() ;


/**
 *@brief 
 * Left motor drives backward
  */
void leftMotorBackward () ;


/**
 *@brief 
 * Right motor drives forward
  */
void rightMotorForward();


/**
 *@brief 
 * Right motor drives backward
  */
void rightMotorBackward ();


/**
 *@brief 
 * Right and left motors drive together forward
  */
void bothSidesForward();


/**
 *@brief 
 * Right and left motors drive together backward
  */
void bothSidesBackward();
 
 
/**
 *@brief 
 * Right and left motors stops to drive
  */
void bothSidesStop ();
 
 
 
/**
 *@brief 
 * Robot rotates right
  */
void turnRight();
 
	


/**
 *@brief 
 * Robot rotates left
  */	
void turnLeft();


/**
 *@brief 
 * Robot rotates harder (faster) right
  */
void hardTurnRight();


/**
 *@brief 
 * Robot rotates hard left
  */

void hardTurnLeft();

#endif
