#include "iesmotors.h"
#include <avr/io.h>
//#define F_CPU 16E6
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "iesusart.h"
#include <limits.h>

#define ADC0 PC0
#define ADC1 PC1
#define ADC2 PC2

#define ECHO PB4
#define TRIGGER PB5
#define TRANSISTOR PC3

#define ENA  DD5 // l
#define IN1  PD7 // l
#define IN2  PB0 // l

#define ENB  DD6 // r
#define IN3  PB1 // r
#define IN4  PB3 // r

				 // l: left; m: middle; r: right; 

#define SENSOR_PIN_L  PINB2
#define SENSOR_PIN_M  PIND4
#define SENSOR_PIN_R  PIND2

/*
#define SENSOR_L (int)((PINB & (1 << SENSOR_PIN_L)) > 0)
#define SENSOR_M (int)((PIND & (1 << SENSOR_PIN_M)) > 0)
#define SENSOR_R (int)((PIND & (1 << SENSOR_PIN_R)) > 0)
*/
//#define SENSORS (int)2*2*SENSOR_L + 2*SENSOR_M + SENSOR_R

#define LED_L  PC0
#define LED_M  PC1
#define LED_R  PC2




unsigned int cnt = 0;
unsigned int cnt2 = 0;
//Ultraschall
unsigned int echo_start = 0;
unsigned int echo_end = 0;
unsigned int echo_duration = 0;

void setSpeed(int left, int right){
	// Set the duty cycles for PD[5|6]
    setDutyCycle(PD5, left); // left motors 0 - 255
    setDutyCycle(PD6, right); // right motors 0 - 255
}

ISR (TIMER2_COMPA_vect) {
  cnt+=1;
  cnt2+=1;
}

void setupTimer2() {
  cli();
  TCCR2B = (1<<CS00); // Prescaler: 1
  TIMSK2 |= (1<<OCIE2A);
  TCCR2A = (1<<WGM01);
  TCNT2 = 0;  
  OCR2A = 255; 
  sei();
}

