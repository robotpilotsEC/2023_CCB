/**
  ******************************************************************************
  * @file           : my_judge.c\h
	* @author         : ccb
	* @date           : 
  * @brief          : 根据《RoboMaster_裁判系统串口协议附录 V1.3》编写
	                    针对机器人间交互数据
	* @history        : 
  ******************************************************************************
  */

/* 目录begin */

//第四层
//**********实时任务
//第三层
//**********绘制任务
//第二层
//**********获取图像数据帧
//********************获取直线数据帧
//********************获取矩形数据帧
//********************获取整圆数据帧
//********************获取椭圆数据帧
//********************获取圆弧数据帧
//********************获取浮点数数据帧
//********************获取整型数数据帧
//********************获取字符数据帧
//**********发送帧数据
//********************发送绘制一个图形帧数据
//********************发送绘制二个图形帧数据
//********************发送绘制五个图形帧数据
//********************发送绘制七个图形帧数据
//********************发送绘制字符帧数据
//第一层
//**********串口发送数据

/* 目录end */

#include "my_judge.h"
#include "crc.h"
#include "string.h"
#include "stdbool.h"
#include "arm_math.h"
#include "stdio.h"
#include "judge_protocol.h"
#include "exchanges_control.h"
#include "control.h"
#include "car_state.h"
//#include "cap_protocol.h"
//#include "judge.h"

/* 配置区 begin */
#define UI_huart huart6  //串口接口
#define send_frequency 30  //发送频率
/* 配置区 end */

extern UART_HandleTypeDef UI_huart;

client_info_t client_info = 
{
	.robot_id = 102,
	.client_id = 0x0166,
};
uint8_t client_tx_buf[128];

graphic_data_struct_t g1_data;
ext_client_custom_graphic_single_t g1;
/**************************************************第四层begin**************************************************/

/**
  * @brief  实时任务
  * @param  更新周期（ms）
  * @retval 
  */
void tick_task(uint16_t time)
{
	uint16_t cnt_max = 1000 / time / send_frequency;
	uint8_t task_num_max = 11;
	static uint16_t cnt = 0;
	static uint8_t task_num = 0;
	client_info_update();
	
	if(cnt >= cnt_max)
	{
		switch(task_num)
		{
			case 0:
				UI_send_char_1();
				break;
			case 1:
				UI_send_char_2();
				break;
			case 2:
				UI_send_char_3();
				break;
			case 3:
				UI_send_char_4();
				break;
			case 4:
				UI_send_char_5();
				break;
			case 5:
				UI_send_char_6();
				break;
			case 6:
				UI_send_char_7();
				break;
			case 7:
				UI_send_char_8();
				break;
			case 8:
				UI_send_int_1();
				break;
			case 9:
				UI_send_group1();
				break;
			case 10:
				UI_send_group2();
				break;
			default:
				break;
		}
		task_num++;
		task_num %= task_num_max;
		cnt = 0;
	}
	else 
	{
		cnt++;
	}
}

void client_info_update(void)
{
	client_info.robot_id = judge.game_robot_status.robot_id;
	client_info.client_id = judge.ids.client_engineer;
}

/**************************************************第四层end**************************************************/


/**************************************************第三层begin**************************************************/

/******************************绘制任务begin******************************/

/******************************绘制任务end******************************/

/**************************************************第三层end**************************************************/

/**************************************************第二层begin**************************************************/

/******************************获取图像数据帧begin******************************/

/**
  * @brief  获取直线数据帧
  * @param  
  * @retval 图形数据结构体
  */
graphic_data_struct_t draw_line(char *name,  //图形名
	             uint8_t operate_tpye,  //图形操作
               uint8_t layer,  //图层数，0~9
               uint8_t color,  //颜色
               uint16_t width,  //线条宽度
               uint16_t start_x,  //起点 x 坐标
               uint16_t start_y,  //起点 y 坐标
               uint16_t end_x,  //终点 x 坐标
               uint16_t end_y)  //终点 y 坐标
{
	graphic_data_struct_t data;
	
	memcpy(data.graphic_name, name, 3);
	data.operate_tpye = operate_tpye;
	data.graphic_tpye = 0;
	data.layer = layer;
	data.color = color;
	data.start_angle = 0;
	data.end_angle = 0;
	data.width = width;
	data.start_x = start_x;
	data.start_y = start_y;
	data.radius = 0;
	data.end_x = end_x;
	data.end_y = end_y;
	
	return data;
}

/**
  * @brief  获取矩形数据帧
  * @param  
  * @retval 图形数据结构体
  */
graphic_data_struct_t draw_rectangle(char *name,  //图形名
	             uint8_t operate_tpye,  //图形操作
               uint8_t layer,  //图层数，0~9
               uint8_t color,  //颜色DSFZa
               uint16_t width,  //线条宽度
               uint16_t start_x,  //起点 x 坐标
               uint16_t start_y,  //起点 y 坐标
               uint16_t end_x,  //对角顶点 x 坐标
               uint16_t end_y)  //对角顶点 y 坐标
{
	graphic_data_struct_t data;
	
	memcpy(data.graphic_name, name, 3);
	data.operate_tpye = operate_tpye;
	data.graphic_tpye = 1;
	data.layer = layer;
	data.color = color;
	data.start_angle = 0;
	data.end_angle = 0;
	data.width = width;
	data.start_x = start_x;
	data.start_y = start_y;
	data.radius = 0;
	data.end_x = end_x;
	data.end_y = end_y;
	
	return data;
}

