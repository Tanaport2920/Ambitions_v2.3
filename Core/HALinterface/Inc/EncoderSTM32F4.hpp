#pragma once

#include "IEncoder.hpp"
#include "stm32f4xx_hal.h"

class EncoderSTM32F4 : public IEncoder {
public:
    EncoderSTM32F4(TIM_HandleTypeDef* htim);

    virtual int32_t getCount() const override;
    virtual void resetCount() override;

    /**
     * @brief エンコーダを開始する
     */
    void start();

    /**
     * @brief エンコーダを停止する
     */
    void stop();

private:
    TIM_HandleTypeDef* m_htim;
};
