#ifndef __PWM_H__
#define __PWM_H__

#include <Arduino.h>

void LEDC_Init(uint16_t frequency, uint8_t resolution);
void pwm_set_duty(uint16_t duty);
void Motor_Control(int Cnt_L, int Cnt_R);
void User_Robot_Task(void *SoccerRobot_Task);

#endif