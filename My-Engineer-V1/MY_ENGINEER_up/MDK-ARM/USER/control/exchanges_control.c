/**
  ******************************************************************************
  * @file           : exchanges_control.c/h
  * @brief          : 
  * @note           : 
  ******************************************************************************
  */

#include "exchanges_control.h"
#include "vision_protocol.h"
#include "car_state.h"
#include "control.h"
#include "stdbool.h"
#include "arm_math.h"

auto_via_motor_info_t 		via_motor;
auto_point_info_t 				point;
unit_cicle_point_info_t 	unit_cicle;
auto_base_info_t	auto_info=
{
	.point=&point,
	.via_motor=&via_motor,
	.unit_cicle=&unit_cicle,
};
auto_config_info_t auto_config=
{
	.start_exchange_flag = AUTO_NO,
	.target_OK = AUTO_NO,
	.via_process_done = AUTO_NO,
	.all_process_done = AUTO_NO,
	.key_dowm1 = AUTO_NO,
	.key_dowm2 = AUTO_NO,
};
auto_info_t Auto=
{
	.info=&auto_info,
	.config=&auto_config,
	.step = 1,
};

/**
  * @Name    Automatic_Exchange
  * @brief   自动兑换主控
  * @param   
  * @retval 
  * @author  ccb
  * @Date    
**/
float y_offset=0.f;
void Automatic_Exchange(auto_info_t *Auto)
{
	auto_config_info_t *config = Auto->config;
	auto_via_motor_info_t *info_motor = Auto->info->via_motor;
	
	if(config->start_exchange_flag)
	{
		Via_Point_Achieve(Auto);
		Final_Path_Achieve(Auto);
	}
	else
	{
		memset(info_motor,0.f,sizeof(&info_motor));
		config->detph_OK=AUTO_NO;
		config->target_OK = AUTO_NO;
	}
	
	if(config->via_process_done==AUTO_OK)
		config->key_dowm1 = AUTO_NO;
	
	if(config->all_process_done==AUTO_OK)
	{
		config->via_process_done = AUTO_NO;
		config->start_exchange_flag=AUTO_NO;
	}
}

/**
  * @Name    Manual_Exchange
  * @brief   手动兑换
  * @param   
  * @retval 
  * @author  ccb
  * @Date    
**/
void Manual_Exchange(void)
{
	car.mode_ctrl = car.mode_switch;
	car.step = 1;
}

/**
  * @Name    Via_Point_Create
  * @brief   中间点生成
  * @param   
  * @retval 
  * @author  ccb
  * @Date    
**/
void Via_Point_Create(auto_info_t *Auto)
{
	auto_point_info_t 				*info 	= 	Auto->info->point;
	unit_cicle_point_info_t 	*unit 	= 	Auto->info->unit_cicle;
	
	//预处理
	info->pitch+=90.f;
	info->pitch = d2r_f32(info->pitch);
	info->yaw = d2r_f32(info->yaw);
	
	//方向向量
	unit->m = arm_sin_f32(info->pitch)*arm_cos_f32(info->yaw);
	unit->n = arm_sin_f32(info->pitch)*arm_sin_f32(info->yaw);
	unit->p = arm_cos_f32(info->pitch);
	
//	arm_sqrt_f32(unit->m*unit->m+unit->n*unit->n+unit->p*unit->p,&unit->norm);
	unit->norm = 1.f;
	
	//单位方向向量
	unit->x = unit->m/unit->norm;
	unit->y = unit->n/unit->norm;
	unit->z = unit->p/unit->norm;
	
	//在步长VIA_POINT_STEP，方向unit->x/y/z上生成通过点
	info->x_via = info->x_end+unit->x*VIA_POINT_STEP;
	info->y_via = info->y_end+unit->y*VIA_POINT_STEP;
	info->z_via = info->z_end+unit->z*VIA_POINT_STEP;
	
}

