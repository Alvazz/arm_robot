/*
 * high_resolution_clock.h
 *
 *  Created on: 2018��6��4��
 *      Author: shuixiang
 */

#ifndef BSP_HIGH_RESOLUTION_CLOCK_H_
#define BSP_HIGH_RESOLUTION_CLOCK_H_

#include "stm32f1xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ͨ�� SysTick ��ȡ���������ڵ�CPUʱ����
// ע��: ʹ�øú�����Ҫȷ�� SysTick �ж�Ϊʹ��״̬
static uint64_t MY_GetCycleCount(void) {
    uint32_t tick_0, tick_1;
    uint32_t count;
    // �ظ���ȡ������ֵ, ֱ��ȷ�� uwTick �� SysTick->VAL ��ͬ����
    do {
        tick_0 = HAL_GetTick();
        count = SysTick->VAL;
        tick_1 = HAL_GetTick();
    } while (tick_0 != tick_1);
    // SysTick ������Ϊ SysTick->LOAD + 1, SysTick Ϊ����ʱ
    return (uint64_t)tick_0 * (SysTick->LOAD + 1) + (SysTick->LOAD - count);
}

/* ͨ�� DWT ��ȡʱ��� */
// ʹ�� DWT ��ʱ��
static void MY_DWTTimerInit(void) {
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    // volatile uint32_t *DWT_LAR  = (uint32_t *) 0xE0001FB0;
    // *DWT_LAR = 0xC5ACCE55;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

extern volatile uint64_t MY_DWT_LAST_CYCLE_COUNT;

// ͨ�� DWT ��ȡ���������ڵ�CPUʱ����
// ע��: ÿ2^32��ʱ������(72M Ƶ����Լ 59.65��), ����Ӧ���øú���һ��
static uint64_t MY_DWTGetCycleCount(void) {
    // ʹ�� J-Link ���س����, ���ܻ��Զ����� trace, ��Ҫ��֤Ϊʹ��״̬
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    // ��¼�ж�ʹ��״̬, ����ͣ�ж�
    uint32_t primask = __get_PRIMASK();
    __disable_irq();
    // ���㵱ǰCPU������
    MY_DWT_LAST_CYCLE_COUNT += DWT->CYCCNT - (uint32_t)(MY_DWT_LAST_CYCLE_COUNT);
    // �ָ��ж�
    __set_PRIMASK(primask);
    return MY_DWT_LAST_CYCLE_COUNT;
}

static uint64_t MY_GetNanoSecFromCycle(uint64_t cpu_cycle_count) {
    uint32_t sec = cpu_cycle_count / SystemCoreClock;
    uint32_t nsec = (cpu_cycle_count % SystemCoreClock) * 1000000000 / SystemCoreClock;
    return (uint64_t)sec * 1000000000 + nsec;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BSP_HIGH_RESOLUTION_CLOCK_H_ */
