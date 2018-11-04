/*
 * File:   PCA9685_Lib.c
 * Author: Wesley Savoie
 *
 * Created on October 25, 2018, 11:23 PM
 */

#include "Includes.h"

void I2C_Write_Command(unsigned char Command, unsigned char Data){
    I2C_Start();										// Start i2c communication
	I2C_Write_Byte(I2C_ADDRESS);                        // Send i2c address of PCA9685 with write command
	I2C_Write_Byte(Command);                            // Send Register Select on i2c
    I2C_Write_Byte(Data);		                        // Set Data
	I2C_Stop();                                         // Stop i2c communication
}

void PCA9685_setPWMFreq(int freq){ //Set the PWM frequency in Hz
    OE_PIN = 1;
    if(freq < 40) freq = 40;
    if(freq > 1000) freq = 1000; //Handle function max/min misuse
    unsigned char prescale_val = (CLOCK_FREQ / 4096 / freq)  - 1;
	I2C_Write_Command(MODE1, 0x10); //sleep
	I2C_Write_Command(PRE_SCALE, prescale_val); // multiplier for PWM frequency
	I2C_Write_Command(MODE1, 0x80); //restart
    I2C_Write_Command(MODE2, 0x04); //totem pole (default)
    OE_PIN = 0;
}

//Set Specific Pin PWM Duty Cycle with both ON and OFF time
//led  = Select LED Channel (0-15)
//on_value   = Set PWM Duty Cycle On Percentage for Selected Channel (0-4095)
//off_value  = Set PWM Duty Cycle Off Percentage for Selected Channel (0-4095)
void PCA9685_setPWM_Full(unsigned char led, int on_value, int off_value) {
    if(led < 0) led = 0;
    if(led > 15) led = 15;
    if(on_value < 0) on_value = 0;
    if(on_value > 4095) on_value = 4095;
    if(off_value < 0) off_value = 0;
    if(off_value > 4095) off_value = 4095; //incorrect data correction/protection
    on_value = (4095 - on_value);
    off_value = (4095 - off_value);  //Data inversion for handling the active low LEDs
	I2C_Write_Command(LED0_ON_L + LED_MULTIPLIER * (led), on_value & 0xFF);
	I2C_Write_Command(LED0_ON_H + LED_MULTIPLIER * (led), on_value >> 8);
	I2C_Write_Command(LED0_OFF_L + LED_MULTIPLIER * (led), off_value & 0xFF);
    I2C_Write_Command(LED0_OFF_H + LED_MULTIPLIER * (led), off_value >> 8);
}

//Set Specific Pin PWM Duty Cycle with only OFF time
//led  = Select LED Channel (0-15)
//value  = Set PWM Duty Cycle for Selected Channel (0-4095)
void PCA9685_setPWM_Simple(unsigned char led, int value) {
	PCA9685_setPWM_Full(led, 0, value);
}

void PCA9685_setAllOn(void) {
    for(int i = 0; i<16; i++){
        PCA9685_setPWM_Full(i, 4095, 4095);
    }
}

void PCA9685_setAllOff(void) {
	for(int i = 0; i<16; i++){
        PCA9685_setPWM_Full(i, 4095, 0);
    }
}

void PCA9685_setAll(int value) {
    for(int i = 0; i<16; i++){
        PCA9685_setPWM_Full(i, 4095, value);
    }
}

void PCA9685_reset(void){               //Reset LED Driver
    OE_PIN = 1;
    I2C_Write_Command(MODE1, 0x00);     // Set MODE1 to Normal Mode
    I2C_Write_Command(MODE2, 0x04);     // Set MODE2 to Totem Pole Mode
    OE_PIN = 0; //Enable Output on the pins.
}