/**
  * @brief  获取整圆数据帧
  * @param  
  * @retval 图形数据结构体
  */
graphic_data_struct_t draw_circle(char *name,  //图形名
	             uint8_t operate_tpye,  //图形操作
               uint8_t layer,  //图层数，0~9
               uint8_t color,  //颜色
               uint16_t width,  //线条宽度
               uint16_t ciclemid_x,  //圆心 x 坐标
               uint16_t ciclemid_y,  //圆心 y 坐标
               uint16_t radius)  //半径
{
	graphic_data_struct_t data;
	
	memcpy(data.graphic_name, name, 3);
	data.operate_tpye = operate_tpye;
	data.graphic_tpye = 2;
	data.layer = layer;
	data.color = color;
	data.start_angle = 0;
	data.end_angle = 0;
	data.width = width;
	data.start_x = ciclemid_x;
	data.start_y = ciclemid_y;
	data.radius = radius;
	data.end_x = 0;
	data.end_y = 0;
	
	return data;
}

/**
  * @brief  获取椭圆数据帧
  * @param  
  * @retval 图形数据结构体
  */
graphic_data_struct_t draw_ellipse(char *name,  //图形名
	             uint8_t operate_tpye,  //图形操作
               uint8_t layer,  //图层数，0~9
               uint8_t color,  //颜色
               uint16_t width,  //线条宽度
               uint16_t start_x,  //圆心 x 坐标
               uint16_t start_y,  //圆心 y 坐标
               uint16_t end_x,  //x 半轴长度
               uint16_t end_y)  //y 半轴长度
{
	graphic_data_struct_t data;
	
	memcpy(data.graphic_name, name, 3);
	data.operate_tpye = operate_tpye;
	data.graphic_tpye = 3;
	data.layer = layer;
	data.color = color;
	data.start_angle = 0;
	data.end_angle = 0;
	data.width = width;
	data.start_x = start_x;
	data.start_y = start_y;
	data.radius = 0;
	data.end_x = end_x;
	data.end_y = end_y;
	
	return data;
}

/**
  * @brief  获取圆弧数据帧
  * @param  
  * @retval 图形数据结构体
  */
graphic_data_struct_t draw_arc(char *name,  //图形名
	             uint8_t operate_tpye,  //图形操作
               uint8_t layer,  //图层数，0~9
               uint8_t color,  //颜色
               uint16_t start_angle,  //起始角度
               uint16_t end_angle,  //终止角度
               uint16_t width,  //线条宽度
               uint16_t circlemin_x,  //圆心 x 坐标
               uint16_t circlemin_y,  //圆心 y 坐标
               uint16_t end_x,  //x 半轴长度
               uint16_t end_y)  //y 半轴长度
{
	graphic_data_struct_t data;
	
	memcpy(data.graphic_name, name, 3);
	data.operate_tpye = operate_tpye;
	data.graphic_tpye = 4;
	data.layer = layer;
	data.color = color;
	data.start_angle = start_angle;
	data.end_angle = end_angle;
	data.width = width;
	data.start_x = circlemin_x;
	data.start_y = circlemin_y;
	data.radius = 0;
	data.end_x = end_x;
	data.end_y = end_y;
	
	return data;
}

/**
  * @brief  获取浮点数数据帧
  * @param  
  * @retval 图形数据结构体
  */
graphic_data_struct_t draw_float(char *name,  //图形名
	             uint8_t operate_tpye,  //图形操作
               uint8_t layer,  //图层数，0~9
               uint8_t color,  //颜色
               uint16_t size,  //字体大小
               uint16_t decimal,  //小数位有效个数
               uint16_t width,  //线条宽度
               uint16_t start_x,  //起点 x 坐标
               uint16_t start_y,  //起点 y 坐标
               int32_t num)  //乘以 1000 后，以 32 位整型数，int32_t
{
	graphic_data_struct_t data;
	
	memcpy(data.graphic_name, name, 3);
	data.operate_tpye = operate_tpye;
	data.graphic_tpye = 5;
	data.layer = layer;
	data.color = color;
	data.start_angle = size;
	data.end_angle = decimal;
	data.width = width;
	data.start_x = start_x;
	data.start_y = start_y;
	data.radius = num;
	data.end_x = num >> 10;
	data.end_y = num >> 21;
	
	return data;
}

/**
  * @brief  获取整型数数据帧
  * @param  
  * @retval 图形数据结构体
  */
graphic_data_struct_t draw_int(char *name,  //图形名
	             uint8_t operate_tpye,  //图形操作
               uint8_t layer,  //图层数，0~9
               uint8_t color,  //颜色
               uint16_t size,  //字体大小
               uint16_t width,  //线条宽度
               uint16_t start_x,  //起点 x 坐标
               uint16_t start_y,  //起点 y 坐标
               int32_t num)  //32 位整型数，int32_t
{
	graphic_data_struct_t data;
	
	memcpy(data.graphic_name, name, 3);
	data.operate_tpye = operate_tpye;
	data.graphic_tpye = 6;
	data.layer = layer;
	data.color = color;
	data.start_angle = size;
	data.end_angle = 0;
	data.width = width;
	data.start_x = start_x;
	data.start_y = start_y;
	data.radius = num;
	data.end_x = num >> 10;
	data.end_y = num >> 21;
	
	return data;
}

