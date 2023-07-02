/* Includes ------------------------------------------------------------------*/
#include "uplift.h"
#include "config.h"
#include "string.h"
#include "control.h"
#include "communicate_protocol.h"
/* Exported variables --------------------------------------------------------*/

uplift_t uplift = 
{
	.front = &uplift_motor[FRONT],
	.back = &uplift_motor[BACK],
	
	.work = Uplift_Work,
	
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
float uplift_mmmax=496000.f;
void Uplift_Pid_Calculating(uplift_t *uplift)
{
	uplift->base_info.target = constrain(uplift->base_info.target,0,uplift_mmmax);
	
	uplift->base_info.output_F = uplift->front->c_posit(uplift->front,-uplift->base_info.target);
	uplift->base_info.output_B = uplift->back->c_posit(uplift->back, uplift->base_info.target);
	
}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
float	feedforward_out_F;
float	feedforward_out_B;
void Uplift_Work_Normal(uplift_t *uplift)
{
	Uplift_Pid_Calculating(uplift);
	
	feedforward_out_F = uplift->front->rx_info.angle_sum * (-0.004f) - 7425.2f;
	feedforward_out_B = uplift->back->rx_info.angle_sum * 0.0041f + 9016.9f;
	
	uplift->front->base_info.motor_out = uplift->base_info.output_F;// + feedforward_out_F
	uplift->back->base_info.motor_out = uplift->base_info.output_B;// + feedforward_out_B
}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
float Uplift_time_cnt=0;	
Dev_Reset_State_e Uplift_Work_Init(uplift_t *uplift)
{
	/*̧��δ��ʼ��������δ��ʼ��->��ʼ��̧��*/
	if(!uplift->reset&&!SYSTEM_RESET)
	{
		uplift->base_info.output_F = uplift->front->c_speed(uplift->front,-UPLIFT_SPEED);
		uplift->base_info.output_B = uplift->back->c_speed(uplift->back, UPLIFT_SPEED);

		uplift->front->base_info.motor_out = uplift->base_info.output_F;
		uplift->back->base_info.motor_out = uplift->base_info.output_B;
		
		/*��ת�ж�*/
		if(distance(uplift->front->rx_info.angle_prev,uplift->front->rx_info.angle)<20\
			 && distance(uplift->back->rx_info.angle_prev,uplift->back->rx_info.angle)<20\
		   &&	m_abs(uplift->back->rx_info.speed)<10)
			Uplift_time_cnt++;
		else
			Uplift_time_cnt = 0;
		
		/*ȷ����ת��Ŀ���ٶ�Ϊ0���ܽǶ���Ϊ0������̧����ʼ����ɣ��˺���ִ��*/
		if(Uplift_time_cnt>300)
		{
			uplift->base_info.output_F = uplift->front->c_speed(uplift->front,0);
			uplift->base_info.output_B = uplift->back->c_speed(uplift->back,0);

			uplift->front->base_info.motor_out = uplift->base_info.output_F;
			uplift->back->base_info.motor_out = uplift->base_info.output_B;
			
			
			uplift->front->rx_info.angle_prev = uplift->front->rx_info.angle;
			uplift->back->rx_info.angle_prev = uplift->back->rx_info.angle;
			uplift->front->rx_info.angle_sum = 0;
			uplift->back->rx_info.angle_sum = 0;
			
			Uplift_time_cnt = 0;
			return DEV_RESET_OK;
		}
		/*����̧����ʼ��δ��ɣ��ظ�if�ж�*/
		else
			return DEV_RESET_NO;
	}
	/*̧����ʼ����ɡ�ϵͳ��ʼ��δ��ɣ�̧���Լ��ȿ�ʼ������ά��Ŀ��Ƕ�Ϊmin*/
	else if(uplift->reset&&!SYSTEM_RESET)
	{
		uplift->base_info.target = communicate_rx_info.uplift_target;
		Uplift_Work_Normal(uplift);
		return DEV_RESET_OK;	
	}
	else
		return uplift->reset;	
}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void Uplift_Work(uplift_t *uplift)
{
	
	if(SYSTEM_RESET)
	{
		uplift->base_info.target = communicate_rx_info.uplift_target;
		Uplift_Work_Normal(uplift);
	}
	
	communicate_tx_info.uplift_angle = -uplift->front->rx_info.angle_sum;
	communicate_tx_info.uplift_speed = -uplift->front->rx_info.speed;
	communicate_tx_info.is_uplift_reset = uplift->reset;
}











