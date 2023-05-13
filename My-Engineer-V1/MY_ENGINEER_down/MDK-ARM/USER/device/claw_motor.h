#ifndef _CLAW_MOTOR_H
#define _CLAW_MOTOR_H

#include "config.h"
#include "motor.h"

typedef enum
{
	CLAW_L = 0,
	CLAW_R,
	CLAW_M,
	
	CLAW_MOTOR_LIST,
	
	
	
}claw_motor_list_e;

extern motor_t claw_motor[CLAW_MOTOR_LIST];

void claw_motor_init(void);
void claw_motor_heart_beat(void);
void claw_motor_rx_data(uint32_t canId, uint8_t *rxBuf);

#endif
