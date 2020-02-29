/* 
 * File:   i2clib.h
 * Author: David Vela
 *
 * Created on 19 de febrero de 2020, 01:36 PM
 */


#ifndef I2CLIB_H
#define	I2CLIB_H
#include <xc.h> 
#include <pic16f887.h>
#include <stdint.h>

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 8000000
#endif
//*****************************************************************************
// Función para inicializar I2C Maestro
//*****************************************************************************
void I2C_Master_Init(const unsigned long c);
//*****************************************************************************
// Función de espera: mientras se esté iniciada una comunicación,
// esté habilitado una recepción, esté habilitado una parada
// esté habilitado un reinicio de la comunicación, esté iniciada
// una comunicación o se este transmitiendo, el IC2 PIC se esperará
// antes de realizar algún trabajo
//*****************************************************************************
void I2C_Master_Wait(void);
//*****************************************************************************
// Función de inicio de la comunicación I2C PIC
//*****************************************************************************
void I2C_Master_Start(void);
//*****************************************************************************
// Función de reinicio de la comunicación I2C PIC
//*****************************************************************************
void I2C_Master_RepeatedStart(void);
//*****************************************************************************
// Función de parada de la comunicación I2C PIC
//*****************************************************************************
void I2C_Master_Stop(void);
//*****************************************************************************
//Función de transmisión de datos del maestro al esclavo
//esta función devolverá un 0 si el esclavo a recibido
//el dato
//*****************************************************************************
void I2C_Master_Write(unsigned d);
//*****************************************************************************
//Función de recepción de datos enviados por el esclavo al maestro
//esta función es para leer los datos que están en el esclavo
//*****************************************************************************
unsigned short I2C_Master_Read(unsigned short a);
//*****************************************************************************
// Función para inicializar I2C Esclavo
//*****************************************************************************
void I2C_Slave_Init(uint8_t address);
//*****************************************************************************

#endif	/* I2CLIB_H */

