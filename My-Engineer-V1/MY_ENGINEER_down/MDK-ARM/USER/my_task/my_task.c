#include "my_task.h"
#include "remote.h"
#include "imu.h"
#include "device.h"
#include "control.h"
#include "car_state.h"
#include "can_protocol.h"
#include "communicate_protocol.h"

void StartControlTask(void const * argument)
{
	rc_init(&rc);
	car_init(&car);
	device_init();	
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

void StartRealTimeTask(void const * argument)
{
	for(;;)
  {
		imu.update(&imu);	
		communicate_data_tx();
    osDelay(1);
  }
}

void StartHeartBeatTask(void const * argument)
{
  for(;;)
  {
		device_heart_beat();
		rc_heart_beat(&rc);
    osDelay(2);
  }
}



