#ifndef __JUDGE_PROTOCOL_H
#define __JUDGE_PROTOCOL_H

#include "config.h"
#include "main.h"
#include "stdbool.h"
#define JUDGE_FRAME_HEADER	0xA5  //��Ϊ֡ͷ��SOF,֡ͷ��Ϊ SOF,length,Seq,CRC8
//***********����ϵͳ�ķ�����Ϣ***************/
enum
{ 
	ID_game_state       						= 0x0001,//����״̬���ݣ�1Hz
	ID_game_result 	   							= 0x0002,//����������ݣ�������������
	ID_game_robot_HP       					= 0x0003,//����������Ѫ�����ݣ�1Hz����
//	ID_dart_status									= 0x0004,//���ڷ���״̬�����ڷ���ʱ����
	ID_ICRA_buff_debuff_zone_status = 0x0005,//�˹�������ս���ӳ���ͷ���״̬��1Hz
	ID_event_data  									= 0x0101,//�����¼����ݣ��¼� �����ı�󡪡� ����
	ID_supply_projectile_action   	= 0x0102,//���ز���վ������ʶ���ݣ����� �����ı�󡪡� ����
//	ID_supply_projectile_booking    = 0x0103,//���󲹸�վ�������� ���������ӷ��͡�����RM �Կ�����δ����10Hz
	ID_referee_warning					 		= 0x0104,//���о������ݣ���������󡪡�����
	ID_dart_remaining_time					= 0x0105,//���ڷ���ڵ���ʱ��1Hz
	ID_game_robot_state    					= 0x0201,//������״̬���ݣ�10Hz
	ID_power_heat_data    					= 0x0202,//ʵʱ�����������ݣ�50Hz
	ID_game_robot_pos        				= 0x0203,//������λ�����ݣ�10Hz
	ID_buff_musk										= 0x0204,//�������������ݣ�1Hz
	ID_aerial_robot_energy					= 0x0205,//���л���������״̬���ݣ�10Hz��ֻ�С������л��������ء�������
	ID_robot_hurt										= 0x0206,//�˺�״̬���ݣ��˺���������
 	ID_shoot_data										= 0x0207,//ʵʱ������ݣ��ӵ��������
	ID_bullet_remaining							= 0x0208,//����ʣ�෢���������������л����ˣ��ڱ������ˡ����Լ�ICRA�����˷��ͣ�1Hz
	ID_rfid_status									= 0x0209,//������RFID״̬��1Hz
	
	ID_dart_client_directive        = 0x020A,//���ڻ����˿ͻ���ָ����, 10Hz
	
	ID_robot_interactive_header_data			= 0x0301,//�����˽������ݣ��������ͷ������������� 10Hz
	ID_controller_interactive_header_data = 0x0302,//�Զ���������������ݽӿڣ�ͨ�������ͻ��˴����������� 30Hz
	ID_map_interactive_header_data        = 0x0303,//�ͻ���С��ͼ�������ݣ������������͡���
	ID_keyboard_information               = 0x0304,//���̡������Ϣ��ͨ������ͼ�����ڡ�������
  ID_smallmap                           = 0x0305,//�ͻ���С��ͼ������Ϣ 
};
//������ö��CMD_ID
//**************����ϵͳ������Ϣ�ĳ��ȣ���λ/�ֽڣ�**************************/
enum judge_data_length_t {
	/* Std */
	LEN_FRAME_HEAD 	                 = 5,	// ֡ͷ����
	LEN_CMD_ID 		                   = 2,	// �����볤��
	LEN_FRAME_TAIL 	                 = 2,	// ֡βCRC16
	/* Ext */
	// 0x000x
	LEN_GAME_STATUS 				         = 11,
	LEN_GAME_RESULT 				         = 1,
	LEN_GAME_ROBOT_HP 			         = 32,
//	LEN_DART_STATUS					         = 3,
	LEN_ICRA_BUFF_DEBUFF_ZONE_STATUS = 11,//0x0005
	// 0x010x
	LEN_EVENT_DATA					         = 4,
	LEN_SUPPLY_PROJECTILE_ACTION	   = 4,//����������������������������������
//	LEN_SUPPLY_PROJECTILE_BOOKING	   = 2,//�Կ���δ����
	LEN_REFEREE_WARNING				       = 2,
	LEN_DART_REMAINING_TIME		     	 = 1,//0x0105
	// 0x020x
	LEN_GAME_ROBOT_STATUS			       = 27,//15!!!!!!!!!!!!!!!!!!!!!!!!!!!
	LEN_POWER_HEAT_DATA 			       = 16,//��������������������
	LEN_GAME_ROBOT_POS				       = 16,
	LEN_BUFF_MASK		 				         = 1,
	LEN_AERIAL_ROBOT_ENERGY 	     	 = 1,//����������
	LEN_ROBOT_HURT				         	 = 1,
	LEN_SHOOT_DATA					         = 7,//��������
	LEN_BULLET_REMAINING	 		       = 6,//��������
	LEN_RFID_STATUS					         = 4,
	LEN_DART_CLIENT_DIRECTIVE        = 6,//0x020A

