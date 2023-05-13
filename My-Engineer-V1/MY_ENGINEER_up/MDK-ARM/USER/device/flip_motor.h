#ifndef _FLIP_MOTOR_H
#define _FLIP_MOTOR_H

#include "config.h"
#include "motor.h"

typedef enum
{
	FLIP_L = 0,
	FLIP_R,
	
  FLIP_MOTOR_LIST,
	
	
	
}flip_motor_list_e;

extern motor_t flip_motor[FLIP_MOTOR_LIST];

void flip_motor_init(void);
void flip_motor_heart_beat(void);





#endif



