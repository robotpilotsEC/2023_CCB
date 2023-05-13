/**
  ******************************************************************************
  * @file           : car_state.c/h
  * @brief          : 
  * @note           : 
  ******************************************************************************
  */
	
	
	
#include "car_state.h"
#include "enter_mode_control.h"
#include "control.h"
#include "communicate_protocol.h"

car_t car;

void car_init(car_t *car)
{
  car->move_mode_status = offline_CAR;
	car->move_mode_commond = offline_CAR;
  car->ctrl_mode = RC_CAR;
	car->step = 1;
	car->step_lock = 0;
	car->ore_num = 0;
	
	/* 整车模式初始化 */
  car_mode_init(car);
}


void car_mode_init(car_t *car) 
{
	car->mode_switch = NORMAL;
}



void car_ctrl(car_t *car) 
{
	/* 整车命令模式更新 */
  car_mode_commond_update(car);
	
	communicate_tx_info.car_mode_switch = car->mode_switch;
	
	/* 整车模式更新 */
  car_mode_enter(car);
	
	communicate_tx_info.car_mode_ctrl = car->mode_ctrl;
}



void car_mode_commond_update(car_t *car) 
{
	if(SYSTEM_RESET)
	{
		/* 遥控器s1状态确认 */
		RC_s1_status_check(car);
		
		/* 控制模式更新 */
		switch (car->ctrl_mode) //判断控制模式
		{
			/* 遥控器 */
			case RC_CAR:
				RC_thumbwheel_status_check(car);
				break;
			
			/* 键盘 */
			case KEY_CAR:
				RC_status_scan(car);
				KEY_status_scan(car);
				break;
			
			case MANUAL_EX:
				break;
			
			default :
				break;
		}
	}
}

//整车状态和模式切换的接口函数
uint32_t switch_time_cnt;
void car_mode_enter(car_t *car)
{
	if(SYSTEM_RESET&&KEY_CTRL)
	{
		switch (car->mode_switch)
		{
			case NORMAL:
				enter_normal_mode();
				break;
			case LOB:
				enter_lob_mode();
				break;
			case SAVE:
				enter_save_mode();
				break;
			case SILVER_ORE:
				enter_silverore_mode();
				break;
			case GOLDEN_ORE:
				enter_goldenore_mode();
				break;
//			case GROUND_ORE:
//				enter_ground_mode();
//				break;
			case EXCHANGE_ORE:
				enter_exchange_mode();
				break;
			default:
				break;
		}
	}
	
	if(car->ore_num>=3)
		car->ore_num = 3;
	else if(car->ore_num<0)
		car->ore_num = 0;
}


void RC_s1_status_check(car_t *car)
{//遥控器s1拨杆状态确认
  switch(rc.base_info->s1.status)
  {
    case up_R:
      car->ctrl_mode = KEY_CAR;
      break;
    case mid_R:
      car->ctrl_mode = RC_CAR;
      break;
    case down_R:
      car->ctrl_mode = MANUAL_EX;
      break;
    default:
      break;
  }
}


void RC_status_scan(car_t *car)
{//遥控器按键扫描
	/* 遥控器s2状态确认 */
  RC_s2_status_check(car);
	
	/* 遥控器旋钮状态确认 */
  RC_thumbwheel_status_check(car);
}



void RC_s2_status_check(car_t *car)
{//遥控器s2状态确认
  switch(rc.base_info->s2.value)
  {
    case 1:
			uplift.target += (int16_t)rc.base_info->ch3 / RC_CNT_MAX * UPLIFT_RC_DEL;
			protract.base_info.target += (int16_t)rc.base_info->ch0 / RC_CNT_MAX * PROTRACT_RC_DEL;
			transverse.base_info.target += (int16_t)rc.base_info->ch1 / RC_CNT_MAX * TRANSVERSE_RC_DEL;
      break;
    case 2:
			if(rc.base_info->ch3 > rc.base_info->ch2)
				flip.mode = FLIP_UP;
			else if(rc.base_info->ch3 < rc.base_info->ch2)
				flip.mode = FLIP_DOWM;
			
			if(rc.base_info->ch1 > rc.base_info->ch0)
				flip.mode = FLIP_LEFT;
			else if(rc.base_info->ch1 < rc.base_info->ch0)
				flip.mode = FLIP_RIGHT;
			
			if(rc.base_info->ch0 == 0 && rc.base_info->ch1 == 0 && \
				 rc.base_info->ch2 == 0 && rc.base_info->ch3 == 0)			
				flip.mode = FLIP_OFF;
			
      break;
    case 3:
			sucker.base_info.target_pitch += (int16_t)rc.base_info->ch3 / RC_CNT_MAX * PITCH_RC_DEL;
			sucker.base_info.target_yaw -= (int16_t)rc.base_info->ch0 / RC_CNT_MAX * YAW_RC_DEL;
			sucker.base_info.target_roll += (int16_t)rc.base_info->ch2 / RC_CNT_MAX * ROLL_RC_DEL;
      break;
    default:
      break;
  }
}