void ADC_Init(void) {
  ADMUX = (1<<REFS0);    
  ADCSRA = (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
  ADCSRA |= (1<<ADEN);
  ADCSRA |= (1<<ADSC); // Single conversion
  while (ADCSRA & (1<<ADSC) );
  ADCW; // Read once to "warm up" ADC.
}

uint16_t ADC_Read(uint8_t channel) {
  ADMUX = (ADMUX & ~(0x1F)) | (channel & 0x1F);
  ADCSRA |= (1<<ADSC);
  while (ADCSRA & (1<<ADSC) );
  return ADCW;                    
}

uint16_t ADC_Read_Avg(uint8_t channel, uint8_t nsamples) {
  uint32_t sum = 0;

  for (uint8_t i = 0; i < nsamples; ++i ) {
    sum += ADC_Read( channel );
  }

  return (uint16_t)( sum / nsamples );
}

ISR(PCINT0_vect) {
    if (PINB & (1 << ECHO)) {
        // JUST RISEN
        PORTC |= (1 << PC0);
        PORTC &= ~(1 << PC2);
        echo_start = cnt;
    } else {
        // JUST FALLEN
        PORTC |= (1 << PC2);
        PORTC &= ~(1 << PC0);
        if (cnt < echo_start) {
            // Need to do something pretty here.
            echo_duration  = UINT_MAX - echo_start + cnt;
        }
        else{
			echo_duration = cnt - echo_start;
		}
		echo_duration = cnt - echo_start;
	}
}
const int time = 25;

void lightLOn(){
	PORTC |= (1 << LED_L);
}

void lightMOn(){
	PORTC |= (1 << LED_M);
}

void lightROn(){
	PORTC |= (1 << LED_R);
}

void lightLOff(){
	PORTC &= ~(1 << LED_L);
}

void lightMOff(){
	PORTC &= ~(1 << LED_M);
}

void lightROff(){
	PORTC &= ~(1 << LED_R);
}

void drive_forward(){
	setSpeed(225,225);
	PORTD |= (1 << IN1);
	PORTB &= ~(1 << IN2);
	PORTB &= ~(1 << IN3);
	PORTB |= (1 << IN4); 
}

void drive_right(){
	/*
	PORTD |=  (1 << IN1); 
	PORTB &= ~(1 << IN2); 
	PORTB &= ~(1 << IN3);
	PORTB &= ~(1 << IN4); 
	*/
	setSpeed(225,150);
	PORTD |= (1 << IN1);
	PORTB &= ~(1 << IN2);
	PORTB &= ~(1 << IN3);
	PORTB |= (1 << IN4); 
}

void drive_right_2(){
	/*
	PORTD |=  (1 << IN1); 
	PORTB &= ~(1 << IN2); 
	PORTB &= ~(1 << IN3);
	PORTB &= ~(1 << IN4); 
	*/
	setSpeed(255,100);
	PORTD |= (1 << IN1);
	PORTB &= ~(1 << IN2);
	PORTB &= ~(1 << IN3);
	PORTB |= (1 << IN4); 
}

void drive_left(){
	/*
	PORTD &= ~(1 << IN1);
	PORTB &= ~(1 << IN2);
	PORTB &= ~(1 << IN3);
	PORTB |= (1 << IN4); 
	*/
	setSpeed(150,225);
	PORTD |= (1 << IN1);
	PORTB &= ~(1 << IN2);
	PORTB &= ~(1 << IN3);
	PORTB |= (1 << IN4); 
	}

void drive_left_2(){
	/*
	PORTD &= ~(1 << IN1);
	PORTB &= ~(1 << IN2);
	PORTB &= ~(1 << IN3);
	PORTB |= (1 << IN4); 
	*/
	setSpeed(100,255);
	PORTD |= (1 << IN1);
	PORTB &= ~(1 << IN2);
	PORTB &= ~(1 << IN3);
	PORTB |= (1 << IN4); 
	}

void turn_left(){
	setSpeed(225,225);
	PORTD &= ~(1 << IN1);
	PORTB |= (1 << IN2);
	PORTB &= ~(1 << IN3); 
	PORTB |= (1 << IN4); 	
}

/*
void turn_left_2(){
	setSpeed(255,255);
	PORTD &= ~(1 << IN1);
	PORTB |= (1 << IN2);
	PORTB &= ~(1 << IN3); 
	PORTB |= (1 << IN4); 	
}
*/
void turn_right(){
	setSpeed(225,225);
	PORTD |= (1 << IN1);
	PORTB &= ~(1 << IN2);
	PORTB |= (1 << IN3);
	PORTB &= ~(1 << IN4); 
	}
	
void drive_backward(){
	setSpeed(225,225);
	PORTD &= ~(1 << IN1);
	PORTB |= (1 << IN2);
	PORTB |= (1 << IN3);
	PORTB &= ~(1 << IN4); 
	}

void stop(){
	PORTD &= ~(1 << IN1);
	PORTB &= ~(1 << IN2);
	PORTB &= ~(1 << IN4); 
	PORTB &= ~(1 << IN3); 
}


int lightSensors(int i){
	switch (i) {
		case 0:
			lightLOff();
			lightMOff();
			lightROff();
			return i;
		case 1:
			lightLOff();
			lightMOff();
			lightROn();
			return i;
		case 2:
			lightLOff();
			lightMOn();
			lightROff();
			return i;
		case 3:
			lightLOff();
			lightMOn();
			lightROn();
			return i;
		case 4:
			lightLOn();
			lightMOff();
			lightROff();
			return i;
		case 5:
			lightLOn();
			lightMOff();
			lightROn();
			break;
		case 6:
			lightLOn();
			lightMOn();
			lightROff();
			return i;
		case 7:
			lightLOn();
			lightMOn();
			lightROn();
			return i;
	}
}


void setupPCINTPB4() {
    cli();
    PCICR |= (1<<PCIE0);
    PCMSK0 |= (1<<PCINT4);
    sei();
}
void setup(){
	// Setup for dirving
	// Delete everything on ports B and D
    DDRD = 0;
    DDRB = 0;
    
    // Set PD5 and PD6 as output (EN[A|B]!)
    DDRD = (1 << ENA) | (1 << ENB);
    
    // Set PD7 as output (IN1)
    DDRD |= (1 << DD7);
    
    // Set PB0, PB1, and PB3 as output (IN[2|3|4]) 
    DDRB = (1 << DD0) | (1 << DD1) | (1 << DD3);
    
    // Make PWM work on PD[5|6]
    setupTimer0();
    
    // Set the duty cycles for PD[5|6]
    setDutyCycle(PD5, 155); // left motors
    setDutyCycle(PD6, 155); // right motors
    
    // Setup for Infrared-Sensor
    // Set Data Direction Register C [0|1|2| as intput.
    DDRC &= ~((1 << DDC0) | (1 << DDC1) | (1 << DDC2));
    DDRC &= ~((1 << ADC0) | (1 << ADC1)| (1 << ADC2));
    DDRC |= (1 << TRANSISTOR);
    
    
    
    // Set Data Direction Register B [2] as input.
    DDRB &= ~(1<<DDB2);
    
    // Set Data Direction Register D [2|4] as input.
    DDRD &= ~((1<<DDD2) | (1<<DDD4));
    
    
    USART_Init(UBRR_SETTING);
    
    
    // New sensors_analog
    
    // Transitor disconnects (disconnects: keine LEDS, sondern Motor. connects: LEDS)
    PORTC |= (1 << TRANSISTOR);
    setupTimer2();
    ADC_Init();
    USART_Init(UBRR_SETTING);
    
    // Ultraschall
    DDRB |= (1 << TRIGGER);
    DDRB &= ~(1 << ECHO);
	setupPCINTPB4();
	
    
}

int get_sensors(){
	int sensor_r = 0;
	int sensor_m = 0;
	int sensor_l = 0;
	
	int value_r = ADC_Read_Avg(0, 3); //20
	int value_m = ADC_Read_Avg(1, 3);
	int value_l = ADC_Read_Avg(2, 3);
	
	if ( value_r > 400 ) { // rechts 700
		sensor_r = 1;
	}
	
	if (value_m > 250 ) { // mitte 200
		sensor_m = 1;
	} 
	
	if (value_l > 250 ) { // links 200
		sensor_l = 1;
	} 
	/*
	char strbuff[17];
	sprintf(strbuff, "%u", value_l);
        USART_print(strbuff);
        USART_print("   ");
        sprintf(strbuff, "%u", value_m);
        USART_print(strbuff);
        USART_print("   ");
        sprintf(strbuff, "%u", value_r);
        USART_print(strbuff);
        USART_print("\n");
     */
	return 2*2*sensor_l + 2*sensor_m + sensor_r;
}


void avoid_obstacle(){
	setSpeed(255, 255);
	drive_backward();
	_delay_ms(200);
	
	turn_right();
	_delay_ms(260);
	
	drive_forward();
	_delay_ms(330);
	
	turn_left();
	_delay_ms(260);
	
	drive_forward();
	_delay_ms(700);
	
	turn_left();
	_delay_ms(260);
	
	while(get_sensors() == 0){
				drive_right_2();
			}
}
	
/*
int main(void) {
	setup();
	while(1){
		turn_right();
	}
	return 0;
	}
*/

int ultrasonic(){
	float ticks_per_of = 16E6 / 256.0;
	float of_per_sec = 1 / ticks_per_of;
	float m_per_sec = 333.0;
	static int last_distance = 20; // static ist nur einmal am Anfang und Global
	if (last_distance <= 12){
		last_distance = 20;
	}
	
	if (cnt * of_per_sec > 0.35) {
		PORTB &= ~(1 << TRIGGER);
		_delay_us(10);
		PORTB |= (1 << TRIGGER);
		_delay_us(10);
		PCMSK0 |= (1<<PCINT4);
		cnt = 0;
		PCMSK0 &= ~(1<<PCINT4);
		PORTB &= ~(1 << TRIGGER);
		_delay_us(2);
		PCMSK0 |= (1<<PCINT4);
		_delay_ms(25); //10
		/*
		char strbuff[17];
		USART_print("ECHO DURATION: ");
		sprintf(strbuff, "%u", echo_duration);
		USART_print(strbuff);
		*/
		

		float distance = echo_duration * of_per_sec * m_per_sec / 2.0 * 100;
		last_distance = (int) distance;
	}
	
	/*
	USART_print("     OBSTACLE DISTANCE: ");
	sprintf(strbuff, "%u", idis);
	USART_print(strbuff);
	USART_print("\n"); 
	*/
	
	return last_distance;
	}
	
int main(void) {
	setup();
	const int array_size = 20;
	int remember[array_size];
	for (int i = 0; i<array_size; i++){
		remember[i] = 2;
	}
	
	int index = 0;
	int count7 = 0;
	int count = 0;
	int countblack = 0;
	int z = get_sensors();
	int time = 1;
	int round = 0;
	int help = 0;
	/*
	extern int start;
	extern int end;
	*/
	
    while (1) {
		stop();
		
		/*
		USART_print("start:\n");
		char strbuff[50];
        sprintf(strbuff, "%u %u %u %u %u %u %u %u %u %u ", remember[0], remember[1], remember[2], remember[3], remember[4], remember[5], remember[6], remember[7], remember[8], remember[9]);
		USART_print(strbuff);
		USART_print("\n");
		*/
		
		/* start, end usart::
		while(start != 1 ||  z != 7){
			z = get_sensors();
		}
		z = get_sensors();
		*/
		if(help == 0){
			DDRC |= ((1 << DDC0) | (1 << DDC1) | (1 << DDC2));
			DDRC |= (1 << TRANSISTOR);
			PORTC |= (1 << LED_L);
			_delay_ms(5000);
			
			help = 1;
			PORTC &= ~(1 << LED_L | 1 << LED_M | 1 << LED_R);
			PORTC &= ~(1 << TRANSISTOR);
			DDRC &= ~((1 << DDC0) | (1 << DDC1) | (1 << DDC2));
		}
		
		if (ultrasonic()<= 12){
			avoid_obstacle();
			round++;
			z = 1;
		}
		
		count7 = 0;
		for (int i = 0; i < array_size; i++){
			if (remember[i] == 7){
				count7++;
				} 
			}
		
		if (count7 >= array_size-2 && z != 7 && remember[(index + array_size - 1) % array_size] == 7){
				if(round >= 3){
					stop();
						USART_print("YAY, FINISHED!");
					return 0;
				}
				while(get_sensors() == 0){
					drive_right_2;
				}	
				z = 3;
				remember[index] = 3; // Enum machen, alles groß
		}
		
		
		if (z == 0 || z == 5){
			if (remember[(index+array_size-1)%array_size] == 4){
				z = 6;
				}
			else if (remember[(index+array_size-1)%array_size] == 1){
				z = 3;
				}
			else{
				z = remember[(index+array_size-1)%array_size];
			}
		}	
		
		
        switch (z) {
			case 1:
				remember[index] = z;			
				drive_right();
				_delay_ms(time);
				break;
				
			case 2:
				remember[index] = z;
				drive_forward();
				_delay_ms(time);
				break;
				
			case 3:	
				remember[index] = z;
				turn_right();
				_delay_ms(time);
				break;
				
			case 4:
				remember[index] = z;
				drive_left();
				_delay_ms(time);
				break;
				
			case 6:
				remember[index] = z;
				turn_left();
				_delay_ms(time);
				break;
				
			case 7:
				remember[index] = 7;
				drive_forward();
				_delay_ms(time);
				break;
		}
		index = (index+1)%array_size;
		
	}
	stop();
    return 0;
}
