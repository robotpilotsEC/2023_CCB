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


/*控制模式*/
typedef enum 
{
  RC_CAR,             //遥控器控制
  KEY_CAR,            //键盘控制
	MANUAL_EX,					//手兑控制
	
	MOVE_NORM = 0,			//正常速度
	MOVE_SLOW,					//缓慢移动

}car_ctrl_mode_e;


typedef enum 
{
  NORMAL = 0,					//常规模式
	LOB,								//空接模式
	SAVE,								//救援模式  (2
	SILVER_ORE,					//银矿模式
	GOLDEN_ORE,					//金矿模式
	GROUND_ORE,					//地矿模式
	EXCHANGE_ORE,				//兑换模式  
	CCB_MODE
}car_mode_e;


typedef enum 
{
  offline_CAR,        //离线模式
	init_CAR,           //初始化模式
}car_move_mode_e;

typedef struct 
{	
  uint8_t move_mode_commond;  //移动模式命令
  uint8_t move_mode_status;   //移动模式状态
	
  car_ctrl_mode_e 	ctrl_mode;          //控制模式
	car_mode_e 				mode_switch;        //模式转换
  car_mode_e 				mode_ctrl;          //模式控制
	uint8_t 					step;          			//控制步骤
}car_t;

extern car_t car;


/* 初始化 */
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


/* 键盘按键状态任务 */
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
