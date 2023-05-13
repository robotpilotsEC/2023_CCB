#ifndef __PNEUMATIC_MOTOR_H
#define __PNEUMATIC_MOTOR_H

#include "config.h"

typedef struct pneu_info_struct{
	GPIO_TypeDef* GPIOx;
	uint16_t 			GPIO_Pin;
	void 					(*ctrl)(struct pneu_info_struct *self, GPIO_PinState);
	void 					(*init)(struct pneu_info_struct *self);
}pneu_t;

extern pneu_t pneu;

void Pneumatic_Ctrl(pneu_t *self, GPIO_PinState	state);
void Pneumatic_Init(pneu_t *self);


#endif
