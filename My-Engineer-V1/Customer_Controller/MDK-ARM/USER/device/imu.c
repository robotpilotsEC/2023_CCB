/**
  ******************************************************************************
  * @file           : imu.c
  * @brief          : 
  * @update         : 
  ******************************************************************************
  */
#include "imu.h"
#include "bmi.h"
#include "ave_filter.h"
#include "config.h"
#include "math_support.h"


imu_lowpass_factor_t factor_t = 
{
	.lowpass_factor = 0.3,
};

imu_line_info_t line_info = 
{
	.init_flag = DEV_OFFLINE,
	.offline_cnt = 0,
	.offline_max_cnt = 50,
};

imu_sensor_all_info_t imu_all_info =
{
	.pitch = 0,
	.yaw = 0,
	.roll = 0,
	.z_offset_pass = 0,
	.z_offset = 0,
	.rate_x = 0,
	.rate_y = 0,
	.rate_z = 0,
	.acc_x = 0,
	.acc_y = 0,
	.acc_z = 0,
	.rate_x_pass = 0,
	.rate_y_pass = 0,
	.rate_z_pass = 0,
	.acc_x_pass = 0,
	.acc_y_pass = 0,
	.acc_z_pass = 0,
	.speed_x_pass = 0,
	.speed_y_pass = 0,
	.speed_z_pass = 0,
};

imu_t imu =
{
	.config = &line_info,
	.factor = &factor_t,
	.info = &imu_all_info,
	
	.update = Imu_Update,
};

float xxxxxxxx;
float yyyyyyyy;
float zzzzzzzz;
float z_acc_offset = 16000.f;
float imu_death_line = 300.f;

void Imu_Update(imu_t *imu)
{
	imu_info_update_cal(imu);
}

float imu_pseed_K = 0.001f;

void imu_info_update_cal(imu_t *imu)
{
	imu_sensor_all_info_t *imu_info = imu->info;
	
	BMI_Get_RawData(&imu_info->rate_x, &imu_info->rate_y, &imu_info->rate_z,
									&imu_info->acc_x, &imu_info->acc_y, &imu_info->acc_z);
	imu_info->rate_z -= 3.f;
	imu_info->z_offset = imu_info->acc_z + z_acc_offset;
	
	/*  ----------------------µÍÍ¨ÂË²¨----------------------------------*/
	imu_info->rate_x_pass = lowpass_imu(imu->factor->lowpass_factor, imu_info->rate_x_pass, imu_info->rate_x);
	imu_info->rate_y_pass = lowpass_imu(imu->factor->lowpass_factor, imu_info->rate_y_pass, imu_info->rate_y);
	imu_info->rate_z_pass = lowpass_imu(imu->factor->lowpass_factor, imu_info->rate_z_pass, imu_info->rate_z);
	imu_info->acc_x_pass = lowpass_imu(imu->factor->lowpass_factor, imu_info->acc_x_pass, imu_info->acc_x);
	imu_info->acc_y_pass = lowpass_imu(imu->factor->lowpass_factor, imu_info->acc_y_pass, imu_info->acc_y);
	imu_info->acc_z_pass = lowpass_imu(imu->factor->lowpass_factor, imu_info->acc_z_pass, imu_info->acc_z);
	
	BMI_Get_EulerAngle(&imu_info->pitch,&imu_info->roll,&imu_info->yaw,\
										&imu_info->rate_x_pass,&imu_info->rate_y_pass,&imu_info->rate_z_pass,\
										&imu_info->acc_x_pass,&imu_info->acc_y_pass,&imu_info->acc_z_pass);
	BMI_Get_Acceleration(imu_info->pitch,imu_info->roll,imu_info->yaw,\
											imu_info->acc_x_pass,imu_info->acc_y_pass,imu_info->acc_z_pass,\
											&imu_info->acc_x_G,&imu_info->acc_y_G,&imu_info->acc_z_G);
	
//	imu_info->z_offset_pass = lowpass_imu(imu->factor->lowpass_factor, imu_info->z_offset, imu_info->z_offset_pass);

	
	if(abs(imu_info->acc_x) > imu_death_line)
		imu_info->speed_x += imu_pseed_K*imu_info->acc_x_G;
	if(abs(imu_info->acc_y) > imu_death_line)
		imu_info->speed_y += imu_pseed_K*imu_info->acc_y_G;
	if(abs(imu_info->z_offset) > imu_death_line)
		imu_info->speed_z += imu_pseed_K*imu_info->acc_z_G;
	
	imu_info->speed_x_pass = lowpass_imu(imu->factor->lowpass_factor, imu_info->speed_x_pass, imu_info->speed_x);
	imu_info->speed_y_pass = lowpass_imu(imu->factor->lowpass_factor, imu_info->speed_y_pass, imu_info->speed_y);
	imu_info->speed_z_pass = lowpass_imu(imu->factor->lowpass_factor, imu_info->speed_z_pass, imu_info->speed_z);

	xxxxxxxx = imu_info->speed_x_pass;
	yyyyyyyy = imu_info->speed_y_pass;
	zzzzzzzz = imu_info->speed_z_pass;
}

