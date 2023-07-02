#ifndef __CAN_PROTOCOL_H
#define __CAN_PROTOCOL_H

#include "config.h"

/*CAN发送或是接收的ID*/
typedef enum
{
	CAN_0x200_ID	= 0x200,		
	CAN_0x1ff_ID = 0x1FF,
}CAN_ID;

uint8_t can_send(void);
void CAN1_rxDataHandler(uint32_t canId, uint8_t *rxBuf);
void CAN2_rxDataHandler(uint32_t canId, uint8_t *rxBuf);
#endif

