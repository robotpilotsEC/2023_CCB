/*
* 自定义控制器
*	
*	2023.6.13
*/
#include "custom_control.h"
#include "control.h"
#include "judge_protocol.h"

custom_base_info_t custom_info =
{
	.x_speed = 0.f,
	.y_speed = 0.f,
	.z_speed = 0.f,
	.pitch_speed = 0.f,
	.yaw_speed = 0.f,
	.roll_speed = 0.f,
};

custom_work_info_t work_info=
{
	.x_speed_max = 2000.f,
	.y_speed_max = 2000.f,
	.z_speed_max = 2000.f,
	.pitch_speed_max = 2000.f,
	.yaw_speed_max = 2000.f,
	.roll_speed_max = 2000.f,
	
	.x_state = DEV_NO,
	.y_state = DEV_NO,
	.z_state = DEV_NO,
	.pitch_state = DEV_NO,
	.yaw_state = DEV_NO,
	.roll_state = DEV_NO,
};

custom_t custom=
{
	.info = &custom_info,
	.work = &work_info,
	.state = DEV_NO,
};

void CustomSpeedCheck(custom_t *custom)
{
	if(range(uplift.measure_angle,UPLIFT_MIN,UPLIFT_MAX))
		custom->work->z_state = DEV_OK;
	else
		custom->work->z_state = DEV_NO;
	
	if(range(transverse.base_info.measure_angle,TRANSVERSE_MIN,TRANSVERSE_MAX))
		custom->work->x_state = DEV_OK;
	else
		custom->work->x_state = DEV_NO;
	
	if(range(protract.base_info.measure_angle,PROTRACT_MIN,PROTRACT_MAX))
		custom->work->y_state = DEV_OK;
	else
		custom->work->y_state = DEV_NO;
	
	if(range(sucker.base_info.measure_pitch_angle,SUCKER_PITCH_MIN,SUCKER_PITCH_MAX))
		custom->work->pitch_state = DEV_OK;
	else
		custom->work->pitch_state = DEV_NO;
	
	if(range(sucker.base_info.measure_yaw_angle,SUCKER_YAW_MIN,SUCKER_YAW_MAX))
		custom->work->yaw_state = DEV_OK;
	else
		custom->work->yaw_state = DEV_NO;
	
		custom->work->roll_state = DEV_OK;
}

void CustomSpeedUpdate(custom_t *custom)
{
	if(custom->work->x_state == DEV_OK)
		custom->info->x_speed = constrain(judge.custom_info.x_speed,-custom->work->x_speed_max,custom->work->x_speed_max);
	else
		custom->info->x_speed = 0;
	
	if(custom->work->y_state == DEV_OK)
		custom->info->y_speed = constrain(judge.custom_info.y_speed,-custom->work->y_speed_max,custom->work->y_speed_max);
	else
		custom->info->y_speed = 0;
	
	if(custom->work->z_state == DEV_OK)
		custom->info->z_speed = constrain(judge.custom_info.z_speed,-custom->work->z_speed_max,custom->work->z_speed_max);
	else
		custom->info->z_speed = 0;
	
	if(custom->work->pitch_state == DEV_OK)
		custom->info->pitch_speed = constrain(judge.custom_info.pitch_speed,-custom->work->pitch_speed_max,custom->work->pitch_speed_max);
	else
		custom->info->pitch_speed = 0;
	
	if(custom->work->yaw_state == DEV_OK)
		custom->info->yaw_speed = constrain(judge.custom_info.yaw_speed,-custom->work->yaw_speed_max,custom->work->yaw_speed_max);
	else
		custom->info->yaw_speed = 0;
	
	if(custom->work->roll_state == DEV_OK)
		custom->info->roll_speed = constrain(judge.custom_info.roll_speed,-custom->work->roll_speed_max,custom->work->roll_speed_max);
	else
		custom->info->roll_speed = 0;
}

void Custom2DeviceSpeed(custom_t *custom)
{
	
}
	

Dev_Work_State_e CustomControl(custom_t *custom)
{
	if(custom->state == DEV_NO)
		return DEV_NO;
	
	CustomSpeedCheck(custom);
	
	CustomSpeedUpdate(custom);
	
	Custom2DeviceSpeed(custom);
	
	return custom->state;
}






