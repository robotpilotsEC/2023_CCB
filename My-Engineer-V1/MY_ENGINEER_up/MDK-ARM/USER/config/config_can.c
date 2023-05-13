/**
  ******************************************************************************
  * @file           : RP_drv
  * @brief          : 
  * @note           : start 2022-12-12 
  ******************************************************************************
  */

#include "config_can.h"
#include "device.h"


void CAN2_RX(uint32_t canId, uint8_t *rxBuf)
{
	switch (canId)
	{
		case DEFFL_MOTOR_ID:
			sucker_motor[DEFFL].rx(&sucker_motor[DEFFL],rxBuf,8);
		break;
		case YAW_MOTOR_ID:
			sucker_motor[YAW].rx(&sucker_motor[YAW],rxBuf,8);
		break;
		case DEFFR_MOTOR_ID:
			sucker_motor[DEFFR].rx(&sucker_motor[DEFFR],rxBuf,8);
		break;
		case PROTRACT_MOTOR_ID:
			protract_motor.rx(&protract_motor,rxBuf,8);
		break;	
		case TRANSVERSE_MOTOR_B_ID:
			transverse_motor[TRANSVERSE_B].rx(&transverse_motor[TRANSVERSE_B],rxBuf,8);
		break;	
		default:
			break;
	}
		 
}


void CAN1_RX(uint32_t canId, uint8_t *rxBuf)
{
	switch (canId)
	{
		case FLIP_MOTOR_L_ID:
			flip_motor[FLIP_L].rx(&flip_motor[FLIP_L],rxBuf,8);
		break;
		case FLIP_MOTOR_R_ID:
			flip_motor[FLIP_R].rx(&flip_motor[FLIP_R],rxBuf,8);
		break;
		case TRANSVERSE_MOTOR_F_ID:
			transverse_motor[TRANSVERSE_F].rx(&transverse_motor[TRANSVERSE_F],rxBuf,8);
		break;
		default:
			break;
	}
}




