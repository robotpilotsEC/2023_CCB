/**
  ************************************* Copyright ******************************   
  *                 (C) Copyright 2022, hwx, China, SZU.
  *                            N0   Rights  Reserved
  *                              
  *                   
  * @FileName   : chassis.c   
  * @Version    : v1.1		
  * @Author     : hwx			
  * @Date       : 2022-11-06         
  * @Description:    
  *
  *
  ******************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "chassis.h"
#include "remote.h"
#include "config.h"
#include "string.h"
#include "imu.h"
#include "math_support.h"
#include "car_state.h"
#include "control.h"
/* Exported variables --------------------------------------------------------*/

Chassis_InitTypeDef 	chassis_init = 
{
	.motor_LF = &chassis_motor[CHAS_LF],
	.motor_RF = &chassis_motor[CHAS_RF],
	.motor_LB = &chassis_motor[CHAS_LB],
	.motor_RB = &chassis_motor[CHAS_RB],
};


chassis_t chassis = {
	
	.init      = Chassis_Init,
	.work      = Chassis_Work,

};




/* Function  body --------------------------------------------------------*/
/**
  * @Name    Chassic_init
  * @brief   注册底盘
  * @param   底盘类 底盘初始化结构体
  * @retval
  * @author  HWX
  * @Date    2022-11-06
**/

void Chassis_Init(chassis_t *Chassis , Chassis_InitTypeDef *Chassis_Init_structure)
{
	
	
	if(Chassis_Init_structure->motor_LF         	== NULL ||\
		 Chassis_Init_structure->motor_RF           == NULL ||\
		 Chassis_Init_structure->motor_LB           == NULL ||\
		 Chassis_Init_structure->motor_RB           == NULL )
	{
		return;
	}

	/*注册四个电机*/
	Chassis->motor_LB = Chassis_Init_structure->motor_LB;
	Chassis->motor_LF = Chassis_Init_structure->motor_LF;
	Chassis->motor_RF = Chassis_Init_structure->motor_RF;
	Chassis->motor_RB = Chassis_Init_structure->motor_RB;
		
	
	Chassis->work_info.output_max              = MAX_SPEED;
	Chassis->work_info.speed_max               = CHASSIS_OUTPUT_MAX;
	Chassis->work_info.config.cycle_Kp				 = CHASSIS_CYCLE_KP;
}



/**
  * @Name    Chassis_Speed_Slow_Dowm
  * @brief   梯度
  * @param   底盘 三个方向速度
  * @retval
  * @author  CCB
  * @Date    2022-11-08
**/
int16_t last_front,last_right,last_cycle;
void Chassis_Speed_Slow_Dowm(chassis_t *chassis,int16_t *front, int16_t *right, int16_t *cycle)
{
	if(chassis->work_info.config.brake_flag == 1)
	{
		last_front = 0;
		last_right = 0;
		return;
	}
	
	

//	if(*front - last_front > CHASSIS_SPEED_CONSTRAIN)
//		*front = last_front + CHASSIS_SPEED_CONSTRAIN;
//	else if(*front - last_front < -CHASSIS_SPEED_CONSTRAIN)
//		*front = last_front - CHASSIS_SPEED_CONSTRAIN;
//	
//	if(*right - last_right > CHASSIS_SPEED_CONSTRAIN)
//		*right = last_right + CHASSIS_SPEED_CONSTRAIN;
//	else if(*right - last_right < -CHASSIS_SPEED_CONSTRAIN)
//		*right = last_right - CHASSIS_SPEED_CONSTRAIN;
//	
//	if(*front != 0)
//		last_front = *front;
//	else
//		last_front = 0;
//	
//	if(*right != 0)
//		last_right = *right;
//	else
//		last_right = 0;
	
}