/**
  * @Name    Via_Point_Check
  * @brief   中间点干涉判断
  * @param   
  * @retval 
  * @author  ccb
  * @Date    
**/
float car_d0 = 0;
float link_d = 0;
float link_L = 0;
void Via_Point_Check(auto_info_t *Auto)
{
	auto_config_info_t 		*config 		= 	Auto->config;
	auto_point_info_t 		*info 			= 	Auto->info->point;
	auto_via_motor_info_t	*via_motor	=		Auto->info->via_motor;
	
	//深度在通过点主控中判断
	if(config->detph_OK==AUTO_OK)
	{
		//通过点转电机目标值判断是否越界
		via_motor->x = ((vision_rx_info.x_ore-info->x_via-FRONT_X_OFFSET)-(car_d0+link_d+link_L*arm_cos_f32(info->yaw)))/TRANSVERSE_A2CM;
		via_motor->y = (info->y_via+FRONT_Y_OFFSET*arm_cos_f32(info->yaw))/PROTRACT_A2CM;
		via_motor->z = (info->z_via-FRONT_Z_OFFSET*arm_cos_f32(info->pitch-pi/2.f))/UPLIFT_A2CM+uplift.measure_angle;
		via_motor->pitch = -info->pitch*SUCKER_PITCH_D2A;
		via_motor->yaw = (180.f+info->yaw)*SUCKER_YAW_D2A;
		via_motor->roll = info->roll*SUCKER_ROLL_D2A;
		if(range(via_motor->x,TRANSVERSE_MIN,TRANSVERSE_MAX) && \
			 range(via_motor->y,PROTRACT_MIN,PROTRACT_MAX) &&\
			 range(via_motor->z,UPLIFT_MIN,UPLIFT_MAX)&&\
			 range(via_motor->pitch,SUCKER_PITCH_MIN,SUCKER_PITCH_MAX)&&\
			 range(via_motor->yaw,SUCKER_YAW_SIDE,SUCKER_YAW_MAX))
				config->target_OK = AUTO_OK;
		else 
			config->target_OK = AUTO_NO;
	}
	else
		return;
}

/**
  * @Name    Via_Point_Work
  * @brief   控电机到中间点
  * @param   
  * @retval 
  * @author  ccb
  * @Date    
**/
void Via_Point_Work(auto_info_t *Auto)
{
	auto_config_info_t 		*config 		= 	Auto->config;
	auto_via_motor_info_t	*via_motor	=		Auto->info->via_motor;
	
	//通过点目标值合适+按键按下=控电机到目标点
	if(config->key_dowm1==AUTO_OK)
	{
		switch(config->via_process_done)
		{
			case AUTO_OK:
				Auto->step = 1;
				break;
			
			default:
				switch(Auto->step)
				{
					case 1:
//						uplift.target = via_motor->z;
//						if(distance(uplift.measure_angle,uplift.target)<40000&&m_abs(uplift.measure_speed)<500)
//							Auto->step ++;
					uplift.target = UPLIFT_INTERFERE;
					if(UPLIFT_INTERFERE_OK)
						Auto->step ++;
						break;
					case 2:
//						transverse.base_info.target = 
						break;
					case 3:
						break;
					case 4:
						break;
					case 5:
						break;
					case 6:
						break;
					default:
						break;
				}
				break;		
		}
		if(distance(uplift.measure_angle,uplift.target)<40000&&m_abs(uplift.measure_speed)<500)
		{
			transverse.base_info.target = via_motor->x;
			protract.base_info.target = via_motor->y;

			if(distance(transverse.base_info.measure_angle,transverse.base_info.target)<1000&&\
				 m_abs(transverse.base_info.measure_speed)<10&&\
				 distance(protract.base_info.measure_angle,protract.base_info.target)<1000&&\
				 m_abs(protract.base_info.measure_speed)<10)
				config->via_process_done = AUTO_OK;
		}
	}
}

