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

#include "stm32f4xx_hal.h"
#include "stdbool.h"
#include "remote.h"


#define KEY_CTRL 									(car->ctrl_mode == KEY_CAR)
#define	CAR_MODE_SWITCH_DONE			(car->mode_switch == car->mode_ctrl)
#define CTRL_DOWN	 								(rc.base_info->Ctrl.status  == down_K || rc.base_info->Ctrl.status  == short_press_K || rc.base_info->Ctrl.status  == long_press_K)
#define SHIFT_DOWN	 							(rc.base_info->Shift.status == down_K || rc.base_info->Shift.status == short_press_K || rc.base_info->Shift.status == long_press_K)
#define MOUSEL_DOWN	 							(rc.base_info->mouse_btn_l.status == down_K || rc.base_info->mouse_btn_l.status == short_press_K || rc.base_info->mouse_btn_l.status == long_press_K)
#define MOUSER_DOWN	 							(rc.base_info->mouse_btn_r.status == down_K || rc.base_info->mouse_btn_r.status == short_press_K || rc.base_info->mouse_btn_r.status == long_press_K)
#define UPLIFT_KEY_DEL						(70.f)
#define TRANSVERS_KEY_DEL					(50.f)
#define SHIFT_EXCGANGE	 					(SHIFT_DOWN&&car->mode_switch == EXCHANGE_ORE)
#define FDOS_MODE									(car->mode_switch == EXCHANGE_ORE||car->mode_switch == GOLDEN_ORE)


/*����ģʽ*/
typedef enum 
{
  RC_CAR,             //ң��������
  KEY_CAR,            //���̿���
	MANUAL_EX,					//�ֶҿ���
	
	MOVE_NORM = 0,			//�����ٶ�
	MOVE_SLOW,					//�����ƶ�

}car_ctrl_mode_e;


typedef enum 
{
  NORMAL = 0,					//����ģʽ
	LOB,								//�ս�ģʽ
	SAVE,								//��Ԯģʽ  (2
	SILVER_ORE,					//����ģʽ
	GOLDEN_ORE,					//���ģʽ
	GROUND_ORE,					//�ؿ�ģʽ
	EXCHANGE_ORE,				//�һ�ģʽ  
	CCB_MODE
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
