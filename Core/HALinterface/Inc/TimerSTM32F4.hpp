#pragma once

#include "ITimer.hpp"
#include "stm32f4xx_hal.h"

class TimerSTM32F4 : public ITimer {
public:
    TimerSTM32F4(TIM_HandleTypeDef* htim);

    virtual void start() override;
    virtual void stop() override;
    virtual void setCallback(void (*callback)()) override;

    // 割り込みハンドラから呼ばれるメソッド
    void onInterrupt();

private:
    TIM_HandleTypeDef* m_htim;
    void (*m_callback)() = nullptr;
};
