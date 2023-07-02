#ifndef _SUCKER_H
#define _SUCKER_H

/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "sucker_motor.h"
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Exported variables ---------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define SUCKER_YAW_D2A								(1481.48f)
#define SUCKER_PITCH_D2A							(1277.77f)
#define SUCKER_ROLL_D2A								(7222.22f)

//右正左负 顺正左负 400000
#define SUCKER_YAW_MAX								(400000)
#define SUCKER_YAW_MID								(266667)
#define SUCKER_YAW_SIDE								(133333)
#define SUCKER_YAW_MIN								(4000)

#define SUCKER_YAW_LEFT								(315525)//33
#define SUCKER_YAW_RIGHT							(213125)//36

#define SUCKER_YAW_GRO								SUCKER_YAW_MIN
#define SUCKER_YAW_LOB								SUCKER_YAW_MIN
#define SUCKER_YAW_GOLDEN							SUCKER_YAW_MID
#define SUCKER_YAW_SILVER							SUCKER_YAW_MID
#define SUCKER_YAW_PUSH_ORE						SUCKER_YAW_MIN
#define SUCKER_YAW_EXCHANGE						SUCKER_YAW_SILVER
#define SUCKER_YAW_PLACE							(64000)

#define SUCKER_YAW_MINI_OK 						(distance(sucker.base_info.measure_yaw_angle,SUCKER_YAW_MIN)<300 && m_abs(sucker.base_info.measure_yaw_speed < 2))
#define SUCKER_YAW_SIDE_OK 						(distance(sucker.base_info.measure_yaw_angle,SUCKER_YAW_SIDE)<300 && m_abs(sucker.base_info.measure_yaw_speed < 2))
#define SUCKER_YAW_LEFT_OK 						(distance(sucker.base_info.measure_yaw_angle,SUCKER_YAW_LEFT)<300 && m_abs(sucker.base_info.measure_yaw_speed < 2))
#define SUCKER_YAW_RIGHT_OK 					(distance(sucker.base_info.measure_yaw_angle,SUCKER_YAW_RIGHT)<300 && m_abs(sucker.base_info.measure_yaw_speed < 2))
#define SUCKER_YAW_MID_OK 						(distance(sucker.base_info.measure_yaw_angle,SUCKER_YAW_MID)<300 && m_abs(sucker.base_info.measure_yaw_speed < 2))
#define LOB_SUCKER_YAW_IS_OK 					(distance(sucker.base_info.measure_yaw_angle,SUCKER_YAW_LOB)<300 && m_abs(sucker.base_info.measure_yaw_speed < 2))
#define GRO_SUCKER_YAW_IS_OK 					SUCKER_YAW_INIT_OK
#define GOLDEN_SUCKER_YAW_IS_OK 			(distance(sucker.base_info.measure_yaw_angle,SUCKER_YAW_GOLDEN)<300 && m_abs(sucker.base_info.measure_yaw_speed < 2))
#define SILVER_SUCKER_YAW_IS_OK 			(distance(sucker.base_info.measure_yaw_angle,SUCKER_YAW_SILVER)<300 && m_abs(sucker.base_info.measure_yaw_speed < 2))
#define EXCHANGE_SUCKER_YAW_IS_OK 		SUCKER_YAW_INIT_OK
#define PUSH_ORE_SUCKER_YAW_IS_OK 		SUCKER_YAW_INIT_OK
#define PLACE_SUCKER_YAW_IS_OK 				(distance(sucker.base_info.measure_yaw_angle,SUCKER_YAW_PLACE)<1000 && m_abs(sucker.base_info.measure_yaw_speed < 2))

//pitch向上左正右负 
#define SUCKER_PITCH_MAX								(230000)
#define SUCKER_PITCH_MID								(115000)
#define SUCKER_PITCH_MIN								(4000)
#define SUCKER_PITCH_LOB								(8888)
#define SUCKER_PITCH_GROUND							SUCKER_PITCH_MAX
#define SUCKER_PITCH_GOLDEN							SUCKER_PITCH_MAX
#define SUCKER_PITCH_SILVER							SUCKER_PITCH_MAX
#define SUCKER_PITCH_PUSH_ORE						SUCKER_PITCH_MIN
#define SUCKER_PITCH_EXCHANGE						SUCKER_PITCH_SILVER
#define SUCKER_PITCH_PLACE							(95000)

