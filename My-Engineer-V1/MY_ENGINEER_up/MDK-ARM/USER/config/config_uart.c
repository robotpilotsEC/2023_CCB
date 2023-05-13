/**
  ******************************************************************************
  * @file           : config_uart.c\h
  * @brief          : 
  * @note           : 
  ******************************************************************************
  */
	
#include "config_uart.h"
#include "remote.h"
#include "remote_protocol.h"
#include "vision_protocol.h"
#include "communicate_protocol.h"
#include "judge_protocol.h"

void USART1_rxDataHandler(uint8_t *rxBuf)
{
	vision_data_rx(rxBuf);
}

void USART2_rxDataHandler(uint8_t *rxBuf)
{
	/* ң������Ϣ���� */
	rc_base_info_update(rc.base_info,rxBuf);
	rc_base_info_check(rc.base_info);
	
	/* ң�������� */
	rc_interrupt_update(&rc);
}

void USART3_rxDataHandler(uint8_t *rxBuf)
{
  communicate_data_rx(rxBuf);
}

void USART4_rxDataHandler(uint8_t *rxBuf)
{
}

void USART5_rxDataHandler(uint8_t *rxBuf)
{
}

void USART6_rxDataHandler(uint8_t *rxBuf)
{
	judge_update(&judge,rxBuf);
}
