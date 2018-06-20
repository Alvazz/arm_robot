#pragma once

#include <cmath>
#include <algorithm>
#include <limits>

#include "stm32f1xx_hal.h"

#include "main_cpp.hpp"

class AccelLimitedController {
public:
    float current_pos;
    float current_vel;

    int update_interval_ms;
    int last_time_ms;

    float target_pos = 0;
    float target_vel = 0;

    float output_pos = 0;
    float output_vel = 0;

    float max_vel = std::numeric_limits<float>::infinity();
    float max_accel = std::numeric_limits<float>::infinity();
    float tol_pos = 0.001;

    AccelLimitedController(float _current_pos = 0, float _current_vel = 0,
            int _update_interval_ms = 10) :
            current_pos(_current_pos), current_vel(_current_vel), update_interval_ms(
                    _update_interval_ms), last_time_ms(HAL_GetTick()) {

    }

    bool update() {
        // �����������Ƿ񵽴�
        int now_time_ms = HAL_GetTick();
        if (now_time_ms - last_time_ms < update_interval_ms) {
            return false;
        }
        float actual_interval = (now_time_ms - last_time_ms) / 1000.0f;
        last_time_ms = now_time_ms;

        // λ����Сʱ, ��Ϊ����
        if (std::abs(target_pos - current_pos) <= tol_pos) {
            output_pos = target_pos;
            output_vel = 0;
            return true;
        }
        // λ�����
        float diff_pos = target_pos - current_pos;
        // ���쵽��
        float vel = diff_pos / update_interval_ms * 1000;
        // �����ٶ��������ٶȷ���, �������ٶ���Ϊ 0
        if (diff_pos * target_vel <= 0) {
            target_vel = 0;
        }
        // ���������ٶ�, ���㵱ǰλ�õ��������ٶ�
        float distance = std::abs(diff_pos);
        // �ַ��Ŵ���
        if (diff_pos > 0) {
            float limit_vel = std::sqrt(
                    2 * max_accel * distance + target_vel * target_vel);
            vel = std::min(vel, limit_vel);
        } else {
            float limit_vel = -std::sqrt(
                    2 * max_accel * distance + target_vel * target_vel);
            vel = std::max(vel, limit_vel);
        }
        // ���Ƽ��ٶ�
        float accel = (vel - current_vel) / actual_interval;
        accel = std::min(accel, max_accel);
        accel = std::max(accel, -max_accel);
        vel = current_vel + accel * actual_interval;
        // �����ٶ�
        vel = std::min(vel, max_vel);
        vel = std::max(vel, -max_vel);
        float pos = current_pos + vel * actual_interval;

        output_vel = vel;
        output_pos = pos;
//        terminal.nprintf<70>("servo: interval = %.3f,  pos = %.2f, vel = %.2f\n", 
//            actual_interval, pos, vel);
        return true;
    }
};
