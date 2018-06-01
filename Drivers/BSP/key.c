/******************************************************************************
 * �ļ���  ��  key.c
 * �ļ����ܣ�  ��ⰴ���Ƿ񱻰����Լ���¼���´�����״̬����
 ******************************************************************************/
#include "key.h"

uint32_t HUST_BUTTOM_START_STATUS_COUNT_ONE = 0; //BUF_START��������
uint32_t HUST_BUTTOM_STOP_STATUS_COUNT_ONE = 0; //BUF_STOP��������
uint32_t HUST_BUTTOM_STOP1_STATUS_COUNT_ONE = 0; //BUF_STOP1��������
uint32_t HUST_BUTTOM_STOP2_STATUS_COUNT_ONE = 0; //BUF_STOP1��������
uint32_t HUST_BUTTOM_STOP1_STATUS_FLAG = 0;      //BUF_STOP1��־λ
uint32_t HUST_BUTTOM_STOP2_STATUS_FLAG = 0;      //BUF_STOP2��־λ

static struct KeyStateStatus Statusstate = { NoKeyDown, NoKeyDown,
        ContinueNoKeyDown, ContinueNoKeyDown };
static struct Continue_Key_Down_StateStatus Continue_Key_Down_state = {
        Continue_No_Key_Down, Continue_No_Key_Down };
static struct Continue_Key_Release_StateStatus Continue_Key_Release_state = {
        Continue_No_Key_Release, Continue_No_Key_Release };
static uint8_t Down_State_key = 0;              //��������ʱ�ĵ�ƽ��1Ϊ�ߵ�ƽ��0Ϊ�͵�ƽ
static uint32_t tickstart = 0;
static uint32_t tickstart_Continue = 0;
static StateStatus state_Once = NoKeyDown;
static Continue_StateStatus state_Continue = ContinueNoKeyDown;
/******************************************************************************
 * ������  ��  KeyStatus
 * �������ܣ�  ��ⰴ���Ƿ񱻰���
 ******************************************************************************/
static StateStatus KeyStatus_Once(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,
        uint8_t Down_state) {
    StateStatus KeyReturn = NoKeyDown;
    uint32_t KeyPress = 1;
    if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == Down_state)   //��ȡ��������
            {
        KeyPress = 0;
    }
    if (GPIOx == GPIOC && GPIO_Pin == GPIO_PIN_10) {
        state_Once = Statusstate.Start_Status;
    }
    if (GPIOx == GPIOC && GPIO_Pin == GPIO_PIN_11) {
        state_Once = Statusstate.Stop_Status;
    }
    switch (state_Once) {
    case NoKeyDown:
        if (!KeyPress) {
            state_Once = KeySureDown;
            tickstart = HAL_GetTick();
        }
        break;
    case KeySureDown:
        if (!KeyPress) {
            if (HAL_GetTick() - tickstart >= 100) {
                state_Once = OnceKeyDown;
                KeyReturn = OnceKeyDown;
            }
        } else
            state_Once = NoKeyDown;
        break;
    case OnceKeyDown:
        if (KeyPress)    //��������ɿ�������Ϊ����������
        {
            state_Once = KeySureRelease;
            tickstart = HAL_GetTick();
        }
        break;
    case KeySureRelease:
        if (KeyPress) {
            if (HAL_GetTick() - tickstart >= 50) {
                state_Once = NoKeyDown;
                KeyReturn = NoKeyDown;
            }
        } else
            state_Once = OnceKeyDown;
    }
    if (GPIOx == GPIOC && GPIO_Pin == GPIO_PIN_10) {
        Statusstate.Start_Status = state_Once;
    }
    if (GPIOx == GPIOC && GPIO_Pin == GPIO_PIN_11) {
        Statusstate.Stop_Status = state_Once;
    }
    return KeyReturn;
}

/******************************************************************************
 * ������  ��  KeyStatus_Continue
 * �������ܣ�  ��ⰴ���Ƿ񱻳���
 ******************************************************************************/
