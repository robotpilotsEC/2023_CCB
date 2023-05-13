/**
  ******************************************************************************
  * @file           : device.c/h
  * @brief          : 
  * @note           :  
  ******************************************************************************
  */
#include "device.h"
#include "control.h"

device_t device [] ={
	[DEVICE_01] = {
	 .motor = &transverse_motor[TRANSVERSE_F],	
	},
	[DEVICE_02] = {
	 .motor = &transverse_motor[TRANSVERSE_B],	
	},
	[DEVICE_03] = {
	 .motor = &flip_motor[FLIP_L],	
	},
	[DEVICE_04] = {
	 .motor = &flip_motor[FLIP_R],	
	}, 
	[DEVICE_05] = {
	 .motor = &sucker_motor[SUCKER_PITCH],	
	},
	[DEVICE_06] = {
	 .motor = &sucker_motor[SUCKER_YAW],	
	}, 
	[DEVICE_07] = {
	 .motor = &sucker_motor[SUCKER_ROLL],	
	},
	[DEVICE_08] = {
	 .motor = &protract_motor,	
	}, 
};

void device_init(void)
{
	flip_motor_init();
	sucker_motor_init();
	protract_motor_init();
	transverse_motor_init();
	pneumatic_init(&pneumatic);
}

void device_heart_beat(void)
{
	flip_motor_heart_beat();
	sucker_motor_heart_beat();
	protract_motor_heart_beat();
	transverse_motor_heart_beat();
}

void device_work(void)
{
	flip.work(&flip);
	uplift.work(&uplift);
	rescue.work(&rescue);
	gimbal.work(&gimbal);
	sucker.work(&sucker);
	protract.work(&protract);
	transverse.work(&transverse);
	pneumatic.work(&pneumatic);
	if(!RC_ONLINE)
	{
		for(uint16_t i=0;i<DEVICE_CNT;i++)
		{
			device[i].motor->base_info.motor_out = 0;
			device[i].motor->base_info.pid_out = 0;
		}
	}
}

