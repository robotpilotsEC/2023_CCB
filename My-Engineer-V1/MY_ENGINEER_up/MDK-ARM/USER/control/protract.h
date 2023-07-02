#ifndef _PROTRACT_H
#define _PROTRACT_H

/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "protract_motor.h"
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

//右正左负

/* Exported variables ---------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define	PROTRACT_A2MM								(0.0003f)
#define	PROTRACT_A2CM								(0.00003f)

#define PROTRACT_MAX								(480000.f)
#define PROTRACT_MID								(250000)
#define PROTRACT_MIN								(10000)
#define PROTRACT_GRO								PROTRACT_MIN
#define PROTRACT_TWO_ORES						(327288)
#define PROTRACT_SILVER1						(400000.f)
#define PROTRACT_LOB								PROTRACT_MID
#define PROTRACT_GOLDEN							PROTRACT_MID
#define PROTRACT_SILVER							PROTRACT_MID
#define PROTRACT_PUSH_ORE						PROTRACT_MIN
#define PROTRACT_EXCHANGE						PROTRACT_SILVER

#define PROTRACT_MINI_OK 						(distance(protract.base_info.measure_angle,PROTRACT_MIN)<300 && (protract.base_info.measure_speed == 0))
#define PROTRACT_MAX_OK 						(distance(protract.base_info.measure_angle,PROTRACT_MAX)<300 && (protract.base_info.measure_speed == 0))
#define PROTRACT_TWO_ORE_OK 				(distance(protract.base_info.measure_angle,PROTRACT_TWO_ORES)<300 && (protract.base_info.measure_speed == 0))
#define PROTRACT_MID_OK 						(distance(protract.base_info.measure_angle,PROTRACT_MID)<300 && protract.base_info.measure_speed == 0)
#define LOB_PROTRACT_IS_OK 					PROTRACT_MID_OK
#define GRO_PROTRACT_IS_OK 					PROTRACT_INIT_OK
#define GOLDEN_PROTRACT_IS_OK 			PROTRACT_MID_OK
#define SILVER_PROTRACT_IS_OK 			PROTRACT_MID_OK
#define SILVER1_PROTRACT_IS_OK 			(distance(protract.base_info.measure_angle,PROTRACT_SILVER1)<300 && (protract.base_info.measure_speed == 0))
#define EXCHANGE_PROTRACT_IS_OK 		PROTRACT_INIT_OK
#define PUSH_ORE_PROTRACT_IS_OK 		PROTRACT_INIT_OK

/* Exported types ------------------------------------------------------------*/
/** 
  * @brief  平移状态枚举
  */ 
typedef enum 
{
	PROTRACT_OFFLINE = 0,	
	
	PROTRACT_ONLINE,

}protract_work_state_e;



/** 
  * @brief  平移基本信息定义
  */ 
typedef __packed struct 
{
	
	float        target;
	int32_t			 measure_angle;
	float			 	 angle2mm;
	int16_t			 measure_speed;
	int16_t    	 output;

}protract_base_info_t;


/** 
  * @brief  平移类定义
  */ 
typedef struct protract_class_t
{	
	/*外部电机*/
	motor_t        		 *motor;
	
	
	protract_base_info_t   	base_info;
	protract_work_state_e   work_sate;
	
	void                (*work)(struct protract_class_t *protract);
	
	Dev_Reset_State_e							reset;
}protract_t;


extern protract_t protract;



/* Exported functions --------------------------------------------------------*/

/*work*/
void Protract_Work(protract_t *protract);

/*init*/
Dev_Reset_State_e Protract_Work_Init(protract_t *protract);

/*pid_cal*/
void Protract_Pid_Calculating(protract_t *protract);




#endif
