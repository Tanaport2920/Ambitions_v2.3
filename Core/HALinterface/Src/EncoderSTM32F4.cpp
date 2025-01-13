#include "../Inc/EncoderSTM32F4.hpp"
#include "stm32f4xx_hal.h"

EncoderSTM32F4::EncoderSTM32F4(TIM_HandleTypeDef* htim)
    : m_htim(htim)
{
    // エンコーダモードで初期化後、カウントスタート
    // CubeMXのMX_TIMx_Init() で Encoder mode に設定しておく
    HAL_TIM_Encoder_Start(m_htim, TIM_CHANNEL_ALL);
}

int32_t EncoderSTM32F4::getCount() const {
    // CNT レジスタを取得
    return static_cast<int32_t>(__HAL_TIM_GET_COUNTER(m_htim));
}

void EncoderSTM32F4::resetCount() {
    __HAL_TIM_SET_COUNTER(m_htim, 0);
}

void EncoderSTM32F4::start(){
    HAL_TIM_Encoder_Start(m_htim, TIM_CHANNEL_ALL);
}

void EncoderSTM32F4::stop(){
    HAL_TIM_Encoder_Stop(m_htim, TIM_CHANNEL_ALL);
}

