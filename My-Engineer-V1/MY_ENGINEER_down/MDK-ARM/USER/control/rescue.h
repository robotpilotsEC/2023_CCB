#ifndef _RESCUE_H
#define _RESCUE_H

/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "rescue_motor.h"
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Exported variables ---------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define RESCUE_MAX								(75000)
#define RESCUE_MID								(50000)
#define RESCUE_MIN								(5000)
//�£��Ҹ����� ��0~-75227 ��
/* Exported types ------------------------------------------------------------*/
/** 
  * @brief  ƽ��״̬ö��
  */ 
typedef enum 
{
	RESCUE_OFFLINE = 0,	
	
	RESCUE_ONLINE,

}rescue_work_state_e;



/** 
  * @brief  ƽ�ƻ�����Ϣ����
  */ 
typedef __packed struct 
{
	
	float        target;
	int32_t			 measure_angle;
	int16_t			 measure_speed;
	int16_t    	 output_L;
	int16_t    	 output_R;

}rescue_base_info_t;


/** 
  * @brief  ƽ���ඨ��
  */ 
typedef struct rescue_class_t
{	
	motor_t 							*left;
	motor_t 							*right;
	
	rescue_base_info_t   	base_info;
	rescue_work_state_e   work_sate;
	
	void                (*work)(struct rescue_class_t *rescue);
	
	Dev_Reset_State_e							reset;
}rescue_t;


extern rescue_t rescue;



/* Exported functions --------------------------------------------------------*/

/*work*/
void Rescue_Work(rescue_t *rescue);

/*init*/
Dev_Reset_State_e Rescue_Work_Init(rescue_t *rescue);

/*pid_cal*/
void Rescue_Pid_Calculating(rescue_t *rescue);




#endif
