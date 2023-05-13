/*
* claw
*	
*	2023.3.4
* Ç°Éì
*/

/* Includes ------------------------------*/
#include "claw.h"
#include "control.h"
/* Exported variables ---------------------*/



claw_t claw = 
{
	.motor_L = &claw_motor[CLAW_L],
	.motor_R = &claw_motor[CLAW_R],
	
	.work = Claw_Work,
	
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
void Claw_Pid_Calculating(claw_t *claw)
{
	claw->base_info.target = constrain(claw->base_info.target,CLAW_MIN,CLAW_MAX);
	
	claw->base_info.output_L = claw->motor_L->c_posit(claw->motor_L,-claw->base_info.target);
	claw->base_info.output_R = claw->motor_R->c_posit(claw->motor_R, claw->base_info.target);

}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void Claw_Work_Normal(claw_t *claw)
{
	Claw_Pid_Calculating(claw);
	
	claw->motor_L->base_info.motor_out = claw->base_info.output_L;
	claw->motor_R->base_info.motor_out = claw->base_info.output_R;
}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
float claw_time_cnt=0;	
float claw_speed = 500.f;
Dev_Reset_State_e Claw_Work_Init(claw_t *claw)
{
	if(!claw->reset&&!SYSTEM_RESET)
	{
		claw->base_info.output_L = claw->motor_L->c_speed(claw->motor_L,  claw_speed);
		claw->base_info.output_R = claw->motor_R->c_speed(claw->motor_R, -claw_speed);
		claw->motor_L->base_info.motor_out = claw->base_info.output_L;
		claw->motor_R->base_info.motor_out = claw->base_info.output_R;
		
		
		if((distance(claw->motor_L->rx_info.angle_prev,claw->motor_L->rx_info.angle)<20)&&(m_abs(claw->motor_L->rx_info.speed)==0)\
			 &&(distance(claw->motor_R->rx_info.angle_prev,claw->motor_R->rx_info.angle)<20)&&(m_abs(claw->motor_R->rx_info.speed)==0))
			claw_time_cnt++;
		else
			claw_time_cnt = 0;
		
		if(claw_time_cnt>50)
		{
			claw->motor_L->rx_info.angle_sum = 0;
			claw->motor_R->rx_info.angle_sum = 0;
			
			claw_time_cnt = 0;
			return DEV_RESET_OK;
		}
		else
			return DEV_RESET_NO;
	}
	else if(claw->reset&&!SYSTEM_RESET)
	{
		claw->base_info.target = 0;
		
		Claw_Work_Normal(claw);
		return DEV_RESET_OK;	
	}
	else
		return claw->reset;	
		
}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void Claw_Work(claw_t *claw)
{
	claw->base_info.measure_angle = claw->motor_R->rx_info.angle_sum;
	claw->base_info.measure_speed = claw->motor_R->rx_info.speed;
	
	if (SYSTEM_RESET)
			Claw_Work_Normal(claw);
}











