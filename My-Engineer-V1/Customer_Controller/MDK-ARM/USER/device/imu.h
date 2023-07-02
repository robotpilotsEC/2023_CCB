#ifndef _imu_H
#define _imu_H

#include "stm32f4xx_hal.h"

typedef struct{
	float lowpass_factor;
}imu_lowpass_factor_t;

typedef struct{
	uint8_t		init_flag;
	uint8_t offline_cnt;
	uint8_t offline_max_cnt;
}imu_line_info_t;

typedef struct {
/*  ----------------------滤波前----------------------------------*/
	short rate_x;										//陀螺仪x轴速度
	short rate_y;										//陀螺仪y轴速度
	short rate_z;										//陀螺仪z轴速度
	short acc_x;										//陀螺仪x轴加速度
	short acc_y;										//陀螺仪y轴加速度
	short acc_z;										//陀螺仪z轴加速度
/*  ----------------------滤波后----------------------------------*/
	float rate_x_pass;							//陀螺仪x轴速度
	float rate_y_pass;							//陀螺仪y轴速度
	float rate_z_pass;							//陀螺仪z轴速度
	float acc_x_pass;								//陀螺仪x轴加速度
	float acc_y_pass;								//陀螺仪y轴加速度
	float acc_z_pass;								//陀螺仪z轴加速度
	
	
	float acc_x_G;								//陀螺仪x轴无重力加速度
	float acc_y_G;								//陀螺仪y轴无重力加速度
	float acc_z_G;								//陀螺仪z轴无重力加速度
/*  ----------------------角度----------------------------------*/
	float pitch;										//pitch
	float yaw;											//yaw
	float roll;											//roll
/*  ----------------------积分后----------------------------------*/
	float z_offset;
	float z_offset_pass;
	
	float speed_x;									//陀螺仪x轴线速度
	float speed_y;									//陀螺仪y轴线速度
	float speed_z;									//陀螺仪z轴线速度
	float speed_x_pass;							//陀螺仪x轴线速度
	float speed_y_pass;							//陀螺仪y轴线速度
	float speed_z_pass;							//陀螺仪z轴线速度
	
} imu_sensor_all_info_t;

typedef struct imu_sensor_total_struct
{
	imu_line_info_t 				*config;
	imu_lowpass_factor_t 		*factor;
	imu_sensor_all_info_t 	*info;
	
	void										(*update)(struct imu_sensor_total_struct *self);
}imu_t;

extern imu_t imu;

void imu_info_update_cal(imu_t *imu);
void Imu_Update(imu_t *imu);

#endif
