#ifndef _SUCKER_MOTOR_H
#define _SUCKER_MOTOR_H

#include "config.h"
#include "motor.h"

typedef enum
{
	SUCKER_PITCH = 0,
	SUCKER_YAW,
	SUCKER_ROLL,
	
  SUCKER_MOTOR_LIST,
	
	
	
}sucker_motor_list_e;

extern motor_t sucker_motor[SUCKER_MOTOR_LIST];

void sucker_motor_init(void);
void sucker_motor_heart_beat(void);





#endif



