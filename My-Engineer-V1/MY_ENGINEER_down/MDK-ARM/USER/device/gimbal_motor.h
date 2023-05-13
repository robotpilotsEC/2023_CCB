#ifndef _GIMBAL_MOTOR_H
#define _GIMBAL_MOTOR_H

#include "config.h"
#include "motor.h"

typedef enum
{
	GIMBAL_PITCH = 0,
	GIMBAL_YAW,
	
	GIMBAL_MOTOR_LIST,
	
}gimbal_motor_list_e;

extern motor_t gimbal_motor[GIMBAL_MOTOR_LIST];

void gimbal_motor_init(void);
void gimbal_motor_heart_beat(void);





#endif
