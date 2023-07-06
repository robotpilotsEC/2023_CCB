 /**
  ******************************************************************************
  * @file           : enter_control.c/h
  * @brief          : 
  * @note           : 
  ******************************************************************************
  */
 
 
#include "enter_mode_control.h"
#include "exchanges_control.h"
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
					Auto.config->key_dowm1 = AUTO_NO;
					Auto.config->key_dowm2 = AUTO_NO;
					Auto.config->via_process_done = AUTO_NO;
					Auto.config->all_process_done = AUTO_NO;
					Auto.config->start_exchange_flag = AUTO_NO;
					flip.mode = FLIP_OFF;
					pneumatic.pneu_state = OFF;
					protract.base_info.target = PROTRACT_MID;
					rescue.target = RESCUE_MIN;
					sucker.base_info.target_roll = 0;
					if(PROTRACT_MID_OK)
						car.step ++;
					break;
				case 2:
					if(SUCKER_YAW_MINI_OK&&SUCKER_PITCH_MID_OK)
						car.step = 4;
					else
					{
						if(uplift.measure_angle<UPLIFT_INTERFERE)
						{
							uplift.target = UPLIFT_INTERFERE;
							if(UPLIFT_INTERFERE_OK)
								transverse.base_info.target = TRANSVERSE_NORMAL;
						}
						else
							transverse.base_info.target = TRANSVERSE_NORMAL;
							
						if(NORMAL_TRANSVERSE_IS_OK)
							car.step ++;
					}
					break;
				case 3:
					sucker.base_info.target_pitch = SUCKER_PITCH_MID;
					sucker.base_info.target_yaw = SUCKER_YAW_MIN;
					if(SUCKER_YAW_MINI_OK&&SUCKER_PITCH_MID_OK)
						car.step ++;
					break;
				case 4:
					transverse.base_info.target = TRANSVERSE_MIN;
					if(car.ore_num == 0)
					{
						uplift.target = UPLIFT_MIN;
						if(UPLIFT_MINI_OK&&TRANSVERSE_MINI_OK)
							car.step ++;
					}
					else if(car.ore_num == 1)
						uplift.target = UPLIFT_ONE_ORE;
					else if(car.ore_num == 2)
						uplift.target = UPLIFT_ONE_ORE;
					if(OTT_UPLIFT_IS_OK&&TRANSVERSE_MINI_OK)
						car.step ++;
					break;
				case 5:
					gimbal.target_pitch = GIMBAL_PITCH_MAX;
					gimbal.target_yaw = GIMBAL_YAW_MIN;
					if(GB_PITCH_MAX_OK&&GB_YAW_MINI_OK)
						car.step ++;
					break;
				case 6:
//					if(RESCUE_MINI_OK)
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
int	down_time_cnt = 2500;//2500
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
					if(PROTRACT_MID_OK&&(uplift.measure_angle>UPLIFT_LOB/3.f))
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
						car.step ++;
					break;
				case 5:
					car.step_lock = 1;
					break;
				case 6:
					car.step_lock = 0;
					sucker.base_info.target_yaw = SUCKER_YAW_MIN;
					if(SUCKER_YAW_MINI_OK)
					{
						transverse.base_info.target = TRANSVERSE_MIN;
						if(TRANSVERSE_MINI_OK)
							car.step ++;
					}
					break;
				case 7:
					sucker.base_info.target_pitch = SUCKER_PITCH_MID;
					if(car.ore_num == 0)
						uplift.target = UPLIFT_ONE_ORE;
					else if(car.ore_num == 1)
						uplift.target = UPLIFT_ONE_ORE;
					else if(car.ore_num == 2)
						uplift.target = UPLIFT_ONE_ORE;
					if(SUCKER_PITCH_MID_OK&&OTT_UPLIFT_IS_OK)
						car.step ++;
					break;
				case 8:
					car.time_cnt ++;
					flip.mode = FLIP_DOWM;
					if(car.time_cnt>800)
					{
						pneumatic.pneu_state = OFF;
						car.time_cnt = 0;
						car.step ++;
					}
					
					break;
				case 9:
					flip.mode = FLIP_DOWM;
					transverse.base_info.target = TRANSVERSE_AFTER_PLACE;
					car.time_cnt ++;
					
					if(car.time_cnt>down_time_cnt)//2500
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
					car.step_lock = 0;
					pneumatic.pneu_state = ON;
					if(GOLDEN_TRANSVERSE_IS_OK)
						car.step ++;
					break;
				case 5:
					car.step_lock = 1;
					break;
				case 6:
					car.step_lock = 0;
					uplift.target = UPLIFT_PUTDOWN;
					if(PUTDOWN_UPLIFT_IS_OK)
						car.step_lock = 1;
					break;
				case 7:
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
				case 8:
					sucker.base_info.target_pitch = SUCKER_PITCH_MID;
					if(car.ore_num == 0)
						uplift.target = UPLIFT_ONE_ORE;
					else if(car.ore_num == 1)
						uplift.target = UPLIFT_ONE_ORE;
					else if(car.ore_num == 2)
						uplift.target = UPLIFT_ONE_ORE;
					if(SUCKER_PITCH_MID_OK&&OTT_UPLIFT_IS_OK)
						car.step ++;
					break;
				case 9:
					car.time_cnt ++;
					flip.mode = FLIP_DOWM;
					if(car.time_cnt>800)
					{
						pneumatic.pneu_state = OFF;
						car.time_cnt = 0;
						car.step ++;
					}
					break;
				case 10:
					flip.mode = FLIP_DOWM;
					transverse.base_info.target = TRANSVERSE_AFTER_PLACE;
					car.time_cnt ++;
					
					if(car.time_cnt>down_time_cnt)
					{
						car.time_cnt = 0;
						flip.mode = FLIP_OFF;
						car.mode_ctrl = GOLDEN_ORE;
						car.ore_num ++;
					}
					
					break;
				case 11:
					break;
			}
		break;
	}
}

 /**
 * @date        
 * @brief       银矿模式
 */
