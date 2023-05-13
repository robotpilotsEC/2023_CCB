/* Includes ------------------------------------------------------------------*/
#include "transverse.h"
#include "control.h"
/* Exported variables --------------------------------------------------------*/



transverse_t transverse = 
{
	.front = &transverse_motor[FRONT],
	.back = &transverse_motor[BACK],
	
	.work = Transverse_Work,
	
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
void Transverse_Pid_Calculating(transverse_t *transverse)
{
	transverse->base_info.target = constrain(transverse->base_info.target,TRANSVERSE_MIN,TRANSVERSE_MAX);
	
	transverse->base_info.output_F = transverse->front->c_posit(transverse->front, transverse->base_info.target);
	transverse->base_info.output_B = transverse->back->c_posit(transverse->back,  -transverse->base_info.target);

}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void Transverse_Work_Normal(transverse_t *transverse)
{
	Transverse_Pid_Calculating(transverse);
	
	transverse->front->base_info.motor_out = transverse->base_info.output_F;
	transverse->back->base_info.motor_out = transverse->base_info.output_B;
}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
float Transverse_time_cnt=0;	
float	tra_speed = 2000.f;
Dev_Reset_State_e Transverse_Work_Init(transverse_t *transverse)
{
	if(!transverse->reset&&!SYSTEM_RESET)
	{
		transverse->base_info.output_F = transverse->front->c_speed(transverse->front, -tra_speed);
		transverse->base_info.output_B = transverse->back->c_speed(transverse->back, tra_speed);

		transverse->front->base_info.motor_out = transverse->base_info.output_F;
		transverse->back->base_info.motor_out = transverse->base_info.output_B;
		
		
		if(distance(transverse->front->rx_info.angle_prev,transverse->front->rx_info.angle)<20\
			 && distance(transverse->back->rx_info.angle_prev,transverse->back->rx_info.angle)<20\
			 && m_abs(transverse->back->rx_info.speed == 0))
			Transverse_time_cnt++;
		else
			Transverse_time_cnt = 0;
		
		if(Transverse_time_cnt>50)
		{
			transverse->front->rx_info.angle_prev = transverse->front->rx_info.angle;
			transverse->back->rx_info.angle_prev = transverse->front->rx_info.angle;
			transverse->front->rx_info.angle_sum = 0;
			transverse->back->rx_info.angle_sum = 0;
			
			Transverse_time_cnt = 0;
			return DEV_RESET_OK;
		}
		else
			return DEV_RESET_NO;
	}
	else if(transverse->reset&&!SYSTEM_RESET)
	{
		transverse->base_info.target = TRANSVERSE_MIN;
		Transverse_Work_Normal(transverse);
		return DEV_RESET_OK;	
	}
	else
		return transverse->reset;	
		
}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void Transverse_Work(transverse_t *transverse)
{
	transverse->base_info.measure_angle = transverse->front->rx_info.angle_sum;
	transverse->base_info.angle2mm = transverse->front->rx_info.angle_sum*TRANSVERSE_A2MM;
	transverse->base_info.measure_speed = transverse->front->rx_info.speed;
	
	if(SYSTEM_RESET)
		Transverse_Work_Normal(transverse);
}











