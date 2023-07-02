/* Includes ------------------------------------------------------------------*/
#include "Pneumatic.h"
#include "config.h"
#include "string.h"
#include "control.h"
/* Exported variables --------------------------------------------------------*/

pneumatic_t pneumatic = 
{
	.work = pneumatic_work,
	.init = pneumatic_init,
};


void pneumatic_init(pneumatic_t *pneumatic)
{
	pneumatic->pneu = &pneu;
	pneumatic->pneu_state = OFF;
}


void pneumatic_work(pneumatic_t *pneumatic)
{
	if(SYSTEM_RESET)
	{
		switch (pneumatic->pneu_state)
		{
			case ON:
				pneumatic->pneu->ctrl(pneumatic->pneu,GPIO_PIN_SET);
				break;
			case OFF:
				pneumatic->pneu->ctrl(pneumatic->pneu,GPIO_PIN_RESET);
				break;
			default:
				break;
		}
	}
}