/**
  * @Name    Chassis_Speed_Limit
  * @brief   速度限制（等比例缩小）
  * @param   底盘 三个方向速度
  * @retval
  * @author  HWX CCB
  * @Date    2022-11-26
**/
void Chassis_Speed_Limit(chassis_t *chassis,int16_t *front, int16_t *right, int16_t *cycle)
{
	
	int16_t speed_sum;
	float RATE;
	
	speed_sum = c_abs(*front) + c_abs(*right) + c_abs(*cycle);
	
	if(speed_sum > chassis->work_info.speed_max)
	{
		RATE = (float)chassis->work_info.speed_max / (float)speed_sum;
	}
	else 
		RATE = 1;
	
	*front *= RATE;
	*right *= RATE;
	*cycle *= RATE;
	
}


/**
  * @Name    Chassis_Brake_Flag
  * @brief   刹车标志
  * @param   底盘 三个方向速度
  * @retval
  * @author   CCB
  * @Date    2022-12-2
**/
uint16_t speed_sum;
uint8_t brake_flag,brake_ch;
void Chassis_Brake_Flag(chassis_t *chassis, int16_t *front, int16_t *right, int16_t *cycle)
{
	
  speed_sum = c_abs(chassis->motor_LB->rx_info.speed) + c_abs(chassis->motor_RB->rx_info.speed) +\
											 c_abs(chassis->motor_LF->rx_info.speed) + c_abs(chassis->motor_RF->rx_info.speed);
	
	if(speed_sum > 8000)
		brake_flag = 1;
	else if(chassis->work_info.config.brake_flag == 0)
		brake_flag = 0;
	else if(chassis->work_info.config.brake_flag == 1)
	{
		if(speed_sum == 0)
			brake_flag = 0;
	}
		
	if(car.ctrl_mode == RC_CAR)
	{
		if(rc.base_info->ch0 == 0 && rc.base_info->ch2 == 0 && rc.base_info->ch3 == 0)
			brake_ch = 1;
		else
			brake_ch = 0;
	}
	else if(car.ctrl_mode == KEY_CAR)
	{
		if(rc.base_info->W.cnt == 0 && rc.base_info->S.cnt == 0 && \
			 rc.base_info->A.cnt == 0 && rc.base_info->D.cnt == 0 && \
				rc.info->mouse_x_K < 0.001f && rc.info->mouse_x_K > -0.001f)
			brake_ch = 1;
		else
			brake_ch = 0;
	}
	else
		brake_ch = 0;
		
	if(brake_ch && brake_flag)
		chassis->work_info.config.brake_flag = 1;
	else 
		chassis->work_info.config.brake_flag = 0;
	

}


/**
  * @Name    Chassis_Speed_Limit
  * @brief   刹车
  * @param   底盘 三个方向速度
  * @retval
  * @author   CCB
  * @Date    2022-12-2
**/
void Chassis_Brake(chassis_t *chassis)
{
	if(chassis->work_info.config.brake_flag == 1)
	{	
		chassis->base_info.output.motor_LF_current = chassis->motor_LF->c_speed(chassis->motor_LF ,0);
		chassis->base_info.output.motor_RF_current = chassis->motor_RF->c_speed(chassis->motor_RF ,0);
		chassis->base_info.output.motor_LB_current = chassis->motor_LB->c_speed(chassis->motor_LB ,0);
		chassis->base_info.output.motor_RB_current = chassis->motor_RB->c_speed(chassis->motor_RB ,0);
	}
}


