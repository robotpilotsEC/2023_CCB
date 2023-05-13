/* Includes ------------------------------------------------------------------*/
#include "rescue.h"
#include "control.h"
#include "communicate_protocol.h"
/* Exported variables --------------------------------------------------------*/

rescue_t rescue = 
{
	.reset = DEV_RESET_NO,
	.work = Rescue_Work,
};


Dev_Reset_State_e Rescue_Work_Init(rescue_t *rescue)
{
	return communicate_rx_info.is_recue_reset;
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
	rescue->measure_angle = -communicate_rx_info.rescue_angle;
	rescue->measure_speed = -communicate_rx_info.rescue_speed;
	
	rescue->target = constrain(rescue->target,RESCUE_MIN,RESCUE_MAX);
	communicate_tx_info.rescue_target = rescue->target;
	
}











