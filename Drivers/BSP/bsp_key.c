/******************************************************************************
  * �ļ���  ��  bsp_key.c
  * �ļ����ܣ�  ��ⰴ���Ƿ񱻰����Լ���¼���´���
 ******************************************************************************/ 
#include "bsp_key.h"
//��¼��ǰ��������
uint32_t Key_statenumber[KEY_NUMBER] ;
uint8_t Down_State = 0 ;                      //��������ʱ�ĵ�ƽ��1Ϊ�ߵ�ƽ��0Ϊ�͵�ƽ
uint32_t HUST_BUTTOM_START_STATUS_COUNT = 0 ; //BUF_START��������
uint32_t HUST_BUTTOM_STOP_STATUS_COUNT  = 0 ; //BUF_STOP��������
uint32_t HUST_BUTTOM_STOP1_STATUS_COUNT = 0 ; //BUF_STOP1��������
uint32_t HUST_BUTTOM_STOP2_STATUS_COUNT = 0 ; //BUF_STOP1��������

/******************************************************************************
  * ������  ��  Key_Scan
	* ���������  �����������λ�ã�״ָ̬ʾ
  * ���ֵ  ��  �������KEY_ON��û�������KEY_OFF
  * �������ܣ�  ��ⰴ���Ƿ񱻰��º�λ
 ******************************************************************************/ 
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin ,uint8_t Down_state)
{
	uint32_t tickstart = 0;
	if( HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == Down_state )
	{
		//��ȡ����/�͵�ƽ��ʼʱ��ʱ��
		tickstart = HAL_GetTick();
		////��ȡ����/�͵�ƽ������ʱ��
		while( HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == Down_state );
		//����ʱ����ֵ����
		if( HAL_GetTick() - tickstart > 100)
			return KEY_ON;
		else 
			return KEY_OFF;
	}
	else
		return KEY_OFF;
}

/******************************************************************************
  * ������  ��  Key_Scan_Clock
	* ���������  �����������λ�ã�״ָ̬ʾ
  * ���ֵ  ��  �������KEY_ON��û�������KEY_OFF
  * �������ܣ�  ��ⰴ���Ƿ񱻰��º󲻸�λ
 ******************************************************************************/ 
uint8_t Key_Scan_Clock(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin ,uint8_t Down_state)
{
	uint32_t tickstart = 0;
	uint8_t  flag = 0; //���λ
	if( HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == Down_state )
	{
		//��ȡ����/�͵�ƽ��ʼʱ��ʱ��
		tickstart = HAL_GetTick();
		////��ȡ����/�͵�ƽ������ʱ��
		while( HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == Down_state )
		{
			if( HAL_GetTick() - tickstart > 1000) //����ʱ����ֵ����
			{
				flag = 1;
				break;
			}
		} 
		if( 1 == flag)
		{
			return KEY_ON;
		}
		else
			return KEY_OFF;
	}
	else
		return KEY_OFF;
}

/******************************************************************************
  * ������  ��  Key_Number
	* ���������  �����������λ�ã�״ָ̬ʾ��������Ŀ
  * ���ֵ  ��  ��
  * �������ܣ�  ��ⰴ�����´���
 ******************************************************************************/  
void HUST_BUTTOM_STATUS_COUNT( GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin ,uint8_t Down_state, uint8_t GPIO_Number)
{
	if( Key_Scan( GPIOx, GPIO_Pin, Down_state) == KEY_ON)
	{
		Key_statenumber[GPIO_Number]++;
	}
}

/******************************************************************************
  * ������  ��  BUF_START
	* ���������  ��
  * ���ֵ  ��  ��
  * �������ܣ�  ���BUF_START�������´���
 ******************************************************************************/ 
void BUF_START(void)
{
	if( Key_Scan( GPIOC, GPIO_PIN_10, Down_State ) == KEY_ON)
	{
		HUST_BUTTOM_START_STATUS_COUNT++;
	}
}

/******************************************************************************
  * ������  ��  BUF_STOP
	* ���������  ��
  * ���ֵ  ��  ��
  * �������ܣ�  ���BUF_STOP�������´���
 ******************************************************************************/ 
void BUF_STOP(void)
{
	if( Key_Scan( GPIOC, GPIO_PIN_11, Down_State ) == KEY_ON)
	{
		HUST_BUTTOM_STOP_STATUS_COUNT++;
	}
}

/******************************************************************************
  * ������  ��  BUF_STOP1/2
	* ���������  ��
  * ���ֵ  ��  ��
  * �������ܣ�  ���BUF_STOP1/2P�������´���
 ******************************************************************************/ 
void BUF_STOP1(void)
{
	if( Key_Scan_Clock( GPIOA, GPIO_PIN_1, Down_State ) == KEY_ON)
	{
		HUST_BUTTOM_STOP1_STATUS_COUNT++;
	}
}

void BUF_STOP2(void)
{
	if( Key_Scan_Clock( GPIOA, GPIO_PIN_0, Down_State ) == KEY_ON)
	{
		HUST_BUTTOM_STOP2_STATUS_COUNT++;
	}
}




