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
		rc_ctrl(&rc);
		car_ctrl(&car);
//		Automatic_Exchange(&Auto);
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
		tick_task(1);
		vision_data_tx();
		communicate_data_tx();
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
		check_judge_offline(&judge);
		rc_heart_beat(&rc);
    osDelay(2);
  }
}



