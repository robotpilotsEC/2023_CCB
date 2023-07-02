#ifndef _UPLIFT_H
#define _UPLIFT_H

/* Includes ------------------------------------------------------------------*/
#include "config.h"

/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Exported variables ---------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define	UPLIFT_A2MM								(0.0012f)
#define	UPLIFT_A2CM								(0.00012f)

#define UPLIFT_MAX								(496000)
#define UPLIFT_MID								(200000)
#define UPLIFT_MIN								(2000)
#define UPLIFT_INTERFERE					(100000)
#define UPLIFT_ONE_ORE						(120000)
#define UPLIFT_TWO_ORE						(250000)
#define UPLIFT_THREE_ORE					(400000)
#define UPLIFT_LOB								UPLIFT_MAX
#define UPLIFT_GOLDEN							(320000)
#define UPLIFT_SILVER							(320000)
#define UPLIFT_PUTDOWN						(244000)
#define UPLIFT_PUTUP							(400000)
#define UPLIFT_GROUND							(60000)
#define UPLIFT_EXCHANGE						UPLIFT_SILVER
#define UPLIFT_PLACE							(100000)

#define MID_UPLIFT_IS_OK 					(distance(uplift.measure_angle,UPLIFT_MID)<600 && uplift.measure_speed == 0)
#define ONE_UPLIFT_IS_OK 					(distance(uplift.measure_angle,UPLIFT_ONE_ORE)<1000 && uplift.measure_speed == 0)
#define TWO_UPLIFT_IS_OK 					(distance(uplift.measure_angle,UPLIFT_TWO_ORE)<1000 && uplift.measure_speed == 0)
#define THREE_UPLIFT_IS_OK 				(distance(uplift.measure_angle,UPLIFT_THREE_ORE)<1000 && uplift.measure_speed == 0)
#define OTT_UPLIFT_IS_OK 					(ONE_UPLIFT_IS_OK||TWO_UPLIFT_IS_OK||THREE_UPLIFT_IS_OK)
#define MAX_UPLIFT_IS_OK 					(distance(uplift.measure_angle,UPLIFT_MAX)<600 && uplift.measure_speed == 0)
#define PUTDOWN_UPLIFT_IS_OK 			(distance(uplift.measure_angle,UPLIFT_PUTDOWN)<600 && uplift.measure_speed == 0)
#define PUTUP_UPLIFT_IS_OK 				(distance(uplift.measure_angle,UPLIFT_PUTUP)<600 && uplift.measure_speed == 0)
#define LOB_UPLIFT_IS_OK 					(distance(uplift.measure_angle,UPLIFT_LOB)<600 && uplift.measure_speed == 0)
#define GOLDEN_UPLIFT_IS_OK 			(distance(uplift.measure_angle,UPLIFT_GOLDEN)<600 && uplift.measure_speed == 0)
#define SILVER_UPLIFT_IS_OK 			(distance(uplift.measure_angle,UPLIFT_SILVER)<600 && uplift.measure_speed == 0)
#define EXCHANGE_UPLIFT_IS_OK 		SILVER_UPLIFT_IS_OK
#define PUSH_ORE_UPLIFT_IS_OK 		GOLDEN_UPLIFT_IS_OK
#define GROUND_UPLIFT_IS_OK 			(distance(uplift.measure_angle,UPLIFT_GROUND)<600 && uplift.measure_speed == 0)
#define PLACE_UPLIFT_INIT_OK 			(distance(uplift.measure_angle,UPLIFT_PLACE)<600 && uplift.measure_speed == 0)
#define UPLIFT_MINI_OK 						(distance(uplift.measure_angle,UPLIFT_MIN)<600 && uplift.measure_speed == 0)
#define UPLIFT_INTERFERE_OK 			(distance(uplift.measure_angle,UPLIFT_INTERFERE)<600 && uplift.measure_speed == 0)

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  Ì§ÉýÀà¶¨Òå
  */ 
typedef struct uplift_class_t
{	
	float        						target;
	int32_t			 						measure_angle;
	float			 							angle2mm;
	int16_t			 						measure_speed;
	void										(*work)(struct uplift_class_t *uplift_t); 		
	
	Dev_Reset_State_e			 	reset;
}uplift_t;


extern uplift_t uplift;

/* Exported functions --------------------------------------------------------*/

/*work*/
void Uplift_Work(uplift_t *uplift);

/*init*/
Dev_Reset_State_e Uplift_Work_Init(uplift_t *uplift);


#endif
