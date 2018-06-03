#pragma once

#include <cmath>
#include <algorithm>

#include "stm32f1xx_hal.h"

#include "accel_limited_controller.hpp"

namespace hustac {

class Servo {
public:
    Servo(TIM_HandleTypeDef* _htim, uint32_t _channel, float _range,
            float init_angle = 0, int _update_interval_ms = 100) :
            htim(_htim), channel(_channel), range(_range), controller(
                    init_angle, 0, _update_interval_ms) {
        controller.max_vel = 30;
        controller.max_accel = 30;
    }
    // �������
    void start() {
        HAL_TIM_PWM_Start(htim, channel);
        _set_pulse_width(_angle2width(controller.current_pos));
    }
    // ֹͣ���
    void stop() {
        HAL_TIM_PWM_Stop(htim, channel);
    }
    // �趨�����Ƕ�
    void set_angle(float angle) {
        controller.target_pos = angle;
    }
    // ��ȡ��ǰ�Ƕ�
    float get_angle() {
        return controller.current_pos;
    }
    // ���Ƹ���
    bool update() {
        if (controller.update()) {
            controller.current_vel = controller.output_vel;
            controller.current_pos = controller.output_pos;
            _set_pulse_width(_angle2width(controller.current_pos));
            return true;
        } else {
            return false;
        }
    }
private:
    int _angle2width(float angle) {
        angle /= range * (max_width_ms - min_width_ms);
        int ms = (int) std::round(angle);
        ms = std::min(ms, max_width_ms);
        ms = std::max(ms, min_width_ms);
        return ms;
    }
    void _set_pulse_width(int ms) {
        __HAL_TIM_SET_COMPARE(htim, channel, ms);
    }
public:
    TIM_HandleTypeDef* htim; // TIM��ʱ��
    uint32_t channel;		// TIMͨ��
    float range;			// ��ת��Χ/deg
    AccelLimitedController controller;
    int min_width_ms = 500;		// ��С����/ms
    int max_width_ms = 2500;		// �������/ms

};

extern Servo servo_yaw;
extern Servo servo_pitch;

}
