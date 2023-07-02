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
/*  ----------------------�˲�ǰ----------------------------------*/
	short rate_x;										//������x���ٶ�
	short rate_y;										//������y���ٶ�
	short rate_z;										//������z���ٶ�
	short acc_x;										//������x����ٶ�
	short acc_y;										//������y����ٶ�
	short acc_z;										//������z����ٶ�
/*  ----------------------�˲���----------------------------------*/
	float rate_x_pass;							//������x���ٶ�
	float rate_y_pass;							//������y���ٶ�
	float rate_z_pass;							//������z���ٶ�
	float acc_x_pass;								//������x����ٶ�
	float acc_y_pass;								//������y����ٶ�
	float acc_z_pass;								//������z����ٶ�
	
	
	float acc_x_G;								//������x�����������ٶ�
	float acc_y_G;								//������y�����������ٶ�
	float acc_z_G;								//������z�����������ٶ�
/*  ----------------------�Ƕ�----------------------------------*/
	float pitch;										//pitch
	float yaw;											//yaw
	float roll;											//roll
/*  ----------------------���ֺ�----------------------------------*/
	float z_offset;
	float z_offset_pass;
	
	float speed_x;									//������x�����ٶ�
	float speed_y;									//������y�����ٶ�
	float speed_z;									//������z�����ٶ�
	float speed_x_pass;							//������x�����ٶ�
	float speed_y_pass;							//������y�����ٶ�
	float speed_z_pass;							//������z�����ٶ�
	
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
