/*
 * button.cpp
 *
 *  Created on: 2018��6��3��
 *      Author: shuixiang
 */

#include "main.h"

#include "button.hpp"

namespace hustac {

// �������Զ��ظ�
Button button_up(KEY_UP_GPIO_Port, KEY_UP_Pin, GPIO_PIN_RESET, 20, 1000, 100);
Button button_down(KEY_DN_GPIO_Port, KEY_DN_Pin, GPIO_PIN_RESET, 20, 1000, 100);
// �����󴥷���������
Button button_start(BUT_START_GPIO_Port, BUT_START_Pin, GPIO_PIN_RESET, 20, 1000, 0);
Button button_stop(BUT_STOP_GPIO_Port, BUT_STOP_Pin, GPIO_PIN_RESET, 20, 1000, 0);
// �������������
Button button_emergency_stop_left(BUT_STOP1_GPIO_Port, BUT_STOP1_Pin, GPIO_PIN_RESET, 20, 0, 0);
Button button_emergency_stop_right(BUT_STOP2_GPIO_Port, BUT_STOP2_Pin, GPIO_PIN_RESET, 20, 0, 0);

}

