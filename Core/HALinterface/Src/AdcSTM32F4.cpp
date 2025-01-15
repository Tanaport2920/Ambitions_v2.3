#include "../Inc/AdcSTM32F4.hpp"
#include "stm32f4xx_hal.h"
#include "../../Inc/adc.h"

AdcSTM32F4::AdcSTM32F4(ADC_HandleTypeDef* hadc)
    : m_hadc(hadc)
{
    MX_ADC1_Init();
    MX_ADC2_Init();
    MX_ADC3_Init();
}

uint16_t AdcSTM32F4::read(uint8_t channel) {
    // 1. ADC チャンネルを設定
    ADC_ChannelConfTypeDef sConfig = {0};

    // channel に応じて ADC_CHANNEL_0, ADC_CHANNEL_1 などを切り替える
    // (CubeMXなどで使っているチャンネル番号と対応づける)
    switch (channel) {
        case 0:
            sConfig.Channel = ADC_CHANNEL_0;
            break;
        case 1:
            sConfig.Channel = ADC_CHANNEL_1;
            break;
        // 必要に応じて追加...
        default:
            sConfig.Channel = ADC_CHANNEL_0; 
            break;
    }

    sConfig.Rank         = 1;  // シーケンス内での順位
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES; // サンプリング時間(必要に応じて変更)
    HAL_ADC_ConfigChannel(m_hadc, &sConfig);

    // 2. ADC開始
    HAL_ADC_Start(m_hadc);

    // 3. 変換完了待ち
    if (HAL_ADC_PollForConversion(m_hadc, 10) == HAL_OK) {
        // 4. 変換結果を取得 (12bit想定)
        return static_cast<uint16_t>(HAL_ADC_GetValue(m_hadc));
    }

    // 失敗したら0を返すなど
    return 0;
}
