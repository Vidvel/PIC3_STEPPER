/*
 * File:   PIC3_PD2.c
 * Author: David Vela
 *
 * Created on 26 de febrero de 2020, 04:15 PM
 */

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)


#include <xc.h>
#include "stepperlib.h"
#include "i2clib.h"

char z;
char  signal = 0;
char dummyvar = 0;
uint8_t sel = 0;
uint8_t send = 0;

void __interrupt() ISR(void){
    if(PIR1bits.SSPIF == 1){ 
        SSPCONbits.CKP = 0;
       
        if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL)){
            z = SSPBUF;                 // Read the previous value to clear the buffer
            SSPCONbits.SSPOV = 0;       // Clear the overflow flag
            SSPCONbits.WCOL = 0;        // Clear the collision bit
            SSPCONbits.CKP = 1;         // Enables SCL (Clock)
        }

        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) {
            z = SSPBUF;                 // Lectura del SSBUF para limpiar el buffer y la bandera BF
            PIR1bits.SSPIF = 0;         // Limpia bandera de interrupción recepción/transmisión SSP
            SSPCONbits.CKP = 1;         // Habilita entrada de pulsos de reloj SCL
            while(!SSPSTATbits.BF);     // Esperar a que la recepción se complete
            signal = SSPBUF;             // Guardar en el PORTD el valor del buffer de recepción
            __delay_us(250);
            
        }else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){
            z = SSPBUF;
            BF = 0;
            SSPBUF = send; 
            SSPCONbits.CKP = 1;
            __delay_us(250);
            while(SSPSTATbits.BF);
        }
       
        PIR1bits.SSPIF = 0;    
    }
    else
        asm("nop");
}

void setup(void);

void main(void){
    setup();
    while(1){
        /*
        if ((signal == 1)&&(PORTBbits.RB7 == 0)){
            send = 0;
        }
        else if ((signal == 1)&&(PORTBbits.RB7 == 1)){
            send = 1;
        }
        else if ((signal == 0)&&(PORTBbits.RB6 == 0)){
            send = 0;
        }
        else if ((signal == 0)&&(PORTBbits.RB6 == 1)){
            send = 1;
        }*/
        if (signal == 1){
            for(int i=0;i<steps;i++){
                wave_drive(clockwise);
                signal = 0;
            }
        }
        else if (signal == 0){
            ;
        }
    }
}

void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    TRISB = 0b11000000;
    PORTB = 0b00000011;
    OSCCONbits.IRCF = 7; //Oscilador de 8MHz
    I2C_Slave_Init(0x20); // Definición como Slaver
}
