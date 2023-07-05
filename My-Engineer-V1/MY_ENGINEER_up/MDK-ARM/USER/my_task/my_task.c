#include "my_task.h"
#include "device.h"
#include "car_state.h"
#include "control.h"
#include "can_protocol.h"
#include "vision_protocol.h"
#include "communicate_protocol.h"
#include "exchanges_control.h"
#include "my_judge.h"
#include "judge_protocol.h"

extern IWDG_HandleTypeDef hiwdg;
/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void StartControlTask(void const * argument)
{
	rc_init(&rc);
	car_init(&car);
	device_init();
  for(;;)
  {
		car_ctrl(&car);
		Automatic_Exchange(&Auto);
		system_reset();
		device_work();
		can_send();
    osDelay(1);
  }
}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void StartRealTimeTask(void const * argument)
{
	for(;;)
  {
		rc_ctrl(&rc);
		communicate_data_tx();
//		HAL_IWDG_Refresh(&hiwdg);
		check_judge_offline(&judge);
    osDelay(1);
  }
}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void StartHeartBeatTask(void const * argument)
{
  for(;;)
  {
		device_heart_beat();
		rc_heart_beat(&rc);
		vision_data_tx();
		tick_task(1);
    osDelay(1);
  }
}



