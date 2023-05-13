#include "control.h"
#include "car_state.h"
#include "imu.h"
#include "communicate_protocol.h"

/*ϵͳ�ṹ��ʵ��*/
control_t control = {
	.master_reset = DEV_RESET_NO,
	.slaver_reset = DEV_RESET_NO,
};

/**
 * @date        
 * @brief       ϵͳ��λ
 */
void system_reset(void)
{
	if(!SYSTEM_RESET&&RC_ONLINE)
	{
		rescue.reset = Rescue_Work_Init(&rescue);
		gimbal.reset = Gimbal_Work_Init(&gimbal);
		if(communicate_rx_info.is_uplift_start_reset)
			uplift.reset = Uplift_Work_Init(&uplift);
				
		if(uplift.reset&&gimbal.reset&&rescue.reset)
			control.slaver_reset = DEV_RESET_OK;
	
	}
	else if(!RC_ONLINE)
	{	/*ң�����������¸�λ*/
		gimbal.base_info.target_pitch = 0;
		gimbal.base_info.target_yaw = 0;
		rescue.base_info.target = 0;
		uplift.base_info.target = 0;

		chassis.work_info.config.chassis_imu_angle = imu.info->yaw;
		chassis.base_info.target.front_speed  = 0;
		chassis.base_info.target.right_speed  = 0;
		
		car.mode_switch = NORMAL;
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


