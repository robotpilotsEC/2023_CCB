#include "imu.h"
#include "bmi.h"
#include "ave_filter.h"
#include "config.h"
#include "math_support.h"


ave_filter_t imu_yaw_dif_speed_ave_filter;
ave_filter_t imu_pitch_dif_speed_ave_filter;
ave_filter_t imu_roll_dif_speed_ave_filter;

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
	.yaw = 0,
	.pitch = 0,
	.roll = 0,
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
};

imu_t imu =
{
	.config = &line_info,
	.factor = &factor_t,
	.info = &imu_all_info,
	
	.update = Imu_Update,
};

short gyrox, gyroy, gyroz, gyro_x;
short accx, accy, accz;
short pitch___t;

void Imu_Update(imu_t *imu)
{
	imu_info_update_cal(imu);
}


void imu_info_update_cal(imu_t *imu)
{
	imu_sensor_all_info_t *imu_info = imu->info;
	
	BMI_Get_RawData(&imu_info->rate_x, &imu_info->rate_y, &imu_info->rate_z,
									&imu_info->acc_x, &imu_info->acc_y, &imu_info->acc_z);
	
	gyrox = imu_info->rate_x;
	gyro_x = imu_info->rate_x_pass;
	/*  ----------------------µÍÍ¨ÂË²¨----------------------------------*/
	imu_info->rate_x_pass = lowpass_imu(imu->factor->lowpass_factor, imu_info->rate_x_pass, imu_info->rate_x);
	imu_info->rate_y_pass = lowpass_imu(imu->factor->lowpass_factor, imu_info->rate_y_pass, imu_info->rate_y);
	imu_info->rate_z_pass = lowpass_imu(imu->factor->lowpass_factor, imu_info->rate_z_pass, imu_info->rate_z);
	imu_info->acc_x_pass = lowpass_imu(imu->factor->lowpass_factor, imu_info->acc_x_pass, imu_info->acc_x);
	imu_info->acc_y_pass = lowpass_imu(imu->factor->lowpass_factor, imu_info->acc_y_pass, imu_info->acc_y);
	imu_info->acc_z_pass = lowpass_imu(imu->factor->lowpass_factor, imu_info->acc_z_pass, imu_info->acc_z);

	/*  ----------------------½âËã½Ç¶È----------------------------------*/
	BMI_Get_EulerAngle(&imu_info->pitch,&imu_info->roll,&imu_info->yaw,\
										&imu_info->pitch_,&imu_info->roll_,&imu_info->yaw_,\
										&imu_info->rate_x_pass,&imu_info->rate_y_pass,&imu_info->rate_z_pass,\
										&imu_info->acc_x_pass,&imu_info->acc_y_pass,&imu_info->acc_z_pass);
	/*yaw*/
	imu_info->yaw_dif_speed = imu_info->yaw_ ;
	if(abs(imu_info->yaw_dif_speed) > 180)
	{
		if(imu_info->yaw_dif_speed > 0)
		{
			imu_info->yaw_dif_speed -= 360;
		}
		else if(imu_info->yaw_dif_speed <= 0)
		{
			imu_info->yaw_dif_speed -= -360;
		}
	}
	imu_info->yaw_dif_speed *= 1000.f;
	imu_info->yaw_dif_speed_ave = ave_fil_update(&imu_yaw_dif_speed_ave_filter,imu_info->yaw_dif_speed,3);
	imu_info->yaw_dif_last = imu_info->yaw_;
	/*pitch*/
	imu_info->pitch_dif_speed = imu_info->pitch_ ;
	if(abs(imu_info->pitch_dif_speed) > 180)
	{
		if(imu_info->pitch_dif_speed > 0)
		{
			imu_info->pitch_dif_speed -= 360;
		}
		else if(imu_info->pitch_dif_speed <= 0)
		{
			imu_info->pitch_dif_speed -= -360;
		}
	}
	imu_info->pitch_dif_speed *= 1000.f;
	imu_info->pitch_dif_speed_ave = ave_fil_update(&imu_pitch_dif_speed_ave_filter,imu_info->pitch_dif_speed,3);
	imu_info->pitch_dif_last = imu_info->pitch_;
	/*roll*/
	imu_info->roll_dif_speed = imu_info->roll_ ;
	if(abs(imu_info->roll_dif_speed) > 180)
	{
		if(imu_info->roll_dif_speed > 0)
		{
			imu_info->roll_dif_speed -= 360;
		}
		else if(imu_info->roll_dif_speed <= 0)
		{
			imu_info->roll_dif_speed -= -360;
		}
	}
	imu_info->roll_dif_speed *= 1000.f;
	imu_info->roll_dif_speed_ave = ave_fil_update(&imu_roll_dif_speed_ave_filter,imu_info->roll_dif_speed,3);
	imu_info->roll_dif_last = imu_info->roll_;
}

