#ifndef _FLIP_H
#define _FLIP_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "math.h"
#include "drv_can.h"
#include "flip_motor.h"
#include "stdbool.h"
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Exported variables ---------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define FLIP_SPEED				(2000)


/* Exported types ------------------------------------------------------------*/
/** 
  * @brief  ����״̬ö��
  */ 
typedef enum 
{
	FLIP_OFFLINE = 0,	
	
	FLIP_ONLINE,

}flip_work_state_e;


/** 
  * @brief  ����״̬ö��
  */ 
typedef enum 
{
	FLIP_OFF = 0,	
	
	FLIP_DOWM,
	FLIP_UP,
	FLIP_LEFT,
	FLIP_RIGHT,

}flip_work_mdoe_e;

/** 
  * @brief  ���������Ϣ����
  */ 
typedef __packed struct 
{
	
	float     	target;
	int16_t    	measure;
	int16_t     output_L;
	int16_t     output_R;

}flip_base_info_t;


/** 
  * @brief  �����ඨ��
  */ 
typedef struct flip_class_t
{	
	/*�ⲿ���*/
	motor_t        		 *left;
	motor_t        		 *right;
	
	
	flip_base_info_t   	base_info;
	flip_work_state_e   work_sate;
	flip_work_mdoe_e    mode;
	
	void                (*work)(struct flip_class_t *flip);
	
}flip_t;


extern flip_t flip;



/* Exported functions --------------------------------------------------------*/


/*woprk*/
void Flip_Work(flip_t *flip);

/*pid_cal*/
void Flip_Pid_Calculating(flip_t *flip);




#endif
