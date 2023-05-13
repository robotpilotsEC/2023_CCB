/* Includes ------------------------------------------------------------------*/
#include "can_protocol.h"
#include "drv_can.h"
#include "string.h"
#include "config_can.h"
#include "control.h"
#include "remote.h"
#include "device.h"
#include "motor.h"



typedef struct {
	CAN_RxHeaderTypeDef header;
	uint8_t				data[8];
} CAN_RxFrameTypeDef;

CAN_RxFrameTypeDef hcan1RxFrame;
CAN_RxFrameTypeDef hcan2RxFrame;

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;





/*--------------------------------------��-------------------------------------------*/
/*--------------------------------------��-------------------------------------------*/
/*--------------------------------------��-------------------------------------------*/
/*--------------------------------------��-------------------------------------------*/
/*--------------------------------------��-------------------------------------------*/
/**
  * @brief  can�����жϣ���stm32f4xx_hal_can.c��������
  * @param  
  * @retval 
  */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  if(hcan == &hcan1)
  {
		HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &hcan1RxFrame.header, hcan1RxFrame.data);
		CAN1_RX(hcan1RxFrame.header.StdId, hcan1RxFrame.data);
  }
  else if(hcan == &hcan2)
  {
		HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &hcan2RxFrame.header, hcan2RxFrame.data);
		CAN2_RX(hcan2RxFrame.header.StdId, hcan2RxFrame.data);
  }
  else 
    return;
}





































/*--------------------------------------��-------------------------------------------*/
/*--------------------------------------��-------------------------------------------*/
/*--------------------------------------��-------------------------------------------*/
/*--------------------------------------��-------------------------------------------*/
/*--------------------------------------��-------------------------------------------*/
uint8_t can_txbuff[8];
void can_send(void)
{
	memset(can_txbuff,0,sizeof(can_txbuff));
	
	/*****0x200��*****/
	HAL_CAN_TxHeadeInit(CAN_0x200_ID);
	/*CAN1*/
	if(RC_ONLINE)
	{
		/*���͵��ɸѡ����*/
		for(uint16_t i=0;i<DEVICE_CNT;i++)
			if(device[i].motor->id.drive_type == M_CAN1)
				if(device[i].motor->id.rx_id>=0x201&&device[i].motor->id.rx_id<=0x204)
					device[i].motor->tx(device[i].motor,can_txbuff,8);
	}
	while(HAL_CAN_AddTxMessage(&hcan1,&CAN_TxHeadeType,can_txbuff,(uint32_t *)CAN_TX_MAILBOX0)!=HAL_OK);
	memset(can_txbuff,0,sizeof(can_txbuff));
	/*CAN2*/
	if(RC_ONLINE)
	{
		/*���͵��ɸѡ����*/
		for(uint16_t i=0;i<DEVICE_CNT;i++)
			if(device[i].motor->id.drive_type == M_CAN2)
				if(device[i].motor->id.rx_id>=0x201&&device[i].motor->id.rx_id<=0x204)
					device[i].motor->tx(device[i].motor,can_txbuff,8);
	}
	while(HAL_CAN_AddTxMessage(&hcan2,&CAN_TxHeadeType,can_txbuff,(uint32_t *)CAN_TX_MAILBOX1)!=HAL_OK);
	memset(can_txbuff,0,sizeof(can_txbuff));

	/*****0x1ff��*****/
	HAL_CAN_TxHeadeInit(CAN_0x1ff_ID);
	/*CAN1*/
	if(RC_ONLINE)
	{
		/*���͵��ɸѡ����*/
		for(uint16_t i=0;i<DEVICE_CNT;i++)
			if(device[i].motor->id.drive_type == M_CAN1)
				if(device[i].motor->id.rx_id>=0x205&&device[i].motor->id.rx_id<=0x208)
					device[i].motor->tx(device[i].motor,can_txbuff,8);
	}
	while(HAL_CAN_AddTxMessage(&hcan1,&CAN_TxHeadeType,can_txbuff,(uint32_t *)CAN_TX_MAILBOX0)!=HAL_OK);
	memset(can_txbuff,0,sizeof(can_txbuff));
	/*CAN2*/
	if(RC_ONLINE)
	{
		/*���͵��ɸѡ����*/
		for(uint16_t i=0;i<DEVICE_CNT;i++)
			if(device[i].motor->id.drive_type == M_CAN2)
				if(device[i].motor->id.rx_id>=0x205&&device[i].motor->id.rx_id<=0x208)
					device[i].motor->tx(device[i].motor,can_txbuff,8);
	}
	while(HAL_CAN_AddTxMessage(&hcan2,&CAN_TxHeadeType,can_txbuff,(uint32_t *)CAN_TX_MAILBOX1)!=HAL_OK);
	memset(can_txbuff,0,sizeof(can_txbuff));
	
}