/**
  * @brief  获取字符数据帧
  * @param  
  * @retval 图形数据结构体
  */
graphic_data_struct_t draw_char(char *name,  //图形名
	             uint8_t operate_tpye,  //图形操作
               uint8_t layer,  //图层数，0~9
               uint8_t color,  //颜色
               uint16_t size,  //字体大小
               uint16_t length,  //字符长度
               uint16_t width,  //线条宽度
               uint16_t start_x,  //起点 x 坐标
               uint16_t start_y)  //起点 y 坐标
{
	graphic_data_struct_t data;
	
	memcpy(data.graphic_name, name, 3);
	data.operate_tpye = operate_tpye;
	data.graphic_tpye = 7;
	data.layer = layer;
	data.color = color;
	data.start_angle = size;
	data.end_angle = length;
	data.width = width;
	data.start_x = start_x;
	data.start_y = start_y;
	data.radius = 0;
	data.end_x = 0;
	data.end_y = 0;
	
	return data;
}

/******************************获取图像数据帧end******************************/


/******************************发送帧数据begin******************************/

/**
	* @brief  发送绘制一个图形帧数据
  * @param  
  * @retval 
  */
uint8_t client_send_single_graphic(ext_client_custom_graphic_single_t data)
{
	frame_t frame;
	ext_student_interactive_header_data_t data_header;
	
	/* 帧头 */
	frame.frame_header.SOF = 0xA5;
	frame.frame_header.data_length = LEN_ID_draw_one_graphic;
	frame.frame_header.seq = 0;
	memcpy(client_tx_buf, &frame.frame_header, 4);
	Append_CRC8_Check_Sum(client_tx_buf, 5);
	
	/* 命令码ID */
	frame.cmd_id = 0x301;
	memcpy(&client_tx_buf[5], (void*)&frame.cmd_id, 2);
	
	/* 数据段 */
	data_header.data_cmd_id = ID_draw_one_graphic;
	data_header.sender_ID = client_info.robot_id;
	data_header.receiver_ID = client_info.client_id;
	memcpy(&client_tx_buf[7], &data_header, 6);
	memcpy(&client_tx_buf[13], &data.grapic_data_struct, 15);
	
	/* 帧尾 */
	Append_CRC16_Check_Sum(client_tx_buf, 5 + 2 + LEN_ID_draw_one_graphic + 2);
	
	/* 发送 */
	return uart_send_data(client_tx_buf, 5 + 2 + LEN_ID_draw_one_graphic + 2);
}

/**
	* @brief  发送绘制二个图形帧数据
  * @param  
  * @retval 
  */
uint8_t client_send_double_graphic(ext_client_custom_graphic_double_t data)
{
	frame_t frame;
	ext_student_interactive_header_data_t data_header;
	
	/* 帧头 */
	frame.frame_header.SOF = 0xA5;
	frame.frame_header.data_length = LEN_ID_draw_two_graphic;
	frame.frame_header.seq = 0;
	memcpy(client_tx_buf, &frame.frame_header, 4);
	Append_CRC8_Check_Sum(client_tx_buf, 5);
	
	/* 命令码ID */
	frame.cmd_id = 0x301;
	memcpy(&client_tx_buf[5], (void*)&frame.cmd_id, 2);
	
	/* 数据段 */
	data_header.data_cmd_id = ID_draw_two_graphic;
	data_header.sender_ID = client_info.robot_id;
	data_header.receiver_ID = client_info.client_id;
	memcpy(&client_tx_buf[7], &data_header, 6);
	memcpy(&client_tx_buf[13], data.grapic_data_struct, 15*2);
	
	/* 帧尾 */
	Append_CRC16_Check_Sum(client_tx_buf, 5 + 2 + LEN_ID_draw_two_graphic + 2);
	
	/* 发送 */
	return uart_send_data(client_tx_buf, 5 + 2 + LEN_ID_draw_two_graphic + 2);
}

/**
	* @brief  发送绘制五个图形帧数据
  * @param  
  * @retval 
  */
uint8_t client_send_five_graphic(ext_client_custom_graphic_five_t data)
{
	frame_t frame;
	ext_student_interactive_header_data_t data_header;
	
	/* 帧头 */
	frame.frame_header.SOF = 0xA5;
	frame.frame_header.data_length = LEN_ID_draw_five_graphic;
	frame.frame_header.seq = 0;
	memcpy(client_tx_buf, &frame.frame_header, 4);
	Append_CRC8_Check_Sum(client_tx_buf, 5);
	
	/* 命令码ID */
	frame.cmd_id = 0x301;
	memcpy(&client_tx_buf[5], (void*)&frame.cmd_id, 2);
	
	/* 数据段 */
	data_header.data_cmd_id = ID_draw_five_graphic;
	data_header.sender_ID = client_info.robot_id;
	data_header.receiver_ID = client_info.client_id;
	memcpy(&client_tx_buf[7], &data_header, 6);
	memcpy(&client_tx_buf[13], data.grapic_data_struct, 15*5);
	
	/* 帧尾 */
	Append_CRC16_Check_Sum(client_tx_buf, 5 + 2 + LEN_ID_draw_five_graphic + 2);
	
	/* 发送 */
	return uart_send_data(client_tx_buf, 5 + 2 + LEN_ID_draw_five_graphic + 2);
}

