
/*
* uplift_motor
*	中间层注册电机
*	2022.12.12
* 抬升
*/


#include "uplift_motor.h"

motor_t uplift_motor[UPLIFT_MOTOR_LIST] =
{
	[UPLIFT_F] = {
		.id.drive_type = M_CAN1,
		.id.motor_type = RM3508,
		.id.rx_id = 0x201,
		
		.init = motor_class_init,
	},
	[UPLIFT_B] = {
		.id.drive_type = M_CAN2,
		.id.motor_type = RM3508,
		.id.rx_id = 0x201,
		
		.init = motor_class_init,
	},
};


																								/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float uplift_3508_posit_pid_param[7] 	 		= {		0.3,		0,		 0,			0,			0,				   0,			 5000};
																							/*kp		ki		kd		d_err		int_max		iout_max		out_max*/
float uplift_3508_posit_in_pid_param[7] 	= {		18,		0.5,		0,			0,		2000,			2000,			 5000};

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
	uplift_motor[UPLIFT_F].init(&uplift_motor[UPLIFT_F]);
	//电机速度pid初始化
	uplift_motor[UPLIFT_F].pid_init(&uplift_motor[UPLIFT_F].pid.position,uplift_3508_posit_pid_param);
	uplift_motor[UPLIFT_F].pid_init(&uplift_motor[UPLIFT_F].pid.position_in,uplift_3508_posit_in_pid_param);
	uplift_motor[UPLIFT_F].pid_init(&uplift_motor[UPLIFT_F].pid.speed,uplift_3508_speed_pid_param);
	
	//电机初始化
	uplift_motor[UPLIFT_B].init(&uplift_motor[UPLIFT_B]);
	//电机速度pid初始化
	uplift_motor[UPLIFT_B].pid_init(&uplift_motor[UPLIFT_B].pid.position,uplift_3508_posit_pid_param);
	uplift_motor[UPLIFT_B].pid_init(&uplift_motor[UPLIFT_B].pid.position_in,uplift_3508_posit_in_pid_param);
	uplift_motor[UPLIFT_B].pid_init(&uplift_motor[UPLIFT_B].pid.speed,uplift_3508_speed_pid_param);
	
	

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
	uplift_motor[UPLIFT_F].heartbeat(&uplift_motor[UPLIFT_F]);
	uplift_motor[UPLIFT_B].heartbeat(&uplift_motor[UPLIFT_B]);
}