/**
  * @brief  遥控器旋钮状态确认
  */
void RC_thumbwheel_status_check(car_t *car)
{
	switch(car->ctrl_mode)
	{
		case KEY_CAR:
			switch(rc.base_info->thumbwheel.status)
			{
				case up_R:
					pneumatic.pneu_state = ON;
					break;
				case mid_R:
					break;
				case down_R:
					pneumatic.pneu_state = OFF;
					break;
				default:
					break;
			}
			break;
		case RC_CAR:
			if(rc.base_info->thumbwheel.value > 10)
				rescue.target += RESCUE_RC_DEL;
			else if(rc.base_info->thumbwheel.value <= -10)
				rescue.target -= RESCUE_RC_DEL;
			break;
		default:
			break;
	}
}


/** 
  * @brief  键盘按键扫描
  * @note   各个按键的状态任务
  */
void KEY_status_scan(car_t *car)
{
	
	KEY_W_status_check(car);
	KEY_A_status_check(car);
	KEY_S_status_check(car);
	KEY_D_status_check(car);
	KEY_Shift_status_check(car);
	KEY_Ctrl_status_check(car);
	KEY_E_status_check(car);
	KEY_G_status_check(car);
	KEY_Q_status_check(car);
	KEY_B_status_check(car);
	KEY_R_status_check(car);
	KEY_X_status_check(car);
	KEY_F_status_check(car);
	KEY_C_status_check(car);
	KEY_V_status_check(car);
	KEY_mouse_l_status_check(car);
	KEY_mouse_r_status_check(car);
	KEY_Z_status_check(car);
}


void KEY_Q_status_check(car_t *car)
{
  switch(rc.base_info->Q.status)
  {
    case down_K:
			/*************************
			*	Ctrl+Q = 空接
			*	Q = 横移
			*************************/
			if(CTRL_DOWN)
			{
				car->mode_switch = LOB;
				car->mode_ctrl = CCB_MODE;
				car->step = 1;
				car->step_lock = 0;
			}
			else if(!CTRL_DOWN&&MODE_ORE)
				protract.base_info.target -= PROTRACT_KEY_DEL;
			else
				break;
			
      break;
    case up_K:
      break;
    case short_press_K:
			
			if(!CTRL_DOWN&&MODE_ORE)
				protract.base_info.target -= PROTRACT_KEY_DEL;
			else
				break;
			
      break;
    case long_press_K:
			
			if(!CTRL_DOWN&&MODE_ORE)
				protract.base_info.target -= PROTRACT_KEY_DEL;
			else
				break;
			
      break;
    default:
      break;
  }
}

void KEY_E_status_check(car_t *car)
{
  switch(rc.base_info->E.status)
  {
    case down_K:
			/*************************
			*	Ctrl+E = 大资源岛
			*	E = 横移
			*************************/
			if(CTRL_DOWN)
			{
				car->mode_switch = GOLDEN_ORE;
				car->mode_ctrl = CCB_MODE;
				car->step = 1;
				car->step_lock = 0;
			}
			else if(!CTRL_DOWN&&MODE_ORE)
				protract.base_info.target += PROTRACT_KEY_DEL;
			else
				break;
			
      break;
    case up_K:
      break;
    case short_press_K:
			
			if(!CTRL_DOWN&&MODE_ORE)
				protract.base_info.target += PROTRACT_KEY_DEL;
			else
				break;
			
      break;
    case long_press_K:
			
			if(!CTRL_DOWN&&MODE_ORE)
				protract.base_info.target += PROTRACT_KEY_DEL;
			else
				break;
			
      break;
    default:
      break;
  }
}

void KEY_R_status_check(car_t *car)
{
  switch(rc.base_info->R.status)
  {
    case down_K:
			if(MOUSEL_ONLY)
				uplift.target -= UPLIFT_KEY_DEL;
			else if(MOUSER_ONLY)
				uplift.target += UPLIFT_KEY_DEL;
			else
      break;
    case up_K:
      break;
    case short_press_K:
			if(MOUSEL_ONLY)
				uplift.target -= UPLIFT_KEY_DEL;
			else if(MOUSER_ONLY)
				uplift.target += UPLIFT_KEY_DEL;
			else
      break;
    case long_press_K:
			if(MOUSEL_ONLY)
				uplift.target -= UPLIFT_KEY_DEL;
			else if(MOUSER_ONLY)
				uplift.target += UPLIFT_KEY_DEL;
			else
      break;
    default:
      break;
  }
}