/**
	* @brief  发送绘制七个图形帧数据
  * @param  
  * @retval 
  */
uint8_t client_send_seven_graphic(ext_client_custom_graphic_seven_t data)
{
	frame_t frame;
	ext_student_interactive_header_data_t data_header;
	
	/* 帧头 */
	frame.frame_header.SOF = 0xA5;
	frame.frame_header.data_length = LEN_ID_draw_seven_graphic;
	frame.frame_header.seq = 0;
	memcpy(client_tx_buf, &frame.frame_header, 4);
	Append_CRC8_Check_Sum(client_tx_buf, 5);
	
	/* 命令码ID */
	frame.cmd_id = 0x301;
	memcpy(&client_tx_buf[5], (void*)&frame.cmd_id, 2);
	
	/* 数据段 */
	data_header.data_cmd_id = ID_draw_seven_graphic;
	data_header.sender_ID = client_info.robot_id;
	data_header.receiver_ID = client_info.client_id;
	memcpy(&client_tx_buf[7], &data_header, 6);
	memcpy(&client_tx_buf[13], data.grapic_data_struct, 15*7);
	
	/* 帧尾 */
	Append_CRC16_Check_Sum(client_tx_buf, 5 + 2 + LEN_ID_draw_seven_graphic + 2);
	
	/* 发送 */
	return uart_send_data(client_tx_buf, 5 + 2 + LEN_ID_draw_seven_graphic + 2);
}

/**
	* @brief  发送绘制字符帧数据
  * @param  
  * @retval 
  */
uint8_t client_send_char(ext_client_custom_character_t data)
{
	frame_t frame;
	ext_student_interactive_header_data_t data_header;
	
	/* 帧头 */
	frame.frame_header.SOF = 0xA5;
	frame.frame_header.data_length = LEN_ID_draw_char_graphic;
	frame.frame_header.seq = 0;
	memcpy(client_tx_buf, &frame.frame_header, 4);
	Append_CRC8_Check_Sum(client_tx_buf, 5);
	
	/* 命令码ID */
	frame.cmd_id = 0x301;
	memcpy(&client_tx_buf[5], (void*)&frame.cmd_id, 2);
	
	/* 数据段 */
	data_header.data_cmd_id = ID_draw_char_graphic;
	data_header.sender_ID = client_info.robot_id;
	data_header.receiver_ID = client_info.client_id;
	memcpy(&client_tx_buf[7], &data_header, 6);
	memcpy(&client_tx_buf[13], &data.grapic_data_struct, 15);
	memcpy(&client_tx_buf[28], data.data, 30);
	
	/* 帧尾 */
	Append_CRC16_Check_Sum(client_tx_buf, 5 + 2 + LEN_ID_draw_char_graphic + 2);
	
	/* 发送 */
	return uart_send_data(client_tx_buf, 5 + 2 + LEN_ID_draw_char_graphic + 2);
}

/******************************发送帧数据end****************************************/

/**************************************************第二层end**************************************************/


/**************************************************第一层begin**************************************************/

/**
	* @brief  串口发送数据
  * @param  
  * @retval 
  */
uint8_t uart_send_data(uint8_t *txbuf, uint16_t length)
{
	return HAL_UART_Transmit_DMA(&UI_huart, txbuf, length);
}

/**************************************************第一层end**************************************************/
uint8_t fonts_size = 18;
uint16_t start_x;

graphic_data_struct_t pitch_buff;
ext_client_custom_character_t pitch_character;
graphic_data_struct_t yaw_buff;
ext_client_custom_character_t yaw_character;
graphic_data_struct_t roll_buff;
ext_client_custom_character_t roll_character;
graphic_data_struct_t x_buff;
ext_client_custom_character_t x_character;
graphic_data_struct_t y_buff;
ext_client_custom_character_t y_character;
graphic_data_struct_t z_buff;
ext_client_custom_character_t z_character;
graphic_data_struct_t car_buff;
ext_client_custom_character_t car_character;
graphic_data_struct_t car_switch_buff;
ext_client_custom_character_t car_switch_character;
graphic_data_struct_t pneu_buff;
ext_client_custom_character_t pneu_character;
graphic_data_struct_t vision_buff;
ext_client_custom_character_t vision_character;

char pitch_info[30] = {"PITCH:"};
char yaw_info[30] = {"YAW:"};
char roll_info[30] = {"ROLL:"};
char x_info[30] = {"X:"};
char y_info[30] = {"Y:"};
char z_info[30] = {"Z:"};
char car_info[30] = {"MDOE_NOW:"};
char car_switch_info[30] = {"MDOE_NEXT:"};
char pneu_info[30] = {"PNEU:"};
char vision_info[30] = {"VISION:"};

