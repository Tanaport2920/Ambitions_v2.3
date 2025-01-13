#pragma once

#include "IAdc.hpp"
#include "stm32f4xx_hal.h"  // HAL関連のヘッダ

class AdcSTM32F4 : public IAdc {
public:
    // コンストラクタで、使用するADCハンドルとチャンネル設定などを受け取る
    AdcSTM32F4(ADC_HandleTypeDef* hadc);

    // IAdcインターフェースの実装
    virtual uint16_t read(uint8_t channel) override;

private:
    ADC_HandleTypeDef* m_hadc;
};