/**
  * @Name    Chassis_Speed_Calculating
  * @brief   底盘速度解算
  * @param   三个方向速度
  * @retval
  * @author  HWX CCB
  * @Date    2022-12-3
**/
int16_t cycle_save;
void Chassis_Speed_Calculating(chassis_t *chassis, int16_t *front, int16_t *right, int16_t *cycle)
{
	chassis_config_t *config = &chassis->work_info.config;
	
	if(!config->spin_flag)
	{
		Chassis_Brake_Flag(chassis,front, right, cycle);
		Chassis_Speed_Slow_Dowm(chassis,front, right, cycle);
		Chassis_Speed_Limit(chassis,front, right, cycle);
	}
	
	
	
	if(car.mode_switch==SAVE&&*cycle!=0)
		cycle_save = 8000*(*cycle)/config->chassis_speed_max;
	else
		cycle_save = 0;
		
	
	chassis->base_info.output.motor_LF_speed   = (  *front + *right + *cycle) - cycle_save;
	chassis->base_info.output.motor_RF_speed   = (- *front + *right + *cycle) - cycle_save;
	chassis->base_info.output.motor_LB_speed   = (  *front - *right + *cycle) + cycle_save;
	chassis->base_info.output.motor_RB_speed   = (- *front - *right + *cycle) + cycle_save;		
	
}


/**
  * @Name    Chassis_Pid_Calculating
  * @brief   使用到底盘包
  * @param   底盘 
  * @retval 
  * @author  HWX CCB
  * @Date    2022-12-03
**/
void Chassis_Pid_Calculating(chassis_t *chassis)
{
	
	chassis->base_info.output.motor_LF_current = chassis->motor_LF->c_speed(chassis->motor_LF ,chassis->base_info.output.motor_LF_speed);
	chassis->base_info.output.motor_RF_current = chassis->motor_RF->c_speed(chassis->motor_RF ,chassis->base_info.output.motor_RF_speed);
	chassis->base_info.output.motor_LB_current = chassis->motor_LB->c_speed(chassis->motor_LB ,chassis->base_info.output.motor_LB_speed);
	chassis->base_info.output.motor_RB_current = chassis->motor_RB->c_speed(chassis->motor_RB ,chassis->base_info.output.motor_RB_speed);
	
	Chassis_Brake(chassis);
	
}



/**
  * @Name    Chassis_Pid_Calculating
  * @brief   使用到底盘包
  * @param   底盘 
  * @retval 
  * @author  HWX CCB
  * @Date    2022-12-03
**/

void Chassis_Speed_Max_Switch(chassis_t *chassis)
{
	chassis_config_t *config = &chassis->work_info.config;
	switch(car.mode_switch)
	{
		case LOB:
			config->chassis_speed_max = 3500.f;
			break;
		case SILVER_ORE:
			config->chassis_speed_max = 3500.f;
			break;
		case GOLDEN_ORE:
			config->chassis_speed_max = 3500.f;
			break;
		case GROUND_ORE:
			config->chassis_speed_max = 3500.f;
			break;
		case EXCHANGE_ORE:
			config->chassis_speed_max = 3500.f;
			break;
		default:
			config->chassis_speed_max = 6000.f * (1.3f - (float)uplift.back->rx_info.angle_sum/UPLIFT_MAX);
			if(CTRL_DOWN)
				config->chassis_speed_max*=0.27f;
				
			break;
	}	
}

