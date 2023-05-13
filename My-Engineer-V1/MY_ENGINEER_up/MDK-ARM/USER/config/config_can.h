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


/* 电机can接收id */
/*can1*/
#define DEFFL_MOTOR_ID 0x201
#define DEFFR_MOTOR_ID 0x202
#define YAW_MOTOR_ID 0x203
#define PROTRACT_MOTOR_ID 0x204
#define TRANSVERSE_MOTOR_F_ID 0x205
/*can2*/
#define FLIP_MOTOR_L_ID 0x201 
#define FLIP_MOTOR_R_ID 0x202
#define TRANSVERSE_MOTOR_B_ID 0x205

void CAN1_RX(uint32_t canId, uint8_t *rxBuf);
void CAN2_RX(uint32_t canId, uint8_t *rxBuf);



#endif
