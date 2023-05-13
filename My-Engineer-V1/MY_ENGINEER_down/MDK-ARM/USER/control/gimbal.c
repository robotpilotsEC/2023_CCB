/*
* gimbal
*	
*	2023.3.4
* ¶Ò»»
*/

/* Includes ------------------------------*/
#include "gimbal.h"
#include "config.h"
#include "string.h"
#include "control.h"
#include "communicate_protocol.h"
/* Exported variables --------------------*/



gimbal_t gimbal = 
{
	.pitch = &gimbal_motor[PITCH],
	.yaw = &gimbal_motor[YAW],
	
	.work = Gimbal_Work,
	
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
void Gimbal_Pid_Calculating(gimbal_t *gimbal)
{
	gimbal->base_info.target_pitch 	= constrain(gimbal->base_info.target_pitch,GIMBAL_PITCH_MIN,GIMBAL_PITCH_MAX);
	gimbal->base_info.target_yaw 		= constrain(gimbal->base_info.target_yaw,GIMBAL_YAW_MIN,GIMBAL_YAW_MAX);
	
	gimbal->base_info.output_pitch 	= gimbal->pitch->c_posit(gimbal->pitch, -gimbal->base_info.target_pitch);
	gimbal->base_info.output_yaw 		= gimbal->yaw->c_posit(gimbal->yaw, -gimbal->base_info.target_yaw);

}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void Gimbal_Work_Normal(gimbal_t *gimbal)
{
	Gimbal_Pid_Calculating(gimbal);
	
	gimbal->pitch->base_info.motor_out 	= gimbal->base_info.output_pitch;
	gimbal->yaw->base_info.motor_out 		= gimbal->base_info.output_yaw;
}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
float gimbal_time_cnt=0;	
float gimbal_time_cnt1=0;
Dev_Reset_State_e Gimbal_Work_Init(gimbal_t *gimbal)
{
	if(!gimbal->reset&&!SYSTEM_RESET)
	{
		gimbal->base_info.output_pitch = gimbal->pitch->c_speed(gimbal->pitch, 1000);
		gimbal->pitch->base_info.motor_out = gimbal->base_info.output_pitch;
		gimbal->base_info.output_yaw = gimbal->yaw->c_speed(gimbal->yaw, 1000);
		gimbal->yaw->base_info.motor_out = gimbal->base_info.output_yaw;
		
		if((distance(gimbal->pitch->rx_info.angle_prev,gimbal->pitch->rx_info.angle)<50)\
				&&(m_abs(gimbal->pitch->rx_info.speed)==0)\
				&&(distance(gimbal->yaw->rx_info.angle_prev,gimbal->yaw->rx_info.angle)<50)\
				&&(m_abs(gimbal->yaw->rx_info.speed)==0))
			gimbal_time_cnt++;
		else
			gimbal_time_cnt = 0;
		
		if(gimbal_time_cnt>100)
		{
			gimbal->pitch->rx_info.angle_prev = gimbal->pitch->rx_info.angle;
			gimbal->yaw->rx_info.angle_prev = gimbal->yaw->rx_info.angle;
			gimbal->pitch->rx_info.angle_sum = 0;
			gimbal->yaw->rx_info.angle_sum = 0;
			
			gimbal_time_cnt = 0;
			return DEV_RESET_OK;
		}
		else
			return DEV_RESET_NO;
	}
	else if(gimbal->reset&&!SYSTEM_RESET)
	{
		gimbal->base_info.target_pitch = communicate_rx_info.pitch_target;
		gimbal->base_info.target_yaw = communicate_rx_info.yaw_target;
		Gimbal_Work_Normal(gimbal);
		return DEV_RESET_OK;	
	}
	else
		return gimbal->reset;	
}


/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
uint8_t aaa = 0;
void Gimbal_Work(gimbal_t *gimbal)
{
	if(SYSTEM_RESET)
	{
		gimbal->base_info.target_pitch = communicate_rx_info.pitch_target;
		gimbal->base_info.target_yaw = communicate_rx_info.yaw_target;
		Gimbal_Work_Normal(gimbal);
	}
	
	communicate_tx_info.gimbal_pitch_angle = gimbal->pitch->rx_info.angle_sum;
	communicate_tx_info.gimbal_pitch_speed = gimbal->pitch->rx_info.speed;
	communicate_tx_info.gimbal_yaw_angle = gimbal->yaw->rx_info.angle_sum;
	communicate_tx_info.gimbal_yaw_speed = gimbal->yaw->rx_info.speed;
	communicate_tx_info.is_gimbal_reset = gimbal->reset;
	
}











