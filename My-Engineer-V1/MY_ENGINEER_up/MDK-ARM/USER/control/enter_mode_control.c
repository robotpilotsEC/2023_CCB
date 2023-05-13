 /**
  ******************************************************************************
  * @file           : enter_control.c/h
  * @brief          : 
  * @note           : 
  ******************************************************************************
  */
 
 
#include "enter_mode_control.h"
#include "car_state.h"
#include "control.h"

 /**
 * @date        
 * @brief       常规模式
 */
void enter_normal_mode(void)
{
	switch(car.mode_ctrl)
	{
		case NORMAL:
			car.step = 1;
			car.step_lock = 0;
		
		break;
		default:
			switch(car.step)
			{
				case 1:
					pneumatic.pneu_state = OFF;
					gimbal.target_pitch = GIMBAL_PITCH_MAX;
					gimbal.target_yaw = GIMBAL_YAW_MIN;
					protract.base_info.target = PROTRACT_MID;
					rescue.target = RESCUE_MIN;
					if(PROTRACT_MID_OK)
						car.step ++;
				break;
				case 2:
					sucker.base_info.target_pitch = SUCKER_PITCH_MID;
					sucker.base_info.target_yaw = SUCKER_YAW_MIN;
					protract.base_info.target = PROTRACT_MID;
					if(SUCKER_YAW_MINI_OK&&SUCKER_PITCH_MID_OK&&PROTRACT_MID_OK)
						car.step ++;
				break;
				case 3:
					if(uplift.measure_angle<UPLIFT_INTERFERE)
					{
						uplift.target = UPLIFT_INTERFERE;
						if(UPLIFT_INTERFERE_OK)
							transverse.base_info.target = TRANSVERSE_MIN;
					}
					else
						transverse.base_info.target = TRANSVERSE_MIN;
						
					if(TRANSVERSE_MINI_OK)
						car.step ++;
				break;
				case 4:
					if(car.ore_num == 0)
						uplift.target = UPLIFT_ONE_ORE;
					else if(car.ore_num == 1)
						uplift.target = UPLIFT_THREE_ORE;
					else if(car.ore_num == 2)
						uplift.target = UPLIFT_THREE_ORE;
					if(OTT_UPLIFT_IS_OK)
						car.step ++;
						
				break;
				case 5:
					if(GB_PITCH_MAX_OK&&GB_YAW_MINI_OK)
						car.step ++;
				break;
				case 6:
					if(RESCUE_MINI_OK)
						car.step ++;
				break;
				case 7:
						car.mode_ctrl = NORMAL;
				break;
			}
		}
}


 /**
 * @date        
 * @brief       空接模式
 */
