#include <avr/io.h>
#include "iesusart.h"
#include "iesmotors.h"
#include <util/delay.h>
#include "iesadc.h"
#include <stdio.h>
#include "iessreg.h"
#include "iesisr.h"
#include "motors.h"



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
}
    return 0;
}

