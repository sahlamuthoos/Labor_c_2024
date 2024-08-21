
#include <avr/io.h>
#define F_CPU 16E6
#include <util/delay.h>


int main(void) {
	//Set Data Direction Register B5 as output.

DDRB = (1<<DDB2) ;

DDRD = (1<<DDD4) ;

PORTB = (1<<PORTB2) ;

while (1) {

  // Set pin/bit 5 to high (VCC) and wait half a sec.

  PORTD = (1<<PORTD4) ;

  _delay_ms (500) ;

  // Set pin/bit 5 to low (GND) and wait half a sec.

  PORTD &= ~ (1<<PORTD4) ;

 _delay_ms (500) ;
}
 return 0;
}