void enter_lob_mode(void)
{
	switch(car.mode_ctrl)
	{
		case LOB:
			car.step = 1;
			car.step_lock = 0;
			
		break;
		default:
			switch(car.step)
			{
				case 1:
					gimbal.target_pitch = GIMBAL_PITCH_MIN;
					gimbal.target_yaw = GIMBAL_YAW_MID;
					protract.base_info.target = PROTRACT_MID;
					transverse.base_info.target = TRANSVERSE_MIN;
					if(GB_YAW_MID_OK&&GB_PITCH_MIN_OK&&TRANSVERSE_MINI_OK)
						car.step ++;
				break;
				case 2:
					uplift.target = UPLIFT_LOB;
					if(PROTRACT_MID_OK&&(uplift.measure_angle>UPLIFT_LOB/3.5f))
						car.step ++;
					break;
				case 3:
					sucker.base_info.target_pitch = SUCKER_PITCH_MIN;
					sucker.base_info.target_yaw = SUCKER_YAW_MID;
					transverse.base_info.target = TRANSVERSE_LOB;
					if(SUCKER_YAW_MID_OK&&SUCKER_PITCH_MINI_OK)
						car.step ++;
					break;
				case 4:
					car.step_lock = 0;
					pneumatic.pneu_state = ON;
					if(LOB_TRANSVERSE_IS_OK&&LOB_UPLIFT_IS_OK)
						car.step_lock = 1;
				break;
				case 5:
					car.step_lock = 0;
					sucker.base_info.target_yaw = SUCKER_YAW_MIN;
					if(SUCKER_YAW_MINI_OK)
					{
						transverse.base_info.target = TRANSVERSE_MIN;
						if(TRANSVERSE_MINI_OK)
							car.step ++;
					}
				break;
				case 6:
					sucker.base_info.target_pitch = SUCKER_PITCH_MID;
					if(car.ore_num == 0)
						uplift.target = UPLIFT_ONE_ORE;
					else if(car.ore_num == 1)
						uplift.target = UPLIFT_THREE_ORE;
					else if(car.ore_num == 2)
						uplift.target = UPLIFT_THREE_ORE;
					if(SUCKER_PITCH_MID_OK&&OTT_UPLIFT_IS_OK)
						car.step ++;
					break;
				case 7:
					car.time_cnt ++;
					if(car.time_cnt>4000)
					{
						pneumatic.pneu_state = OFF;
						car.time_cnt = 0;
						car.step ++;
					}
					
					break;
				case 8:
					flip.mode = FLIP_DOWM;
					car.time_cnt ++;
					
					if(car.time_cnt>2000)
					{
						car.time_cnt = 0;
						flip.mode = FLIP_OFF;
						car.mode_ctrl = LOB;
						car.ore_num ++;
					}
				break;
			}
		break;
	}
}

 /**
 * @date        
 * @brief       金矿槽模式
 */
void enter_goldenore_mode(void)
{
	switch(car.mode_ctrl)
	{
		case GOLDEN_ORE:
			car.step = 1;
			car.step_lock = 0;
			
		break;
		default:
			switch(car.step)
			{
				case 1:
					gimbal.target_pitch = GIMBAL_PITCH_MIN;
					gimbal.target_yaw = GIMBAL_YAW_MID;
					protract.base_info.target = PROTRACT_MID;
					if(GB_YAW_MID_OK&&GB_PITCH_MIN_OK)
						car.step ++;
				break;
				case 2:
					uplift.target = UPLIFT_GOLDEN;
					if(GOLDEN_PROTRACT_IS_OK&&GOLDEN_UPLIFT_IS_OK)
						car.step ++;
					break;
				case 3:
					sucker.base_info.target_pitch = SUCKER_PITCH_GOLDEN;
					sucker.base_info.target_yaw = SUCKER_YAW_GOLDEN;
					transverse.base_info.target = TRANSVERSE_GOLDEN;
					if(GOLDEN_SUCKER_YAW_IS_OK&&GOLDEN_SUCKER_PITCH_IS_OK)
						car.step ++;
					break;
				case 4:
					pneumatic.pneu_state = ON;
					if(GOLDEN_TRANSVERSE_IS_OK)
						car.step_lock = 1;
				break;
				case 5:
//					car.step_lock = 0;
//					uplift.target = UPLIFT_PUTDOWN;
//					if(PUTDOWN_UPLIFT_IS_OK)
						car.step_lock = 1;
						
				break;
				case 6:
					car.step_lock = 0;
					uplift.target = UPLIFT_PUTUP;
					if(PUTUP_UPLIFT_IS_OK)
					{
						sucker.base_info.target_pitch = SUCKER_PITCH_MIN;
						if(SUCKER_PITCH_MINI_OK)
						{
							sucker.base_info.target_yaw = SUCKER_YAW_MIN;
							if(SUCKER_YAW_MINI_OK)
							{
								transverse.base_info.target = TRANSVERSE_MIN;
								if(TRANSVERSE_MINI_OK)
									car.step ++;
							}
						}
					}
				break;
				case 7:
					sucker.base_info.target_pitch = SUCKER_PITCH_MID;
					if(car.ore_num == 0)
						uplift.target = UPLIFT_ONE_ORE;
					else if(car.ore_num == 1)
						uplift.target = UPLIFT_THREE_ORE;
					else if(car.ore_num == 2)
						uplift.target = UPLIFT_THREE_ORE;
					if(SUCKER_PITCH_MID_OK&&OTT_UPLIFT_IS_OK)
						car.step ++;
					break;
				case 8:
					car.time_cnt ++;
					if(car.time_cnt>4000)
					{
						pneumatic.pneu_state = OFF;
						car.time_cnt = 0;
						car.step ++;
					}
					break;
				case 9:
					flip.mode = FLIP_DOWM;
					car.time_cnt ++;
					
					if(car.time_cnt>2000)
					{
						car.time_cnt = 0;
						flip.mode = FLIP_OFF;
						car.mode_ctrl = GOLDEN_ORE;
						car.ore_num ++;
					}
					
					break;
				case 10:
				break;
			}
		break;
	}
}

 /**
 * @date        
 * @brief       银矿模式
 */
