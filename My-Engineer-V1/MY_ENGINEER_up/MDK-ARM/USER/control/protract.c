/*
* protract
*	
*	2023.3.4
* ǰ��
*/

/* Includes ------------------------------*/
#include "protract.h"
#include "control.h"
/* Exported variables ---------------------*/



protract_t protract = 
{
	.motor = &protract_motor,
	
	.work = Protract_Work,
	
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
void Protract_Pid_Calculating(protract_t *protract)
{
	protract->base_info.target = constrain(protract->base_info.target,PROTRACT_MIN,PROTRACT_MAX);
	
	protract->base_info.output = protract->motor->c_posit(protract->motor, protract->base_info.target);

}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void Protract_Work_Normal(protract_t *protract)
{
	Protract_Pid_Calculating(protract);
	
	protract->motor->base_info.motor_out = protract->base_info.output;
}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
float protract_time_cnt=0;	
float pro_speed = 2000.f;
Dev_Reset_State_e Protract_Work_Init(protract_t *protract)
{
	if(!protract->reset&&!SYSTEM_RESET)
	{
		protract->base_info.output = protract->motor->c_speed(protract->motor, -pro_speed);
		protract->motor->base_info.motor_out = protract->base_info.output;
		
		
		if((distance(protract->motor->rx_info.angle_prev,protract->motor->rx_info.angle)<20)\
				&&(m_abs(protract->motor->rx_info.speed)<=20))
			protract_time_cnt++;
		else
			protract_time_cnt = 0;
		
		if(protract_time_cnt>50)
		{
			protract->motor->rx_info.angle_sum = 0;
			
			protract_time_cnt = 0;
			return DEV_RESET_OK;
		}
		else
			return DEV_RESET_NO;
	}
	else if(protract->reset&&!SYSTEM_RESET)
	{
		protract->base_info.target = PROTRACT_MID;
		Protract_Work_Normal(protract);
		return DEV_RESET_OK;	
	}
	else
		return protract->reset;	
		
}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void Protract_Work(protract_t *protract)
{
	protract->base_info.measure_angle = protract->motor->rx_info.angle_sum;
	protract->base_info.angle2mm = protract->motor->rx_info.angle_sum*PROTRACT_A2MM;
	protract->base_info.measure_speed = protract->motor->rx_info.speed;
	
	if (SYSTEM_RESET)
			Protract_Work_Normal(protract);
}










