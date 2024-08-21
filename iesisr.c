
#include "iesisr.h"





// We want to toggle the LED every 0.5s.
// In every second, 16E6/256=62500 interrupts are fired.
// In every half-second 62500/2=31250 ticks are fired.
//rename half second

uint16_t cnt2=0;
ISR(TIMER1_COMPA_vect) {
  cnt+=1;
  cnt2+=1;

  if(cnt2==62500){
	  second=1;
	  if(counttime){
	   runTime+=1;
  }
	  cnt2=0;
  }
  if(cnt%6250==0){
	  centi_second=1;
  }
  
  
  
}

void setupTimer01() {
  cli();                   // Disable interrupts!
  TCCR1B |= (1 << CS10);   // Prescaler: 1 => 16E6 ticks/second
  TCCR1B |= (1 << WGM12);  // Use Timer 1 in CTC-mode
  TIMSK1 |= (1 << OCIE1A); // Enable compare-match-interrupt for OCR1A
  OCR1A = 255;             // Every 16E6/256 ticks COMPA_vect is fired.
                           // This equals an (non-existent) 512-clock-
                           // divisor. We need this information for
                           // later calculations.
                           // BTW: Keep in mind that there is one more
                           // OCR-register for timer 1, which you can
                           // use to do some more neat stuff.
                           // BTW^2: Remember that OCR1[A|B] are 16 bit!
  sei();                   // Enable interrupts!
}


