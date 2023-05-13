
/*
* rescue_motor
*	中间层注册电机
*	2022.12.12
* 抬升
*/


#include "rescue_motor.h"

motor_t rescue_motor[RESCUE_MOTOR_LIST] =
{
	[LEFT] = {
		.id.drive_type = M_CAN2,
		.id.motor_type = RM3508,
		.id.rx_id = 0x205,
		
		.init = motor_class_init,
	},
	[RIGHT] = {
		.id.drive_type = M_CAN2,
		.id.motor_type = RM3508,
		.id.rx_id = 0x206,
		
		.init = motor_class_init,
	},
};


																								/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float rescue_3508_posit_pid_param[7] 	 		= {		1,		0,		 0,			0,			1000,				   1000,			 2000};
																							/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float rescue_3508_posit_in_pid_param[7] 	= {		8,		0.1,		0,			0,		2000,			4000,			 10000};

																				/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float rescue_3508_speed_pid_param[7] 	= {		5,		0.1,		0,			0,				1500,			2000,			 5000};



/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void rescue_motor_init(void)
{
	//电机初始化
	rescue_motor[LEFT].init(&rescue_motor[LEFT]);
	//电机速度pid初始化
	rescue_motor[LEFT].pid_init(&rescue_motor[LEFT].pid.position,rescue_3508_posit_pid_param);
	rescue_motor[LEFT].pid_init(&rescue_motor[LEFT].pid.position_in,rescue_3508_posit_in_pid_param);
	rescue_motor[LEFT].pid_init(&rescue_motor[LEFT].pid.speed,rescue_3508_speed_pid_param);
	
	//电机初始化
	rescue_motor[RIGHT].init(&rescue_motor[RIGHT]);
	//电机速度pid初始化
	rescue_motor[RIGHT].pid_init(&rescue_motor[RIGHT].pid.position,rescue_3508_posit_pid_param);
	rescue_motor[RIGHT].pid_init(&rescue_motor[RIGHT].pid.position_in,rescue_3508_posit_in_pid_param);
	rescue_motor[RIGHT].pid_init(&rescue_motor[RIGHT].pid.speed,rescue_3508_speed_pid_param);
	
	
	
	//电机初始化
	rescue_motor[LEFT].init(&rescue_motor[LEFT]);
	//电机速度pid初始化
	rescue_motor[LEFT].pid_init(&rescue_motor[LEFT].pid.position,rescue_3508_posit_pid_param);
	rescue_motor[LEFT].pid_init(&rescue_motor[LEFT].pid.position_in,rescue_3508_posit_in_pid_param);
	rescue_motor[LEFT].pid_init(&rescue_motor[LEFT].pid.speed,rescue_3508_speed_pid_param);
	
	//电机初始化
	rescue_motor[RIGHT].init(&rescue_motor[RIGHT]);
	//电机速度pid初始化
	rescue_motor[RIGHT].pid_init(&rescue_motor[RIGHT].pid.position,rescue_3508_posit_pid_param);
	rescue_motor[RIGHT].pid_init(&rescue_motor[RIGHT].pid.position_in,rescue_3508_posit_in_pid_param);
	rescue_motor[RIGHT].pid_init(&rescue_motor[RIGHT].pid.speed,rescue_3508_speed_pid_param);
	
	

}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void rescue_motor_heart_beat(void)
{
	rescue_motor[LEFT].heartbeat(&rescue_motor[LEFT]);
	rescue_motor[RIGHT].heartbeat(&rescue_motor[RIGHT]);
}



