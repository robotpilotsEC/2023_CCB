/**
  ******************************************************************************
  * @file           : RP_drv
  * @brief          : 
  * @note           : start 2022-12-12 
  ******************************************************************************
  */

#include "config_can.h"
#include "device.h"


void CAN1_RX(uint32_t canId, uint8_t *rxBuf)
{
	switch (canId)
	{
		case CHASSIS_MOTOR_LF_ID:
			chassis_motor[LF].rx(&chassis_motor[LF],rxBuf,8);
		break;
		case CHASSIS_MOTOR_RF_ID:
			chassis_motor[RF].rx(&chassis_motor[RF],rxBuf,8);
		break;
		case CHASSIS_MOTOR_LB_ID:
			chassis_motor[LB].rx(&chassis_motor[LB],rxBuf,8);
		break;
		case CHASSIS_MOTOR_RB_ID:
			chassis_motor[RB].rx(&chassis_motor[RB],rxBuf,8);
		break;	
		default:
			break;
	}
		 
}


void CAN2_RX(uint32_t canId, uint8_t *rxBuf)
{
	switch (canId)
	{
		case UPLIFT_MOTOR_F_ID:
			uplift_motor[FRONT].rx(&uplift_motor[FRONT],rxBuf,8);
		break;
		case UPLIFT_MOTOR_B_ID:
			uplift_motor[BACK].rx(&uplift_motor[BACK],rxBuf,8);
		break;
		case GIMBAL_PITCH_ID:
			gimbal_motor[PITCH].rx(&gimbal_motor[PITCH],rxBuf,8);
		break;
		case GIMBAL_YAW_ID:
			gimbal_motor[YAW].rx(&gimbal_motor[YAW],rxBuf,8);
		break;
		case RESCUE_MOTOR_L_ID:
			rescue_motor[LEFT].rx(&rescue_motor[LEFT],rxBuf,8);
		break;
		case RESCUE_MOTOR_R_ID:
			rescue_motor[RIGHT].rx(&rescue_motor[RIGHT],rxBuf,8);
		break;
		default:
			break;
	}
}




