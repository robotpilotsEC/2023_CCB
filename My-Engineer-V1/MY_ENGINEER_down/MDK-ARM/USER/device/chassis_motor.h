#ifndef _CHASSIS_MOTOR_H
#define _CHASSIS_MOTOR_H

#include "config.h"
#include "motor.h"

typedef enum
{
	CHAS_LF = 0,
	CHAS_RF,
	CHAS_LB,
	CHAS_RB,
	
	CHASSIS_MOTOR_LIST,
	
}chassis_motor_list_e;


extern motor_t chassis_motor[CHASSIS_MOTOR_LIST];

void chassis_motor_init(void);
void chassis_motor_heart_beat(void);
void chassis_motor_rx_data(uint32_t canId, uint8_t *rxBuf);

#endif
