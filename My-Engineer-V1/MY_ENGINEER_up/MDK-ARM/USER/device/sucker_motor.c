
/*
* sucker_motor
*	中间层注册电机
*	2023.3.4
* 横移
*/


#include "sucker_motor.h"

motor_t sucker_motor[SUCKER_MOTOR_LIST] =
{
	[DEFFL] = {
		.id.drive_type = M_CAN2,
		.id.motor_type = RM2006,
		.id.rx_id = 0x201,
		
		.init = motor_class_init,
	},
	[YAW] = {
		.id.drive_type = M_CAN2,
		.id.motor_type = RM2006,
		.id.rx_id = 0x203,
		
		.init = motor_class_init,
	},
	[DEFFR] = {
		.id.drive_type = M_CAN2,
		.id.motor_type = RM2006,
		.id.rx_id = 0x202,
		
		.init = motor_class_init,
	},
};


																						/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float DEFFL_posit_pid_param[7] 	 			= {		1,		0,		0,			0,			0,			0,			 3000};
																						/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float DEFFL_posit_in_pid_param[7] 		= {		6,		0.1,		0,			0,		1500,			2000,		10000};
																						/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float DEFFL_speed_pid_param[7] 				= {		8,		0.1,		0,			0,		1500,			1500,		2000};

																						/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float YAW_posit_pid_param[7] 	 			= {		1,		0,		0,			0,			0,			0,			 2000};
																						/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float YAW_posit_in_pid_param[7] 			= {		10,		0.1,		0,			0,		1500,			2000,		10000};
																						/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float YAW_speed_pid_param[7] 				= {		8,		0.1,		0,			0,		1500,			1500,		2000};

																						/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float DEFFR_posit_pid_param[7] 	 			= {		1,		0,		0,			0,			0,			0,			 3000};
																						/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float DEFFR_posit_in_pid_param[7] 		= {		6,		0.1,		0,			0,		1500,			2000,		10000};
																						/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float DEFFR_speed_pid_param[7] 				= {		8,		0.1,		0,			0,		1500,			1500,		2000};



void sucker_motor_init(void)
{
	//电机初始化
	sucker_motor[DEFFL].init(&sucker_motor[DEFFL]);
	//电机速度pid初始化
	sucker_motor[DEFFL].pid_init(&sucker_motor[DEFFL].pid.position,DEFFL_posit_pid_param);
	sucker_motor[DEFFL].pid_init(&sucker_motor[DEFFL].pid.position_in,DEFFL_posit_in_pid_param);
	sucker_motor[DEFFL].pid_init(&sucker_motor[DEFFL].pid.speed,DEFFL_speed_pid_param);
	
	//电机初始化
	sucker_motor[YAW].init(&sucker_motor[YAW]);
	//电机速度pid初始化
	sucker_motor[YAW].pid_init(&sucker_motor[YAW].pid.position,YAW_posit_pid_param);
	sucker_motor[YAW].pid_init(&sucker_motor[YAW].pid.position_in,YAW_posit_in_pid_param);
	sucker_motor[YAW].pid_init(&sucker_motor[YAW].pid.speed,YAW_speed_pid_param);
	
	//电机初始化
	sucker_motor[DEFFR].init(&sucker_motor[DEFFR]);
	//电机速度pid初始化
	sucker_motor[DEFFR].pid_init(&sucker_motor[DEFFR].pid.position,DEFFR_posit_pid_param);
	sucker_motor[DEFFR].pid_init(&sucker_motor[DEFFR].pid.position_in,DEFFR_posit_in_pid_param);
	sucker_motor[DEFFR].pid_init(&sucker_motor[DEFFR].pid.speed,DEFFR_speed_pid_param);
	
	

}


void sucker_motor_heart_beat(void)
{
	sucker_motor[DEFFL].heartbeat(&sucker_motor[DEFFL]);
	sucker_motor[YAW].heartbeat(&sucker_motor[YAW]);
	sucker_motor[DEFFR].heartbeat(&sucker_motor[DEFFR]);
}