void UI_send_char_1(void)
{
	static int cnt = 0;
  static int operate_tpye = ADD;
	
  if(cnt == 0)//add num
  {
    operate_tpye = ADD;  
  }
  else 
  {
    operate_tpye = MODIFY;
  }
	
	pitch_buff = draw_char("gc0",  
	                        operate_tpye,  
                          1,  
                          CYAN_BLUE,  
                          18,  
                          strlen(pitch_info),  
                          2,  
                          Client_mid_position_x - 750,  
                          Client_mid_position_y + 125);  
	
	pitch_character.grapic_data_struct = pitch_buff;
	memcpy(&pitch_character.data,&pitch_info,sizeof(pitch_info));
		
	client_send_char(pitch_character);

	
	cnt++;
  cnt %= 30;
}

void UI_send_char_2(void)
{
	static int cnt = 0;
  static int operate_tpye = ADD;
	
  if(cnt == 0)//add num
  {
    operate_tpye = ADD;  
  }
  else 
  {
    operate_tpye = MODIFY;
  }
	
	yaw_buff = draw_char("gc1",  
												operate_tpye,  
												1,  
												CYAN_BLUE,  
												18,  
												strlen(yaw_info),  
												2,  
												Client_mid_position_x - 714,  
												Client_mid_position_y + 100);  
	
	yaw_character.grapic_data_struct = yaw_buff;
	memcpy(&yaw_character.data,&yaw_info,sizeof(yaw_info));
		
	client_send_char(yaw_character);

	
	cnt++;
  cnt %= 30;
}

void UI_send_char_3(void)
{
	static int cnt = 0;
  static int operate_tpye = ADD;
	
  if(cnt == 0)//add num
  {
    operate_tpye = ADD;  
  }
  else 
  {
    operate_tpye = MODIFY;
  }
	
	roll_buff = draw_char("gc2",  
												operate_tpye,  
												1,  
												CYAN_BLUE,  
												18,  
												strlen(roll_info),  
												2,  
												Client_mid_position_x - 732,  
												Client_mid_position_y + 75);  
	
	roll_character.grapic_data_struct = roll_buff;
	memcpy(&roll_character.data,&roll_info,sizeof(roll_info));
		
	client_send_char(roll_character);

	
	cnt++;
  cnt %= 30;
}

void UI_send_char_4(void)
{
	static int cnt = 0;
  static int operate_tpye = ADD;
	
  if(cnt == 0)//add num
  {
    operate_tpye = ADD;  
  }
  else 
  {
    operate_tpye = MODIFY;
  }
	
	x_buff = draw_char("gc3",  
											operate_tpye,  
											1,  
											CYAN_BLUE,  
											18,  
											strlen(x_info),  
											2,  
											Client_mid_position_x - 678,  
											Client_mid_position_y + 50);  
	
	x_character.grapic_data_struct = x_buff;
	memcpy(&x_character.data,&x_info,sizeof(x_info));
		
	client_send_char(x_character);

	
	cnt++;
  cnt %= 30;
}



void UI_send_char_5(void)
{
	static int cnt = 0;
  static int operate_tpye = ADD;
	
  if(cnt == 0)//add num
  {
    operate_tpye = ADD;  
  }
  else 
  {
    operate_tpye = MODIFY;
  }
	
	y_buff = draw_char("gc4",  
	                        operate_tpye,  
                          1,  
                          CYAN_BLUE,  
                          18,  
                          strlen(y_info),  
                          2,  
                          Client_mid_position_x - 678,  
                          Client_mid_position_y + 25);  
	
	y_character.grapic_data_struct = y_buff;
	memcpy(&y_character.data,&y_info,sizeof(y_info));
		
	client_send_char(y_character);

	
	cnt++;
  cnt %= 30;
}


void UI_send_char_6(void)
{
	static int cnt = 0;
  static int operate_tpye = ADD;
	
  if(cnt == 0)//add num
  {
    operate_tpye = ADD;  
  }
  else 
  {
    operate_tpye = MODIFY;
  }
	
	z_buff = draw_char("gc5",  
	                        operate_tpye,  
                          1,  
                          CYAN_BLUE,  
                          18,  
                          strlen(z_info),  
                          2,  
                          Client_mid_position_x - 678,  
                          Client_mid_position_y );  
	
	z_character.grapic_data_struct = z_buff;
	memcpy(&z_character.data,&z_info,sizeof(z_info));
		
	client_send_char(z_character);

	
	cnt++;
  cnt %= 30;
}


graphic_data_struct_t mode_ctrl_buff;
ext_client_custom_character_t mode_ctrl_character;
graphic_data_struct_t mode_switch_buff;
ext_client_custom_character_t mode_switch_character;

char NORMAL_info[30] = {"NORMAL"};
char LOB_info[30] = {"LOB"};
char RESCUE_info[30] = {"RESCUE"};
char GOLDEN_info[30] = {"GOLDEN"};
char SILVER_info[30] = {"SILVER"};
char EXCHANGE_info[30] = {"EXCHANGE"};
char CCB_info[30] = {"CCB"};

char mode_ctrl_info[30];
char mode_switch_info[30];

