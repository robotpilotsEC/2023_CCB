#ifndef _TRANSVERSE_H
#define _TRANSVERSE_H

/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "transverse_motor.h"
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

//front 前正后负 back反

/* Exported variables ---------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define	TRANSVERSE_A2MM												(0.0005f)
#define	TRANSVERSE_A2CM												(0.00005f)

#define TRANSVERSE_MAX												(740000)
#define TRANSVERSE_MIN												(5000)
#define TRANSVERSE_SPEED											(-800)

#define TRANSVERSE_LOB												TRANSVERSE_MAX
#define TRANSVERSE_NORMAL											(80000)
#define TRANSVERSE_GROUND											(120000)
#define TRANSVERSE_GOLDEN											TRANSVERSE_LOB
#define TRANSVERSE_SILVER											(100000)
#define TRANSVERSE_EXCHANGE										TRANSVERSE_SILVER
#define TRANSVERSE_PUSH_ORE										TRANSVERSE_AFTER_PLACE
#define TRANSVERSE_BEFORE_EXCHANGE						(50000)
#define TRANSVERSE_PLACE											(40000)
#define TRANSVERSE_AFTER_PLACE								(120000)

#define LOB_TRANSVERSE_IS_OK 									(distance(transverse.base_info.measure_angle,TRANSVERSE_LOB)<300 && m_abs(transverse.base_info.measure_speed <10))
#define NORMAL_TRANSVERSE_IS_OK 							(distance(transverse.base_info.measure_angle,TRANSVERSE_NORMAL)<300 && transverse.base_info.measure_speed < 50)
#define GOLDEN_TRANSVERSE_IS_OK 							LOB_TRANSVERSE_IS_OK
#define SILVER_TRANSVERSE_IS_OK 							(distance(transverse.base_info.measure_angle,TRANSVERSE_SILVER)<300 && m_abs(transverse.base_info.measure_speed <10))
#define EXCHANGE_TRANSVERSE_IS_OK 						SILVER_TRANSVERSE_IS_OK
#define PUSH_ORE_TRANSVERSE_IS_OK 						AFTER_PLACE_TRANSVERSE_IS_OK
#define BEFORE_EXCHANGE_TRANSVERSE_IS_OK 			(distance(transverse.base_info.measure_angle,TRANSVERSE_MAX)<300 && m_abs(transverse.base_info.measure_speed <10))
#define GROUND_TRANSVERSE_IS_OK 							(distance(transverse.base_info.measure_angle,TRANSVERSE_GROUND)<300 && m_abs(transverse.base_info.measure_speed <10))
#define PLACE_TRANSVERSE_IS_OK 								(distance(transverse.base_info.measure_angle,TRANSVERSE_PLACE)<300 && m_abs(transverse.base_info.measure_speed <10))
#define AFTER_PLACE_TRANSVERSE_IS_OK 					(distance(transverse.base_info.measure_angle,TRANSVERSE_AFTER_PLACE)<300 && m_abs(transverse.base_info.measure_speed <10))
#define TRANSVERSE_MINI_OK 										(distance(transverse.base_info.measure_angle,TRANSVERSE_MIN)<300 && m_abs(transverse.base_info.measure_speed <10))


/* Exported types ------------------------------------------------------------*/
/** 
  * @brief  平移状态枚举
  */ 
typedef enum 
{
	TRANSVERSE_OFFLINE = 0,	
	
	TRANSVERSE_ONLINE,

}transverse_work_state_e;



/** 
  * @brief  平移基本信息定义
  */ 
typedef __packed struct 
{
	
	float        target;
	int32_t			 measure_angle;
	float			 	 angle2mm;
	int16_t			 measure_speed;
	int16_t    	 output_F;
	int16_t    	 output_B;

}transverse_base_info_t;


/** 
  * @brief  平移类定义
  */ 
typedef struct transverse_class_t
{	
	/*外部电机*/
	motor_t        		 *front;
	motor_t        		 *back;
	
	
	transverse_base_info_t   	base_info;
	transverse_work_state_e   work_sate;
	
	void                (*work)(struct transverse_class_t *transverse);
	
	Dev_Reset_State_e							reset;
}transverse_t;


extern transverse_t transverse;



/* Exported functions --------------------------------------------------------*/

/*work*/
void Transverse_Work(transverse_t *transverse);

/*init*/
Dev_Reset_State_e Transverse_Work_Init(transverse_t *transverse);

/*pid_cal*/
void transverse_Pid_Calculating(transverse_t *transverse);




#endif