/**
  * @Name    Via_Point_Achieve
  * @brief   中间点实现，包络以上生成，检查，控制三个中间点函数
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void Via_Point_Achieve(auto_info_t *Auto)
{
	auto_config_info_t 	*config = Auto->config;
	auto_point_info_t 	*info 	= Auto->info->point;
	
	if(config->via_process_done==AUTO_NO)
	{
		if(config->target_OK==AUTO_NO)
		{
			/*车不能靠太近*/
			if(vision_rx_info.x_ore>=78.f)
				config->detph_OK = AUTO_OK;
			else
				config->detph_OK = AUTO_NO;
				
			info->x_end = 0.f;
			info->y_end = vision_rx_info.y_ore;
			info->z_end = vision_rx_info.z_ore;
			info->pitch = vision_rx_info.pitch_ore;
			info->yaw = vision_rx_info.yaw_ore;
			info->roll = vision_rx_info.roll_ore;
			Via_Point_Create(Auto);
			Via_Point_Check(Auto);
		}
		else 
			Via_Point_Work(Auto);
	}
	else
		return;
}

/**
  * @Name    Final_Path_Achieve
  * @brief   控电机到达末端点
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
float max;
void Final_Path_Achieve(auto_info_t *Auto)
{
	auto_config_info_t 			*config 	 = Auto->config;
	unit_cicle_point_info_t *unit 		 = Auto->info->unit_cicle;
	auto_via_motor_info_t		*via_motor =	Auto->info->via_motor;
	
	max=c_max2(unit->m,unit->n);
	max=c_max2(max,unit->p);
	
	if(config->via_process_done==AUTO_OK&&config->key_dowm2==AUTO_OK&&config->all_process_done==AUTO_NO)
	{
		if(max==unit->m)
		{
			transverse.base_info.target = via_motor->x+unit->m*VIA_POINT_STEP/TRANSVERSE_A2CM;
			protract.base_info.target = via_motor->y+((transverse.base_info.measure_angle-via_motor->x)/(unit->m*VIA_POINT_STEP/TRANSVERSE_A2CM))*(unit->n/PROTRACT_A2CM);
			uplift.target = via_motor->z+((transverse.base_info.measure_angle-via_motor->x)/(unit->m*VIA_POINT_STEP/TRANSVERSE_A2CM))*(unit->p/UPLIFT_A2CM);
		}
		else if(max==unit->n)
		{
			protract.base_info.target = via_motor->y+unit->n*VIA_POINT_STEP/PROTRACT_A2CM;
			transverse.base_info.target = via_motor->x+((protract.base_info.measure_angle-via_motor->y)/(unit->n*VIA_POINT_STEP/PROTRACT_A2CM))*(unit->m/TRANSVERSE_A2CM);
			uplift.target = via_motor->z+((protract.base_info.measure_angle-via_motor->y)/(unit->n*VIA_POINT_STEP/PROTRACT_A2CM))*(unit->p/UPLIFT_A2CM);
		}
		else
		{
			uplift.target = via_motor->z+unit->p*VIA_POINT_STEP/UPLIFT_A2CM;
			transverse.base_info.target = via_motor->x+((uplift.measure_angle-via_motor->z)/(unit->p*VIA_POINT_STEP/UPLIFT_A2CM))*(unit->m/TRANSVERSE_A2CM);
			protract.base_info.target = via_motor->y+((uplift.measure_angle-via_motor->z)/(unit->p*VIA_POINT_STEP/UPLIFT_A2CM))*(unit->n/PROTRACT_A2CM);
		}
		
		if(distance(transverse.base_info.measure_angle,transverse.base_info.target)<2500&&\
			 m_abs(transverse.base_info.measure_speed)<10&&\
			 distance(protract.base_info.measure_angle,protract.base_info.target)<1000&&\
			 m_abs(protract.base_info.measure_speed)<10&&\
			 distance(uplift.measure_angle,uplift.target)<1000&&\
			 m_abs(uplift.measure_speed)<10)//--------------------------------
			config->all_process_done = AUTO_OK;
	}
	else
		return;
}




















