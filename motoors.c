

#include "motors.h"



void leftMotorForward() {
	   // Set IN2 to LOW, nothing else HIGH -> No motors turn
    PORTB &= ~(1 << RIGHT_TIRE_BEHIND);

	// Set IN1 to HIGH and don't set IN2 to HIGH (leave LOW) -> Left motors FORWARD
    PORTD |= (1 << RIGHT_TIRE_FRONT); // Use OR, since overwriting will disable EN[A|B]!
    

	
}

void leftMotorBackward () {
	    // Set IN1 to LOW and don't set IN2 to HIGH (leave LOW) -> Left motors OFF
    PORTD &= ~(1 << RIGHT_TIRE_FRONT);
    
	
    // Set IN2 to HIGH and don't set anything else to HIGH -> Left motors BACKWARD
    PORTB |= (1 << RIGHT_TIRE_BEHIND);
	
} 

void rightMotorForward() {
	   // Set IN3 to LOW and don't set anything else to HIGH -> Right motors OFF
    PORTB &= ~(1 << LEFT_TIRE_BEHIND);


    // Set IN4 to HIGH and don't set anything else to HIGH -> Right motors FORWARD
    PORTB |= (1 << LEFT_TIRE_FRONT);
    
}

void rightMotorBackward () {
	   // Set IN4 to LOW, nothing else HIGH -> No motors turn
    PORTB &= ~(1 << LEFT_TIRE_FRONT);
 
     // Set IN3 to HIGH and don't set anything else to HIGH -> Right motors BACKWARD
    PORTB |= (1 << LEFT_TIRE_BEHIND);

    
}


void bothSidesForward() {
	setDutyCycle(PD5, NORMAL_SPEED);
    setDutyCycle(PD6, NORMAL_SPEED);
	rightMotorForward();
	leftMotorForward();
	

}

 void bothSidesBackward(){
	setDutyCycle(PD5, NORMAL_SPEED);
    setDutyCycle(PD6, NORMAL_SPEED);
	 rightMotorBackward();
	 leftMotorBackward();
 }
 void bothSidesStop (){
	     // Both sides stop
    PORTD &= ~(1 << RIGHT_TIRE_FRONT);//left
    PORTB &= ~(1 << RIGHT_TIRE_BEHIND);
    
    PORTB &= ~(1 << LEFT_TIRE_FRONT); //right
    PORTB &= ~(1 << LEFT_TIRE_BEHIND);
   
}
 
 
 void turnRight() {
	setDutyCycle(PD5, NORMAL_SPEED);
    setDutyCycle(PD6, NORMAL_SPEED);
	leftMotorForward();
	PORTB &= ~(1 << LEFT_TIRE_FRONT);//right
    PORTB &= ~(1 << LEFT_TIRE_BEHIND);
	 
 }
 
	
	
void turnLeft() {
	setDutyCycle(PD5, NORMAL_SPEED);
    setDutyCycle(PD6, NORMAL_SPEED);
	rightMotorForward();
	PORTD &= ~(1 << RIGHT_TIRE_FRONT);//left
    PORTB &= ~(1 << RIGHT_TIRE_BEHIND);
	
}

void hardTurnRight() {
	setDutyCycle(PD5, TURN_SPEED);
    setDutyCycle(PD6, TURN_SPEED);
	leftMotorForward();
	rightMotorBackward();
}

void hardTurnLeft() {
	setDutyCycle(PD5, TURN_SPEED);
    setDutyCycle(PD6, TURN_SPEED);
	rightMotorForward();
	leftMotorBackward();
	
}
