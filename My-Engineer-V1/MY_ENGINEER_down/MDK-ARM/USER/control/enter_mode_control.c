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
 * @brief       进入常规模式
 */
void enter_normal_mode(void)
{
	switch(car.mode_ctrl)
	{
		case NORMAL:
			car.step = 1;
		break;
		default:
			switch(car.step)
			{
				case 1:	
				break;
				case 2:
				break;
			}
		}
}


 /**
 * @date        
 * @brief       进入空接模式
 */
void enter_lob_mode(void)
{
	switch(car.mode_ctrl)
	{
		case LOB:
			car.step = 1;
		break;
		default:
			switch(car.step)
			{
				case 1:	
				break;
				case 2:
				break;
			}
		break;
	}
}

 /**
 * @date        
 * @brief       进入金矿模式
 */
void enter_goldenore_mode(void)
{
	switch(car.mode_ctrl)
	{
		case GOLDEN_ORE:
			car.step = 1;
		break;
		default:
			switch(car.step)
			{
				case 1:	
				break;
				case 2:
				break;
			}
		break;
	}
}

 /**
 * @date        
 * @brief       进入银矿模式
 */
void enter_silverore_mode(void)
{
	switch(car.mode_ctrl)
	{
		case SILVER_ORE:
			car.step = 1;
		break;
		default:
			switch(car.step)
			{
				case 1:	
				break;
				case 2:
				break;
			}
		break;
	}
}

 /**
 * @date        
 * @brief       进入地矿模式
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
				break;
				case 2:
				break;
			}
		break;
	}
}

 /**
 * @date        
 * @brief       进入兑换模式
 */
void enter_exchange_mode(void)
{
	switch(car.mode_ctrl)
	{
		case EXCHANGE_ORE:
			/*模式切换完成后进行自动化*/
//			auto_process();
		break;
		default:
			switch(car.step)
			{
				case 1:	
				break;
				case 2:
				break;
				case 3:
				break;
				case 4:
				break;
				}
		break;
	}
}
	







