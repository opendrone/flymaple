/**
 * @file   motor.h
 * @author tonghuix <tonghuix@tonghuix-1011PX>
 * @date   Sat May 19 16:45:38 2012
 * 
 * @brief  Motor Control Header File
 * 
 * 
 */

void motorCcontrol(void);

void motorInit(void);

void motorStop();

void motorHalf();

void motorCustom(int pwm0, int pwm1, int pwm2, int pwm3);

