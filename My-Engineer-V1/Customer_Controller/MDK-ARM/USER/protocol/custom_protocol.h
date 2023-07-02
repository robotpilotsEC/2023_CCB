/**
  ******************************************************************************
  * @file           : custom_potocol.c\h
  * @brief          : 
  * @update         : 
  ******************************************************************************
  */

#ifndef __CUSTOM_PROTOCOL_H
#define __CUSTOM_PROTOCOL_H

#include "config.h"


typedef __packed struct 
{
	uint8_t  SOF;
	uint8_t  mode;  //0-non 1-¶Ò¿ó 2-¿Õ½Ó
	uint8_t  CRC8;	
	
	float    pitch_speed;  	//pitch
	float    yaw_speed;  		//yaw
	float    roll_speed;  	//roll
	float    x_speed;  			//x
	float    y_speed;  			//y
	float    z_speed;  			//z
	
	uint16_t CRC16;
	
}custom_tx_info_t;

extern custom_tx_info_t custom_tx_info;

uint8_t custom_data_tx(void);
uint8_t custom_data_rx(uint8_t *rxBuf);

#endif
