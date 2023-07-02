/*
* 自定义控制器
*	
*	2023.6.13
*/
#ifndef _CUSTOM_CONTROL_H
#define _CUSTOM_CONTROL_H

/* Includes ------------------------------------------------------------------*/
#include "config.h"
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables ---------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

typedef struct
{
	float x_speed;
	float y_speed;
	float z_speed;
	float pitch_speed;
	float yaw_speed;
	float roll_speed;
	
}custom_base_info_t;

typedef struct
{
	float x_speed_max;
	float y_speed_max;
	float z_speed_max;
	float pitch_speed_max;
	float yaw_speed_max;
	float roll_speed_max;
	
	Dev_Work_State_e x_state;
	Dev_Work_State_e y_state;
	Dev_Work_State_e z_state;
	Dev_Work_State_e pitch_state;
	Dev_Work_State_e yaw_state;
	Dev_Work_State_e roll_state;
}custom_work_info_t;

typedef __packed struct
{
	custom_base_info_t *info;
	custom_work_info_t *work;
	Dev_Work_State_e state;
}custom_t;

extern custom_t custom;




#endif