	// 0x030x
	//LEN_robot_interactive_header_data      = n,
	//LEN_controller_interactive_header_data = n,
	LEN_MAP_INTERACTIVE_HEADERDATA           = 15,
	LEN_KEYBOARD_INFORMATION                 = 12,//0x0304

		LEN_SENTRY_INFO                          = 1,
};//��2-4
/*******************����ϵͳ��Ϣ��������**************************/



typedef __packed struct
{
	uint8_t  sof;
	uint16_t data_length;
	uint8_t  seq;
	uint8_t  crc8;
} std_frame_header_t;//LEN_FRAME_HEAD


typedef __packed struct
{
 uint8_t game_type : 4;
 uint8_t game_progress : 4;
 uint16_t stage_remain_time;
uint64_t SyncTimeStamp;
} ext_game_status_t;

//LEN_CMD_ID
//LEN_FRAME_TAIL
/* ID: 0x0005 	Byte:	11	�˹�������ս���ӳ���ͷ���״̬ */
typedef __packed struct
{
	uint8_t F1_zone_status:1;            //����״̬
	uint8_t F1_zone_buff_debuff_status:3;//�췽��Ѫ��
	uint8_t F2_zone_status:1;
	uint8_t F2_zone_buff_debuff_status:3;//�췽��ҩ������
	uint8_t F3_zone_status:1;
	uint8_t F3_zone_buff_debuff_status:3;//������Ѫ��
	uint8_t F4_zone_status:1;
	uint8_t F4_zone_buff_debuff_status:3;//������ҩ������
	uint8_t F5_zone_status:1;
	uint8_t F5_zone_buff_debuff_status:3;//��ֹ�����
	uint8_t F6_zone_status:1;
	uint8_t F6_zone_buff_debuff_status:3;//��ֹ�ƶ���
	uint16_t red1_bullet_left;           //�췽 1 ��ʣ�൯��
	uint16_t red2_bullet_left;           //�췽 2 ��ʣ�൯��
	uint16_t blue1_bullet_left;          //���� 1 ��ʣ�൯��
	uint16_t blue2_bullet_left;          //���� 2 ��ʣ�൯��
} ext_ICRA_buff_debuff_zone_status_t;//LEN_ICRA_BUFF_DEBUFF_ZONE_STATUS  ��3-5
/* ID: 0x0102  Byte:  4    ����վ������ʶ���� */
typedef __packed struct 
{ 
	uint8_t supply_projectile_id;  //����վ�� ID
	uint8_t supply_robot_id;       //���������� ID
	uint8_t supply_projectile_step;//�����ڿ���״̬
	uint8_t supply_projectile_num; //��������
} ext_supply_projectile_action_t;//LEN_SUPPLY_PROJECTILE_ACTION  ��3-7
/* ID: 0X0201  Byte: 27    ������״̬���� */
typedef __packed struct 
{ 
	uint8_t robot_id;                       //�������� ID
	uint8_t robot_level;                    //�����˵ȼ�
	uint16_t remain_HP;                     //������ʣ��Ѫ��
	uint16_t max_HP;                        //����������Ѫ��
	uint16_t shooter_id1_17mm_cooling_rate; //������ 1 �� 17mm ǹ��ÿ����ȴֵ
	uint16_t shooter_id1_17mm_cooling_limit;//������ 1 �� 17mm ǹ����������
	uint16_t shooter_id1_17mm_speed_limit;  //������ 1 �� 17mm ǹ�������ٶ� ��λ m/s
	uint16_t shooter_id2_17mm_cooling_rate; //������ 2 �� 17mm ǹ��ÿ����ȴֵ
	uint16_t shooter_id2_17mm_cooling_limit;//������ 2 �� 17mm ǹ����������
	uint16_t shooter_id2_17mm_speed_limit;  //������ 2 �� 17mm ǹ�������ٶ� ��λ m/s
	uint16_t shooter_id1_42mm_cooling_rate; //������ 42mm ǹ��ÿ����ȴֵ
	uint16_t shooter_id1_42mm_cooling_limit;//������ 42mm ǹ����������
	uint16_t shooter_id1_42mm_speed_limit;  //������ 42mm ǹ�������ٶ� ��λ m/s
	uint16_t chassis_power_limit;           //�����˵��̹�����������
	//���ص�Դ������
	uint8_t mains_power_gimbal_output  : 1; //gimbal ������� 1 Ϊ�� 24V �����0 Ϊ�� 24v ���
	uint8_t mains_power_chassis_output : 1; //chassis �������1 Ϊ�� 24V �����0 Ϊ�� 24v ���
	uint8_t mains_power_shooter_output : 1; //shooter �������1 Ϊ�� 24V �����0 Ϊ�� 24v ���
} ext_game_robot_status_t; //LEN_GAME_ROBOT_STATUS  ��3-10
/* ID: 0X0202  Byte: 16    ʵʱ������������ */
typedef __packed struct 
{ 
	uint16_t chassis_volt;   				// ���������ѹ����λ��mV
	uint16_t chassis_current;				// ���������������λ��mA
	float chassis_power;   					// ����˲ʱ���ʣ���λ��W
	uint16_t chassis_power_buffer;	// ���̹��ʻ��壬��λ��60J������������(���¸��ݹ���������250J)
	uint16_t shooter_id1_17mm_cooling_heat; //1 �� 17mm ǹ������
	uint16_t shooter_id2_17mm_cooling_heat; //2 �� 17mm ǹ������
	uint16_t shooter_id1_42mm_cooling_heat;	//42mm ǹ������
} ext_power_heat_data_t; //LEN_POWER_HEAT_DATA   ��3-11
/* ID: 0x0205  Byte:  1    ���л���������״̬���� */
typedef __packed struct 
{ 
	uint8_t attack_time;//�ɹ���ʱ�� ��λ s��30s �ݼ��� 0
} ext_aerial_robot_energy_t; //LEN_AERIAL_ROBOT_ENERGY  ��3-14
/* ID: 0x0206  Byte:  1    �˺�״̬���� */
typedef __packed struct 
{ 
	uint8_t armor_id : 4; 	// װ���˺�ʱ����װ��ID
	uint8_t hurt_type : 4; 	// 0x0װ���˺� 0x1ģ����� 0x2������ 0x3������ 0x4������ 0x5ײ��
} ext_robot_hurt_t; //LEN_ROBOT_HURT  ��3-15
/* ID: 0x0207  Byte:  7    ʵʱ������� */
typedef __packed struct 
{ 
	uint8_t bullet_type; 	// �ӵ�����(1-17mm, 2-42mm)
	uint8_t shooter_id;   // ������� ID��1��1 �� 17mm ���������2��2 �� 17mm ���������3��42mm ���������
	uint8_t bullet_freq;  // �ӵ���Ƶ(Hz)
	float bullet_speed;		// �ӵ�����(m/s)
} ext_shoot_data_t; //LEN_SHOOT_DATA  ��3-16
/* ID: 0x0208  Byte:  6    �ӵ�ʣ�෢�������� */
typedef __packed struct
{
	uint16_t bullet_remaining_num_17mm;//17mm �ӵ�ʣ�෢����Ŀ
	uint16_t bullet_remaining_num_42mm;//42mm �ӵ�ʣ�෢����Ŀ
	uint16_t coin_remaining_num;       //ʣ��������
} ext_bullet_remaining_t; //LEN_BULLET_REMAINING   ��3-17
/* ID: 0x0209  Byte:  4 	������RFID״̬ */
typedef __packed struct
{
	uint32_t rfid_status;
} ext_rfid_status_t;//LEN_RFID_STATUS  ��3-18
/*ID��0x020A   Byte��6  ���ڻ����˿ͻ���ָ������*/
	/*******************************************************************************/
