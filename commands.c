#include "commands.h"


 void commandS(short *roundCounter, enum condition currentCommand, srr_t *regmdl, srr_t *lastSeen, srr_t *last_model_state) {
	*currentCommand = 's';	
	char lengthOfTime[110];
	if (*regmdl != *last_model_state) {
		update_hardware(regmdl);
		*last_model_state = *regmdl;
		}
				
	if (*regmdl != 0) {
		*lastSeen = *regmdl;
		} 
	if (*roundCounter >= 3){
		bothSidesStop();
		sprintf(lengthOfTime, "Finally finished", runTime);
		USART_print(lengthOfTime);	
		}
	if ( hZ > 62500) {
		
		if (*roundCounter == 0 ) {
			USART_print("Currently I go round 1 \n");
							
		} else if (*roundCounter == 1) {
			USART_print("Round 2\n");
							
		} else if (*roundCounter == 2) {
			USART_print("Round 3 \n");
							
		} 
			hZ = 0;
						
		}
 }

 void commandP1 (enum condition *currentCommand) {
	bothSidesStop();
	*currentCommand = 'P';
	USART_print("paused ...........zzz\n");
 }


 //void commandT(enum condition *currentCommand) {
	//*currentCommand = 'T';
	//turnRight();
	//USART_print("Lalala\n");	
 //}

 

 void command0(enum condition *currentCommand, srr_t *regmdl, char *startField, short *roundCounter,  srr_t *onOffLight, srr_t *lastSeen, srr_t *last_model_state) {
			
	USART_print ("Hey you,you know what to do! \n");
	update_model(regmdl, startField, roundCounter, 0);
	if(*regmdl !=  7) {
		if(*regmdl!= *last_model_state) {
			update_hardware(regmdl);
			*last_model_state = *regmdl;
		} else if (newHz > 31250) {
			*onOffLight = ~(*onOffLight);
			update_hardware(onOffLight);
			newHz = 0;
				
		}
	}
	
	if (hZ > 62500) {
		USART_print("same story ,different student \n");
		hZ = 0;
	}
}

void commandReset(){
	_delay_ms(3000);
	wdt_enable(WDTO_2S);
	clk();
}  
void commandT(enum condition *currentCommand) {
	*currentCommand = 'T';
	hardTurnRight();
	USART_print("Artifical trouble! Help me \n");	
 }

 void commandH(enum condition *currentCommand) {
	*currentCommand = 'H';
	bothSidesStop();
	USART_print("Thanks for help. Now please rescue and reset me! \n");
 }
