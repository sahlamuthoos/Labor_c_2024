#include <avr/io.h>
#include "iesusart.h"
#include "iesmotors.h"
#include <util/delay.h>
#include "iesadc.h"
#include <stdio.h>

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
void leftdirection(){
	PORTD |= (1 << PD7);
    PORTB &= ~(1 << PB3);
	PORTB &= ~(1 << PB0);
    PORTB &= ~(1 << PB1);

}
void leftmotoroff(){
	PORTD &= ~(1 << PD7);
       
}
void leftBackward(){
	PORTB |= (1 << PB0);
}

void turnRight(){
	PORTD &= ~(1 << PD7);
    PORTB = (1 << PB3);
	PORTB &= ~(1 << PB0);
    PORTB &= ~(1 << PB1);

			 
}
void rightmotoroff(){
	PORTB &= ~(1 << PB1); 
} 
void rightBackward(){
	 PORTB |= (1 << PB1);
}

int main(void) {
	initial();
	USART_init(UBRR_SETTING);

    DR_ADC0 &= ~(1 << DP_ADC0);
    DR_ADC1 &= ~(1 << DP_ADC1);
    DR_ADC2 &= ~(1 << DP_ADC2);

    ADC_init();

    unsigned char strbuff[sizeof(ADCMSG) + 15]; // WTF, why + 15? Oo

    // Just to make things clear: You have to be extremely careful with
    // the size of the stringbuffer. Better safe than sorry! But memory
    // as well as time are so so so precious!

    uint16_t adcval0 = 0;
    uint16_t adcval1 = 0;
    uint16_t adcval2 = 0;
     short middle=0;
     short left=0;
     short right=0;
	while (1) {
		
       // adcval0 = ADC_read_avg(ADMUX_CHN_ADC0, ADC_AVG_WINDOW);
        //adcval1 = ADC_read_avg(ADMUX_CHN_ADC1, ADC_AVG_WINDOW);
        adcval2 = ADC_read_avg(ADMUX_CHN_ADC2, ADC_AVG_WINDOW);
        middle=adcval1>600;
        //right=adcval0 >500;
        //left=adcval2>500;
        if () {
			middle;
            forward();
            
           // USART_print("Moving straight\n");
        } else if (PIND & (1 << PIND2)
         {
			 right;
		     leftdirection();
		      setDutyCycle(PD6, 155);
			  rightBackward();
			  
          
			 //USART_print("Turning left\n");
        } else if (PINB & (1 << PINB2) 
        {
			left;
			 turnRight();
             setDutyCycle(PD5, 155);
           leftBackward();
             
			
            //USART_print("Turning right\n");
        } 
         
        
    
}
    
    return 0;
}