void KEY_F_status_check(car_t *car)
{
  switch(rc.base_info->F.status)
  {
    case down_K:
			/*************************
			*	F	=	Close Flip
			*	F+Ctrl	=	Flip Dowm
			*	F+Shift	=	Flip Up
			*	F+MouseR	=	Flip Right
			*	F+MouseL	=	Flip Left
			*************************/
			if(!CTRL_DOWN&&!SHIFT_DOWN&&!MOUSEL_DOWN&&!MOUSER_DOWN)
				flip.mode = FLIP_OFF;
			else if(CTRL_DOWN&&!SHIFT_DOWN&&!MOUSEL_DOWN&&!MOUSER_DOWN)
				flip.mode = FLIP_DOWM;
			else if(!CTRL_DOWN&&SHIFT_DOWN&&!MOUSEL_DOWN&&!MOUSER_DOWN)
				flip.mode = FLIP_UP;
			else if(!CTRL_DOWN&&!SHIFT_DOWN&&MOUSEL_DOWN&&!MOUSER_DOWN)
				flip.mode = FLIP_RIGHT;
			else if(!CTRL_DOWN&&!SHIFT_DOWN&&!MOUSEL_DOWN&&MOUSER_DOWN)
				flip.mode = FLIP_LEFT;
			else 
				break;
			
      break;
    case up_K:
				flip.mode = FLIP_OFF;
      break;
    case short_press_K:
			if(!CTRL_DOWN&&!SHIFT_DOWN&&!MOUSEL_DOWN&&!MOUSER_DOWN)
				flip.mode = FLIP_OFF;
			else if(CTRL_DOWN&&!SHIFT_DOWN&&!MOUSEL_DOWN&&!MOUSER_DOWN)
				flip.mode = FLIP_DOWM;
			else if(!CTRL_DOWN&&SHIFT_DOWN&&!MOUSEL_DOWN&&!MOUSER_DOWN)
				flip.mode = FLIP_UP;
			else if(!CTRL_DOWN&&!SHIFT_DOWN&&MOUSEL_DOWN&&!MOUSER_DOWN)
				flip.mode = FLIP_RIGHT;
			else if(!CTRL_DOWN&&!SHIFT_DOWN&&!MOUSEL_DOWN&&MOUSER_DOWN)
				flip.mode = FLIP_LEFT;
			else 
				break;
      break;
    case long_press_K:
			if(!CTRL_DOWN&&!SHIFT_DOWN&&!MOUSEL_DOWN&&!MOUSER_DOWN)
				flip.mode = FLIP_OFF;
			else if(CTRL_DOWN&&!SHIFT_DOWN&&!MOUSEL_DOWN&&!MOUSER_DOWN)
				flip.mode = FLIP_DOWM;
			else if(!CTRL_DOWN&&SHIFT_DOWN&&!MOUSEL_DOWN&&!MOUSER_DOWN)
				flip.mode = FLIP_UP;
			else if(!CTRL_DOWN&&!SHIFT_DOWN&&MOUSEL_DOWN&&!MOUSER_DOWN)
				flip.mode = FLIP_RIGHT;
			else if(!CTRL_DOWN&&!SHIFT_DOWN&&!MOUSEL_DOWN&&MOUSER_DOWN)
				flip.mode = FLIP_LEFT;
			else 
				break;
      break;
    default:
      break;
  }
}

void KEY_Z_status_check(car_t *car)
{
  switch(rc.base_info->Z.status)
  {
    case down_K:
			if(CTRL_DOWN&&!SHIFT_DOWN)
			{
				car->mode_switch = NORMAL;
				car->mode_ctrl = CCB_MODE;
				car->step = 1;
				car->step_lock = 1;
			}
			else
      break;
    case up_K:
			break;
    case short_press_K:
      break;
    case long_press_K:
      break;
    default:
      break;
  }
}

