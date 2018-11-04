#ifndef LED_GROUPS_H
#define	LED_GROUPS_H

//Right Eye LEDs
#define RIGHT_EYE_BR 9
#define RIGHT_EYE_BL 10
#define RIGHT_EYE_T 8

//Left Eye LEDs
#define LEFT_EYE_BR 5
#define LEFT_EYE_BL 6
#define LEFT_EYE_T 7

//Mouth LEDs counting Left to Right
#define MOUTH_1 4
#define MOUTH_2 3
#define MOUTH_3 2
#define MOUTH_4 1
#define MOUTH_5 0
#define MOUTH_6 15
#define MOUTH_7 14
#define MOUTH_8 13
#define MOUTH_9 12
#define MOUTH_10 11

//Global Pattern Variable Arrays
unsigned char EYE_CYCLE_1[8] = {RIGHT_EYE_BL, RIGHT_EYE_T, RIGHT_EYE_BR, RIGHT_EYE_BL, LEFT_EYE_BR, LEFT_EYE_T, LEFT_EYE_BL, LEFT_EYE_BR};
unsigned char MOUTH_CYCLE_1[10] = {MOUTH_1, MOUTH_2, MOUTH_3, MOUTH_4, MOUTH_5, MOUTH_6, MOUTH_7, MOUTH_8, MOUTH_9, MOUTH_10};

#endif

