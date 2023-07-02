#include "drive.h"


void drive_init(void)
{
	CAN1_Init();
	CAN2_Init();
	USART1_Init();
	USART2_Init();
	USART3_Init();
	USART4_Init();
	USART6_Init();
}


