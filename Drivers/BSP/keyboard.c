/******************************************************************************
  * �ļ���  ��  keyboard.c
  * �ļ����ܣ�  ��ⰴ���Ƿ񱻰����Լ���¼���´�����״̬����
 ******************************************************************************/ 
#include "keyboard.h"

//KEY_DOWN_TIME��KEY_HOLD_TIME���ݵ��������ȷ��
#define KEY_MAX  4	                                    //��4������
#define KEY_MSG_FIFO_MAX   200           	              //���洢�ļ�����Ϣ
uint32_t KEY_HOLD_TIME   =   120;//20000;	             	//�����жϰ������µ�ʱ�䣬���������ʱ������Ϊ�ǳ���
uint32_t KEY_DOWN_TIME   =	 40;//2500;				          //�����жϰ������µ�ʱ�䣬���������ʱ������Ϊ�Ƕ̰�
KEY_MSG KEY_MSG_FIFO[KEY_MSG_FIFO_MAX];   		          //�������水������Ϣ
uint32_t KEY_Press_Time[KEY_MAX];
uint8_t key_msg_rear = 0,key_msg_front = 0;             //key_msg_rear����ָʾ��ǰ����İ�����Ϣ
														                            //key_msg_front����ָʾ��ǰ��ȡ�İ�����Ϣ
volatile KEY_MSG_STATUS key_msg_status = KEY_MSG_EMPTY; //key_msg_status����ָʾ��ǰ��Ϣ���е�״̬


//���水����Ϣ
uint8_t Send_KeyMsg(KEY_MSG key_msg)
{
	if(key_msg_status == KEY_MSG_FULL)		//��Ϣ���������Ϣ�Ѿ�����
	{
		return 0;
	}
	
	//���水����Ϣ
	KEY_MSG_FIFO[key_msg_rear].status = key_msg.status;
	KEY_MSG_FIFO[key_msg_rear].key    = key_msg.key;
	key_msg_rear++;
	
	if(key_msg_rear >= KEY_MSG_FIFO_MAX) //���������Ϣ���������ͷ�ٴ���
	{
		key_msg_rear = 0;			
	}
	if(key_msg_rear == key_msg_front)	   //һ�������key_msg_rear>key_msg_front�ģ����һֱ������Ϣ
	{									                   //ʹkey_msg_rear�ӵ���key_msg_front���ʱ�����ʱ���ǲ�����
		key_msg_status = KEY_MSG_FULL;	   //������Ϣ�ģ���Ϊ��Ϣ��û��ȡ��
	}
	else
	{
		key_msg_status = KEY_MSG_NORMAL;
	}
	return 1;
}

//��ȡ��Ϣ������İ�����Ϣ
uint8_t Get_KeyMsg(KEY_MSG *key_msg)
{
	if(key_msg_status == KEY_MSG_EMPTY)		//��Ϣ���������Ϣ�Ѿ�ȡ��
	{
		return 0;
	}
	
	//ȡ��Ϣ
	key_msg->status = KEY_MSG_FIFO[key_msg_front].status;
	key_msg->key    = KEY_MSG_FIFO[key_msg_front].key;
	key_msg_front++;
	
	if(key_msg_front >= KEY_MSG_FIFO_MAX)  //���������Ϣ���������ͷ�ٴ���
	{
		key_msg_front = 0;			
	}
	
	if(key_msg_front == key_msg_rear)	  //���������ʱ��˵����Ϣ�������Ѿ�û����Ϣ��
	{
		key_msg_status = KEY_MSG_EMPTY;
	}
	return 1;
}

//����ĸ�����������ȥ����¼ʱ��
void Check_Key(void)
{
	KEY_MSG key_msg ;
	uint8_t KEY_IN = 0;
	uint8_t col;
	if( HAL_GPIO_ReadPin(KEYC_PORT,KEYC_10_PIN) == 0 || HAL_GPIO_ReadPin(KEYC_PORT,KEYC_11_PIN) == 0 \
		  || HAL_GPIO_ReadPin(KEYA_PORT,KEYA_0_PIN) == 0  || HAL_GPIO_ReadPin(KEYA_PORT,KEYA_1_PIN) == 0 )
	{
		for(col = 0;col < 4;col++)
		{
				if(col == 3)
					KEY_IN = HAL_GPIO_ReadPin(KEYA_PORT,KEYA_0_PIN);
				else if(col == 2)
					KEY_IN = HAL_GPIO_ReadPin(KEYA_PORT,KEYA_1_PIN);
				else if(col == 1)
					KEY_IN = HAL_GPIO_ReadPin(KEYC_PORT,KEYC_11_PIN);
				else if(col == 0)
					KEY_IN = HAL_GPIO_ReadPin(KEYC_PORT,KEYC_10_PIN);
				if( KEY_IN == 0x00)
				{
					KEY_Press_Time[col]++; 
					if(KEY_Press_Time[col]<=KEY_DOWN_TIME) //һֱѭ��ֱ���ﵽԤ���ʱ��
					{
						continue;
					}
					else if(KEY_Press_Time[+col]==KEY_DOWN_TIME+1)
					{
						key_msg.key=(KEY_Type)(col);
						key_msg.status=KEY_DOWN;
						Send_KeyMsg(key_msg);
					}
					else if(KEY_Press_Time[col]<=KEY_HOLD_TIME)
					{
						continue;
					}
					else if(KEY_Press_Time[col]==KEY_HOLD_TIME+1)
					{
						key_msg.key=(KEY_Type)(col);   
						key_msg.status=KEY_HOLD;
						Send_KeyMsg(key_msg);
					}
					else
					{
						KEY_Press_Time[col] = KEY_DOWN_TIME+1;
					}
				}
				else
				{
					key_msg.key=(KEY_Type)(col); 
					key_msg.status=KEY_IDLE;
					KEY_Press_Time[col]=0;
				}
		}
		
	}
	else
	{
		for(int i=0;i<4;i++)
		{
			key_msg.key=(KEY_Type)(i); 
			key_msg.status=KEY_IDLE;
			KEY_Press_Time[i]=0;
			//Send_Key_msg(key_msg); 
		}
	}	
}


