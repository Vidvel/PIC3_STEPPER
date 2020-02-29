/* 
 * File:   stepperlib.h
 * Author: David Vela
 *
 * Created on 26 de febrero de 2020, 04:16 PM
 */

#ifndef STEPPERLIB_H
#define	STEPPERLIB_H
#define _XTAL_FREQ 8000000
#define speed 1 // Speed Range 10 to 1  10 = lowest , 1 = highest
#define steps 3000 // how much step it will take
#define clockwise 0 // clockwise direction macro
#define anti_clockwise 1 // anti clockwise direction macro
#include <xc.h> 
#include <pic16f887.h>
#include <stdint.h>

void full_drive (char direction); // This function will drive the motor in full drive mode
void half_drive (char direction); // This function will drive the motor in full drive mode
void wave_drive (char direction); // This function will drive the motor in full drive mode
void ms_delay(unsigned int val);
 

#endif	/* STEPPERLIB_H */

