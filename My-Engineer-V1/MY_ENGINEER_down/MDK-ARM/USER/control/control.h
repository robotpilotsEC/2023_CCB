#ifndef __CONTROL_H
#define __CONTROL_H

#include "config.h"
#include "remote.h"
#include "gimbal.h"
#include "rescue.h"
#include "uplift.h"
#include "chassis.h"


#define RC_ONLINE 	 		(rc.info->status == DEV_ONLINE)
#define SYSTEM_RESET 		(control.master_reset == DEV_RESET_OK)

typedef struct 
{
	Dev_Reset_State_e				 	master_reset;	//主板复位标志
	Dev_Reset_State_e					slaver_reset;	//从板复位标志
}control_t;


extern control_t control;

void system_reset(void);

#endif