static Continue_StateStatus KeyStatus_Continue(GPIO_TypeDef* GPIOx,
        uint16_t GPIO_Pin, uint8_t Down_state) {
    Continue_StateStatus KeyReturn = ContinueKeySureDown;
    uint32_t KeyPress = 1;
    if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == Down_state)   //��ȡ��������
            {
        KeyPress = 0;
    }
    if (GPIOx == GPIOA && GPIO_Pin == GPIO_PIN_1) {
        state_Continue = Statusstate.Stop1_Status;
    }
    if (GPIOx == GPIOA && GPIO_Pin == GPIO_PIN_0) {
        state_Continue = Statusstate.Stop2_Status;
    }
    switch (state_Continue) {
    case ContinueNoKeyDown:
        if (!KeyPress) {
            state_Continue = ContinueKeySureDown;
            tickstart_Continue = HAL_GetTick();
        }
        break;
    case ContinueKeySureDown:
        if (!KeyPress) {
            if (HAL_GetTick() - tickstart_Continue >= 100) {
                state_Continue = ContinueKeyDown;
                KeyReturn = ContinueKeyDown;
            }
        } else
            state_Continue = ContinueNoKeyDown;
        break;
    case ContinueKeyDown:
        if (!KeyPress) {
            state_Continue = ContinueKeyDown;
            KeyReturn = ContinueKeyDown;
        }
        if (KeyPress)    //��������ɿ�������Ϊ����������
        {
            state_Continue = ContinueKeySureRelease;
            tickstart_Continue = HAL_GetTick();
        }
        break;
    case KeySureRelease:
        if (KeyPress) {
            if (HAL_GetTick() - tickstart_Continue >= 100) {
                state_Continue = ContinueNoKeyDown;
                KeyReturn = ContinueNoKeyDown;
            }
        } else
            state_Continue = ContinueKeyDown;
    }
    if (GPIOx == GPIOA && GPIO_Pin == GPIO_PIN_1) {
        Statusstate.Stop1_Status = state_Continue;
    }
    if (GPIOx == GPIOA && GPIO_Pin == GPIO_PIN_0) {
        Statusstate.Stop2_Status = state_Continue;
    }
    return KeyReturn;
}

/******************************************************************************
 * ������  ��  Buttom_Status_Continue_Down
 * �������ܣ�  ��ⰴ���Ƿ񱻳�����û���ɿ�
 ******************************************************************************/
static Continue_State_Down_Status Buttom_Status_Continue_Down(
        GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t Down_state) {
    Continue_State_Down_Status KeyReturn = Continue_No_Key_Down;
    uint32_t KeyPress = 1;
    Continue_State_Down_Status state_Continue_Down = Continue_No_Key_Down;
    if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == Down_state)   //��ȡ��������
            {
        KeyPress = 0;
        if (GPIOx == GPIOA && GPIO_Pin == GPIO_PIN_1) {
            state_Continue_Down = Continue_Key_Down_state.Stop_one_Status;
        }
        if (GPIOx == GPIOA && GPIO_Pin == GPIO_PIN_0) {
            state_Continue_Down = Continue_Key_Down_state.Stop_two_Status;
        }
    }
    switch (state_Continue_Down) {
    case Continue_No_Key_Down:
        if (!KeyPress) {
            state_Continue_Down = Continue_Key_Sure_Down;
            tickstart_Continue = HAL_GetTick();
        }
        break;
    case Continue_Key_Sure_Down:
        if (!KeyPress) {
            if (HAL_GetTick() - tickstart_Continue >= 1000) {
                state_Continue_Down = Continue_Key_Down;
                KeyReturn = Continue_Key_Down;
            }
        } else
            state_Continue_Down = Continue_No_Key_Down;
        break;
    case Continue_Key_Down:
        if (!KeyPress) {
            state_Continue_Down = Continue_Key_Down;
            KeyReturn = Continue_Key_Down;
        }
        break;
    }
    if (GPIOx == GPIOA && GPIO_Pin == GPIO_PIN_1) {
        Continue_Key_Down_state.Stop_one_Status = state_Continue_Down;
    }
    if (GPIOx == GPIOA && GPIO_Pin == GPIO_PIN_0) {
        Continue_Key_Down_state.Stop_two_Status = state_Continue_Down;
    }
    return KeyReturn;
}

/******************************************************************************
 * ������  ��  Buttom_Status_Continue_Release
 * �������ܣ�  ��ⰴ���Ƿ񱻳������ɿ�
 ******************************************************************************/