uint16_t ccbccbccb = 0;
uint16_t ccbccbccb1 = 0;
void UI_send_char_7(void)
{
	static int cnt = 0;
  static int operate_tpye = ADD;
	
  if(cnt == 0)//add num
  {
    operate_tpye = ADD;  
  }
  else 
  {
    operate_tpye = MODIFY;
  }
	
	switch(car.mode_ctrl)
	{
		case NORMAL:
			memcpy(mode_ctrl_info,NORMAL_info,sizeof(NORMAL_info));
			break;
		case LOB:
			memcpy(mode_ctrl_info,LOB_info,sizeof(LOB_info));
			break;
		case SAVE:
			memcpy(mode_ctrl_info,RESCUE_info,sizeof(RESCUE_info));
			break;
		case SILVER_ORE:
			memcpy(mode_ctrl_info,SILVER_info,sizeof(SILVER_info));
			break;
		case GOLDEN_ORE:
			memcpy(mode_ctrl_info,GOLDEN_info,sizeof(GOLDEN_info));
			break;
		case EXCHANGE_ORE:
			memcpy(mode_ctrl_info,EXCHANGE_info,sizeof(EXCHANGE_info));
			break;
		case CCB_MODE:
			memcpy(mode_ctrl_info,CCB_info,sizeof(CCB_info));
			break;
		default:
			break;
	}
	
	mode_ctrl_buff = draw_char("gc6",  
															operate_tpye,  
															1,  
															GREEN,  
															18,  
															strlen(mode_ctrl_info),  
															2,  
															Client_mid_position_x + 500,  
															Client_mid_position_y + 125);  
	
	mode_ctrl_character.grapic_data_struct = mode_ctrl_buff;
	memcpy(&mode_ctrl_character.data,&mode_ctrl_info,sizeof(mode_ctrl_info));
		
	client_send_char(mode_ctrl_character);

	
	cnt++;
  cnt %= 30;
}

void UI_send_char_8(void)
{
	static int cnt = 0;
  static int operate_tpye = ADD;
	
  if(cnt == 0)//add num
  {
    operate_tpye = ADD;  
  }
  else 
  {
    operate_tpye = MODIFY;
  }
	
	switch(car.mode_switch)
	{
		case NORMAL:
			memcpy(mode_switch_info,NORMAL_info,sizeof(NORMAL_info));
			break;
		case LOB:
			memcpy(mode_switch_info,LOB_info,sizeof(LOB_info));
			break;
		case SAVE:
			memcpy(mode_switch_info,RESCUE_info,sizeof(RESCUE_info));
			break;
		case SILVER_ORE:
			memcpy(mode_switch_info,SILVER_info,sizeof(SILVER_info));
			break;
		case GOLDEN_ORE:
			memcpy(mode_switch_info,GOLDEN_info,sizeof(GOLDEN_info));
			break;
		case EXCHANGE_ORE:
			memcpy(mode_switch_info,EXCHANGE_info,sizeof(EXCHANGE_info));
			break;
		case CCB_MODE:
			memcpy(mode_switch_info,CCB_info,sizeof(CCB_info));
			break;
		default:
			break;
	}
	
	mode_switch_buff = draw_char("gc7",  
															operate_tpye,  
															1,  
															GREEN,  
															18,  
															strlen(mode_switch_info),  
															2,  
															Client_mid_position_x + 500,  
															Client_mid_position_y + 50);  
	
	mode_switch_character.grapic_data_struct = mode_switch_buff;
	memcpy(&mode_switch_character.data,&mode_switch_info,sizeof(mode_switch_info));
		
	client_send_char(mode_switch_character);

	
	cnt++;
  cnt %= 30;
}
///************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
ext_client_custom_graphic_seven_t Group1;
ext_client_custom_graphic_seven_t Group2;
ext_client_custom_graphic_seven_t Group3;
ext_client_custom_graphic_seven_t Group4;

void UI_send_int_1(void)
{
	static int cnt = 0;
  static int operate_tpye = ADD;
	
  if(cnt == 0)//add num
  {
    operate_tpye = ADD;  
  }
  else 
  {
    operate_tpye = MODIFY;
  }
	
	Group1.grapic_data_struct[0] = draw_int("gi1",  
																					operate_tpye,  
																					1,  
																					ORANGE,  
																					18,  
																					2,  
																					Client_mid_position_x - 642,  
																					Client_mid_position_y + 125,
																					sucker.base_info.pitch_A2D);  
	
	Group1.grapic_data_struct[1] = draw_int("gi2",  
																					operate_tpye,  
																					1,  
																					ORANGE,  
																					18,  
																					2,  
																					Client_mid_position_x - 642,  
																					Client_mid_position_y + 100,
																					sucker.base_info.yaw_A2D);  

	Group1.grapic_data_struct[2] = draw_int("gi3",  
																					operate_tpye,  
																					1,  
																					ORANGE,  
																					18,  
																					2,  
																					Client_mid_position_x - 642,  
																					Client_mid_position_y + 75,
																					sucker.base_info.roll_A2D);
																				
	Group1.grapic_data_struct[3] = draw_int("gi4",  
																					operate_tpye,  
																					1,  
																					ORANGE,  
																					18,  
																					2,  
																					Client_mid_position_x - 642,  
																					Client_mid_position_y + 50,
																					transverse.base_info.angle2mm);  
																			
	Group1.grapic_data_struct[4] = draw_int("gi5",  
																					operate_tpye,  
																					1,  
																					ORANGE,  
																					18,  
																					2,  
																					Client_mid_position_x - 642,  
																					Client_mid_position_y + 25,
																					protract.base_info.angle2mm);  

	Group1.grapic_data_struct[5] = draw_int("gi6",  
																					operate_tpye,  
																					1,  
																					ORANGE,  
																					18,  
																					2,  
																					Client_mid_position_x - 642,  
																					Client_mid_position_y + 0,
																					uplift.angle2mm);
																					
	Group1.grapic_data_struct[6] = draw_int("gi7",  
																					operate_tpye,  
																					1,  
																					ORANGE,  
																					25,  
																					4,  
																					Client_mid_position_x + 540,  
																					Client_mid_position_y - 0,
																					car.step);
	
	client_send_seven_graphic(Group1);

	cnt++;
  cnt %= 30;
}


