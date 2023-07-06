/*
* protract
*	
*	2023.3.4
* Ç°Éì
*/

/* Includes ------------------------------*/
#include "protract.h"
#include "device.h"
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
	if(!protract->reset&&!SYSTEM_RESET&&protract->work_sate)
	{
		protract->base_info.output = protract->motor->c_speed(protract->motor, -pro_speed);
		protract->motor->base_info.motor_out = protract->base_info.output;
		
		
		if((distance(protract->motor->rx_info.angle_prev,protract->motor->rx_info.angle)<200)\
				&&(m_abs(protract->motor->rx_info.speed)<=50))
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
	else if(protract->reset&&!SYSTEM_RESET&&protract->work_sate)
	{
		Protract_Work_Normal(protract);
		return DEV_RESET_OK;	
	}
	else if(!protract->work_sate)
		return DEV_RESET_OK;	
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
	if(protract->motor->state.work_state)
		protract->work_sate = M_ONLINE;
	else
		protract->work_sate = M_OFFLINE;
	
	protract->base_info.measure_angle = protract->motor->rx_info.angle_sum;
	protract->base_info.angle2mm = protract->motor->rx_info.angle_sum*PROTRACT_A2MM;
	protract->base_info.measure_speed = protract->motor->rx_info.speed;
	
	if(SYSTEM_RESET&&DEVICE_ALLRIGHT_P)
		Protract_Work_Normal(protract);
}











