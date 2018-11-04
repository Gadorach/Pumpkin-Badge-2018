#ifndef __INCLUDES_H
#define __INCLUDES_H

// Define CPU Frequency
// This must be defined, if __delay_ms()
// or __delay_us() functions are used in the code
#define _XTAL_FREQ 16000000 //define 16MHz internal frequency for software use (dosen't set it, just defines it in Hz)

// Include files
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <pic12f1572.h>         //This is the PIC's own setting file, change for your PIC if it's not a 12F1572
#include "I2C.h"
#include "PCA9685_Lib.h"
#include "LED_Groups.h"
#endif