/*
	������ ID��
	1��Ӣ��(��)��
	2������(��)��
	3/4/5������(��)��
	6������(��)��
	7���ڱ�(��)��
	9���״�죩
	101��Ӣ��(��)��
	102������(��)��
	103/104/105������(��)��
	106������(��)��
	107���ڱ�(��)��
	109���״����

	�ͻ��� ID�� 
	0x0101 ΪӢ�۲����ֿͻ���(��) ��
	0x0102 Ϊ���̲����ֿͻ���( �� )��
	0x0103/0x0104/0x0105 Ϊ���������ֿͻ���(��)��
	0x0106 Ϊ���в����ֿͻ���((��)�� 

	0x0165��Ӣ�۲����ֿͻ���(��)��
	0x0166�����̲����ֿͻ���(��)��
	0x0167/0x0168/0x0169�����������ֿͻ���(��)��
	0x016A�����в����ֿͻ���(��)�� 
*/
enum judge_robot_ID{
	hero_red       = 1,
	engineer_red   = 2,
	infantry3_red  = 3,
	infantry4_red  = 4,
	infantry5_red  = 5,
	plane_red      = 6,
	
	hero_blue      = 101,
	engineer_blue  = 102,
	infantry3_blue = 103,
	infantry4_blue = 104,
	infantry5_blue = 105,
	plane_blue     = 106,
};
typedef struct{
	uint16_t teammate_hero;
	uint16_t teammate_engineer;
	uint16_t teammate_infantry3;
	uint16_t teammate_infantry4;
	uint16_t teammate_infantry5;
	uint16_t teammate_plane;
	uint16_t teammate_sentry;
	
	uint16_t client_hero;
	uint16_t client_engineer;
	uint16_t client_infantry3;
	uint16_t client_infantry4;
	uint16_t client_infantry5;
	uint16_t client_plane;
} ext_interact_id_t;

