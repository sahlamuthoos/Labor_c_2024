#include <avr/io.h>
#include "iesusart.h"
#include "iesmotors.h"
#include <util/delay.h>
#include "iesadc.h"
#include <stdio.h>
#include "iessreg.h"
#include "iesisr.h"
#include "motors.h"
#include <avr/wdt.h>
#include <avr/interrupt.h>

 uint16_t elpsed_seconds=0;
ISR(TIMER1_COMPA_vect) {
  cnt+=1;
  if(cnt>=31250){
	  elpsed_seconds++;
	  cnt=0;
  }
void setupWatchdogTimer() {
    wdt_reset();
    WDTCSR |= (1 << WDCE) | (1 << WDE);
    WDTCSR = (1 << WDE) | (1 << WDP2) | (1 << WDP1); // Set for ~2s timeout
}

void resetWatchdogTimer() {
    wdt_reset();
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
    char lastright =0;
    
   setupTimer01(); 
   int counter=0;
   char startfeld=0;
  char input=0;
  unsigned char some_letter = 'A' - 1;
  char modus=0;
  char correctright=0;
  char correctleft=0;
 uint16_t total_seconds=0;
 USART_init(103);

	while (1) {
		adcval0 = ADC_read_avg(ADMUX_CHN_ADC0, ADC_AVG_WINDOW);
        adcval1 = ADC_read_avg(ADMUX_CHN_ADC1, ADC_AVG_WINDOW);
        adcval2 = ADC_read_avg(ADMUX_CHN_ADC2, ADC_AVG_WINDOW);
        middle=adcval1 > 500;
        right=adcval0 > 450;
        left=adcval2 > 350;
		update_model(regmdl,middle,left,right);
        if (*regmdl != last_model_state) {
           update_hardware(regmdl);
           last_model_state = *regmdl;
        }
        
        input=USART_receiveByte();
        if(input=='S'){
			modus='S';
			USART_print("Here I am once more, going down the only round I've ever known...\n");
             uint16_t elapsed_seconds = 0; // Reset elapsed time counter
		}else if((input=='P')&&(modus=='S')){
			modus='P';
			}
			else if((input=='T')&&((modus=='S')||(modus=='P'))){
			modus='T';
			}else if((input=='H')&&(modus=='T')){
			modus=='H';
			}
			else if (input=='E'){
			modus='E';
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
					total_seconds=elapsed_seconds;
					char final_message[100];
					sprintf(final_message,"Finally finished after %d second",total_seconds);
					USART_print(final_message);
					_delay_ms(5000);
					setupWatchdogTimer();
					while(1);
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
            correctright=0;
			 correctleft=0;
            
        } else if (right) {
			if(correctright){
				turnRight();
			}else{
			 correctright=1;
			 correctleft=0;
			 moveRight(); 
			 }
			
        } else if (left) {
			if(correctleft){
				turnLeft();
			}else{
			 correctleft=1;
			 correctright=0;
			 moveLeft(); 
			 }
			
			
        } 
        
        
        else if(!(middle)&&!(left)&&!(right)){
			 
        if(lastright){
			correctright=1;
			turnRight();
		}
		else{
			turnLeft();
			correctleft=1;
			}
		}
		if(right || left){
			if(right){
				lastright=1;
			}else{
				lastright=0;
			}
   }
  }
  if(modus=='T'){
	  rotateClockwise();
	  
	  USART_print("LalaLa \n");
  }
  
  if(modus=='H'){
	  stop();
  }
  if(modus=='P'){
	  stop();
	  USART_print("Paused ........zzzzz ....P agein to unpause me\n");
	 // if(input=='P'){
		//  forward();
	 // }
	  
	  
  }
  
}
    return 0;
}

