#pragma once

#include <stdint.h>         // uint8_t, uint32_t 等
#include "../../HALinterface/Inc/IGpio.hpp"        // GpioSTM32F4 が継承しているインターフェース
#include "stm32f4xx_hal.h"  // HAL_GetTick() を使うため

class Button {
public:
    // コンストラクタで使用する GPIO (IGpio*) と
    // ロング押し判定時間(ミリ秒)を渡す
    Button(IGpio* gpio, uint32_t longPressThresholdMs = 1000);

    // ボタンの状態を取得する
    //   押下→離したタイミングで押下時間を測り、On or LongOn を返す
    //   押されていない場合は Off
    uint8_t checkState();

private:
    IGpio*   m_gpio;
    uint32_t m_longPressThreshold; // ロング押し判定の閾値[ms]
    enum{
        Off = 0,
        On,
        LongOn
    };
};