typedef struct
{
	float x_speed;
	float y_speed;
	float z_speed;
	float pitch_speed;
	float yaw_speed;
	float roll_speed;
	
}custom_controler_info_t;

typedef struct {
	std_frame_header_t							fream_header;				// ֡ͷ��Ϣ

	ext_game_status_t								ext_game_status;	//0x001
	ext_supply_projectile_action_t	supply_projectile_action;		// 0x0102
	
	ext_game_robot_status_t					game_robot_status;	// 0x0201
	ext_power_heat_data_t						power_heat_data;		// 0x0202
	ext_aerial_robot_energy_t				aerial_robot_energy;// 0x0205
	ext_robot_hurt_t								robot_hurt;					// 0x0206
	ext_shoot_data_t								shoot_data;					// 0x0207
	ext_bullet_remaining_t					bullet_remaining;		// 0x0208	
	ext_rfid_status_t								rfid_status;				// 0x0209	
	
	custom_controler_info_t					custom_info;				//0x0302
	
	ext_interact_id_t								ids;								//�뱾�������Ļ�����id
	
	uint16_t                        self_client;        //�����ͻ���
	
	bool	 		data_valid;	// ������Ч��

	Dev_Work_State_e power_heat_data_state;
	
	uint8_t		power_heat_data_offline_cnt;
	uint8_t		power_heat_data_offline_max_cnt;
	
} judge_t;

extern judge_t judge;
void check_judge_offline(judge_t *judge_sen);
void judge_update(judge_t *judge_sen,uint8_t *rxBuf);
//void judge_send(void);


#endif
