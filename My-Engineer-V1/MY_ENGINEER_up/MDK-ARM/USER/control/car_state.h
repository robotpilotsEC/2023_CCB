/**
  ******************************************************************************
  * @file           : car_state.c\h
  * @brief          : 
  * @note           : 
	*                   
  ******************************************************************************
  */
#ifndef _CAR_STSTE_H
#define _CAR_STSTE_H

#include "config.h"
#include "stdbool.h"
#include "remote.h"

#define MODE_DONE									(car->mode_switch == car->mode_ctrl)
#define MODE_DONE_ALL							(car.mode_switch == car.mode_ctrl)
#define ORE_MODE									(car.mode_ctrl == LOB||car.mode_ctrl == SILVER_ORE||car.mode_ctrl == GOLDEN_ORE||car.mode_ctrl == EXCHANGE_ORE)
#define MODE_ORE									(car->mode_switch == LOB||car->mode_switch == SILVER_ORE||car->mode_switch == GOLDEN_ORE||car->mode_switch == EXCHANGE_ORE)
#define NO_ORE_MODE								(car.mode_ctrl == PLACE_ORE)
#define STEP_PRO_OK								1

#define KEY_CTRL 									(car->ctrl_mode == KEY_CAR)
#define	CAR_MODE_SWITCH_DONE			(car->mode_switch == car->mode_ctrl)
#define CTRL_DOWN	 								(rc.base_info->Ctrl.status  == down_K || rc.base_info->Ctrl.status  == short_press_K || rc.base_info->Ctrl.status  == long_press_K)
#define SHIFT_DOWN	 							(rc.base_info->Shift.status == down_K || rc.base_info->Shift.status == short_press_K || rc.base_info->Shift.status == long_press_K)
#define MOUSEL_DOWN	 							(rc.base_info->mouse_btn_l.status == down_K || rc.base_info->mouse_btn_l.status == short_press_K || rc.base_info->mouse_btn_l.status == long_press_K)
#define MOUSER_DOWN	 							(rc.base_info->mouse_btn_r.status == down_K || rc.base_info->mouse_btn_r.status == short_press_K || rc.base_info->mouse_btn_r.status == long_press_K)
#define MOUSER_ONLY	 							(MOUSER_DOWN&&!MOUSEL_DOWN)
#define MOUSEL_ONLY	 							(!MOUSER_DOWN&&MOUSEL_DOWN)
#define B_DOWN										(rc.base_info->B.status == down_K || rc.base_info->B.status == short_press_K || rc.base_info->B.status == long_press_K)
#define SHIFT_EXCGANGE	 					(SHIFT_DOWN&&(car->mode_switch == EXCHANGE_ORE||car->mode_switch == GOLDEN_ORE))
#define FDOS_MODE									(car->mode_switch == EXCHANGE_ORE||car->mode_switch == GOLDEN_ORE)
#define	FDOS_RELAX								(rc.base_info->X.status == relax_K&&rc.base_info->C.status == relax_K&&rc.base_info->V.status == relax_K&&rc.base_info->R.status == relax_K)

#define RC_CNT_MAX								(660.f)

#define UPLIFT_RC_DEL							(120.f)
#define TRANSVERSE_RC_DEL					(200.f)
#define PROTRACT_RC_DEL						(200.f)
#define YAW_RC_DEL								(200.f)
#define PITCH_RC_DEL							(200.f)
#define ROLL_RC_DEL								(150.f)
#define RESCUE_RC_DEL							(35.f)

#define UPLIFT_KEY_DEL						(120.f)
#define GBPITCH_KEY_DEL						(70.f)
#define GBYAW_KEY_DEL							(rc.info->mouse_x_K*3.f)
#define TRANSVERSE_KEY_DEL				(120.f)
#define PROTRACT_KEY_DEL					(120.f)
#define YAW_KEY_DEL								(100.f)
#define PITCH_KEY_DEL							(100.f)
#define ROLL_KEY_DEL							(100.f)

/*����ģʽ*/
typedef enum 
{
  RC_CAR,             //ң��������
  KEY_CAR,            //���̿���
  MANUAL_EX,          //�ֶҿ���
	
	MOVE_NORM = 0,			//�����ٶ�
	MOVE_SLOW,					//�����ƶ�

}car_ctrl_mode_e;


typedef enum 
{
  NORMAL = 0,					//����ģʽ
	LOB,								//�ս�ģʽ
	SAVE,								//��Ԯģʽ
	SILVER_ORE,					//����ģʽ
	GOLDEN_ORE,					//���ģʽ
	GROUND_ORE,					//�ؿ�ģʽ
	EXCHANGE_ORE,				//�һ�ģʽ  
	CCB_MODE,
}car_mode_e;


typedef enum 
{
  offline_CAR,        //����ģʽ
	init_CAR,           //��ʼ��ģʽ
}car_move_mode_e;

typedef struct 
{	
  uint8_t move_mode_commond;  //�ƶ�ģʽ����
  uint8_t move_mode_status;   //�ƶ�ģʽ״̬
	
  car_ctrl_mode_e 	ctrl_mode;          //����ģʽ
	car_mode_e 				mode_switch;        //ģʽת��
  car_mode_e 				mode_ctrl;          //ģʽ����
	uint8_t 					step;          			//���Ʋ���
	uint8_t 					step_lock;          //�ֶ���1��
	int8_t						ore_num;						//��ʯ����
	float							time_cnt;
}car_t;

extern car_t car;


/* ��ʼ�� */
void car_init(car_t *car);
void car_mode_init(car_t *car);
void car_ctrl(car_t *car);
void car_mode_commond_update(car_t *car);
void car_mode_enter(car_t *car);

void RC_s1_status_check(car_t *car);
void RC_status_scan(car_t *car);
void RC_s2_status_check(car_t *car);
void RC_thumbwheel_status_check(car_t *car);
void KEY_status_scan(car_t *car);


/* ���̰���״̬���� */
void KEY_mouse_l_status_check(car_t *car);
void KEY_mouse_r_status_check(car_t *car);
void KEY_Q_status_check(car_t *car);
void KEY_W_status_check(car_t *car);
void KEY_E_status_check(car_t *car);
void KEY_R_status_check(car_t *car);
void KEY_A_status_check(car_t *car);
void KEY_S_status_check(car_t *car);
void KEY_D_status_check(car_t *car);
void KEY_F_status_check(car_t *car);
void KEY_G_status_check(car_t *car);
void KEY_Z_status_check(car_t *car);
void KEY_X_status_check(car_t *car);
void KEY_C_status_check(car_t *car);
void KEY_V_status_check(car_t *car);
void KEY_B_status_check(car_t *car);
void KEY_Shift_status_check(car_t *car);
void KEY_Ctrl_status_check(car_t *car);


#endif
