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

/*控制模式*/
typedef enum 
{
  RC_CAR,             //遥控器控制
  KEY_CAR,            //键盘控制
  MANUAL_EX,          //手兑控制
	
	MOVE_NORM = 0,			//正常速度
	MOVE_SLOW,					//缓慢移动

}car_ctrl_mode_e;


typedef enum 
{
  NORMAL = 0,					//常规模式
	LOB,								//空接模式
	SAVE,								//救援模式
	SILVER_ORE,					//银矿模式
	GOLDEN_ORE,					//金矿模式
	GROUND_ORE,					//地矿模式
	EXCHANGE_ORE,				//兑换模式  
	CCB_MODE,
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
	uint8_t 					step_lock;          //手动加1锁
	int8_t						ore_num;						//矿石数量
	float							time_cnt;
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
