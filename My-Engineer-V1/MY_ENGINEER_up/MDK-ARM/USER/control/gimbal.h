#ifndef _GIMBAL_H
#define _GIMBAL_H

/* Includes ------------------------------------------------------------------*/
#include "config.h"

/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Exported variables ---------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define GIMBAL_PITCH_MAX							(70000)//下负上正  23535~-46773 70000  34->42903 21
#define GIMBAL_PITCH_MID							(30000)
#define GIMBAL_PITCH_MIN							(5000)

#define GB_PITCH_MID_OK								(distance(gimbal.pitch_angle,GIMBAL_PITCH_MID)<600 && m_abs(gimbal.pitch_speed<50))
#define GB_PITCH_MIN_OK								(distance(gimbal.pitch_angle,GIMBAL_PITCH_MIN)<600 && m_abs(gimbal.pitch_speed<50))
#define GB_PITCH_MAX_OK								(distance(gimbal.pitch_angle,GIMBAL_PITCH_MAX)<600 && m_abs(gimbal.pitch_speed<50))

#define GIMBAL_YAW_MAX								(210000)//左负右正 -176024~31273 205000
#define GIMBAL_YAW_MID								(105000)
#define GIMBAL_YAW_MIN								(5000)

#define GB_YAW_MINI_OK								(distance(gimbal.yaw_angle,GIMBAL_YAW_MIN)<600 && m_abs(gimbal.yaw_speed<50))
#define GB_YAW_MID_OK									(distance(gimbal.yaw_angle,GIMBAL_YAW_MID)<600 && m_abs(gimbal.yaw_speed<50))
#define GB_YAW_MAX_OK									(distance(gimbal.yaw_angle,GIMBAL_YAW_MAX)<600 && m_abs(gimbal.yaw_speed<50))

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  抬升类定义
  */ 
typedef struct gimbal_class_t
{	
	float        						target_pitch;
	float        						target_yaw;
	int32_t			 						pitch_angle;
	int16_t			 						pitch_speed;
	int32_t			 						yaw_angle;
	int16_t			 						yaw_speed;
	void										(*work)(struct gimbal_class_t *gimbal_t); 		
	
	Dev_Reset_State_e			 	reset;
}gimbal_t;


extern gimbal_t gimbal;

/* Exported functions --------------------------------------------------------*/

/*work*/
void Gimbal_Work(gimbal_t *gimbal);

/*init*/
Dev_Reset_State_e Gimbal_Work_Init(gimbal_t *gimbal);


#endif
