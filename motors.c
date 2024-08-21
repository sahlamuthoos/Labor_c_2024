 
 # include "motors.h"
 #include "iesmotors.h"
 #include "iesusart.h"
 void initial() {
    // Set Data Direction Register C [0|1|2| as input.
    DDRC &= ~((1 << DDC0) | (1 << DDC1) | (1 << DDC2));

    // Initialize UART for debugging
    USART_init(UBRR_SETTING);

    // Set PD5 and PD6 as output (EN[A|B]!)
    DDRD |= (1 << PD5) | (1 << PD6);

    // Set PD7 as output (IN1)
    DDRD |= (1 << PD7);

    // Set PB0, PB1, and PB3 as output (IN[2|3|4])
    DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB3);

    // Make PWM work on PD[5|6]
    setupTimer0();

    // Initial duty cycles for PD5/PD6
    setDutyCycle(PD5, 155);
    setDutyCycle(PD6, 155);
    }
   
 
 void forward(){
	PORTB &= ~(1 << PB0);
    PORTB &= ~(1 << PB1);
	PORTD |= (1 << PD7);
    PORTB |= (1 << PB3);
    setDutyCycle(PD6, 150);
	setDutyCycle(PD5, 155);
    
    }
    void moveBackward(){
	PORTD &= ~(1 << PD7);
    PORTB &= ~(1 << PB3);
	PORTB |= (1 << PB0);
    PORTB |= (1 << PB1);

    }
    void stop(){
	// Both sides stop backward
    PORTB &= ~(1 << PB0);
    PORTB &= ~(1 << PB1);
	// Both sides stop
    PORTD &= ~(1 << PD7);
    PORTB &= ~(1 << PB3);

    
   }
    void turnRight(){
	setDutyCycle(PD6, 200);
	setDutyCycle(PD5, 200);
	PORTD |= (1 << PD7);
    PORTB &= ~(1 << PB3);
	PORTB &= ~(1 << PB0);
    
    PORTB |= (1 << PB1);


   }
    void turnLeft(){
	setDutyCycle(PD6, 200);
    setDutyCycle(PD5, 200);
	PORTD &= ~(1 << PD7);
    PORTB |= (1 << PB3);
	PORTB |= (1 << PB0);
    
    PORTB &= ~(1 << PB1);


  }
   void leftmotoroff(){
	PORTD &= ~(1 << PD7);
       
   }
   void leftBackward(){
	PORTB |= (1 << PB0);
   }
    void moveRight(){
	setDutyCycle(PD6, 170);
	setDutyCycle(PD5, 170);
	PORTD |= (1 << PD7);
    PORTB &= ~(1 << PB3);
	PORTB &= ~(1 << PB0);
    
    PORTB |= (1 << PB1);


   }
   void moveLeft(){
	setDutyCycle(PD6, 170);
    setDutyCycle(PD5, 170);
	PORTD &= ~(1 << PD7);
    PORTB |= (1 << PB3);
	PORTB |= (1 << PB0);
    
    PORTB &= ~(1 << PB1);


  }
   


  void rightmotoroff(){
	PORTB &= ~(1 << PB1); 
  } 
  void rightBackward(){
	 PORTB |= (1 << PB1);
  }
  void rotateClockwise(){
	   setDutyCycle(PD6,250);
	setDutyCycle(PD5, 250);
	//
	PORTD |= (1 << PD7);
	//link FORWARD 0
	 PORTB &= ~(1 << PB0);
	 
	//right motor forward
	PORTB |= (1 << PB1);
	
	 // right backward 0
	PORTB &= ~(1 << PB3);
	  
  }
