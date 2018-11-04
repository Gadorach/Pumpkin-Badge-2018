#ifndef __PCA9685_Lib_H
#define __PCA9685_Lib_H

#define I2C_ADDRESS 0x80        //PCA9685 in default, All LOW address bit state
#define I2C_ADDRESS_READ 0x81   //PCA9685 in default, All LOW address bit state
#define OE_PIN LATAbits.LATA4   //Microcontroller Pin attached to OE (Output Enable) Pin

#define MODE1 0x00              //Mode  register  1
#define MODE2 0x01              //Mode  register  2
#define SUB_ADR1 0x02           //I2C-bus subaddress 1
#define SUB_ADR2 0x03           //I2C-bus subaddress 2
#define SUB_ADR3 0x04           //I2C-bus subaddress 3
#define ALL_CALL_ADR 0x05       //LED All Call I2C-bus address
#define LED0 0x6                //LED0 start register
#define LED0_ON_L 0x6           //LED0 output and brightness control byte 0
#define LED0_ON_H 0x7           //LED0 output and brightness control byte 1
#define LED0_OFF_L 0x8          //LED0 output and brightness control byte 2
#define LED0_OFF_H 0x9          //LED0 output and brightness control byte 3
#define LED_MULTIPLIER 4        // Multiplier vs LED0 for calculating the other 15 channels
#define ALL_LED_ON_L 0xFA       //load all the LEDn_ON registers, byte 0 (turn 0-7 channels on)
#define ALL_LED_ON_H 0xFB       //load all the LEDn_ON registers, byte 1 (turn 8-15 channels on)
#define ALL_LED_OFF_L 0xFC      //load all the LEDn_OFF registers, byte 0 (turn 0-7 channels off)
#define ALL_LED_OFF_H 0xFD      //load all the LEDn_OFF registers, byte 1 (turn 8-15 channels off)
#define PRE_SCALE 0xFE          //prescaler for output frequency
#define CLOCK_FREQ 25000000.0   //25MHz default osc clock

void PCA9685_setPWMFreq(int); //Set the PWM frequency in Hz (40Hz to 1000Hz)
void PCA9685_setPWM_Full(unsigned char, int, int); //Set Specific PWM Duty Cycle
void PCA9685_setPWM_Simple(unsigned char, int); //Set All PWM Duty Cycle
void PCA9685_reset(void); //Reset LED Driver
void I2C_Write_Command(unsigned char, unsigned char); //Write I2C Commands to the PCA9685
void PCA9685_setAllOff(void); //Turn All LEDs Off
void PCA9685_setAllOn(void); //Turn All LEDs On
void PCA9685_setAll(int); //Set All LEDs to a value (0-4095)

#endif
