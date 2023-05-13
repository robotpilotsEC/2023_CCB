/**
  ******************************************************************************
  * @file           : control.c\h
  * @brief          : 
  * @update         : 
  ******************************************************************************
  */
	
#include "control.h"
#include "car_state.h"
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
float reset_time_cnt;
uint8_t reset_step = 0;
void system_reset(void)
{
	if(!SYSTEM_RESET&&RC_ONLINE)
	{
		flip.mode = FLIP_UP;
		if(flip.mode == FLIP_UP)
			reset_time_cnt ++;
		else
			reset_time_cnt = 0;
		
		if(reset_time_cnt > 2000)
		{
			flip.mode = FLIP_OFF;
			communicate_tx_info.is_uplift_start_reset = 1;
			/*1抬升复位*/
			uplift.reset = Uplift_Work_Init(&uplift);
			rescue.reset = Rescue_Work_Init(&rescue);
			gimbal.reset = Gimbal_Work_Init(&gimbal);
			protract.reset = Protract_Work_Init(&protract);
			if(uplift.reset&&rescue.reset&&protract.reset)
			{
				if(!reset_step)
					uplift.target = UPLIFT_INTERFERE;
				if(UPLIFT_INTERFERE_OK)
				{
					reset_step = 1;
					/*4兑换复位*/
					transverse.reset = Transverse_Work_Init(&transverse);
					sucker.reset = Sucker_Work_Init(&sucker);
					if(sucker.reset&&transverse.reset)//
					{
						uplift.target = UPLIFT_MIN;
						gimbal.target_pitch = GIMBAL_PITCH_MAX;
						gimbal.target_yaw = GIMBAL_YAW_MIN;
						/*5系统复位*/
						if(control.slaver_reset)
							control.master_reset = DEV_RESET_OK;
					}
				}
			}
		}
	}
	else if(!RC_ONLINE)
	{	/*遥控器离线重新复位*/
		reset_time_cnt = 0;
		transverse.base_info.target = TRANSVERSE_MIN;
		uplift.target = 0;
		sucker.base_info.target_pitch = 0;
		sucker.base_info.target_yaw = 0;
		sucker.base_info.target_roll = 0;
		protract.base_info.target = 0;
		gimbal.target_pitch = 0;
		gimbal.target_yaw = 0;
		rescue.target = 0;
		
		flip.mode = FLIP_OFF;
		pneumatic.pneu_state = OFF;
		car.mode_switch = NORMAL;
		car.step = 1;
		car.ore_num = 0;
		reset_step = 0;
				
		communicate_tx_info.is_uplift_start_reset = 0;
		rescue.reset = DEV_RESET_NO;
		uplift.reset = DEV_RESET_NO;
		sucker.reset = DEV_RESET_NO;
		protract.reset = DEV_RESET_NO;
		transverse.reset = DEV_RESET_NO;
		control.slaver_reset = DEV_RESET_NO;
		control.master_reset = DEV_RESET_NO;
	}
	
	communicate_tx_info.is_master_reset = control.master_reset;
	control.slaver_reset = communicate_rx_info.is_slave_reset;
}



