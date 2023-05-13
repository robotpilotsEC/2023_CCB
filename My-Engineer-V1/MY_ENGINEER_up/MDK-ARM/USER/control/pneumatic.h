#ifndef _PNEUMATIC_H
#define _PNEUMATIC_H

#include "pneumatic_motor.h"

typedef enum
{
	OFF,
	ON,
}pneu_state_e;

typedef __packed struct pneumatic_class_t
{
	pneu_t 					*pneu;
	
	void						(*work)(struct pneumatic_class_t *self);
	void						(*init)(struct pneumatic_class_t *self);
	
	pneu_state_e    pneu_state;
}pneumatic_t;

extern pneumatic_t pneumatic;


void pneumatic_work(pneumatic_t *pneumatic);
void pneumatic_init(pneumatic_t *pneumatic);

#endif
