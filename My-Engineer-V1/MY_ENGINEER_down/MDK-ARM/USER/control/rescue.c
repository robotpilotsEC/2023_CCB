/*
* rescue
*	
*	2023.3.4
* Ç°Éì
*/

/* Includes ------------------------------*/
#include "rescue.h"
#include "config.h"
#include "string.h"
#include "control.h"
#include "communicate_protocol.h"
/* Exported variables ---------------------*/



rescue_t rescue = 
{
	.left = &rescue_motor[LEFT],
	.right = &rescue_motor[RIGHT],
	
	.work = Rescue_Work,
	
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
void Rescue_Pid_Calculating(rescue_t *rescue)
{
	rescue->base_info.target = constrain(rescue->base_info.target,RESCUE_MIN,RESCUE_MAX);
	
	rescue->base_info.output_L = rescue->left->c_posit(rescue->left,    rescue->base_info.target);
	rescue->base_info.output_R = rescue->right->c_posit(rescue->right, -rescue->base_info.target);

}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void Rescue_Work_Normal(rescue_t *rescue)
{
	Rescue_Pid_Calculating(rescue);
	
	rescue->left->base_info.motor_out = rescue->base_info.output_L;
	rescue->right->base_info.motor_out = rescue->base_info.output_R;
}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
float rescue_time_cnt=0;	
float rescue_speed = 500.f;
Dev_Reset_State_e Rescue_Work_Init(rescue_t *rescue)
{
	if(!rescue->reset&&!SYSTEM_RESET)
	{
		rescue->base_info.output_L = rescue->left->c_speed(rescue->left,  -rescue_speed);
		rescue->base_info.output_R = rescue->right->c_speed(rescue->right, rescue_speed);
		rescue->left->base_info.motor_out = rescue->base_info.output_L;
		rescue->right->base_info.motor_out = rescue->base_info.output_R;
		
		
		if((distance(rescue->left->rx_info.angle_prev,rescue->left->rx_info.angle)<20)&&(m_abs(rescue->left->rx_info.speed)==0)\
			 &&(distance(rescue->right->rx_info.angle_prev,rescue->right->rx_info.angle)<20)&&(m_abs(rescue->right->rx_info.speed)==0))
			rescue_time_cnt++;
		else
			rescue_time_cnt = 0;
		
		if(rescue_time_cnt>500)
		{
			rescue->left->rx_info.angle_sum = 0;
			rescue->right->rx_info.angle_sum = 0;
			
			rescue_time_cnt = 0;
			return DEV_RESET_OK;
		}
		else
			return DEV_RESET_NO;
	}
	else if(rescue->reset&&!SYSTEM_RESET)
	{
		rescue->base_info.target = 0;
		
		Rescue_Work_Normal(rescue);
		return DEV_RESET_OK;	
	}
	else
		return rescue->reset;	
		
}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void Rescue_Work(rescue_t *rescue)
{
	
	if(SYSTEM_RESET)
	{
		rescue->base_info.target = communicate_rx_info.rescue_target;
		Rescue_Work_Normal(rescue);
	}
	
	communicate_tx_info.rescue_angle = rescue->right->rx_info.angle_sum;
	communicate_tx_info.rescue_speed = rescue->right->rx_info.speed;
	communicate_tx_info.is_recue_reset = rescue->reset;
	
}











