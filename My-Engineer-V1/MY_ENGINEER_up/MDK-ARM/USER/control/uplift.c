/* Includes ------------------------------------------------------------------*/
#include "uplift.h"
#include "control.h"
#include "communicate_protocol.h"
/* Exported variables --------------------------------------------------------*/

uplift_t uplift = 
{
	.reset = DEV_RESET_NO,
	.work = Uplift_Work,
};


Dev_Reset_State_e Uplift_Work_Init(uplift_t *uplift)
{
	return communicate_rx_info.is_uplift_reset;
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
	uplift->measure_angle = communicate_rx_info.uplift_angle;
	uplift->angle2mm = communicate_rx_info.uplift_angle*UPLIFT_A2MM+400.f;
	uplift->measure_speed = communicate_rx_info.uplift_speed;
	
	uplift->target = constrain(uplift->target,UPLIFT_MIN,UPLIFT_MAX);
	communicate_tx_info.uplift_target = uplift->target;
	
}