/**
  * @Name    Chassis_speed_ctrl_switch
  * @brief   使用到底盘包
  * @param   底盘 
  * @retval 
  * @author  CCB
  * @Date    2023-04-28
**/
int16_t front,right,cycle;
void Chassis_speed_ctrl_switch(chassis_t *chassis,int16_t RC_FS,int16_t RC_RS,int16_t RC_CS,float Key_FS,float Key_BS,float Key_RS,float Key_LS,float Key_CS,uint8_t mode)
{
	chassis_target_t *target = &chassis->base_info.target;
	chassis_config_t *config = &chassis->work_info.config;
	
	if(mode)
	{
		switch(car.ctrl_mode)
		{
			case RC_CAR:
				target->front_speed = (int16_t)RC_FS / RC_CNT_MAX * config->chassis_speed_max;
				target->right_speed = (int16_t)RC_RS / RC_CNT_MAX * config->chassis_speed_max;
				if(RC_CS == 0 && config->brake_flag == 0 && speed_sum == 0)			
					config->chassis_imu_angle = imu.info->yaw;
			
				target->cycle_err = config->chassis_imu_angle - imu.info->yaw;
				target->cycle_err = Half_Turn(target->cycle_err,360.f);
				
				if(c_abs(target->cycle_err) < 45.f)
					config->chassis_imu_angle += RC_CS * IMU_K;
				config->chassis_imu_angle = Half_Turn(config->chassis_imu_angle,360.f);
			
				cycle = (int16_t)target->cycle_err*config->cycle_Kp;
				break;
				
			case KEY_CAR:
				target->front_speed = (float)(Key_FS - Key_BS) / KEY_W_CNT_MAX * config->chassis_speed_max;
				target->right_speed = (float)(Key_RS - Key_LS) / KEY_W_CNT_MAX * config->chassis_speed_max;
				if(Key_CS == 0 && config->brake_flag == 0 && speed_sum == 0)			
					config->chassis_imu_angle = imu.info->yaw;
				
				target->cycle_err = config->chassis_imu_angle - imu.info->yaw;
				target->cycle_err = Half_Turn(target->cycle_err,360.f);
				
				if(c_abs(target->cycle_err) < 45.f)
					config->chassis_imu_angle += Key_CS * IMU_K;
				config->chassis_imu_angle = Half_Turn(config->chassis_imu_angle,360.f);
			
				cycle = (int16_t)target->cycle_err*config->cycle_Kp;
			
				break;
			
			default:
				break;
		}
	}
	else if(!mode)
	{
		switch(car.ctrl_mode)
		{
			case RC_CAR:
				target->front_speed = (int16_t)RC_FS / RC_CNT_MAX * config->chassis_speed_max;
				target->right_speed = (int16_t)RC_RS / RC_CNT_MAX * config->chassis_speed_max;
				target->cycle_err = (int16_t)RC_CS / RC_CNT_MAX * config->chassis_speed_max;
				cycle = (int16_t)target->cycle_err;
			
				config->chassis_imu_angle = imu.info->yaw;
				break;
				
			case KEY_CAR:
				target->front_speed = (float)(Key_FS - Key_BS) / KEY_W_CNT_MAX * config->chassis_speed_max;
				target->right_speed = (float)(Key_RS - Key_LS) / KEY_W_CNT_MAX * config->chassis_speed_max;
				target->cycle_err = Key_CS * KEY_K;
				cycle = (int16_t)target->cycle_err;
			
				config->chassis_imu_angle = imu.info->yaw;
				break;
			
			default:
				break;
		}
	}
}