static Continue_State_Release_Status Buttom_Status_Continue_Release(
        GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t Down_state) {
    Continue_State_Release_Status KeyReturn = Continue_No_Key_Release;
    uint32_t KeyPress = 1;
    Continue_State_Release_Status state_Continue_Release =
            Continue_No_Key_Release;
    if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) != Down_state)   //��ȡ��������
            {
        KeyPress = 0;
        if (GPIOx == GPIOA && GPIO_Pin == GPIO_PIN_1) {
            state_Continue_Release = Continue_Key_Release_state.Stop_one_Status;
        }
        if (GPIOx == GPIOA && GPIO_Pin == GPIO_PIN_0) {
            state_Continue_Release = Continue_Key_Release_state.Stop_two_Status;
        }
    }
    switch (state_Continue_Release) {
    case Continue_No_Key_Release:
        if (!KeyPress) {
            state_Continue_Release = Continue_Key_Sure_Release;
            tickstart_Continue = HAL_GetTick();
        }
        break;
    case Continue_Key_Sure_Release:
        if (!KeyPress) {
            if (HAL_GetTick() - tickstart_Continue >= 1000) {
                state_Continue_Release = Continue_Key_Release;
                KeyReturn = Continue_Key_Release;
            }
        } else
            state_Continue_Release = Continue_No_Key_Release;
        break;
    case Continue_Key_Release:
        if (!KeyPress) {
            state_Continue_Release = Continue_Key_Release;
            KeyReturn = Continue_Key_Release;
        }
        break;
    }
    if (GPIOx == GPIOA && GPIO_Pin == GPIO_PIN_1) {
        Continue_Key_Release_state.Stop_one_Status = state_Continue_Release;
    }
    if (GPIOx == GPIOA && GPIO_Pin == GPIO_PIN_0) {
        Continue_Key_Release_state.Stop_two_Status = state_Continue_Release;
    }
    return KeyReturn;
}

/******************************************************************************
 * ������  ��  HUST_BUTTOM_START_STATUS
 * �������ܣ�  ���BUF_START�������´���
 ******************************************************************************/
void HUST_BUTTOM_START_STATUS(void) {
    if (KeyStatus_Once( GPIOC, GPIO_PIN_10, Down_State_key) == OnceKeyDown) {
        HUST_BUTTOM_START_STATUS_COUNT_ONE++;
    }
}

/******************************************************************************
 * ������  ��  HUST_BUTTOM_STOP_STATUS
 * �������ܣ�  ���BUF_STOP�������´���
 ******************************************************************************/
void HUST_BUTTOM_STOP_STATUS(void) {
    if (KeyStatus_Once( GPIOC, GPIO_PIN_11, Down_State_key) == OnceKeyDown) {
        HUST_BUTTOM_STOP_STATUS_COUNT_ONE++;
    }
}

/******************************************************************************
 * ������  ��  HUST_BUTTOM_STOP1_STATUS
 * �������ܣ�  ���BUF_STOP1�������´���
 ******************************************************************************/
void HUST_BUTTOM_STOP1_STATUS(void) {
    Continue_StateStatus KeyReturn = ContinueKeySureDown;
    KeyReturn = KeyStatus_Continue( GPIOA, GPIO_PIN_1, Down_State_key);
    if (KeyReturn == ContinueKeyDown) {
        HUST_BUTTOM_STOP1_STATUS_FLAG = 1;
    } else if (KeyReturn == ContinueNoKeyDown) {
        HUST_BUTTOM_STOP1_STATUS_FLAG = 0;
    }
}

/******************************************************************************
 * ������  ��  HUST_BUTTOM_STOP2_STATUS
 * �������ܣ�  ���BUF_STOP2�������´���
 ******************************************************************************/
void HUST_BUTTOM_STOP2_STATUS(void) {
    Continue_StateStatus KeyReturn = ContinueKeySureDown;
    KeyReturn = KeyStatus_Continue( GPIOA, GPIO_PIN_0, Down_State_key);
    if (KeyReturn == ContinueKeyDown) {
        HUST_BUTTOM_STOP2_STATUS_FLAG = 1;
    } else if (KeyReturn == ContinueNoKeyDown) {
        HUST_BUTTOM_STOP2_STATUS_FLAG = 0;
    }
}

/******************************************************************************
 * ������  ��  HUST_BUTTOM_STOP_ONE_STATUS
 * �������ܣ�  ���BUF_STOP2��������
 ******************************************************************************/
void HUST_BUTTOM_STOP_TWO_STATUS(void) {
    if (Buttom_Status_Continue_Down( GPIOA, GPIO_PIN_0, Down_State_key)
            == Continue_Key_Down) {
    }
    if (Buttom_Status_Continue_Release( GPIOA, GPIO_PIN_0, Down_State_key)
            == Continue_Key_Down) {
    }
}

/******************************************************************************
 * ������  ��  HUST_BUTTOM_STOP_ONE_STATUS
 * �������ܣ�  ���BUF_STOP1��������
 ******************************************************************************/
void HUST_BUTTOM_STOP_ONE_STATUS(void) {
    if (Buttom_Status_Continue_Down( GPIOA, GPIO_PIN_1, Down_State_key)
            == Continue_Key_Down) {
    }
    if (Buttom_Status_Continue_Release( GPIOA, GPIO_PIN_1, Down_State_key)
            == Continue_Key_Down) {
    }
}

