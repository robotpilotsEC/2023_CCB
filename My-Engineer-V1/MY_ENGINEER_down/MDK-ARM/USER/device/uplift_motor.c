
/*
* uplift_motor
*	中间层注册电机
*	2022.12.12
* 抬升
*/


#include "uplift_motor.h"

motor_t uplift_motor[UPLIFT_MOTOR_LIST] =
{
	[FRONT] = {
		.id.drive_type = M_CAN2,
		.id.motor_type = RM3508,
		.id.rx_id = 0x201,
		
		.init = motor_class_init,
	},
	[BACK] = {
		.id.drive_type = M_CAN2,
		.id.motor_type = RM3508,
		.id.rx_id = 0x202,
		
		.init = motor_class_init,
	},
};

																								/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float uplift_3508_posit_pid_param[7] 	 		= {		1,		0,		 0,			0,			1000,				   1000,			 2000};
																							/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float uplift_3508_posit_in_pid_param[7] 	= {		8,		0,		0,			0,		2000,			4000,			 12000};

																				/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float uplift_3508_speed_pid_param[7] 	= {		5,		0.1,		0,			0,				1500,			2000,			 5000};



/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void uplift_motor_init(void)
{
	//电机初始化
	uplift_motor[FRONT].init(&uplift_motor[FRONT]);
	//电机速度pid初始化
	uplift_motor[FRONT].pid_init(&uplift_motor[FRONT].pid.position,uplift_3508_posit_pid_param);
	uplift_motor[FRONT].pid_init(&uplift_motor[FRONT].pid.position_in,uplift_3508_posit_in_pid_param);
	uplift_motor[FRONT].pid_init(&uplift_motor[FRONT].pid.speed,uplift_3508_speed_pid_param);
	
	//电机初始化
	uplift_motor[BACK].init(&uplift_motor[BACK]);
	//电机速度pid初始化
	uplift_motor[BACK].pid_init(&uplift_motor[BACK].pid.position,uplift_3508_posit_pid_param);
	uplift_motor[BACK].pid_init(&uplift_motor[BACK].pid.position_in,uplift_3508_posit_in_pid_param);
	uplift_motor[BACK].pid_init(&uplift_motor[BACK].pid.speed,uplift_3508_speed_pid_param);
	
	
	
	//电机初始化
	uplift_motor[FRONT].init(&uplift_motor[FRONT]);
	//电机速度pid初始化
	uplift_motor[FRONT].pid_init(&uplift_motor[FRONT].pid.position,uplift_3508_posit_pid_param);
	uplift_motor[FRONT].pid_init(&uplift_motor[FRONT].pid.position_in,uplift_3508_posit_in_pid_param);
	uplift_motor[FRONT].pid_init(&uplift_motor[FRONT].pid.speed,uplift_3508_speed_pid_param);
	
	//电机初始化
	uplift_motor[BACK].init(&uplift_motor[BACK]);
	//电机速度pid初始化
	uplift_motor[BACK].pid_init(&uplift_motor[BACK].pid.position,uplift_3508_posit_pid_param);
	uplift_motor[BACK].pid_init(&uplift_motor[BACK].pid.position_in,uplift_3508_posit_in_pid_param);
	uplift_motor[BACK].pid_init(&uplift_motor[BACK].pid.speed,uplift_3508_speed_pid_param);
	
	

}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void uplift_motor_heart_beat(void)
{
	uplift_motor[FRONT].heartbeat(&uplift_motor[FRONT]);
	uplift_motor[BACK].heartbeat(&uplift_motor[BACK]);
}