void KEY_X_status_check(car_t *car)
{
  switch(rc.base_info->X.status)
  {
    case down_K:
			if(CTRL_DOWN)
			{
				car->mode_switch = SAVE;
				car->mode_ctrl = CCB_MODE;
				car->step = 1;
				car->step_lock = 1;
			}
			else if(!CTRL_DOWN&&FDOS_MODE&&MOUSEL_ONLY)
				sucker.base_info.target_pitch -= PITCH_KEY_DEL;
			else if(!CTRL_DOWN&&FDOS_MODE&&MOUSER_ONLY)
				sucker.base_info.target_pitch += PITCH_KEY_DEL;
			else
      break;
    case up_K:
      break;
    case short_press_K:
			if(!CTRL_DOWN&&FDOS_MODE&&MOUSEL_ONLY)
				sucker.base_info.target_pitch -= PITCH_KEY_DEL;
			else if(!CTRL_DOWN&&FDOS_MODE&&MOUSER_ONLY)
				sucker.base_info.target_pitch += PITCH_KEY_DEL;
			else
      break;
    case long_press_K:
			if(!CTRL_DOWN&&FDOS_MODE&&MOUSEL_ONLY)
				sucker.base_info.target_pitch -= PITCH_KEY_DEL;
			else if(!CTRL_DOWN&&FDOS_MODE&&MOUSER_ONLY)
				sucker.base_info.target_pitch += PITCH_KEY_DEL;
			else
      break;
    default:
      break;
  }
}

void KEY_C_status_check(car_t *car)
{
  switch(rc.base_info->C.status)
  {
		/**/
    case down_K:
			if(CTRL_DOWN)
			{
				car->mode_switch = EXCHANGE_ORE;
				car->mode_ctrl = CCB_MODE;
				car->step = 1;
				car->step_lock = 1;
			}
			else if(!CTRL_DOWN&&FDOS_MODE&&MOUSEL_ONLY)
				sucker.base_info.target_yaw += YAW_KEY_DEL;
			else if(!CTRL_DOWN&&FDOS_MODE&&MOUSER_ONLY)
				sucker.base_info.target_yaw -= YAW_KEY_DEL;
    case up_K:
			
      break;
    case short_press_K:
			if(!CTRL_DOWN&&FDOS_MODE&&MOUSEL_ONLY)
				sucker.base_info.target_yaw += YAW_KEY_DEL;
			else if(!CTRL_DOWN&&FDOS_MODE&&MOUSER_ONLY)
				sucker.base_info.target_yaw -= YAW_KEY_DEL;
      break;
    case long_press_K:
			if(!CTRL_DOWN&&FDOS_MODE&&MOUSEL_ONLY)
				sucker.base_info.target_yaw += YAW_KEY_DEL;
			else if(!CTRL_DOWN&&FDOS_MODE&&MOUSER_ONLY)
				sucker.base_info.target_yaw -= YAW_KEY_DEL;
      break;
		case relax_K:
    default:
      break;
  }
}

void KEY_V_status_check(car_t *car)
{
  switch(rc.base_info->V.status)
  {
    case down_K:
			if(CTRL_DOWN)
			{
				car->mode_switch = SILVER_ORE;
				car->mode_ctrl = CCB_MODE;
				car->step = 1;
				car->step_lock = 1;
			}
			else if(!CTRL_DOWN&&MOUSEL_ONLY)
				sucker.base_info.target_roll -= ROLL_KEY_DEL;
			else if(!CTRL_DOWN&&MOUSER_ONLY)
				sucker.base_info.target_roll += ROLL_KEY_DEL;
			else
				
      break;
    case up_K:
      break;
    case short_press_K:
			if(!CTRL_DOWN&&MOUSEL_ONLY)
				sucker.base_info.target_roll -= ROLL_KEY_DEL;
			else if(!CTRL_DOWN&&MOUSER_ONLY)
				sucker.base_info.target_roll += ROLL_KEY_DEL;
			else
      break;
    case long_press_K:
			if(!CTRL_DOWN&&MOUSEL_ONLY)
				sucker.base_info.target_roll -= ROLL_KEY_DEL;
			else if(!CTRL_DOWN&&MOUSER_ONLY)
				sucker.base_info.target_roll += ROLL_KEY_DEL;
			else
      break;
		case relax_K:
    default:
      break;
  }
}

void KEY_G_status_check(car_t *car)
{
  switch(rc.base_info->G.status)
  {
    case down_K:
			if(CTRL_DOWN)
			{
				car->step = 1;
				car->step_lock = 1;
			}
      break;
    case up_K:
      break;
    case short_press_K:
      break;
    case long_press_K:
      break;
		case relax_K:
    default:
      break;
  }
}

void KEY_B_status_check(car_t *car)
{
  switch(rc.base_info->B.status)
  {
    case down_K:
				
      break;
    case up_K:
      break;
    case short_press_K:
      break;
    case long_press_K:
      break;
    default:
      break;
  }
}

