/* Includes ------------------------------------------------------------------*/
#include "flip.h"
#include "remote.h"
#include "config.h"
#include "string.h"
#include "control.h"
/* Exported variables --------------------------------------------------------*/
flip_t flip = 
{
	.left = &flip_motor[LEFT],
	.right = &flip_motor[RIGHT],
	
	.work = Flip_Work,
	.mode = FLIP_OFF,
};

/* Function  body --------------------------------------------------------*/
/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void Flip_Pid_Calculating(flip_t *flip)
{
	switch (flip->mode)
	{
		case FLIP_OFF:
			flip->base_info.output_L = flip->left->c_speed(flip->left,0);
			flip->base_info.output_R = flip->right->c_speed(flip->right,0);
			break;
		case FLIP_DOWM:
			flip->base_info.output_L = flip->left->c_speed(flip->left,-FLIP_SPEED);
			flip->base_info.output_R = flip->right->c_speed(flip->right, FLIP_SPEED);
			break;
		case FLIP_UP:
			flip->base_info.output_L = flip->left->c_speed(flip->left, FLIP_SPEED);
			flip->base_info.output_R = flip->right->c_speed(flip->right,-FLIP_SPEED);
			break;
		case FLIP_RIGHT:
			flip->base_info.output_L = flip->left->c_speed(flip->left, FLIP_SPEED);
			flip->base_info.output_R = flip->right->c_speed(flip->right, FLIP_SPEED);
			break;
		case FLIP_LEFT:
			flip->base_info.output_L = flip->left->c_speed(flip->left,-FLIP_SPEED);
			flip->base_info.output_R = flip->right->c_speed(flip->right,-FLIP_SPEED);
			break;
		default:
			break;
	}
}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void Flip_Work_Normal(flip_t *flip)
{
	Flip_Pid_Calculating(flip);
	
	flip->left->base_info.motor_out =  flip->base_info.output_L;
	flip->right->base_info.motor_out =  flip->base_info.output_R;
}

/**
  * @Name    
  * @brief   
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void Flip_Work(flip_t *flip)
{
	if(flip->left->state.work_state&&flip->right->state.work_state)
		flip->work_sate = MOTOR_OK;
	else
		flip->work_sate = MOTOR_NO;
		
	Flip_Work_Normal(flip);
}











