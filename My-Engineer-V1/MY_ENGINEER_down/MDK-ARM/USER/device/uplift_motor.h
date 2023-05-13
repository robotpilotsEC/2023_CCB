#ifndef _UPLIFT_MOTOR_H
#define _UPLIFT_MOTOR_H

#include "config.h"
#include "motor.h"

typedef enum
{
	UPLIFT_F = 0,
	UPLIFT_B,
	
	UPLIFT_MOTOR_LIST,
	
	
	
}uplift_motor_list_e;

extern motor_t uplift_motor[UPLIFT_MOTOR_LIST];

void uplift_motor_init(void);
void uplift_motor_heart_beat(void);





#endif
