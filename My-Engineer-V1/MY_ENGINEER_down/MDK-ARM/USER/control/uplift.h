#ifndef _UPLIFT_H
#define _UPLIFT_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "math.h"
#include "drv_can.h"
#include "uplift_motor.h"
#include "stdbool.h"
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Exported variables ---------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

//抬升：前负后正
#define UPLIFT_MAX								(600000)
#define UPLIFT_GRO								(0)
#define UPLIFT_GOLDEN							(0)
#define UPLIFT_SILVER							(0)
#define UPLIFT_EXCHANGE						UPLIFT_SILVER
#define UPLIFT_PUSH_ORE						UPLIFT_GOLDEN
#define UPLIFT_MIN								(0)
#define UPLIFT_LOB								(0)
#define UPLIFT_SPEED							(-250)
#define UPLIFT_TORQUE							(800)


/* Exported types ------------------------------------------------------------*/
/** 
  * @brief  抬升基本信息定义
  */ 
typedef __packed struct 
{
	
	float        target;
	int16_t   	 measure;
	int16_t    	 output_F;
	int16_t    	 output_B;

}uplift_base_info_t;


/** 
  * @brief  抬升类定义
  */ 
typedef struct uplift_class_t
{	
	/*外部电机*/
	motor_t        		 *front;
	motor_t        		 *back;
	
	
	uplift_base_info_t   	base_info;
	motor_state_e   			work_sate;
	
	void                (*work)(struct uplift_class_t *uplift);
	
	Dev_Reset_State_e							reset;
}uplift_t;


extern uplift_t uplift;

/* Exported functions --------------------------------------------------------*/

/*work*/
void Uplift_Work(uplift_t *uplift);

/*init*/
Dev_Reset_State_e Uplift_Work_Init(uplift_t *uplift);

/*pid_cal*/
void Uplift_Pid_Calculating(uplift_t *uplift);


#endif
