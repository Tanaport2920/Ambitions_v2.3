#pragma once

#include "stm32f4xx_hal.h"

class PwmSTM32F4 {
public:
    /**
     * @brief STM32F4 用 PWM クラス
     * @param htim     CubeMX生成の TIM_HandleTypeDef (ex: &htim1)
     * @param channel  TIM_CHANNEL_x (TIM_CHANNEL_1 等)
     */
    PwmSTM32F4(TIM_HandleTypeDef* htim, uint32_t channel);

    /**
     * @brief 0.0～1 の範囲でPWM値をセット
     */
    void setDutyCycle(float duty);

    /**
     * @brief PWM をスタート（必要なら呼ぶ）
     */
    void start();

    /**
     * @brief PWM をストップ
     */
    void stop();

private:
    TIM_HandleTypeDef* m_htim;
    uint32_t           m_channel;
};