float left_roll = 33.f;
float right_roll = 36.f;
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
					sucker.base_info.target_roll = 0;
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
						car.step ++;
					break;
				case 5:
					car.step_lock = 1;
					break;
				case 6:
					car.step_lock = 0;
					uplift.target = UPLIFT_PUTDOWN;
					if(PUTDOWN_UPLIFT_IS_OK)
						car.step_lock = 1;
					break;
				case 7:
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
				case 8:
					sucker.base_info.target_pitch = SUCKER_PITCH_MID;
					if(car.ore_num == 0)
						uplift.target = UPLIFT_ONE_ORE;
					else if(car.ore_num == 1)
						uplift.target = UPLIFT_ONE_ORE;
					else if(car.ore_num == 2)
						uplift.target = UPLIFT_ONE_ORE;
					if(SUCKER_PITCH_MID_OK&&OTT_UPLIFT_IS_OK)
					{
						car.step ++;
						car.ore_num ++;
					}
					break;
				case 9:
					car.time_cnt ++;
					flip.mode = FLIP_DOWM;
					if(car.time_cnt>800)
					{
						pneumatic.pneu_state = OFF;
						car.time_cnt = 0;
						car.step ++;
					}
					break;
					
				case 10:
					flip.mode = FLIP_DOWM;
					transverse.base_info.target = TRANSVERSE_AFTER_PLACE;
					car.time_cnt ++;
					
					if(car.time_cnt>down_time_cnt)
					{
						car.time_cnt = 0;
						flip.mode = FLIP_OFF;
						car.mode_ctrl = SILVER_ORE;
					}
					break;
					
					
					
					/*两矿*/
					/*NO.1*/
				case 11:
					flip.mode = FLIP_DOWM;
					pneumatic.pneu_state = ON;
					gimbal.target_pitch = GIMBAL_PITCH_MIN;
					gimbal.target_yaw = GIMBAL_YAW_MID;
					protract.base_info.target  = PROTRACT_MIN;
					uplift.target = UPLIFT_SILVER;
					if(GB_YAW_MID_OK&&GB_PITCH_MIN_OK&&SILVER_UPLIFT_IS_OK)
						car.step ++;
					break;
				case 12:
					sucker.base_info.target_pitch = SUCKER_PITCH_SILVER;
					sucker.base_info.target_yaw = SUCKER_YAW_LEFT;
					transverse.base_info.target = TRANSVERSE_TWO_ORES;
					if(SUCKER_YAW_LEFT_OK&&SILVER_SUCKER_PITCH_IS_OK&&TWO_ORES_TRANSVERSE_IS_OK)
						car.step ++;
					break;
				case 13:
					car.step_lock = 1;
					break;
				case 14:
					car.step_lock = 0;
					uplift.target = UPLIFT_PUTDOWN;
					if(PUTDOWN_UPLIFT_IS_OK)
						car.time_cnt ++;
					else
						car.time_cnt = 0;
					
					if(car.time_cnt>300)
					{
						car.time_cnt = 0;
						car.step ++;
					}
					break;
				case 15:
					uplift.target = UPLIFT_MAX;
					if(MAX_UPLIFT_IS_OK)
						car.step ++;
					break;
				case 16:
					protract.base_info.target = PROTRACT_SILVER1;
					transverse.base_info.target = TRANSVERSE_MIN;
					sucker.base_info.target_roll = 33.f*SUCKER_ROLL_D2A;
					sucker.base_info.target_pitch = SUCKER_PITCH_MIN;
					if(SUCKER_PITCH_MINI_OK&&sucker.base_info.measure_roll_speed == 0)
						sucker.base_info.target_yaw = SUCKER_YAW_MIN;
					if(SUCKER_YAW_MINI_OK&&SUCKER_PITCH_MINI_OK&&TRANSVERSE_MINI_OK&&SILVER1_PROTRACT_IS_OK)
						car.step ++;
					break;
				case 17:
					uplift.target = UPLIFT_ONE_ORE;
					if(ONE_UPLIFT_IS_OK)
						car.step ++;
					break;
				case 18:
					car.step_lock = 1;
					break;
				case 19:
					car.step_lock = 0;
					transverse.base_info.target = TRANSVERSE_AFTER_PLACE;
					if(AFTER_PLACE_TRANSVERSE_IS_OK)
					{
						sucker.base_info.target_pitch = SUCKER_PITCH_MID;
						if(SUCKER_PITCH_MID_OK)
							car.time_cnt ++;
						else
							car.time_cnt = 0;
					}
					
					if(car.time_cnt>800)
					{
						car.time_cnt = 0;
						pneumatic.pneu_state = OFF;
						car.step ++;
					}
					break;
					
				case 20:
					car.step_lock = 1;
					break;
					/*NO.2*/
				case 21:
					car.step_lock = 0;
					sucker.base_info.target_roll = 0.f;
					uplift.target = UPLIFT_SILVER;
					if(SILVER_UPLIFT_IS_OK)
						car.step ++;
					break;
				case 22:
					pneumatic.pneu_state = ON;
					transverse.base_info.target = TRANSVERSE_TWO_ORES2;
					if(TWO_ORES2_TRANSVERSE_IS_OK)
						car.step ++;
					break;
				case 23:
					sucker.base_info.target_pitch = SUCKER_PITCH_SILVER;
					sucker.base_info.target_yaw = SUCKER_YAW_RIGHT;
					protract.base_info.target = PROTRACT_TWO_ORES;
					if(SILVER_SUCKER_PITCH_IS_OK&&SUCKER_YAW_RIGHT_OK&&PROTRACT_TWO_ORE_OK)
						car.step ++;
					break;
				case 24:
					uplift.target = UPLIFT_PUTDOWN;
					if(PUTDOWN_UPLIFT_IS_OK)
						car.time_cnt ++;
					else
						car.time_cnt = 0;
					
					if(car.time_cnt>250)
					{
						car.time_cnt = 0;
						car.step ++;
					}
					break;
				case 25:
					uplift.target = UPLIFT_MAX;
					if(MAX_UPLIFT_IS_OK)
						car.step ++;
					break;
				case 26:
					sucker.base_info.target_yaw = SUCKER_YAW_MID;
					sucker.base_info.target_pitch = SUCKER_PITCH_MIN;
					protract.base_info.target = PROTRACT_MID;
					sucker.base_info.target_roll = 140000.f;
					if(SUCKER_PITCH_MINI_OK&&PROTRACT_MID_OK&&sucker.base_info.measure_roll_speed == 0)
						car.step ++;
					break;
				case 27:
					sucker.base_info.target_yaw = SUCKER_YAW_MIN;
					transverse.base_info.target = TRANSVERSE_NORMAL;
					if(SUCKER_YAW_MINI_OK&&NORMAL_TRANSVERSE_IS_OK)
						car.step ++;
					break;
				case 28:
					uplift.target = UPLIFT_TWO_ORE;
					if(TWO_UPLIFT_IS_OK)
						car.step ++;
					break;
				case 29:
					car.step_lock = 1;
					break;
				case 30:
					car.step_lock = 0;
					transverse.base_info.target = TRANSVERSE_AFTER_PLACE;
					if(AFTER_PLACE_TRANSVERSE_IS_OK)
					{
						sucker.base_info.target_pitch = SUCKER_PITCH_MID;
						if(SUCKER_PITCH_MID_OK)
							car.time_cnt ++;
						else
							car.time_cnt = 0;
					}
					
					if(car.time_cnt>800)
					{
						car.time_cnt = 0;
						pneumatic.pneu_state = OFF;
						car.step ++;
					}
					break;
				case 31:
					car.time_cnt ++;
					if(car.time_cnt>1500)
					{
						car.time_cnt = 0;
						sucker.base_info.target_roll = 0;
						flip.mode = FLIP_OFF;
						car.ore_num = 2;
						car.mode_ctrl = SILVER_ORE;
					}
					break;
