#include "device.h"
#include "control.h"

device_t device [] ={
	[DEVICE_01] = {
	 .motor = &chassis_motor[LF],
	},
	[DEVICE_02] = {
	 .motor = &chassis_motor[RF],
	},
	[DEVICE_03] = {
	 .motor = &chassis_motor[LB],	
	},
	[DEVICE_04] = {
	 .motor = &chassis_motor[RB],	
	},	
	[DEVICE_05] = {
	 .motor = &uplift_motor[FRONT],		
	},
	[DEVICE_06] = {
	 .motor = &uplift_motor[BACK],	
	},
	[DEVICE_07] = {
	 .motor = &gimbal_motor[PITCH],		
	},
	[DEVICE_08] = {
	 .motor = &gimbal_motor[YAW],	
	},
	[DEVICE_09] = {
	 .motor = &rescue_motor[LEFT],		
	},
	[DEVICE_10] = {
	 .motor = &rescue_motor[RIGHT],	
	},
};

void device_init(void)
{
	uplift_motor_init();
	gimbal_motor_init();
	rescue_motor_init();
	chassis_motor_init();
	chassis.init(&chassis,&chassis_init);
}

void device_heart_beat(void)
{
	chassis_motor_heart_beat();
	uplift_motor_heart_beat();
	rescue_motor_heart_beat();
	gimbal_motor_heart_beat();
}

void device_work(void)
{
	gimbal.work(&gimbal);
	rescue.work(&rescue);
	uplift.work(&uplift);
	chassis.work(&chassis);
	if(!RC_ONLINE)
	{
		for(uint16_t i=0;i<DEVICE_CNT;i++)
		{
			device[i].motor->base_info.motor_out = 0;
			device[i].motor->base_info.pid_out = 0;
		}
	}
}

