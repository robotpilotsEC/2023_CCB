/*
* sucker
*	
*	2023.3.4
* ¶Ò»»
*/

/* Includes ------------------------------*/
#include "sucker.h"
#include "control.h"
/* Exported variables --------------------*/



sucker_t sucker = 
{
	.deffL = &sucker_motor[DEFFL],
	.yaw = &sucker_motor[YAW],
	.deffR = &sucker_motor[DEFFR],
	
	.work = Sucker_Work,
	
	.reset = DEV_RESET_NO,
};

/* Function  body --------------------------------------------------------*/

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void Sucker_Pid_Calculating(sucker_t *sucker)
{
	sucker->base_info.target_pitch 	= constrain(sucker->base_info.target_pitch,SUCKER_PITCH_MIN,SUCKER_PITCH_MAX);
	sucker->base_info.target_yaw 		= constrain(sucker->base_info.target_yaw,SUCKER_YAW_MIN,SUCKER_YAW_MAX);
	
	sucker->base_info.output_deffL 	= sucker->deffL->c_posit(sucker->deffL, -sucker->base_info.target_pitch + sucker->base_info.target_roll);
	sucker->base_info.output_yaw 		= sucker->yaw->c_posit(sucker->yaw, -sucker->base_info.target_yaw);
	sucker->base_info.output_deffR 	= sucker->deffR->c_posit(sucker->deffR,  sucker->base_info.target_pitch + sucker->base_info.target_roll);

}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void Sucker_Work_Normal(sucker_t *sucker)
{
	Sucker_Pid_Calculating(sucker);
	
	sucker->deffL->base_info.motor_out 	= sucker->base_info.output_deffL;
	sucker->yaw->base_info.motor_out 		= sucker->base_info.output_yaw;
	sucker->deffR->base_info.motor_out 	= sucker->base_info.output_deffR;
}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
float sucker_time_cnt=0;	
float sucker_time_cnt1=0;
float sucker_speed = 1500.f;
Dev_Reset_State_e Sucker_Work_Init(sucker_t *sucker)
{
	if(!sucker->reset&&!SYSTEM_RESET)
	{
		sucker->base_info.output_deffL = sucker->deffL->c_speed(sucker->deffL, sucker_speed);
		sucker->deffL->base_info.motor_out = sucker->base_info.output_deffL;
		sucker->base_info.output_deffR = sucker->deffR->c_speed(sucker->deffR, -sucker_speed);
		sucker->deffR->base_info.motor_out = sucker->base_info.output_deffR;
		sucker->base_info.output_yaw = sucker->yaw->c_speed(sucker->yaw, sucker_speed);
		sucker->yaw->base_info.motor_out = sucker->base_info.output_yaw;
		
		if((distance(sucker->deffL->rx_info.angle_prev,sucker->deffL->rx_info.angle)<50)\
				&&(m_abs(sucker->deffL->rx_info.speed)==0)\
				&&(distance(sucker->deffR->rx_info.angle_prev,sucker->deffR->rx_info.angle)<50)\
				&&(m_abs(sucker->deffR->rx_info.speed)==0)\
				&&(distance(sucker->yaw->rx_info.angle_prev,sucker->yaw->rx_info.angle)<50)\
				&&(m_abs(sucker->yaw->rx_info.speed)==0))
			sucker_time_cnt++;
		else
			sucker_time_cnt = 0;
		
		if(sucker_time_cnt>50)
		{
			sucker->deffL->rx_info.angle_prev = sucker->deffL->rx_info.angle;
			sucker->deffL->rx_info.angle_sum = 0;
			sucker->deffR->rx_info.angle_prev = sucker->deffR->rx_info.angle;
			sucker->deffR->rx_info.angle_sum = 0;
			sucker->yaw->rx_info.angle_prev = sucker->yaw->rx_info.angle;
			sucker->yaw->rx_info.angle_sum = 0;
			
			sucker_time_cnt = 0;
			return DEV_RESET_OK;
		}
		else
			return DEV_RESET_NO;
	}
	else if(sucker->reset&&!SYSTEM_RESET)
	{
		Sucker_Work_Normal(sucker);
		return DEV_RESET_OK;	
	}
	else
		return sucker->reset;	
}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void Sucker_Work(sucker_t *sucker)
{
	sucker->base_info.measure_pitch_angle = (sucker->deffR->rx_info.angle_sum - sucker->deffL->rx_info.angle_sum)/2.f;
	sucker->base_info.measure_pitch_speed = (sucker->deffR->rx_info.speed - sucker->deffL->rx_info.speed)/2.f;
	sucker->base_info.measure_roll_angle = (sucker->deffL->rx_info.angle_sum + sucker->deffR->rx_info.angle_sum)/2.f;
	sucker->base_info.measure_roll_speed = (sucker->deffL->rx_info.speed + sucker->deffR->rx_info.speed)/2.f;
	sucker->base_info.measure_yaw_angle = -sucker->yaw->rx_info.angle_sum;
	sucker->base_info.measure_yaw_speed = -sucker->yaw->rx_info.speed;
	
	sucker->base_info.pitch_A2D = (sucker->base_info.measure_pitch_angle-SUCKER_PITCH_MIN)*180.f/(SUCKER_PITCH_MAX-SUCKER_PITCH_MIN);
	sucker->base_info.yaw_A2D = (sucker->base_info.measure_yaw_angle-SUCKER_YAW_MIN)*270.f/(SUCKER_YAW_MAX-SUCKER_YAW_MIN);
	sucker->base_info.roll_A2D = sucker->base_info.measure_roll_angle*180.f/1300000.f;
	if(m_abs(sucker->base_info.roll_A2D)>180)
	{
		if(sucker->base_info.roll_A2D>0)
			sucker->base_info.roll_A2D -= 360;
		else if(sucker->base_info.roll_A2D<0)
			sucker->base_info.roll_A2D += 360;
	}

	if(SYSTEM_RESET)
		Sucker_Work_Normal(sucker);			
}











