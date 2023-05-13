/**
  ******************************************************************************
  * @file           : math_support.c\h
  * @brief          : 
  * @note           : 
	*                   ����str_to_num����
  ******************************************************************************
  */
	
#ifndef __MATH_SUPPORT_H
#define __MATH_SUPPORT_H

#include "stm32f4xx_hal.h"

#define abs(x) ((x)>0? (x):(-(x)))
#define sgn(x) (((x)>0)?1:((x)<0?-1:0))


float lowpass(float X_last, float X_new, float K);//��ͨ�˲�
float lowpass_imu(float a, float last, float now);
float ave(int16_t sum, float ave_last, float new_value);  //���ֵ
float Half_Turn(float angle,float max);


int16_t str_to_num(uint8_t *str, uint16_t len);  //�ַ���ת��ֵ
uint8_t num_to_str(int16_t num, uint8_t *str, uint16_t *len);  //�ַ���ת��ֵ
void num_to_str_2(uint16_t num, uint8_t *str, uint16_t len);
void num_to_str_3(int16_t num, uint8_t *str, uint16_t len);

#endif