uint8_t pneu_color=0;
uint8_t vision_color=0;
uint8_t vision_lock=0;
uint16_t ui_normal_pos1;
uint16_t ui_normal_pos2;
uint16_t ui_normal_pos3;
uint16_t ui_normal_pos4;
uint16_t ui_normal_pos5;
uint16_t ui_normal_pos6;
uint16_t ui_normal_pos7;
uint16_t ui_normal_pos8;
uint16_t ui_rescue_pos1;
uint16_t ui_rescue_pos2;
uint16_t ui_rescue_pos3;
uint16_t ui_rescue_pos4;
uint16_t ui_rescue_pos5;
uint16_t ui_rescue_pos6;
uint16_t ui_rescue_pos7;
uint16_t ui_rescue_pos8;
void UI_send_group1(void)
{
	static int cnt = 0;
  static int operate_tpye = ADD;
	
  if(cnt == 0)//add num
  {
    operate_tpye = ADD;  
  }
  else 
  {
    operate_tpye = MODIFY;
  }
	
	vision_lock = Auto.config->target_OK;
	if(!vision_lock)
		vision_color = WHITE;
	else
		vision_color = ORANGE;
	
	Group2.grapic_data_struct[0] = draw_circle("gc8",  
																					operate_tpye,  
																					1,  
																					vision_color,  
																					40,  
																					Client_mid_position_x - 750,  
																					Client_mid_position_y + 200,
																					20);  
	
	if(pneumatic.pneu_state == OFF)
		pneu_color = WHITE;
	else
		pneu_color = ORANGE;
	
	Group2.grapic_data_struct[1] = draw_circle("gc9",  
																					operate_tpye,  
																					1,  
																					pneu_color,  
																					40,  
																					Client_mid_position_x - 600,  
																					Client_mid_position_y + 200,
																					20);  
	
	if(car.mode_switch == NORMAL||car.mode_switch == SAVE)//
	{
		ui_normal_pos1 = Client_mid_position_x - 222;
		ui_normal_pos2 = Client_mid_position_y + 200;
		ui_normal_pos3 = Client_mid_position_x - 816;
		ui_normal_pos4 = 0;
		
		
		ui_normal_pos5 = Client_mid_position_x + 59;
		ui_normal_pos6 = Client_mid_position_y + 200;
		ui_normal_pos7 = Client_mid_position_x + 160;
		ui_normal_pos8 = 0;
	}
	else 
	{
		ui_normal_pos1 = 0;
		ui_normal_pos2 = 0;
		ui_normal_pos3 = 0;
		ui_normal_pos4 = 0;
		ui_normal_pos5 = 0;
		ui_normal_pos6 = 0;
		ui_normal_pos7 = 0;
		ui_normal_pos8 = 0;
	}
	/*left*/
	Group2.grapic_data_struct[2] = draw_line("gl0",
                                       operate_tpye,
                                       1, 
                                       YELLOW, 
                                       3, 
                                       ui_normal_pos1, 
                                       ui_normal_pos2, 
                                       ui_normal_pos3, 
                                       ui_normal_pos4);
	
	/*right*/
  Group2.grapic_data_struct[3] = draw_line("gl1", 
                                       operate_tpye, 
                                       1,  
                                       YELLOW, 
                                       3,  
                                       ui_normal_pos5, 
                                       ui_normal_pos6, 
                                       ui_normal_pos7,  
                                       ui_normal_pos8);

	if(car.mode_switch == SAVE)//
	{
		ui_rescue_pos1 = Client_mid_position_x - 185;
		ui_rescue_pos2 = Client_mid_position_y + 200;
		ui_rescue_pos3 = Client_mid_position_x - 700;
		ui_rescue_pos4 = 0;
		
		
		ui_rescue_pos5 = Client_mid_position_x + 15;
		ui_rescue_pos6 = 740;
		ui_rescue_pos7 = Client_mid_position_x - 20;
		ui_rescue_pos8 = 0;
	}
	else 
	{
		ui_rescue_pos1 = 0;
		ui_rescue_pos2 = 0;
		ui_rescue_pos3 = 0;
		ui_rescue_pos4 = 0;
		ui_rescue_pos5 = 0;
		ui_rescue_pos6 = 0;
		ui_rescue_pos7 = 0;
		ui_rescue_pos8 = 0;
	}
	
		/*rescueL*/
		Group2.grapic_data_struct[4] = draw_line("gl2", 
																				 operate_tpye,
																				 1, 
																				 RED_BLUE, 
																				 3, 
																				 ui_rescue_pos1, 
																				 ui_rescue_pos2, 
																				 ui_rescue_pos3, 
																				 ui_rescue_pos4);
																				 
		/*rescueR*/
		Group2.grapic_data_struct[5] = draw_line("gl3", 
																				 operate_tpye, 
																				 1, 
																				 RED_BLUE, 
																				 3,  
																				 ui_rescue_pos5,  
																				 ui_rescue_pos6, 
																				 ui_rescue_pos7,  
																				 ui_rescue_pos8);
	client_send_seven_graphic(Group2);

	cnt++;
  cnt %= 30;
}

