#ifndef _CLAW_H
#define _CLAW_H

/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "claw_motor.h"
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Exported variables ---------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define CLAW_MAX								(79000)//下负上正
#define CLAW_MIN								(1000)

/* Exported types ------------------------------------------------------------*/
/** 
  * @brief  平移状态枚举
  */ 
typedef enum 
{
	CLAW_OFFLINE = 0,	
	
	CLAW_ONLINE,

}claw_work_state_e;



/** 
  * @brief  平移基本信息定义
  */ 
typedef __packed struct 
{
	
	float        target;
	int32_t			 measure_angle;
	int16_t			 measure_speed;
	int16_t    	 output_L;
	int16_t    	 output_R;

}claw_base_info_t;


/** 
  * @brief  平移类定义
  */ 
typedef struct claw_class_t
{	
	/*外部电机*/
	motor_t        		 *motor_L;
	motor_t        		 *motor_R;
	
	
	claw_base_info_t   	base_info;
	claw_work_state_e   work_sate;
	
	void                (*work)(struct claw_class_t *claw);
	
	Dev_Reset_State_e							reset;
}claw_t;


extern claw_t claw;



/* Exported functions --------------------------------------------------------*/

/*work*/
void Claw_Work(claw_t *claw);

/*init*/
Dev_Reset_State_e Claw_Work_Init(claw_t *claw);

/*pid_cal*/
void Claw_Pid_Calculating(claw_t *claw);




#endif
