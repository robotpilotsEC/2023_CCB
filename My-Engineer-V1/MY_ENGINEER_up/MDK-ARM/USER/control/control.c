/**
  ******************************************************************************
  * @file           : control.c\h
  * @brief          : 
  * @update         : 
  ******************************************************************************
  */
	
#include "device.h"
#include "control.h"
#include "car_state.h"
#include "exchanges_control.h"
#include "communicate_protocol.h"

/*系统结构体实例*/
control_t control = {
	.master_reset = DEV_RESET_NO,
	.slaver_reset = DEV_RESET_NO,
	.reset_step = 1,
};

/**
 * @date        
 * @brief       系统复位
 */
float reset_time_cnt;
uint8_t reset_step = 0;
uint8_t reset_step1 = 0;
void system_reset(void)
{
	if(!DEVICE_ALLRIGHT)
	{
		control.master_reset = DEV_RESET_OK;
		communicate_tx_info.is_all_device_ok = 0;
	}
	else
		communicate_tx_info.is_all_device_ok = 1;
	
	if(!SYSTEM_RESET&&RC_ONLINE&&DEVICE_ALLRIGHT)
	{
		switch (control.reset_step)
		{
			case 1:
				flip.mode = FLIP_UP;
				if(flip.mode == FLIP_UP)
					reset_time_cnt ++;
				else
					reset_time_cnt = 0;
				if(reset_time_cnt>2000)
					control.reset_step ++;
				break;
			case 2:
				flip.mode = FLIP_OFF;
				communicate_tx_info.is_uplift_start_reset = 1;
				/*1抬升复位*/
				uplift.reset = Uplift_Work_Init(&uplift);
				rescue.reset = Rescue_Work_Init(&rescue);
				gimbal.reset = Gimbal_Work_Init(&gimbal);
				protract.reset = Protract_Work_Init(&protract);
				if(uplift.reset&&rescue.reset&&protract.reset&&control.slaver_reset)//
					control.reset_step ++;
				break;
			case 3:
				Protract_Work_Init(&protract);
				gimbal.target_pitch = GIMBAL_PITCH_MAX;
				gimbal.target_yaw = GIMBAL_YAW_MIN;
				uplift.target = UPLIFT_INTERFERE;
				if(UPLIFT_INTERFERE_OK)
					control.reset_step ++;
				break;
			case 4:
				transverse.reset = Transverse_Work_Init(&transverse);
				Protract_Work_Init(&protract);
				if(transverse.reset)
				{
					protract.base_info.target = PROTRACT_MID;
					transverse.base_info.target = TRANSVERSE_NORMAL;
					if(NORMAL_TRANSVERSE_IS_OK&&PROTRACT_MID_OK)
						control.reset_step ++;
				}
				break;
			case 5:
				Protract_Work_Init(&protract);
				Transverse_Work_Init(&transverse);
				sucker.reset = Sucker_Work_Init(&sucker);
				if(sucker.reset&&SUCKER_PITCH_MID_OK)//
						control.reset_step ++;
				break;
			case 6:
				/*5系统复位*/
				Protract_Work_Init(&protract);
				Transverse_Work_Init(&transverse);
				Sucker_Work_Init(&sucker);
				control.master_reset = DEV_RESET_OK;
				car.ctrl_mode = KEY_CAR;
				break;
			case 7:
				break;
			default:
				break;
		}
	}
	else if(SYSTEM_RESET&&RC_ONLINE&&!DEVICE_ALLRIGHT)
	{
		gimbal.target_pitch = GIMBAL_PITCH_MAX;
		gimbal.target_yaw = GIMBAL_YAW_MIN;
	}
	else if((!RC_ONLINE&&DEVICE_ALLRIGHT))// || (transverse.work_sate == M_OFFLINE)
	{	/*遥控器离线重新复位*/
		control.reset_step = 1;
		
		reset_time_cnt = 0;
		transverse.base_info.target = 0;
		uplift.target = 0;
		sucker.base_info.target_pitch = SUCKER_PITCH_MID;
		sucker.base_info.target_yaw = 0;
		sucker.base_info.target_roll = 0;
		protract.base_info.target = 0;
		gimbal.target_pitch = 0;
		gimbal.target_yaw = 0;
		rescue.target = 0;
		
		flip.mode = FLIP_OFF;
		pneumatic.pneu_state = OFF;
		car.mode_switch = NORMAL;
		car.mode_ctrl = CCB_MODE;
		car.ctrl_mode = RC_CAR;
		car.step = 1;
		car.ore_num = 0;
		reset_step = 0;
		reset_step1 = 0;
		
		Auto.config->start_exchange_flag = AUTO_NO;
		Auto.config->via_process_done = AUTO_NO;
		Auto.config->all_process_done = AUTO_NO;
		Auto.step = 1;
				
		communicate_tx_info.is_uplift_start_reset = 0;
		rescue.reset = DEV_RESET_NO;
		uplift.reset = DEV_RESET_NO;
		sucker.reset = DEV_RESET_NO;
		protract.reset = DEV_RESET_NO;
		transverse.reset = DEV_RESET_NO;
		control.slaver_reset = DEV_RESET_NO;
		control.master_reset = DEV_RESET_NO;
	}
	else if(!RC_ONLINE&&!DEVICE_ALLRIGHT)
	{
		control.reset_step = 1;
		reset_time_cnt = 0;
		transverse.base_info.target = TRANSVERSE_MIN;
		uplift.target = 0;
		sucker.base_info.target_pitch = SUCKER_PITCH_MID;
		sucker.base_info.target_yaw = 0;
		sucker.base_info.target_roll = 0;
		protract.base_info.target = 0;
		gimbal.target_pitch = 0;
		gimbal.target_yaw = 0;
		rescue.target = 0;
		
		flip.mode = FLIP_OFF;
		pneumatic.pneu_state = OFF;
		car.mode_switch = NORMAL;
		car.mode_ctrl = CCB_MODE;
		car.ctrl_mode = RC_CAR;
		car.step = 1;
		car.ore_num = 0;
		reset_step = 0;
		reset_step1 = 0;
		
		Auto.config->start_exchange_flag = AUTO_NO;
		Auto.config->via_process_done = AUTO_NO;
		Auto.config->all_process_done = AUTO_NO;
		Auto.step = 1;
				
		communicate_tx_info.is_uplift_start_reset = 0;
		rescue.reset = DEV_RESET_NO;
		uplift.reset = DEV_RESET_NO;
		sucker.reset = DEV_RESET_NO;
		protract.reset = DEV_RESET_NO;
		transverse.reset = DEV_RESET_NO;
	}
	
	communicate_tx_info.is_master_reset = control.master_reset;
	control.slaver_reset = communicate_rx_info.is_slave_reset;
}



