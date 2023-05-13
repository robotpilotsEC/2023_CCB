/*
* chassis_motor
*	�м��ע����
*	2022.11.6 
*/


#include "chassis_motor.h"

motor_t chassis_motor[CHASSIS_MOTOR_LIST] =
{
	[LF] = {
		.id.drive_type = M_CAN1,
		.id.motor_type = RM3508,
		.id.rx_id = 0x201,
		
		.init = motor_class_init,
	},
	[RF] = {
		.id.drive_type = M_CAN1,
		.id.motor_type = RM3508,
		.id.rx_id = 0x202,
		
		.init = motor_class_init,
	},
	[LB] = {
		.id.drive_type = M_CAN1,
		.id.motor_type = RM3508,
		.id.rx_id = 0x203,
		
		.init = motor_class_init,
	},
	[RB] = {
		.id.drive_type = M_CAN1,
		.id.motor_type = RM3508,
		.id.rx_id = 0x204,
		
		.init = motor_class_init,
	},
};


																			/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float chassis_speed_pid_param[7] = {		10,		0.1,		0,			0,				0,			5000,			 8000};

void chassis_motor_init(void)
{
	//�����ʼ��
	chassis_motor[LF].init(&chassis_motor[LF]);
	//����ٶ�pid��ʼ��
	chassis_motor[LF].pid_init(&chassis_motor[LF].pid.speed,chassis_speed_pid_param);
	
	//�����ʼ��
	chassis_motor[RF].init(&chassis_motor[RF]);
	//����ٶ�pid��ʼ��
	chassis_motor[RF].pid_init(&chassis_motor[RF].pid.speed,chassis_speed_pid_param);
	
	//�����ʼ��
	chassis_motor[LB].init(&chassis_motor[LB]);
	//����ٶ�pid��ʼ��
	chassis_motor[LB].pid_init(&chassis_motor[LB].pid.speed,chassis_speed_pid_param);
	
	//�����ʼ��
	chassis_motor[RB].init(&chassis_motor[RB]);
	//����ٶ�pid��ʼ��
	chassis_motor[RB].pid_init(&chassis_motor[RB].pid.speed,chassis_speed_pid_param);
}


void chassis_motor_heart_beat(void)
{
	chassis_motor[LF].heartbeat(&chassis_motor[LF]);
	chassis_motor[RF].heartbeat(&chassis_motor[RF]);
	chassis_motor[LB].heartbeat(&chassis_motor[LB]);
	chassis_motor[RB].heartbeat(&chassis_motor[RB]);
}


