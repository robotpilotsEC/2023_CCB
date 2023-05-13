/**
  ******************************************************************************
  * @file           : vision_potocol.c\h
  * @brief          : 
  * @update         : 
  ******************************************************************************
  */

#ifndef __VISION_PROTOCOL_H
#define __VISION_PROTOCOL_H

#include "config.h"

typedef __packed struct 
{
	uint8_t  SOF;
	uint8_t  mode;
	uint8_t  CRC8;
	
	float    pitch_ore;  	//pitch
	float    yaw_ore;  		//yaw
	float    roll_ore;  	//roll
	float    x_ore;  			//x
	float    y_ore;  			//y
	float    z_ore;  			//z
	
	uint8_t  is_find_ore_bin;  		//0-no 1-yes
	
	uint16_t CRC16;
}vision_rx_info_t;

typedef __packed struct 
{
	uint8_t  SOF;
	uint8_t  mode;  //0-non 1-¶Ò¿ó 2-¿Õ½Ó
	uint8_t  CRC8;
	float    yaw;
	float    pitch;
	
 	uint8_t  my_colour;  //0-À¶É« 1-ºìÉ«
	
	uint16_t CRC16;
	
}vision_tx_info_t;

extern vision_tx_info_t vision_tx_info;
extern vision_rx_info_t vision_rx_info;

uint8_t vision_data_tx(void);
uint8_t vision_data_rx(uint8_t *rxBuf);

#endif
