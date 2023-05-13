#include "Pneumatic_motor.h"

//cubeÃ»ÅäÒý½Å

pneu_t pneu =
{
	.GPIOx = GPIOD,
	.GPIO_Pin = GPIO_PIN_12,
	.ctrl = Pneumatic_Ctrl,
	.init = Pneumatic_Init,
};

void Pneumatic_Ctrl(pneu_t *self, GPIO_PinState	state)
{
	HAL_GPIO_WritePin(self->GPIOx, self->GPIO_Pin, state);
}

void Pneumatic_Init(pneu_t *self)
{
	HAL_GPIO_WritePin(self->GPIOx, self->GPIO_Pin, GPIO_PIN_RESET);
}


