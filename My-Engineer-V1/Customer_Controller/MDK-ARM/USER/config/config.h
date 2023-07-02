/**
  ******************************************************************************
  * @file           : RP_drv
  * @brief          : 
  * @note           : start 2022-11-3 
  ******************************************************************************
  */

#ifndef __CONFIG_H
#define __CONFIG_H

#include "stm32f4xx_hal.h"

#define constrain(x, min, max)	((x>max)?max:(x<min?min:x))
#define distance(x,y)	((x>=y)?(x-y):(y-x))

/******************************全局使用枚举******************************/

typedef enum DEV_WORK_STATE
{
	DEV_OFFLINE = 0,
	DEV_ONLINE,
	
	DEV_OK = 0,
	DEV_NO,
}Dev_Work_State_e;

typedef enum DEV_RESET_STATE
{
	DEV_RESET_NO,
	DEV_RESET_OK,
}Dev_Reset_State_e;

/* 状态灯枚举 */
typedef enum LED_NUM
{
	LED_ORANGE,            
	LED_Blue,              
	LED_RED,
	LED_GREEN,
}LED_Num;

typedef enum
{
	Light_t = 150,//250
	Interval_t = 200,//300
	Wait_t = 500,
}LED_time;

typedef enum
{
	LF,
	RF,
	LB,
	RB,
}motor_num;

typedef enum
{
	LEFT=0,
	RIGHT,
	FRONT=0,
	BACK,
	PITCH=0,
	YAW,
	ROLL,
}motor_name;

typedef enum
{
	LEG_L,
	LEG_R,
	LEG_SUM,
}leg_motor_num;

#endif
