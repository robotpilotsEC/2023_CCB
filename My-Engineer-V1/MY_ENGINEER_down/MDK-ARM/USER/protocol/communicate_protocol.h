/**
  ******************************************************************************
  * @file           : communicate_potocol.c\h
  * @brief          : 
  * @update         : 
  ******************************************************************************
  */

#ifndef __COMMUNICATE_PROTOCOL_H
#define __COMMUNICATE_PROTOCOL_H

#include "config.h"
#include "car_state.h"

typedef __packed struct 
{
	uint8_t  	SOF;
	uint8_t  	datau8_1;
	uint8_t  	CRC8;
	
	Dev_Reset_State_e	 			is_uplift_reset;
	Dev_Reset_State_e	 			is_gimbal_reset;
	Dev_Reset_State_e	 			is_recue_reset;
	Dev_Reset_State_e	 			is_slave_reset;
	
	int32_t									uplift_angle;
	int16_t									uplift_speed;
	int32_t									gimbal_pitch_angle;
	int16_t									gimbal_pitch_speed;
	int32_t									gimbal_yaw_angle;
	int16_t									gimbal_yaw_speed;
	int32_t									rescue_angle;
	int16_t									rescue_speed;

	uint16_t CRC16;	
}communicate_tx_info_t;

typedef __packed struct 
{
	uint8_t  	SOF;
	uint8_t  	datau8_1;
	uint8_t  	CRC8;
	
	Dev_Reset_State_e	 			is_master_reset;
	float										uplift_target;
	float										pitch_target;
	float										yaw_target;
	float										rescue_target;
	
	car_mode_e							car_mode_ctrl;
	car_mode_e							car_mode_switch;	
	uint8_t									is_uplift_start_reset;
	uint8_t									is_gimbal_start_reset;
	uint8_t									is_rescue_start_reset;
	uint8_t									is_all_device_ok;

	uint16_t CRC16;
}communicate_rx_info_t;

extern communicate_tx_info_t communicate_tx_info;
extern communicate_rx_info_t communicate_rx_info;

uint8_t communicate_data_tx(void);
uint8_t communicate_data_rx(uint8_t *rxBuf);

#endif
