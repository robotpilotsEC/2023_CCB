#include "control.h"
#include "car_state.h"
#include "imu.h"
#include "communicate_protocol.h"

/*系统结构体实例*/
control_t control = {
	.master_reset = DEV_RESET_NO,
	.slaver_reset = DEV_RESET_NO,
};

/**
 * @date        
 * @brief       系统复位
 */
uint8_t aaaaaaaaaa=0;
void system_reset(void)
{
	if(!uplift.work_sate||!ALL_DEVICE_OK)
		control.slaver_reset = DEV_RESET_OK;
	
	if(communicate_rx_info.is_master_reset == 1)
		aaaaaaaaaa = 1;
	
	if(!SYSTEM_RESET&&RC_ONLINE&&ALL_DEVICE_OK)
	{
		rescue.reset = Rescue_Work_Init(&rescue);
		gimbal.reset = Gimbal_Work_Init(&gimbal);
		if(communicate_rx_info.is_uplift_start_reset)
			uplift.reset = Uplift_Work_Init(&uplift);
				
		if(uplift.reset&&gimbal.reset&&rescue.reset)
		{
			control.slaver_reset = DEV_RESET_OK;
			car.ctrl_mode = KEY_CAR;
		}
	
	}
	else if(SYSTEM_RESET&&RC_ONLINE&&!ALL_DEVICE_OK)
		gimbal.reset = Gimbal_Work_Init(&gimbal);
	else if(!RC_ONLINE)
	{	/*遥控器离线重新复位*/
		gimbal.base_info.target_pitch = 0;
		gimbal.base_info.target_yaw = 0;
		rescue.base_info.target = 0;
		uplift.base_info.target = 0;

		chassis.work_info.config.chassis_imu_angle = imu.info->yaw;
		chassis.base_info.target.front_speed  = 0;
		chassis.base_info.target.right_speed  = 0;
		chassis.base_info.output.motor_LF_current = 0;
		chassis.base_info.output.motor_RF_current = 0;
		chassis.base_info.output.motor_LB_current = 0;
		chassis.base_info.output.motor_RB_current = 0;
		
		car.mode_switch = NORMAL;
		car.mode_ctrl = NORMAL;
		car.ctrl_mode = RC_CAR;
		car.step = 1;
				
		uplift.reset = DEV_RESET_NO;
		gimbal.reset = DEV_RESET_NO;
		rescue.reset = DEV_RESET_NO;
		control.slaver_reset = DEV_RESET_NO;
		control.master_reset = DEV_RESET_NO;
	}
	
	communicate_tx_info.is_slave_reset = control.slaver_reset;
	control.master_reset = communicate_rx_info.is_master_reset;
}



