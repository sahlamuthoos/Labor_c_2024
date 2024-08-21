#include <avr/io.h>
#include "iesusart.h"
#include "iesmotors.h"
#include <util/delay.h>
#include "iesadc.h"
#include <stdio.h>
#include "iessreg.h"
#include "iesisr.h"

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


  void rightmotoroff(){
	PORTB &= ~(1 << PB1); 
  } 
  void rightBackward(){
	 PORTB |= (1 << PB1);
  }

 int main(void) {
	initial();
	ADC_init();
    //Setup everything
    setup_ddr_all();
     //Allocate 1 byte in memory/on heap for a representation (model)
     //of the register and clear the contents directly, and update
     //everything accordingly.
    srr_t *regmdl = malloc(sizeof(srr_t));
    clear(regmdl);
    srr_t last_model_state = *regmdl;
    unsigned char strbuff[sizeof(ADCMSG) + 15]; 
    // WTF, why + 15? Oo
    // Just to make things clear: You have to be extremely careful with
    // the size of the stringbuffer. Better safe than sorry! But memory
    // as well as time are so so so precious!
    uint16_t adcval0 = 0;
    uint16_t adcval1 = 0;
    uint16_t adcval2 = 0;
    short middle=0;
    short left=0;
    short right=0;
    
   setupTimer01(); 
   int counter=0;
   char startfeld=0;
  char input=0;
  unsigned char some_letter = 'A' - 1;
  char modus=0;
	while (1) {
		adcval0 = ADC_read_avg(ADMUX_CHN_ADC0, ADC_AVG_WINDOW);
        adcval1 = ADC_read_avg(ADMUX_CHN_ADC1, ADC_AVG_WINDOW);
        adcval2 = ADC_read_avg(ADMUX_CHN_ADC2, ADC_AVG_WINDOW);
        middle=adcval1 > 600;
        right=adcval0 > 500;
        left=adcval2 > 500;
		update_model(regmdl,middle,left,right);
        if (*regmdl != last_model_state) {
           update_hardware(regmdl);
           last_model_state = *regmdl;
        }
        
        input=USART_receiveByte();
        if(input=='S'){
			modus='S';
		}
		if(modus=='S'){
        if ((middle && right && left)){			
			if (cnt>1000 && !(startfeld)){
				 counter++;
				if(counter==1){
					USART_print("Currently I go round one\n");
			    }
			    
			   
			    if(counter==2){
					USART_print("YEAH YEAH,done first  lap, feeling proud,going for loap 2/3\n");
			    }
			    if(counter==3){
					USART_print("YEAH YEAH,done 2nd lap, feeling proud,going for loap 3/3\n");
			    }
			    startfeld=1;
				if(counter >3){
					stop();
					USART_print("Finally finished,It's over and done now,after Seconds \n");
					return 0;
		        } 
             }
		 }
		 else{
			 cnt=0;
			 startfeld=0;
		 }
		
        if (middle) {
            forward();
            
        } else if (right) {
			 turnRight();
			
        } else if (left) {
			turnLeft();
			
        } 
	} 
   }
   //if(input=='P'){
	  // stop();
   //}
    
    return 0;
}
