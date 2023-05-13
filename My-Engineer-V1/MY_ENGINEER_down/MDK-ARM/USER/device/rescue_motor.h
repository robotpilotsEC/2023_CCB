#ifndef _RESCUE_MOTOR_H
#define _RESCUE_MOTOR_H

#include "config.h"
#include "motor.h"

typedef enum
{
	RESCUE_L = 0,
	RESCUE_R,
	
	RESCUE_MOTOR_LIST,
	
	
	
}rescue_motor_list_e;

extern motor_t rescue_motor[RESCUE_MOTOR_LIST];

void rescue_motor_init(void);
void rescue_motor_heart_beat(void);





#endif
