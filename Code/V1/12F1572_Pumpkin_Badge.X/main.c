//PIC 12F1572 Pumpkin Badge (MPLABX)
//By Wesley Savoie
//Pin 1 = +4V
//Pin 8 = 0V (GND)
//Refer to schematic for the rest!

// CONFIG1
#pragma config FOSC = INTOSC    // (INTOSC oscillator; I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function IO)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOREN = OFF    // Low Power Brown-out Reset enable bit (LPBOR is disabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

// INCLUDES
#include "Includes.h"

// DEFINITIONS
#define PLED LATAbits.LATA5 //define PLED latch setting for readability
#define BTN_INP TRISAbits.TRISA2
#define BTN PORTAbits.RA2

// Global Variables
unsigned char LEDMODE = 0; //Holds default mode data
unsigned char BTN_DETECT = 0; //Holds default button trigger detection data
unsigned char PWM_FADE_HOLD = 0;

unsigned char PATTERN_HOLD_1 = 0;
unsigned char PATTERN_HOLD_2 = 0;
unsigned char PATTERN_HOLD_SW = 0;

void InitCCT(void){
    //configure main registers
    OSCCON  = 0x7A;             //Setup internal osc to 16MHz
    OSCSTAT = 0x00;             //disable unnecessary modules
    OSCTUNE = 0x00;             //set INTOSC to factory calibrated settings
        
    //setup ports
    ANSELA = 0b00000000; // all pins to digital
    LATA   = 0b00000000; // all latch bits low
    TRISA  = 0b00001100; // all pins to outputs except RA2(BTN) & RA3 (MCLR)
    //WPUA   = 0b00001000; // enable weak pull-ups on RA3
}

void InitPWM(void){
    //Alt PWM1 (PIN 2 (RA5))
    APFCONbits.P1SEL = 1; //Set RA5 as PWM1 Output
    PWM1CLKCON = 0b00110001; // HFINTOSC clock, 1:8 prescaler
    PWM1PH = 0; // phase
    PWM1DC = 0; // duty cycle
    PWM1PR = 4000; // period
    PWM1CON = 0b11000000; // module enable, output enable, normal polarity, standard mode
}

unsigned int PLED_setDC(unsigned int setDC){
    if(setDC > 100){
        setDC = 4095;
    } else {
        setDC = ((setDC*4095)/100);
    }
    PWM1DC = 4095 - setDC;  //Set PWM Duty Cycle (100% = 0, 0% = 4095, so 4096 steps) (Remember, it's inverted as the LED is being pulled to GND to turn on)
    PWM1LD = 1;     //Update the PWM state
}

void initLEDArray(void){
    PCA9685_reset();          //Reset the PCA9685 to prepare it for new data
    PCA9685_setPWMFreq(1000); //Set PWM Frequency to 1000Hz
    PCA9685_setAllOff();
}

void main(void){    
    InitCCT();	// Turn off ADC and comparator to make pins digital IOs
    InitI2C();	// Initialize i2c pins
    
    InitPWM();      //Initialize RA5 PWM
    PLED_setDC(50); //Initialize and set the Power LED PWM Duty Cycle (0% to 100%)
    
    initLEDArray();
    
    while(1){   //Start main loop
        if(BTN == 0){
            PLED_setDC(0);
            __delay_ms(10); //debounce
            if(BTN == 0){
                while(BTN == 0); //wait until button is released
                __delay_ms(10); //debounce
                PLED_setDC(50);
                if(LEDMODE == 0){
                        LEDMODE = 1;
                } else if(LEDMODE == 1){
                        LEDMODE = 2;
                } else if(LEDMODE == 2){
                        LEDMODE = 3;
                } else if(LEDMODE == 3){
                        LEDMODE = 4;
                } else if(LEDMODE == 4){
                        LEDMODE = 0;
                }
            }
            BTN_DETECT = 1;
        }
        
        if(BTN_DETECT == 1){
            if(LEDMODE == 0){ //MODE 0 = All Off (Basic Startup Mode)
                PCA9685_setAllOff();
                PLED_setDC(80);
                __delay_ms(10);
                PLED_setDC(0);
                __delay_ms(10);
            }
            if(LEDMODE == 1){ //MODE 1 = All On (50%) (Power Save Mode)
                PCA9685_setAll(2047);
                    for(int i = 0; i < 2; i++){
                        PLED_setDC(80);
                        __delay_ms(10);
                        PLED_setDC(0);
                        __delay_ms(10);
                }
            }
            if(LEDMODE == 2){ //MODE 2 = All On (90%) (High Brightness Mode)
                PCA9685_setAll(3685);
                    for(int i = 0; i < 3; i++){
                        PLED_setDC(80);
                        __delay_ms(10);
                        PLED_setDC(0);
                        __delay_ms(10);
                }
            }
            if(LEDMODE == 3){
                for(int i = 0; i < 4; i++){
                    PLED_setDC(80);
                    __delay_ms(10);
                    PLED_setDC(0);
                    __delay_ms(10);
                }
                PWM_FADE_HOLD = 1;
            }
            if(LEDMODE == 4){
                for(int i = 0; i < 5; i++){
                    PLED_setDC(80);
                    __delay_ms(10);
                    PLED_setDC(0);
                    __delay_ms(10);
                }
                PCA9685_setAllOff();
            }
            BTN_DETECT = 0;
        }
        
        if(LEDMODE == 3){ //MODE 3 = Quick Cycle Mode
            if(PWM_FADE_HOLD == 0){
                for(int i = 0; i < 4096; i+=128){
                    if(BTN == 0) break;
                    PCA9685_setAll(i);
                    __delay_ms(10);
                }
            }
            if(PWM_FADE_HOLD == 1){
                for(int i = 4096; i > 0; i-=128){
                    if(BTN == 0) break;
                    PCA9685_setAll(i);
                    __delay_ms(10);
                }
            }
            if(PWM_FADE_HOLD == 0) {PWM_FADE_HOLD = 1;} else {PWM_FADE_HOLD = 0;};
        }
        
        if(LEDMODE == 4){ //MODE 3 = Quick Cycle Mode
            PCA9685_setPWM_Simple(EYE_CYCLE_1[PATTERN_HOLD_1], 3685);
            PCA9685_setPWM_Simple(MOUTH_CYCLE_1[PATTERN_HOLD_2], 3685);
            for(unsigned char i = 0; i < 10; i++){
                __delay_ms(10);
                if(BTN == 0) break;
            }
            PCA9685_setPWM_Simple(EYE_CYCLE_1[PATTERN_HOLD_1], 1);
            PCA9685_setPWM_Simple(MOUTH_CYCLE_1[PATTERN_HOLD_2], 1);
            
            PATTERN_HOLD_1++;
            if (PATTERN_HOLD_SW == 0){
                PATTERN_HOLD_2++;
            } else {
                PATTERN_HOLD_2--;
            }
            
            if(PATTERN_HOLD_1 == 8){
                PATTERN_HOLD_1 = 0;
            }
            if(PATTERN_HOLD_2 == 10 && PATTERN_HOLD_SW == 0){
                PATTERN_HOLD_2 = 8;
                PATTERN_HOLD_SW = 1;
            } else if(PATTERN_HOLD_2 == 0 && PATTERN_HOLD_SW == 1){
                PATTERN_HOLD_SW = 0;
            }
        }
    }
}