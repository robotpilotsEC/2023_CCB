#ifndef __DEVICE_H
#define __DEVICE_H

#include "config.h"
#include "motor.h"
#include "chassis_motor.h"
#include "uplift_motor.h"
#include "rescue_motor.h"
#include "gimbal_motor.h"
#include "remote.h"
#include "imu.h"

typedef enum{
	DEVICE_01,
	DEVICE_02,
	DEVICE_03,
	DEVICE_04,
	DEVICE_05,
	DEVICE_06,
	DEVICE_07,
	DEVICE_08,
	DEVICE_09,
	DEVICE_10,
	DEVICE_CNT
}device_cnt_t;


typedef struct{
	motor_t						*motor;
}device_t;

extern device_t device[DEVICE_CNT];

void device_init(void);
void device_heart_beat(void);
void device_work(void);


#endif