uint16_t ui_lob_pos1;
uint16_t ui_lob_pos2;
uint16_t ui_lob_pos3;
uint16_t ui_lob_pos4;
uint16_t ui_lob_pos5;
uint16_t ui_lob_pos6;
uint16_t ui_lob_pos7;
uint16_t ui_lob_pos8;
uint16_t ui_silver_pos1;
uint16_t ui_silver_pos2;
uint16_t ui_silver_pos3;
uint16_t ui_silver_pos4;
uint16_t ui_silver_pos5;
uint16_t ui_silver_pos6;
uint16_t ui_silver_pos7;
uint16_t ui_silver_pos8;
uint16_t ccbbbb=90;
uint16_t ccbbbb1=600;
uint16_t ccbbbb2=90;
uint16_t ccbbbb12=600;
void UI_send_group2(void)
{
	static int cnt = 0;
  static int operate_tpye = ADD;
	
  if(cnt == 0)//add num
  {
    operate_tpye = ADD;  
  }
  else 
  {
    operate_tpye = MODIFY;
  }
	
	
	if(car.mode_switch == LOB||car.mode_switch == LOB)//
	{
		ui_lob_pos1 = Client_mid_position_x - ccbbbb;
		ui_lob_pos2 = Client_mid_position_y + ccbbbb1;
		ui_lob_pos3 = Client_mid_position_x - ccbbbb;
		ui_lob_pos4 = 0;
		
		
		ui_lob_pos5 = Client_mid_position_x + ccbbbb;
		ui_lob_pos6 = Client_mid_position_y + ccbbbb1;
		ui_lob_pos7 = Client_mid_position_x + ccbbbb;
		ui_lob_pos8 = 0;
	}
	else 
	{
		ui_lob_pos1 = 0;
		ui_lob_pos2 = 0;
		ui_lob_pos3 = 0;
		ui_lob_pos4 = 0;
		ui_lob_pos5 = 0;
		ui_lob_pos6 = 0;
		ui_lob_pos7 = 0;
		ui_lob_pos8 = 0;
	}
	/*left*/
	Group3.grapic_data_struct[0] = draw_line("ll1",
                                       operate_tpye,
                                       1, 
                                       RED_BLUE, 
                                       3, 
                                       ui_lob_pos1, 
                                       ui_lob_pos2, 
                                       ui_lob_pos3, 
                                       ui_lob_pos4);
	
	/*right*/
  Group3.grapic_data_struct[1] = draw_line("ll2", 
                                       operate_tpye, 
                                       1,  
                                       RED_BLUE, 
                                       3,  
                                       ui_lob_pos5, 
                                       ui_lob_pos6, 
                                       ui_lob_pos7,  
                                       ui_lob_pos8);
																			 
	if((car.mode_switch == SILVER_ORE||car.mode_switch == SILVER_ORE)&&car.step >= 11)//
	{
		ui_silver_pos1 = Client_mid_position_x - ccbbbb2;
		ui_silver_pos2 = Client_mid_position_y + ccbbbb12;
		ui_silver_pos3 = Client_mid_position_x - ccbbbb2;
		ui_silver_pos4 = 0;
		
		
		ui_silver_pos5 = Client_mid_position_x + ccbbbb2;
		ui_silver_pos6 = Client_mid_position_y + ccbbbb12;
		ui_silver_pos7 = Client_mid_position_x + ccbbbb2;
		ui_silver_pos8 = 0;
	}
	else 
	{
		ui_silver_pos1 = 0;
		ui_silver_pos2 = 0;
		ui_silver_pos3 = 0;
		ui_silver_pos4 = 0;
		ui_silver_pos5 = 0;
		ui_silver_pos6 = 0;
		ui_silver_pos7 = 0;
		ui_silver_pos8 = 0;
	}
	/*left*/
	Group3.grapic_data_struct[2] = draw_line("ls1",
                                       operate_tpye,
                                       1, 
                                       RED_BLUE, 
                                       3, 
                                       ui_silver_pos1, 
                                       ui_silver_pos2, 
                                       ui_silver_pos3, 
                                       ui_silver_pos4);
	
	/*right*/
  Group3.grapic_data_struct[3] = draw_line("ls2", 
                                       operate_tpye, 
                                       1,  
                                       RED_BLUE, 
                                       3,  
                                       ui_silver_pos5, 
                                       ui_silver_pos6, 
                                       ui_silver_pos7,  
                                       ui_silver_pos8);

	client_send_seven_graphic(Group3);

	cnt++;
  cnt %= 30;
}