//				case 31:
//					break;
//				case 32:
//					break;
//				case 33:
//					break;
				
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
int time_ccb_cnt = 2000;//2000
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
					Auto.step = 1;
				
					Auto.config->key_dowm1 = AUTO_NO;
					Auto.config->key_dowm2 = AUTO_NO;
					Auto.config->via_process_done = AUTO_NO;
					Auto.config->all_process_done = AUTO_NO;
				  Auto.config->start_exchange_flag = AUTO_NO;
				
					gimbal.target_pitch = GIMBAL_PITCH_MIN;
					gimbal.target_yaw = GIMBAL_YAW_MID;
					transverse.base_info.target = TRANSVERSE_NORMAL;
					if(car.ore_num == 2)
					{
						uplift.target = UPLIFT_ONE_ORE;
						if(ONE_UPLIFT_IS_OK)
							car.step ++;
					}
					else
					{
						uplift.target = UPLIFT_INTERFERE;
						if(UPLIFT_INTERFERE_OK)
							car.step ++;
					}
				break;
				case 2:
					sucker.base_info.target_pitch = SUCKER_PITCH_MID;
					sucker.base_info.target_yaw = SUCKER_YAW_MIN;
					if(SUCKER_PITCH_MID_OK&&SUCKER_YAW_MINI_OK&&NORMAL_TRANSVERSE_IS_OK)
					{
						flip.mode = FLIP_UP;
						car.time_cnt ++;
						if(car.time_cnt > time_ccb_cnt)
						{
							car.time_cnt = 0;
							flip.mode = FLIP_OFF;
							car.ore_num --;
							car.step ++;
						}
					}
				break;
				case 3:
					car.step_lock = 1;
				break;
				case 4:
					car.step_lock = 0;
					pneumatic.pneu_state = ON;
					transverse.base_info.target = TRANSVERSE_MIN;
					car.step ++;
					break;
				case 5:
					car.step_lock = 1;
				break;
				case 6:
					car.step_lock = 0;
					flip.mode = FLIP_UP;
					sucker.base_info.target_pitch = SUCKER_PITCH_MIN;
					if(SUCKER_PITCH_MINI_OK)
					{
						flip.mode = FLIP_OFF;
						uplift.target = UPLIFT_MAX;
						if(MAX_UPLIFT_IS_OK)
						{
							flip.mode = FLIP_OFF;
							car.step ++;
						}
					}
				break;
				case 7:
					sucker.base_info.target_yaw = SUCKER_YAW_MID;
					if(SUCKER_YAW_MID_OK)
					{
						sucker.base_info.target_pitch = SUCKER_PITCH_MID;
						car.step ++;
					}
				break;
				case 8:
					car.step_lock = 1;
					if(Auto.config->via_process_done == AUTO_OK)
					{
//						Auto.config->via_process_done = AUTO_NO;
						car.step ++;
					}
				break;
				case 9:
					car.step_lock = 0;
					car.step_lock = 1;
				break;
				case 10:
					car.step_lock = 0;
				
					Auto.config->key_dowm1 = AUTO_NO;
					Auto.config->key_dowm2 = AUTO_NO;
					Auto.config->via_process_done = AUTO_NO;
					Auto.config->all_process_done = AUTO_NO;
				  Auto.config->start_exchange_flag = AUTO_NO;
				
					sucker.base_info.target_roll = 0;
					sucker.base_info.target_pitch = SUCKER_PITCH_MID;
					sucker.base_info.target_yaw = SUCKER_YAW_MIN;
					if(SUCKER_PITCH_MID_OK&&SUCKER_YAW_MINI_OK)
						car.step ++;
				break;
				case 11:
					sucker.base_info.roll_A2D = 0;
					transverse.base_info.target = TRANSVERSE_MIN;
					uplift.target = UPLIFT_ONE_ORE;
					pneumatic.pneu_state = OFF;
					car.mode_ctrl = EXCHANGE_ORE;
				break;
				case 12:
				break;
				case 13:
				break;
				case 14:
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
					uplift.target = UPLIFT_MIN;
					if(SUCKER_PITCH_MINI_OK&&UPLIFT_MINI_OK)
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



