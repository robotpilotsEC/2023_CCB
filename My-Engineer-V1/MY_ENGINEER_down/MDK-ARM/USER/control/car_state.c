/**
  ******************************************************************************
  * @file           : car_state.c/h
  * @brief          : 
  * @note           : 
  ******************************************************************************
  */
	
	
	
#include "car_state.h"
#include "control.h"
#include "communicate_protocol.h"

car_t car;

bool car_mode_change = false;           //����ģʽ�л���־

void car_init(car_t *car)
{
  car->move_mode_status = offline_CAR;
	car->move_mode_commond = offline_CAR;
  car->ctrl_mode = RC_CAR;
  car_mode_change = false;
	
	/* ����ģʽ��ʼ�� */
  car_mode_init(car);
}


void car_mode_init(car_t *car) 
{
	car->mode_switch = NORMAL;
}



void car_ctrl(car_t *car) 
{
  car_mode_change = false;
	
	car->mode_switch = communicate_rx_info.car_mode_switch;
	car->mode_ctrl = communicate_rx_info.car_mode_ctrl;
	
	/* ����ģʽ������� */
  car_mode_commond_update(car);
	
	/* ����ģʽ���� */
  car_mode_enter(car);
}



void car_mode_commond_update(car_t *car) 
{
	if(SYSTEM_RESET)
	{
		/* ң����s1״̬ȷ�� */
		RC_s1_status_check(car);
		
		/* ����ģʽ���� */
		switch (car->ctrl_mode) //�жϿ���ģʽ
		{
			/* ң���� */
			case RC_CAR:
				RC_status_scan(car);
				break;
			
			/* ���� */
			case KEY_CAR:
				KEY_status_scan(car);
				break;
			
			default :
				break;
		}
	}
}

void car_mode_enter(car_t *car)
{
//	if(SYSTEM_RESET&&KEY_CTRL)
//	{
//		switch (car->mode)
//		{
//			case NORMAL:
//				enter_normal_mode();
//				break;
//			case LOB:
//				enter_lob_mode();
//				break;
//			case SAVE:
//				enter_save_mode();
//				break;
//			case BLOCK:
//				enter_block_mode();
//				break;
//			case BARRIER:
//				enter_barrier_mode();
//				break;
//			case SILVER_ORE:
//				enter_silverore_mode();
//				break;
//			case GOLDEN_ORE:
//				enter_goldenore_mode();
//				break;
//			case GROUND_ORE:
//				enter_ground_mode();
//				break;
//			case EXCHANGE_ORE:
//				enter_exchange_mode();
//				break;
//			default:
//				break;
//		}
//	}
}


  void RC_s1_status_check(car_t *car)
{//ң����s1����״̬ȷ��
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
{//ң��������ɨ��
	/* ң����s2״̬ȷ�� */
  RC_s2_status_check(car);
	
	/* ң������ť״̬ȷ�� */
  RC_thumbwheel_status_check(car);
}



void RC_s2_status_check(car_t *car)
{//ң����s2״̬ȷ��
  switch(rc.base_info->s2.status)
  {
    case up_R:
      break;
    case mid_R:
      break;
    case down_R:
      break;
    default:
      break;
  }
}

/**
  * @brief  ң������ť״̬ȷ��
  */
void RC_thumbwheel_status_check(car_t *car)
{
  switch(rc.base_info->thumbwheel.status)
  {
    case up_R:
      break;
    case mid_R:
      break;
    case down_R:
      break;
    default:
      break;
  }
}


/** 
  * @brief  ���̰���ɨ��
  * @note   ����������״̬����
  */
void KEY_status_scan(car_t *car)
{
  KEY_mouse_l_status_check(car);
  KEY_mouse_r_status_check(car);
  KEY_Q_status_check(car);
  KEY_W_status_check(car);
  KEY_E_status_check(car);
  KEY_R_status_check(car);
  KEY_A_status_check(car);
  KEY_S_status_check(car);
  KEY_D_status_check(car);
  KEY_F_status_check(car);
  KEY_G_status_check(car);
  KEY_Z_status_check(car);
  KEY_X_status_check(car);
  KEY_C_status_check(car);
  KEY_V_status_check(car);
  KEY_B_status_check(car);
  KEY_Shift_status_check(car);
  KEY_Ctrl_status_check(car);
}

void KEY_mouse_l_status_check(car_t *car)
{
  switch(rc.base_info->mouse_btn_l.status)
  {
    case down_K:
      break;
    case up_K:
      break;
		case relax_K:
      break;
    case short_press_K:
      break;
    case long_press_K:
      break;
    default:
      break;
  }
}

void KEY_mouse_r_status_check(car_t *car)
{
  switch(rc.base_info->mouse_btn_r.status)
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

void KEY_Q_status_check(car_t *car)
{
  switch(rc.base_info->Q.status)
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

void KEY_W_status_check(car_t *car)
{
  switch(rc.base_info->W.status)
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

void KEY_E_status_check(car_t *car)
{
  switch(rc.base_info->E.status)
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

void KEY_R_status_check(car_t *car)
{
  switch(rc.base_info->R.status)
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

void KEY_A_status_check(car_t *car)
{
  switch(rc.base_info->A.status)
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

void KEY_S_status_check(car_t *car)
{
  switch(rc.base_info->S.status)
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

void KEY_D_status_check(car_t *car)
{
  switch(rc.base_info->D.status)
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

void KEY_F_status_check(car_t *car)
{
  switch(rc.base_info->F.status)
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

void KEY_G_status_check(car_t *car)
{
  switch(rc.base_info->G.status)
  {
    case down_K:
			if(SHIFT_DOWN)
			{
				chassis.work_info.config.spin_flag = 1;
				chassis.work_info.config.lock_flag = 0;
			}
      break;
    case up_K:
				chassis.work_info.config.spin_flag = 0;
      break;
    case short_press_K:
			if(SHIFT_DOWN)
				chassis.work_info.config.spin_flag = 1;
      break;
    case long_press_K:
			if(SHIFT_DOWN)
				chassis.work_info.config.spin_flag = 1;
      break;
		case relax_K:
    default:
      break;
  }
}

void KEY_Z_status_check(car_t *car)
{
  switch(rc.base_info->Z.status)
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

void KEY_X_status_check(car_t *car)
{
  switch(rc.base_info->X.status)
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

void KEY_C_status_check(car_t *car)
{
  switch(rc.base_info->C.status)
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

void KEY_V_status_check(car_t *car)
{
  switch(rc.base_info->V.status)
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

void KEY_B_status_check(car_t *car)
{
  switch(rc.base_info->B.status)
  {
    case down_K:
			if(!SHIFT_DOWN)
				chassis.work_info.config.lock_flag = 1;
      break;
    case up_K:
//			if(car->mode_switch != EXCHANGE_ORE)
				chassis.work_info.config.lock_flag = 0;
      break;
    case short_press_K:
			if(!SHIFT_DOWN)
				chassis.work_info.config.lock_flag = 1;
      break;
    case long_press_K:
			if(!SHIFT_DOWN)
				chassis.work_info.config.lock_flag = 1;
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
			if(!G_DOWN)
				chassis.work_info.config.lock_flag = 1;
      break;
    case up_K:
				chassis.work_info.config.lock_flag = 0;
      break;
    case short_press_K:
			if(!G_DOWN)
				chassis.work_info.config.lock_flag = 1;
      break;
    case long_press_K:
			if(!G_DOWN)
				chassis.work_info.config.lock_flag = 1;
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


