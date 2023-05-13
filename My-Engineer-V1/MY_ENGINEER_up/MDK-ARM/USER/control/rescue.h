#ifndef _RESCUE_H
#define _RESCUE_H

/* Includes ------------------------------------------------------------------*/
#include "config.h"

/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Exported variables ---------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define RESCUE_MAX								(75000)
#define RESCUE_MID								(53000)
#define RESCUE_DOWN								(55000)
#define RESCUE_MIN								(5000)

#define RESCUE_MINI_OK 						(distance(rescue.measure_angle,RESCUE_MIN)<600 && rescue.measure_speed == 0)
#define RESCUE_MID_OK 						(distance(rescue.measure_angle,RESCUE_MID)<600 && rescue.measure_speed == 0)
#define RESCUE_DOWN_OK 						(distance(rescue.measure_angle,RESCUE_DOWN)<600 && rescue.measure_speed == 0)

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  Ì§ÉýÀà¶¨Òå
  */ 
typedef struct rescue_class_t
{	
	float        						target;
	int32_t			 						measure_angle;
	float			 							angle2mm;
	int16_t			 						measure_speed;
	void										(*work)(struct rescue_class_t *rescue_t); 		
	
	Dev_Reset_State_e			 	reset;
}rescue_t;


extern rescue_t rescue;

/* Exported functions --------------------------------------------------------*/

/*work*/
void Rescue_Work(rescue_t *rescue);

/*init*/
Dev_Reset_State_e Rescue_Work_Init(rescue_t *rescue);


#endif
