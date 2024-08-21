#include "command.h"
#include "iesusart.h"
#include "iesadc.h"
#include "iesmotors.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "iesisr.h"
 

void driveThreeRounds() {
	uint16_t adcval0, adcval1, adcval2;
  short middle, left, right;
 char lastright;
    static int counter = 0;
    static char startfeld = 0;
    static char modus = 'S';
    static char correctright = 0;
    static char correctleft = 0;

    if ((middle && right && left)) {          
        if (cnt > 1000 && !(startfeld)) {
            counter++;
            if (counter == 1) {
                USART_print("Currently I go round one\n");
            }
            if (counter == 2) {
                USART_print("YEAH YEAH, done first lap, feeling proud, going for lap 2/3\n");
            }
            if (counter == 3) {
                USART_print("YEAH YEAH, done 2nd lap, feeling proud, going for lap 3/3\n");
            }
            startfeld = 1;
            if (counter > 3) {
                stop();
                USART_print("Finally finished, It's over and done now, after Seconds \n");
                return;
            } 
        }
    } else {
        cnt = 0;
        startfeld = 0;
    }

    if (middle) {
        forward();
        correctright = 0;
        correctleft = 0;
    } else if (right) {
        if (correctright) {
            turnRight();
        } else {
            correctright = 1;
            correctleft = 0;
            moveRight(); 
        }
    } else if (left) {
        if (correctleft) {
            turnLeft();
        } else {
            correctleft = 1;
            correctright = 0;
            moveLeft(); 
        }
    } else if (!(middle) && !(left) && !(right)) {
        if (lastright) {
            correctright = 1;
            turnRight();
        } else {
            turnLeft();
            correctleft = 1;
        }
    }

    if (right || left) {
        lastright = right ? 1 : 0;
    }
}
