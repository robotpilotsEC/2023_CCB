/**
  ******************************************************************************
  * @file           : exchanges_control.c/h
  * @brief          : 
  * @note           : 
  ******************************************************************************
  */
#ifndef EXCHANGES_CONTROL_H
#define EXCHANGES_CONTROL_H

#include "config.h"

#define	VIA_POINT_STEP				(15.f)
#define	FRONT_X_OFFSET				(56.f)
#define	FRONT_Y_OFFSET				(7.f)
#define	FRONT_Z_OFFSET				(10.f)

typedef enum	CAR_INIT_CONFIG
{
	AUTO_NO=0,
	AUTO_OK,
	AUTO_FRONT,
}Car_Init_Config_e;

typedef	struct	UNIT_VIA_POINT_INFO
{
	//方向向量
	float			m;
	float			n;
	float			p;
	//步进
	float			x;
	float			y;
	float			z;
	//模长
	float			norm;
}unit_cicle_point_info_t;

typedef	struct	AUTO_VIA_POINT_INFO
{
	//毫米通过点目标点存放
	float			x_end;
	float			y_end;
	float			z_end;
	float			x_via;
	float			y_via;
	float			z_via;
	float			pitch;
	float			yaw;
	float			roll;
}auto_point_info_t;

typedef	struct	AUTO_VIA_MOTOR_INFO
{
	//电机角度目标值存放
	float			x;
	float			y;
	float			z;
	float			pitch;
	float			yaw;
	float			roll;
}auto_via_motor_info_t;

typedef	struct	AUTO_BASE_INFO
{
	unit_cicle_point_info_t 	*unit_cicle;
	auto_point_info_t 				*point;
	auto_via_motor_info_t 		*via_motor;
	
}auto_base_info_t;

typedef	struct	AUTO_CONFIG_INFO
{
	Car_Init_Config_e					start_exchange_flag;
	Car_Init_Config_e 				target_OK;
	Car_Init_Config_e					via_process_done;
	Car_Init_Config_e					all_process_done;
	Car_Init_Config_e					detph_OK;
	Car_Init_Config_e 				key_dowm1;
	Car_Init_Config_e 				key_dowm2;
	
}auto_config_info_t;

typedef	struct	AUTO_INFO
{
	auto_config_info_t 				*config;
	auto_base_info_t					*info;
	uint8_t										step;
}auto_info_t;

extern auto_info_t Auto;

void Automatic_Exchange(auto_info_t *Auto);
void Manual_Exchange(void);
void Via_Point_Create(auto_info_t *Auto);
void Via_Point_Check(auto_info_t *Auto);
void Via_Point_Work(auto_info_t *Auto);
void Via_Point_Achieve(auto_info_t *Auto);
void Final_Path_Achieve(auto_info_t *Auto);






#endif


