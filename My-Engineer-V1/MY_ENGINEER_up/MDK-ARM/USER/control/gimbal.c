/* Includes ------------------------------------------------------------------*/
#include "gimbal.h"
#include "control.h"
#include "vision_protocol.h"
#include "communicate_protocol.h"
/* Exported variables --------------------------------------------------------*/

gimbal_t gimbal = 
{
	.reset = DEV_RESET_NO,
	.work = Gimbal_Work,
};


Dev_Reset_State_e Gimbal_Work_Init(gimbal_t *gimbal)
{
	return communicate_rx_info.is_gimbal_reset;
}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
float gimbal_pitch_degree;
float gimbal_yaw_degree;
void Gimbal_Work(gimbal_t *gimbal)
{
	gimbal->pitch_angle = -communicate_rx_info.gimbal_pitch_angle;
	gimbal->pitch_speed = -communicate_rx_info.gimbal_pitch_speed;
	gimbal->yaw_angle = -communicate_rx_info.gimbal_yaw_angle;
	gimbal->yaw_speed = -communicate_rx_info.gimbal_yaw_speed;
	
	
	if(B_DOWN)
	{
		gimbal->target_pitch += rc.info->mouse_y_K*0.7f;
		if(car.mode_switch!=EXCHANGE_ORE && car.mode_ctrl!=EXCHANGE_ORE)
			gimbal->target_yaw -= rc.info->mouse_x_K*0.7f;
	}
	gimbal->target_pitch = constrain(gimbal->target_pitch,GIMBAL_PITCH_MIN,GIMBAL_PITCH_MAX);
	gimbal->target_yaw = constrain(gimbal->target_yaw,GIMBAL_YAW_MIN,GIMBAL_YAW_MAX);
	communicate_tx_info.pitch_target = gimbal->target_pitch;
	communicate_tx_info.yaw_target = gimbal->target_yaw;
	
	/*ио+об-*/
	vision_tx_info.pitch = (GIMBAL_PITCH_MID-gimbal->pitch_angle)*55.f/GIMBAL_PITCH_MAX;
	/*ср+вС-*/
	vision_tx_info.yaw = (GIMBAL_YAW_MID-gimbal->yaw_angle)*180.f/GIMBAL_YAW_MAX;
}











