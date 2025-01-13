#include "../Inc/PwmSTM32F4.hpp"
#include "stm32f4xx_hal.h"

PwmSTM32F4::PwmSTM32F4(TIM_HandleTypeDef* htim, uint32_t channel)
    : m_htim(htim)
    , m_channel(channel)
{
}

void PwmSTM32F4::start() {
    HAL_TIM_PWM_Start(m_htim, m_channel);
}

void PwmSTM32F4::stop() {
    HAL_TIM_PWM_Stop(m_htim, m_channel);
}

void PwmSTM32F4::setDutyCycle(float duty) {
    // 入力を 0～m_maxDuty にクリップ
    if (duty < 0.0f) {
        duty = 0.0f;
    }
    if (duty > 840.0f) {
        duty = 840.0f;
    }

    // CCR = duty
    __HAL_TIM_SET_COMPARE(m_htim, m_channel, (uint32_t)duty);
}