void KEY_Shift_status_check(car_t *car)
{
  switch(rc.base_info->Shift.status)
  {
    case down_K:
      break;
    case up_K:
      break;
    case short_press_K:
      break;
    case long_press_K:
      break;
    default:
      break;
  }
}

void KEY_Ctrl_status_check(car_t *car)
{
  switch(rc.base_info->Ctrl.status)
  {
    case down_K:
      break;
    case up_K:
      break;
    case short_press_K:
      break;
    case long_press_K:
      break;
    default:
      break;
  }
}

uint8_t downL_flag=0;
uint8_t puneL_flag=0;
void KEY_mouse_l_status_check(car_t *car)
{
  switch(rc.base_info->mouse_btn_l.status)
  {
    case down_K:
			puneL_flag = 1;
		
			if(MODE_DONE)
				downL_flag=0;
			else
				downL_flag = 1;
			
      break;
    case up_K:
			if(puneL_flag&&SHIFT_DOWN)
			{
//				if(pneumatic.pneu_state == ON)
//					pneumatic.pneu_state = OFF;
//				else
					pneumatic.pneu_state = ON;
				puneL_flag = 0;
			}
			else
				puneL_flag = 0;
				
      break;
		case relax_K:
			if(downL_flag&&car->step_lock&&FDOS_RELAX)
				car->step++;	
			downL_flag = 0;
		
      break;
    case short_press_K:
			if(MODE_DONE)
				downL_flag=0;
			else
				downL_flag = 1;
      break;
    case long_press_K:
			if(MODE_DONE)
				downL_flag=0;
			else
				downL_flag = 1;
      break;
    default:
      break;
  }
}

uint8_t mouse_R_dow=0;
void KEY_mouse_r_status_check(car_t *car)
{
  switch(rc.base_info->mouse_btn_r.status)
  {
    case down_K:
			mouse_R_dow = 1;
      break;
    case up_K:
			if(mouse_R_dow&&SHIFT_DOWN)
			{
//				if(pneumatic.pneu_state == ON)
//					pneumatic.pneu_state = OFF;
//				else
					pneumatic.pneu_state = OFF;
				mouse_R_dow = 0;
			}
			else
				mouse_R_dow = 0;
				
      break;
    case short_press_K:
      break;
    case long_press_K:
      break;
    default:
      break;
  }
}


void KEY_W_status_check(car_t *car)
{
  switch(rc.base_info->W.status)
  {
    case down_K:
			if(SHIFT_EXCGANGE)
				transverse.base_info.target += TRANSVERSE_KEY_DEL;
      break;
    case up_K:
      break;
    case short_press_K:
			if(SHIFT_EXCGANGE)
				transverse.base_info.target += TRANSVERSE_KEY_DEL;
      break;
    case long_press_K:
			if(SHIFT_EXCGANGE)
				transverse.base_info.target += TRANSVERSE_KEY_DEL;
      break;
    default:
      break;
  }
}

void KEY_A_status_check(car_t *car)
{
  switch(rc.base_info->A.status)
  {
    case down_K:
			if(SHIFT_EXCGANGE)
				uplift.target += UPLIFT_KEY_DEL;
      break;
    case up_K:
      break;
    case short_press_K:
			if(SHIFT_EXCGANGE)
				uplift.target += UPLIFT_KEY_DEL;
      break;
    case long_press_K:
			if(SHIFT_EXCGANGE)
				uplift.target += UPLIFT_KEY_DEL;
      break;
    default:
      break;
  }
}

void KEY_S_status_check(car_t *car)
{
  switch(rc.base_info->S.status)
  {
    case down_K:
			if(SHIFT_EXCGANGE)
				transverse.base_info.target -= TRANSVERSE_KEY_DEL;
      break;
    case up_K:
      break;
    case short_press_K:
			if(SHIFT_EXCGANGE)
				transverse.base_info.target -= TRANSVERSE_KEY_DEL;
      break;
    case long_press_K:
			if(SHIFT_EXCGANGE)
				transverse.base_info.target -= TRANSVERSE_KEY_DEL;
      break;
    default:
      break;
  }
}

void KEY_D_status_check(car_t *car)
{
  switch(rc.base_info->D.status)
  {
    case down_K:
			if(SHIFT_EXCGANGE)
				uplift.target -= UPLIFT_KEY_DEL;
      break;
    case up_K:
      break;
    case short_press_K:
			if(SHIFT_EXCGANGE)
				uplift.target -= UPLIFT_KEY_DEL;
      break;
    case long_press_K:
			if(SHIFT_EXCGANGE)
				uplift.target -= UPLIFT_KEY_DEL;
      break;
    default:
      break;
  }
}