/**
  * @Name    Chassis_Work_Normal
  * @brief   使用到底盘包
  * @param   底盘 
  * @retval 
  * @author  HWX CCB
  * @Date    2022-12-03
**/
void Chassis_Work_Normal(chassis_t *chassis)
{
	chassis_target_t *target = &chassis->base_info.target;
	chassis_config_t *config = &chassis->work_info.config;
	
	Chassis_Speed_Max_Switch(chassis);
	
	if(!config->lock_flag)
	{
		if(!config->spin_flag)
		{
			switch(car.mode_switch)
			{
				case LOB:
					Chassis_speed_ctrl_switch(chassis,rc.base_info->ch2,-rc.base_info->ch3,rc.base_info->ch0,\
																		rc.base_info->D.cnt,rc.base_info->A.cnt,\
																		rc.base_info->S.cnt,rc.base_info->W.cnt,\
																		rc.info->mouse_x_K,0);
					break;
				case SILVER_ORE:
					Chassis_speed_ctrl_switch(chassis,rc.base_info->ch2,-rc.base_info->ch3,rc.base_info->ch0,\
																		rc.base_info->D.cnt,rc.base_info->A.cnt,\
																		rc.base_info->S.cnt,rc.base_info->W.cnt,\
																		rc.info->mouse_x_K,0);
					break;
				case GOLDEN_ORE:
					Chassis_speed_ctrl_switch(chassis,rc.base_info->ch2,-rc.base_info->ch3,rc.base_info->ch0,\
																		rc.base_info->D.cnt,rc.base_info->A.cnt,\
																		rc.base_info->S.cnt,rc.base_info->W.cnt,\
																		rc.info->mouse_x_K,0);
					break;
				case GROUND_ORE:
					Chassis_speed_ctrl_switch(chassis,rc.base_info->ch2,-rc.base_info->ch3,rc.base_info->ch0,\
																		rc.base_info->D.cnt,rc.base_info->A.cnt,\
																		rc.base_info->S.cnt,rc.base_info->W.cnt,\
																		rc.info->mouse_x_K,0);
					break;
				case EXCHANGE_ORE:
					Chassis_speed_ctrl_switch(chassis,rc.base_info->ch2,-rc.base_info->ch3,rc.base_info->ch0,\
																		rc.base_info->D.cnt,rc.base_info->A.cnt,\
																		rc.base_info->S.cnt,rc.base_info->W.cnt,\
																		rc.info->mouse_x_K/2.f,0);
					break;
				case SAVE:
					Chassis_speed_ctrl_switch(chassis,rc.base_info->ch3,rc.base_info->ch2,rc.base_info->ch0,\
																		rc.base_info->W.cnt,rc.base_info->S.cnt,\
																		rc.base_info->D.cnt,rc.base_info->A.cnt,\
																		rc.info->mouse_x_K,0);
						
					break;
				default:
					Chassis_speed_ctrl_switch(chassis,rc.base_info->ch3,rc.base_info->ch2,rc.base_info->ch0,\
																		rc.base_info->W.cnt,rc.base_info->S.cnt,\
																		rc.base_info->D.cnt,rc.base_info->A.cnt,\
																		rc.info->mouse_x_K,1);
					
					break;
			}	
		}
		else
			Chassis_speed_ctrl_switch(chassis,0,0,4000,0,0,0,0,800.f,0);
	}
	else if(!SHIFT_DOWN)
			Chassis_speed_ctrl_switch(chassis,rc.base_info->ch3,rc.base_info->ch2,0,\
																rc.base_info->W.cnt,rc.base_info->S.cnt,\
																rc.base_info->D.cnt,rc.base_info->A.cnt,\
																0.f,0);
	else if(SHIFT_DOWN)
			Chassis_speed_ctrl_switch(chassis,0,0,0,0,0,0,0,0.f,0);
	
	
	front = target->front_speed;
	right = target->right_speed;
		
	/*底盘速度解算*/
	Chassis_Speed_Calculating(chassis, &front, &right, &cycle);

	/*PID计算*/
	Chassis_Pid_Calculating(chassis);

	chassis->motor_LF->base_info.motor_out = chassis->base_info.output.motor_LF_current;
	chassis->motor_RF->base_info.motor_out = chassis->base_info.output.motor_RF_current;
	chassis->motor_LB->base_info.motor_out = chassis->base_info.output.motor_LB_current;
	chassis->motor_RB->base_info.motor_out = chassis->base_info.output.motor_RB_current;
	
}


/**
  * @Name    Chassis_Work
  * @brief   底盘核心函数
  * @param   底盘 
  * @retval
  * @author  CCB
  * @Date    2022-12-03
**/
void Chassis_Work(chassis_t *chassis)
{
	if(SYSTEM_RESET)
		Chassis_Work_Normal(chassis);
	else
	{
		chassis->work_info.config.chassis_imu_angle = imu.info->yaw;
		chassis->base_info.output.motor_LF_current = 0;
		chassis->base_info.output.motor_RF_current = 0;
		chassis->base_info.output.motor_LB_current = 0;
		chassis->base_info.output.motor_RB_current = 0;
	}
	
}



