/*
 * File:   stepperlib.c
 * Author: David Vela
 *
 * Created on 26 de febrero de 2020, 04:17 PM
 * Funciones extraídas de: 
 * https://circuitdigest.com/microcontroller-projects/interfacing-stepper-motor-with-pic16f877a
 */



#include <xc.h>
#include "stepperlib.h"
 

void full_drive (char direction){
    if (direction == anti_clockwise){
        PORTB = 0b00000011;
        ms_delay(speed);
        PORTB = 0b00000110;
        ms_delay(speed);
        PORTB = 0b00001100;
        ms_delay(speed);
        PORTB = 0b00001001;
        ms_delay(speed);
        PORTB = 0b00000011;
        ms_delay(speed);
    }
    if (direction == clockwise){
        PORTB = 0b00001001;
        ms_delay(speed);
        PORTB = 0b00001100;
        ms_delay(speed);
        PORTB = 0b00000110;
        ms_delay(speed);
        PORTB = 0b00000011;
        ms_delay(speed);
        PORTB = 0b00001001;
        ms_delay(speed);
    }
        
}
 
/* This method will drive the motor in half-drive mode using direction input */
 
void half_drive (char direction){
    if (direction == anti_clockwise){
        PORTB = 0b00000001;
        ms_delay(speed);
        PORTB = 0b00000011;
        ms_delay(speed);
        PORTB = 0b00000010;
        ms_delay(speed);
        PORTB = 0b00000110;
        ms_delay(speed);
        PORTB = 0b00000100;
        ms_delay(speed);
        PORTB = 0b00001100;
        ms_delay(speed);
        PORTB = 0b00001000;
        ms_delay(speed);
        PORTB = 0b00001001;
        ms_delay(speed);
    }
    if (direction == clockwise){
       PORTB = 0b00001001;
       ms_delay(speed);
       PORTB = 0b00001000;
       ms_delay(speed);
       PORTB = 0b00001100;
       ms_delay(speed); 
       PORTB = 0b00000100;
       ms_delay(speed);
       PORTB = 0b00000110;
       ms_delay(speed);
       PORTB = 0b00000010;
       ms_delay(speed);
       PORTB = 0b00000011;
       ms_delay(speed);
       PORTB = 0b00000001;
       ms_delay(speed);
    }
}
 
/* This function will drive the the motor in wave drive mode with direction input*/
 
void wave_drive (char direction){
    if (direction == anti_clockwise){
        PORTB = 0b00000001;
        ms_delay(speed);
        PORTB = 0b00000010;
        ms_delay(speed);
        PORTB = 0b00000100;
        ms_delay(speed);
        PORTB = 0b00001000;
        ms_delay(speed);
    }
     if (direction == clockwise){
        PORTB = 0b00001000;
        ms_delay(speed);
        PORTB = 0b00000100;
        ms_delay(speed);
        PORTB = 0b00000010;
        ms_delay(speed);
        PORTB = 0b00000001;
        ms_delay(speed);
    }
    
}

void ms_delay(unsigned int val)
{
     unsigned int i,j;
        for(i=0;i<val;i++)
            for(j=0;j<225;j++);
}
