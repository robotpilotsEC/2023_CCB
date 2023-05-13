#ifndef _TRANSVERSE_MOTOR_H
#define _TRANSVERSE_MOTOR_H

#include "config.h"
#include "motor.h"

typedef enum
{
	TRANSVERSE_F = 0,
	TRANSVERSE_B,
	
  TRANSVERSE_MOTOR_LIST,
	
}transverse_motor_list_e;

extern motor_t transverse_motor[TRANSVERSE_MOTOR_LIST];

void transverse_motor_init(void);
void transverse_motor_heart_beat(void);



#endif



