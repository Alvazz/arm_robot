
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __key_H
#define __key_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "gpio.h"

/* ����һ��ö�������г���ϵͳ����״̬ */
typedef enum
{
    NoKeyDown = 0,
    KeySureDown ,
    OnceKeyDown,
    KeySureRelease
}StateStatus;


typedef enum
{
    ContinueNoKeyDown = 0,
    ContinueKeySureDown ,
    ContinueKeyDown,
    ContinueKeySureRelease
}Continue_StateStatus;

typedef enum
{
    Continue_No_Key_Down = 0,
    Continue_Key_Sure_Down ,
    Continue_Key_Down,
}Continue_State_Down_Status;

typedef enum
{
    Continue_No_Key_Release = 0,
    Continue_Key_Sure_Release ,
    Continue_Key_Release,
}Continue_State_Release_Status;
    

struct KeyStateStatus
{
	StateStatus Start_Status;
	StateStatus Stop_Status;
	Continue_StateStatus Stop1_Status;
	Continue_StateStatus Stop2_Status;
};

struct Continue_Key_Down_StateStatus
{
	Continue_State_Down_Status Stop_one_Status;
	Continue_State_Down_Status Stop_two_Status;
};

struct Continue_Key_Release_StateStatus
{
	Continue_State_Release_Status Stop_one_Status;
	Continue_State_Release_Status Stop_two_Status;
};

extern uint32_t HUST_BUTTOM_START_STATUS_COUNT_ONE ; //BUF_START��������
extern uint32_t HUST_BUTTOM_STOP_STATUS_COUNT_ONE  ; //BUF_STOP��������
extern uint32_t HUST_BUTTOM_STOP1_STATUS_COUNT_ONE ; //BUF_STOP1��������
extern uint32_t HUST_BUTTOM_STOP2_STATUS_COUNT_ONE ; //BUF_STOP1��������
extern uint32_t HUST_BUTTOM_STOP1_STATUS_FLAG ;      //BUF_STOP1��־λ
extern uint32_t HUST_BUTTOM_STOP2_STATUS_FLAG ;      //BUF_STOP2��־λ

 /***************************************
* �������ܣ�����Ƿ��а�������
 ***************************************/
static StateStatus KeyStatus_Once(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,uint8_t Down_state);

/******************************************************************************
  * ������  ��  KeyStatus_Continue
  * �������ܣ�  ��ⰴ���Ƿ񱻳���
 ******************************************************************************/
static Continue_StateStatus KeyStatus_Continue(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,uint8_t Down_state);

/******************************************************************************
  * ������  ��  Buttom_Status_Continue_Down
  * �������ܣ�  ��ⰴ���Ƿ񱻳�����û���ɿ�
 ******************************************************************************/
static Continue_State_Down_Status Buttom_Status_Continue_Down(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,uint8_t Down_state);

/******************************************************************************
  * ������  ��  Buttom_Status_Continue_Release
  * �������ܣ�  ��ⰴ���Ƿ񱻳�����û���ɿ�
 ******************************************************************************/
static Continue_State_Release_Status Buttom_Status_Continue_Release(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,uint8_t Down_state);

 /***************************************
* �������ܣ���¼BUT_START�������´���
 ***************************************/
void HUST_BUTTOM_START_STATUS(void);

 /***************************************
* �������ܣ���¼BUT_STOP�������´���
 ***************************************/
void HUST_BUTTOM_STOP_STATUS(void);

 /***************************************
* �������ܣ���¼BUT_STOP1�������´���
 ***************************************/
void HUST_BUTTOM_STOP1_STATUS(void);

 /***************************************
* �������ܣ���¼BUT_STOP2�������´���
 ***************************************/
void HUST_BUTTOM_STOP2_STATUS(void);

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
