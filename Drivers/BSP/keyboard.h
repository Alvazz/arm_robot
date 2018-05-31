
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __keyboard_H
#define __keyboard_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "gpio.h"

#define KEYC_PORT  GPIOC
#define KEYA_PORT  GPIOA	

#define KEYA_0_PIN  0  
#define KEYA_1_PIN  1   
#define KEYC_10_PIN 10  
#define KEYC_11_PIN 11  	 

//���������࣬�������Ƶ�ʱ��Ҫ�޸�
typedef enum 
{    
	BUF_START_KEY,
	BUF_STOP_KEY,
	BUF_STOP1_KEY,
	BUF_STOP2_KEY,
}KEY_Type;	 
	 
//������״̬
typedef enum
{
	KEY_IDLE,         		//����̬
  KEY_DOWN,       			//���°���
	KEY_HOLD,				      //����
}KEY_Status;

//������
typedef struct
{
	KEY_Type 	key;			  //�ĸ�����
	KEY_Status  status;   //������״̬
}KEY_MSG;

//��Ϣ��״̬
typedef enum
{
    KEY_MSG_NORMAL,    //һ����Ϣ
    KEY_MSG_FULL,      //��Ϣ����
    KEY_MSG_EMPTY,     //��Ϣ��
}KEY_MSG_STATUS;

uint8_t Send_KeyMsg(KEY_MSG key_msg);
uint8_t Get_KeyMsg(KEY_MSG *key_msg);
void Check_Key(void);

extern uint32_t KEY_HOLD_TIME;						//�����жϰ������µ�ʱ�䣬���������ʱ������Ϊ�ǳ���
extern uint32_t KEY_DOWN_TIME;							

	 
	 
#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */

/**
  * @}
  */

/**
  * @}
  */