void enter_silverore_mode(void)
{
	switch(car.mode_ctrl)
	{
		case SILVER_ORE:
			car.step = 1;
			car.step_lock = 0;
			
		break;
		default:
			switch(car.step)
			{
				case 1:
					gimbal.target_pitch = GIMBAL_PITCH_MIN;
					gimbal.target_yaw = GIMBAL_YAW_MID;
					protract.base_info.target = PROTRACT_SILVER;
					if(GB_YAW_MID_OK&&GB_PITCH_MIN_OK)
						car.step ++;
				break;
				case 2:
					uplift.target = UPLIFT_SILVER;
					if(SILVER_PROTRACT_IS_OK&&SILVER_UPLIFT_IS_OK)
						car.step ++;
					break;
				case 3:
					sucker.base_info.target_pitch = SUCKER_PITCH_SILVER;
					sucker.base_info.target_yaw = SUCKER_YAW_SILVER;
					transverse.base_info.target = TRANSVERSE_SILVER;
					if(SILVER_SUCKER_YAW_IS_OK&&SILVER_SUCKER_PITCH_IS_OK)
						car.step ++;
					break;
				case 4:
					pneumatic.pneu_state = ON;
					if(SILVER_TRANSVERSE_IS_OK)
						car.step_lock = 1;
				break;
				case 5:
					car.step_lock = 0;
					uplift.target = UPLIFT_PUTDOWN;
					if(PUTDOWN_UPLIFT_IS_OK)
						car.step_lock = 1;
					
				break;
				case 6:
					car.step_lock = 0;
					uplift.target = UPLIFT_MAX;
					if(MAX_UPLIFT_IS_OK)
					{
						sucker.base_info.target_pitch = SUCKER_PITCH_MIN;
						if(SUCKER_PITCH_MINI_OK)
						{
							sucker.base_info.target_yaw = SUCKER_YAW_MIN;
							if(SUCKER_YAW_MINI_OK)
							{
								transverse.base_info.target = TRANSVERSE_MIN;
								if(TRANSVERSE_MINI_OK)
										car.step ++;
							}
						}
					}
				break;
				case 7:
					sucker.base_info.target_pitch = SUCKER_PITCH_MID;
					if(car.ore_num == 0)
						uplift.target = UPLIFT_ONE_ORE;
					else if(car.ore_num == 1)
						uplift.target = UPLIFT_THREE_ORE;
					else if(car.ore_num == 2)
						uplift.target = UPLIFT_THREE_ORE;
					if(SUCKER_PITCH_MID_OK&&OTT_UPLIFT_IS_OK)
						car.step ++;
				case 8:
					car.time_cnt ++;
					if(car.time_cnt>4000)
					{
						pneumatic.pneu_state = OFF;
						car.time_cnt = 0;
						car.step ++;
					}
					break;
					
				case 9:
					flip.mode = FLIP_DOWM;
					car.time_cnt ++;
					
					if(car.time_cnt>2000)
					{
						car.time_cnt = 0;
						flip.mode = FLIP_OFF;
						car.mode_ctrl = SILVER_ORE;
						car.ore_num ++;
					}
				break;
				case 10:
				break;
			}
		break;
	}
}

 /**
 * @date        
 * @brief       地矿模式
 */
