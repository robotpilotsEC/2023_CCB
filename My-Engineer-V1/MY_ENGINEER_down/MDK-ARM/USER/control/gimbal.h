/*
* sucker
*	
*	2023.4.2
* 云台
*/
#ifndef _GIMBAL_H
#define _GIMBAL_H

/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "gimbal_motor.h"
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Exported variables ---------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define GIMBAL_PITCH_MAX								(70000)//下负上正  23535~-46773 70000  38->42903 24
#define GIMBAL_PITCH_MID								(34000)
#define GIMBAL_PITCH_MIN								(5000)

#define GIMBAL_YAW_MAX								(200000)//左负右正 -176024~31273 205000
#define GIMBAL_YAW_MID								(100000)
#define GIMBAL_YAW_MIN								(2000)


/* Exported types ------------------------------------------------------------*/
/** 
  * @brief  平移状态枚举
  */ 
typedef enum 
{
	GIMBAL_OFFLINE = 0,	
	
	GIMBAL_ONLINE,

}gimbal_work_state_e;



/** 
  * @brief  平移基本信息定义
  */ 
typedef __packed struct 
{
	
	float        target_pitch;
	float        target_yaw;
	
	int16_t    	 measure_pitch_speed;
	int16_t    	 measure_yaw_speed;
	int32_t    	 measure_pitch_angle;
	int32_t    	 measure_yaw_angle;
	
	int16_t    	 output_pitch;
	int16_t    	 output_yaw;

}gimbal_base_info_t;


/** 
  * @brief  平移类定义
  */ 
typedef struct gimbal_class_t
{	
	motor_t 							*pitch;
	motor_t 							*yaw;
	
	gimbal_base_info_t   	base_info;
	gimbal_work_state_e   work_sate;
	
	void                (*work)(struct gimbal_class_t *gimbal);
	
	Dev_Reset_State_e							reset;
}gimbal_t;


extern gimbal_t gimbal;


/* Exported functions --------------------------------------------------------*/

/*work*/
void Gimbal_Work(gimbal_t *gimbal);

/*init*/
Dev_Reset_State_e Gimbal_Work_Init(gimbal_t *gimbal);

/*pid_cal*/
void Gimbal_Pid_Calculating(gimbal_t *gimbal);




#endif
