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

#define c_sign(x)										((x>=0)?(1):(-1))//符号
#define constrain(x, min, max)			((x>(max))?max:(x<(min)?min:(x)))//限幅
#define range(x, min, max)					((((x)<(max)) && ((x)>(min)))?1:0)//范围
#define c_abs(x) 										((x)>0? (x):(-(x)))//绝对值
#define	c_max2(x,y)									(c_abs(x)>c_abs(y)?x:y)//下限
#define distance(x,y)								((x>=y)?(x-y):(y-x))//距离
#define	d2r_f32(x) 									(0.01745329f*(x))//度to弧度
#define	r2d_f32(x) 									(57.29578f*(x))//弧度to度
#define	pi													(3.141592653f)
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

/* 状态灯枚举 */
typedef enum CAR_NAME
{
	LEFT=0,            
	RIGHT,              
	FRONT=0,
	BACK,
	PITCH=0,
	YAW,
	ROLL,
	DEFFL=0,
	DEFFR=2,
}Car_Name;

#endif
