/**
  ******************************************************************************
  * @file           : RP_drv
  * @brief          : 
  * @note           : start 2022-11-3 
  ******************************************************************************
  */
	
#ifndef __CONFIG_CAN_H
#define __CONFIG_CAN_H

#include "stm32f4xx_hal.h"

/*
#define example_id 0x000
*/

/* 电机can接收id */
#define CHASSIS_MOTOR_LF_ID 0x201
#define CHASSIS_MOTOR_RF_ID 0x202
#define CHASSIS_MOTOR_LB_ID 0x203
#define CHASSIS_MOTOR_RB_ID 0x204

#define UPLIFT_MOTOR_F_ID 0x201
#define UPLIFT_MOTOR_B_ID 0x202
#define GIMBAL_PITCH_ID 0x203
#define GIMBAL_YAW_ID 0x204
#define RESCUE_MOTOR_L_ID 0x205
#define RESCUE_MOTOR_R_ID 0x206


void CAN1_RX(uint32_t canId, uint8_t *rxBuf);
void CAN2_RX(uint32_t canId, uint8_t *rxBuf);



#endif