#define SUCKER_PITCH_MINI_OK 						(distance(sucker.base_info.measure_pitch_angle,SUCKER_PITCH_MIN)<1000 && m_abs(sucker.base_info.measure_pitch_speed < 2))
#define SUCKER_PITCH_MID_OK 						(distance(sucker.base_info.measure_pitch_angle,SUCKER_PITCH_MID)<1000 && m_abs(sucker.base_info.measure_pitch_speed < 2))
#define LOB_SUCKER_PITCH_IS_OK 					(distance(sucker.base_info.measure_pitch_angle,SUCKER_PITCH_LOB)<600 && m_abs(sucker.base_info.measure_pitch_speed < 2))
#define GROUND_SUCKER_PITCH_IS_OK 			(distance(sucker.base_info.measure_pitch_angle,SUCKER_PITCH_GROUND)<600 && m_abs(sucker.base_info.measure_pitch_speed < 2))
#define GOLDEN_SUCKER_PITCH_IS_OK 			(distance(sucker.base_info.measure_pitch_angle,SUCKER_PITCH_GOLDEN)<600 && m_abs(sucker.base_info.measure_pitch_speed < 2))
#define SILVER_SUCKER_PITCH_IS_OK 			(distance(sucker.base_info.measure_pitch_angle,SUCKER_PITCH_SILVER)<600 && m_abs(sucker.base_info.measure_pitch_speed < 2))
#define EXCHANGE_SUCKER_PITCH_IS_OK 		SUCKER_PITCH_INIT_OK
#define PUSH_ORE_SUCKER_PITCH_IS_OK 		SUCKER_PITCH_INIT_OK
#define PLACE_SUCKER_PITCH_IS_OK 				(distance(sucker.base_info.measure_pitch_angle,SUCKER_PITCH_PLACE)<700 && m_abs(sucker.base_info.measure_pitch_speed < 5))

/* Exported types ------------------------------------------------------------*/
/** 
  * @brief  平移状态枚举
  */ 
typedef enum 
{
	SUCKER_OFFLINE = 0,	
	
	SUCKER_ONLINE,

}sucker_work_state_e;



/** 
  * @brief  平移基本信息定义
  */ 
typedef __packed struct 
{
	
	float        target_pitch;
	float        target_yaw;
	float        target_roll;
	
	int16_t    	 measure_pitch_speed;
	int16_t    	 measure_yaw_speed;
	int16_t    	 measure_roll_speed;
	int32_t    	 measure_pitch_angle;
	int32_t    	 measure_yaw_angle;
	int32_t    	 measure_roll_angle;
	
	float				 pitch_A2D;
	float				 yaw_A2D;
	float				 roll_A2D;
	
	int16_t    	 output_deffL;
	int16_t    	 output_yaw;
	int16_t    	 output_deffR;

}sucker_base_info_t;


/** 
  * @brief  平移类定义
  */ 
typedef struct sucker_class_t
{	
	/*外部电机*/
	motor_t        		 *deffL;
	motor_t        		 *yaw;
	motor_t        		 *deffR;
	
	
	sucker_base_info_t   	base_info;
	motor_state_e   		work_sate;
	
	void                (*work)(struct sucker_class_t *sucker);
	
	Dev_Reset_State_e							reset;
	Dev_Reset_State_e							yaw_reset;
	Dev_Reset_State_e							pitch_reset;
}sucker_t;


extern sucker_t sucker;



/* Exported functions --------------------------------------------------------*/

/*work*/
void Sucker_Work(sucker_t *sucker);

/*init*/
Dev_Reset_State_e Sucker_Work_Init(sucker_t *sucker);

/*pid_cal*/
void Sucker_Pid_Calculating(sucker_t *sucker);




#endif
