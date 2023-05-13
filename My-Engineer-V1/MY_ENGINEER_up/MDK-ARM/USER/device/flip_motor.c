
/*
* flip_motor
*	�м��ע����
*	2022.12.12
* ����
*/


#include "flip_motor.h"

motor_t flip_motor[FLIP_MOTOR_LIST] =
{
	[LEFT] = {
		.id.drive_type = M_CAN1,
		.id.motor_type = RM2006,
		.id.rx_id = 0x201,
		
		.init = motor_class_init,
	},
	[RIGHT] = {
		.id.drive_type = M_CAN1,
		.id.motor_type = RM2006,
		.id.rx_id = 0x202,
		
		.init = motor_class_init,
	},
};

																				/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float flip_speed_pid_param[7] 	= {		8,		0.1,		0,			0,		2000,			2000,			 8000};




void flip_motor_init(void)
{
	//�����ʼ��
	flip_motor[LEFT].init(&flip_motor[LEFT]);
	//����ٶ�pid��ʼ��
	flip_motor[LEFT].pid_init(&flip_motor[LEFT].pid.speed,flip_speed_pid_param);
	
	//�����ʼ��
	flip_motor[RIGHT].init(&flip_motor[RIGHT]);
	//����ٶ�pid��ʼ��
	flip_motor[RIGHT].pid_init(&flip_motor[RIGHT].pid.speed,flip_speed_pid_param);
	
	

}


void flip_motor_heart_beat(void)
{
	flip_motor[FLIP_L].heartbeat(&flip_motor[FLIP_L]);
	flip_motor[FLIP_R].heartbeat(&flip_motor[FLIP_R]);
}