void enter_ground_mode(void)
{	
	switch(car.mode_ctrl)
	{
		case GROUND_ORE:
			car.step = 1;
		
		break;
		default:
			switch(car.step)
			{
				case 1:
						car.step = 2;
				break;
				case 9:
					if(GROUND_UPLIFT_IS_OK&&GROUND_TRANSVERSE_IS_OK&&GROUND_SUCKER_PITCH_IS_OK)
					{
						pneumatic.pneu_state = ON;
						car.mode_ctrl = GROUND_ORE;
					}
				break;
			}
		break;
	}
}

 /**
 * @date        
 * @brief       放矿模式
 */
float place_ore_time_cnt;
void enter_placeore_mode(void)
{

}
 /**
 * @date        
 * @brief       兑换模式
 */
float exchange_time_cnt;
void enter_exchange_mode(void)
{
	switch(car.mode_ctrl)
	{
		case EXCHANGE_ORE:
			car.step = 1;
			car.step_lock = 0;

		break;
		default:
			switch(car.step)
			{
				case 1:	
					gimbal.target_pitch = GIMBAL_PITCH_MIN;
					gimbal.target_yaw = GIMBAL_YAW_MID;
					pneumatic.pneu_state = ON;
					car.step ++;
				break;
				case 2:
					sucker.base_info.target_pitch = SUCKER_PITCH_MID;
					sucker.base_info.target_yaw = SUCKER_YAW_MIN;
					car.step ++;
				break;
				case 3:
					car.ore_num --;
					car.mode_ctrl = EXCHANGE_ORE;
				break;
				case 4:
				break;
				case 5:
				break;
				case 6:
				break;
				case 7:
				break;
				case 8:
				break;
				case 9:
				break;
				case 10:
				break;
				case 11:
				break;
				case 12:
				break;
				case 13:
				break;
			}
		break;
	}
}
	
 /**
 * @date        
 * @brief       救援模式
 */
void enter_save_mode(void)
{
	switch(car.mode_ctrl)
	{
		case SAVE:
			car.step = 1;
			car.step_lock = 0;
			
					
		break;
		default:
			switch(car.step)
			{
				case 1:
					pneumatic.pneu_state = OFF;
					gimbal.target_pitch = GIMBAL_PITCH_MAX;
					gimbal.target_yaw = GIMBAL_YAW_MIN;
					protract.base_info.target = PROTRACT_MID;
					rescue.target = RESCUE_MIN;
					if(PROTRACT_MID_OK)
						car.step ++;
				break;
				case 2:
					sucker.base_info.target_pitch = SUCKER_PITCH_MIN;
					sucker.base_info.target_yaw = SUCKER_YAW_MIN;
					protract.base_info.target = PROTRACT_MID;
					if(SUCKER_YAW_MINI_OK&&SUCKER_PITCH_MINI_OK&&PROTRACT_MID_OK)
						car.step ++;
				break;
				case 3:
					if(uplift.measure_angle<UPLIFT_INTERFERE)
					{
						uplift.target = UPLIFT_INTERFERE;
						if(UPLIFT_INTERFERE_OK)
							transverse.base_info.target = TRANSVERSE_MIN;
					}
					else
						transverse.base_info.target = TRANSVERSE_MIN;
						
					if(TRANSVERSE_MINI_OK)
						car.step ++;
				break;
				case 4:
					if(car.ore_num == 0)
						uplift.target = UPLIFT_ONE_ORE;
					else if(car.ore_num == 1)
						uplift.target = UPLIFT_THREE_ORE;
					else if(car.ore_num == 2)
						uplift.target = UPLIFT_THREE_ORE;
					if(SUCKER_PITCH_MINI_OK&&OTT_UPLIFT_IS_OK)
						car.step ++;
				break;
				case 5:
					if(GB_PITCH_MAX_OK&&GB_YAW_MINI_OK)
						car.step ++;
				break;
				case 6:
					rescue.target = RESCUE_MID;
					car.step_lock = 1;
				break;
				case 7:
					car.step_lock = 0;
					rescue.target = RESCUE_DOWN;
					if(RESCUE_DOWN_OK)
						car.mode_ctrl = SAVE;
				break;
			}
		break;
	}
}



