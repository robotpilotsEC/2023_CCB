
/*
* gimbal_motor
*	中间层注册电机
*	2022.12.12
* 抬升
*/


#include "gimbal_motor.h"

motor_t gimbal_motor[GIMBAL_MOTOR_LIST] =
{
	[PITCH] = {
		.id.drive_type = M_CAN2,
		.id.motor_type = RM2006,
		.id.rx_id = 0x203,
		
		.init = motor_class_init,
	},
	[YAW] = {
		.id.drive_type = M_CAN2,
		.id.motor_type = RM2006,
		.id.rx_id = 0x204,
		
		.init = motor_class_init,
	},
};


																								/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float gimbal_2006_posit_pid_param[7] 	 		= {		0.8,		0,		 0,			0,			0,				   0,			 2000};
																							/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float gimbal_2006_posit_in_pid_param[7] 	= {		8,		0.1,		0,			0,		2000,			4000,			 8000};

																				/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float gimbal_2006_speed_pid_param[7] 	= {		5,		0.1,		0,			0,				1500,			2000,			 2000};



/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void gimbal_motor_init(void)
{
	//电机初始化
	gimbal_motor[PITCH].init(&gimbal_motor[PITCH]);
	//电机速度pid初始化
	gimbal_motor[PITCH].pid_init(&gimbal_motor[PITCH].pid.position,gimbal_2006_posit_pid_param);
	gimbal_motor[PITCH].pid_init(&gimbal_motor[PITCH].pid.position_in,gimbal_2006_posit_in_pid_param);
	gimbal_motor[PITCH].pid_init(&gimbal_motor[PITCH].pid.speed,gimbal_2006_speed_pid_param);
	
	//电机初始化
	gimbal_motor[YAW].init(&gimbal_motor[YAW]);
	//电机速度pid初始化
	gimbal_motor[YAW].pid_init(&gimbal_motor[YAW].pid.position,gimbal_2006_posit_pid_param);
	gimbal_motor[YAW].pid_init(&gimbal_motor[YAW].pid.position_in,gimbal_2006_posit_in_pid_param);
	gimbal_motor[YAW].pid_init(&gimbal_motor[YAW].pid.speed,gimbal_2006_speed_pid_param);
	
	
	
	//电机初始化
	gimbal_motor[PITCH].init(&gimbal_motor[PITCH]);
	//电机速度pid初始化
	gimbal_motor[PITCH].pid_init(&gimbal_motor[PITCH].pid.position,gimbal_2006_posit_pid_param);
	gimbal_motor[PITCH].pid_init(&gimbal_motor[PITCH].pid.position_in,gimbal_2006_posit_in_pid_param);
	gimbal_motor[PITCH].pid_init(&gimbal_motor[PITCH].pid.speed,gimbal_2006_speed_pid_param);
	
	//电机初始化
	gimbal_motor[YAW].init(&gimbal_motor[YAW]);
	//电机速度pid初始化
	gimbal_motor[YAW].pid_init(&gimbal_motor[YAW].pid.position,gimbal_2006_posit_pid_param);
	gimbal_motor[YAW].pid_init(&gimbal_motor[YAW].pid.position_in,gimbal_2006_posit_in_pid_param);
	gimbal_motor[YAW].pid_init(&gimbal_motor[YAW].pid.speed,gimbal_2006_speed_pid_param);
	
	

}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void gimbal_motor_heart_beat(void)
{
	gimbal_motor[PITCH].heartbeat(&gimbal_motor[PITCH]);
	gimbal_motor[YAW].heartbeat(&gimbal_motor[YAW]);
}



