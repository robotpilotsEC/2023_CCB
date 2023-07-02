#include "my_task.h"
#include "remote.h"
#include "imu.h"
#include "device.h"
#include "control.h"
#include "car_state.h"
#include "drv_haltick.h"
#include "can_protocol.h"
#include "communicate_protocol.h"

extern IWDG_HandleTypeDef hiwdg;
void StartControlTask(void const * argument)
{
	rc_init(&rc);
	car_init(&car);
  for(;;)
  {
		rc_ctrl(&rc);
		car_ctrl(&car);
		device_work();	
		system_reset();
		can_send();
    osDelay(1);
  }
}

uint32_t time1=0;
uint32_t time2=0;
uint32_t time3=0;
void StartRealTimeTask(void const * argument)
{
	for(;;)
  {
//		time1 = micros();
		HAL_IWDG_Refresh(&hiwdg);
		imu.update(&imu);	
		communicate_data_tx();
//		time2 = micros();
//		time3 = time2-time1;
    osDelay(1);
  }
}

void StartHeartBeatTask(void const * argument)
{
  for(;;)
  {
		device_heart_beat();
		rc_heart_beat(&rc);
    osDelay(1);
  }
}



