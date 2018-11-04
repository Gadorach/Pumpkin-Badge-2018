#ifndef __I2C_H
#define __I2C_H

// Define i2c pins
#define SDA			LATAbits.LATA0				// Data Latch pin for i2c
#define SCK			LATAbits.LATA1              // Clock Latch pin for i2c
#define SDA_IN      PORTAbits.RA0               // Data Input pin for i2c
#define SCK_IN      PORTAbits.RA1               // Clock Input pin for i2c
#define SDA_DIR		TRISAbits.TRISA0			// Data Tris pin direction
#define SCK_DIR		TRISAbits.TRISA1			// Clock Tris pin direction

#define DataPinADCMask		TRISAbits.TRISA0	// It is attached on RA1(AN1) pin
#define ClockPinADCMask		TRISAbits.TRISA1	// It is attached on RA2(AN2) pin

// Define i2c speed
#define I2C_SPEED	400				    // kbps
#define HalfBitDelay 500/I2C_SPEED      // usec

// Define macros
#define Set_SDA_Low		SDA_DIR = 0
#define Set_SDA_High	SDA_DIR = 1
#define Set_SCK_Low		SCK_DIR = 0
#define Set_SCK_High	SCK_DIR = 1

//Function Declarations
void InitI2C(void);
void I2C_Start(void);
void I2C_ReStart(void);
void I2C_Stop(void);
void I2C_Send_ACK(void);
void I2C_Send_NACK(void);
bit  I2C_Write_Byte(unsigned char);
unsigned char I2C_Read_Byte(void);

#endif
