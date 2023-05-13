/*
* claw_motor
*	中间层注册电机
*	2022.11.19 
*/


#include "claw_motor.h"

motor_t claw_motor[CLAW_MOTOR_LIST] =
{
	[CLAW_L] = {
		.id.drive_type = M_CAN2,
		.id.motor_type = RM3508,
		.id.rx_id = 0x203,
		
		.init = motor_class_init,
	},
	[CLAW_R] = {
		.id.drive_type = M_CAN2,
		.id.motor_type = RM3508,
		.id.rx_id = 0x204,
		
		.init = motor_class_init,
	},
	[CLAW_M] = {
		.id.drive_type = M_CAN2,
		.id.motor_type = RM2006,
		.id.rx_id = 0x205,
		
		.init = motor_class_init,
	},
};


																						/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float claw_3508_posit_pid_param[7] 	 		= {		0.75,		0,		0,			0,		1000,			2000,			 5000};
																						/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float claw_3508_posit_in_pid_param[7] 	= {		8,		0.1,		0,			0,		1000,			2000,			 5000};

																				/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float claw_3508_speed_pid_param[7] 	= {		5,		0.1,		0,			0,		1000,			1000,			 2000};



																						/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float claw_2006_posit_pid_param[7] 			= {		0.75,		0,		0,			0,		1000,			2000,			 5000};
																						/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float claw_2006_posit_in_pid_param[7] 	= {		8,		0.1,		0,			0,		1000,			2000,			 5000};

																				/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float claw_2006_speed_pid_param[7] 	= {		8,		0.1,		0,			0,		1000,			1000,			 2000};


void claw_motor_init(void)
{
	//电机初始化
	claw_motor[CLAW_L].init(&claw_motor[CLAW_L]);
	//电机速度pid初始化
	claw_motor[CLAW_L].pid_init(&claw_motor[CLAW_L].pid.position,claw_3508_posit_pid_param);
	claw_motor[CLAW_L].pid_init(&claw_motor[CLAW_L].pid.position_in,claw_3508_posit_in_pid_param);
	claw_motor[CLAW_L].pid_init(&claw_motor[CLAW_L].pid.speed,claw_3508_speed_pid_param);
	
	//电机初始化
	claw_motor[CLAW_R].init(&claw_motor[CLAW_R]);
	//电机速度pid初始化
	claw_motor[CLAW_R].pid_init(&claw_motor[CLAW_R].pid.position,claw_3508_posit_pid_param);
	claw_motor[CLAW_R].pid_init(&claw_motor[CLAW_R].pid.position_in,claw_3508_posit_in_pid_param);
	claw_motor[CLAW_R].pid_init(&claw_motor[CLAW_R].pid.speed,claw_3508_speed_pid_param);
	
	//电机初始化
	claw_motor[CLAW_M].init(&claw_motor[CLAW_M]);
	//电机速度pid初始化
	claw_motor[CLAW_M].pid_init(&claw_motor[CLAW_M].pid.position,claw_2006_posit_pid_param);
	claw_motor[CLAW_M].pid_init(&claw_motor[CLAW_M].pid.position_in,claw_2006_posit_in_pid_param);
	claw_motor[CLAW_M].pid_init(&claw_motor[CLAW_M].pid.speed,claw_2006_speed_pid_param);
	

}


void claw_motor_heart_beat(void)
{
	claw_motor[CLAW_L].heartbeat(&claw_motor[CLAW_L]);
	claw_motor[CLAW_R].heartbeat(&claw_motor[CLAW_R]);
	claw_motor[CLAW_M].heartbeat(&claw_motor[CLAW_M]);
}



