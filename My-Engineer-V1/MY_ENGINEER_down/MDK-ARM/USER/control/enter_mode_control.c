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
 * @brief       ���볣��ģʽ
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
 * @brief       ����ս�ģʽ
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
 * @brief       ������ģʽ
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
 * @brief       ��������ģʽ
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
 * @brief       ����ؿ�ģʽ
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
 * @brief       ����һ�ģʽ
 */
void enter_exchange_mode(void)
{
	switch(car.mode_ctrl)
	{
		case EXCHANGE_ORE:
			/*ģʽ�л���ɺ�����Զ���*/
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
	







