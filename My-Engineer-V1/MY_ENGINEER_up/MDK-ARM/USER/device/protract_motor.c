
/*
* protract_motor
*	中间层注册电机
*	2023.3.5
* 前伸
*/


#include "protract_motor.h"

motor_t protract_motor =
{
	.id.drive_type = M_CAN2,
	.id.motor_type = RM2006,
	.id.rx_id = 0x204,
	
	.init = motor_class_init,

};


																						/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float protract_posit_pid_param[7] 	 		= {		0.4,		0,		0,			0,			0,				0,			 2000};
																						/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float protract_posit_in_pid_param[7] 		= {		10,		0.5,		0,			0,		4000,			2000,			 8000};
																						/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float protract_speed_pid_param[7] 			= {		8,		0.1,		0,			0,		1500,			1500,			 2000};




void protract_motor_init(void)
{
	//电机初始化
	protract_motor.init(&protract_motor);
	//电机速度pid初始化
	protract_motor.pid_init(&protract_motor.pid.position,protract_posit_pid_param);
	protract_motor.pid_init(&protract_motor.pid.position_in,protract_posit_in_pid_param);
	protract_motor.pid_init(&protract_motor.pid.speed,protract_speed_pid_param);
	
}


void protract_motor_heart_beat(void)
{
	protract_motor.heartbeat(&protract_motor);
}




