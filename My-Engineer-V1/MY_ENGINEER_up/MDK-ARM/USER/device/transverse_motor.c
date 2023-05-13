
/*
* transverse_motor
*	中间层注册电机
*	2022.12.12
* 横移
*/


#include "transverse_motor.h"

motor_t transverse_motor[TRANSVERSE_MOTOR_LIST] =
{
	[FRONT] = {
		.id.drive_type = M_CAN1,
		.id.motor_type = RM3508,
		.id.rx_id = 0x205,
		
		.init = motor_class_init,
	},
	[BACK] = {
		.id.drive_type = M_CAN2,
		.id.motor_type = RM3508,
		.id.rx_id = 0x205,
		
		.init = motor_class_init,
	},
};


																										/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float transverse_3508_posit_pid_param[7] 	 		= {		1,		0,		0,			0,				0,			1500,			 4000};
																									/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float transverse_3508_posit_in_pid_param[7] 	= {		8,		0.1,		0,			0,				1500,			2000,		10000};

																				/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float transverse_3508_speed_pid_param[7] 	= {		8,		0.1,		0,			0,				1500,			1500,			 2000};




void transverse_motor_init(void)
{
	//电机初始化
	transverse_motor[FRONT].init(&transverse_motor[FRONT]);
	//电机速度pid初始化
	transverse_motor[FRONT].pid_init(&transverse_motor[FRONT].pid.position,transverse_3508_posit_pid_param);
	transverse_motor[FRONT].pid_init(&transverse_motor[FRONT].pid.position_in,transverse_3508_posit_in_pid_param);
	transverse_motor[FRONT].pid_init(&transverse_motor[FRONT].pid.speed,transverse_3508_speed_pid_param);
	
	//电机初始化
	transverse_motor[BACK].init(&transverse_motor[BACK]);
	//电机速度pid初始化
	transverse_motor[BACK].pid_init(&transverse_motor[BACK].pid.position,transverse_3508_posit_pid_param);
	transverse_motor[BACK].pid_init(&transverse_motor[BACK].pid.position_in,transverse_3508_posit_in_pid_param);
	transverse_motor[BACK].pid_init(&transverse_motor[BACK].pid.speed,transverse_3508_speed_pid_param);
	
	

}


void transverse_motor_heart_beat(void)
{
	transverse_motor[FRONT].heartbeat(&transverse_motor[FRONT]);
	transverse_motor[BACK].heartbeat(&transverse_motor[BACK]);
}




