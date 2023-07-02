#include "my_task.h"
#include "imu.h"
#include "drv_haltick.h"

extern IWDG_HandleTypeDef hiwdg;
void StartControlTask(void const * argument)
{
  for(;;)
  {
    osDelay(1);
  }
}

void StartRealTimeTask(void const * argument)
{
	for(;;)
  {
		HAL_IWDG_Refresh(&hiwdg);
		imu.update(&imu);	
    osDelay(1);
  }
}

void StartHeartBeatTask(void const * argument)
{
  for(;;)
  {
    osDelay(1);
  }
}



