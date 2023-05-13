#ifndef _ENTER_MODE_CONTROL_H
#define _ENTER_MODE_CONTROL_H

#include "config.h"

#define IS_ORE_MODE	(car.mode_ctrl == SILVER_ORE || car.mode_ctrl == GOLDEN_ORE || car.mode_ctrl == GROUND_ORE)
	
void enter_normal_mode(void);
void enter_lob_mode(void);
void enter_goldenore_mode(void);
void enter_silverore_mode(void);
void enter_ground_mode(void);
void enter_placeore_mode(void);
void enter_exchange_mode(void);
void enter_barrier_mode(void);
void enter_block_mode(void);
void enter_save_mode(void);



#endif
