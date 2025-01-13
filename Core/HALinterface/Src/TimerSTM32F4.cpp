#include "../Inc/TimerSTM32F4.hpp"
#include "stm32f4xx_hal.h"

// グローバル or static 変数として、どのTimerSTM32F4インスタンスが
// どのTIM_HandleTypeDefと結びついているか管理が必要になる場合があります。
// もしくは、TIMハンドラの "UserData" にthisポインタを入れる手段もあります。

TimerSTM32F4::TimerSTM32F4(TIM_HandleTypeDef* htim)
    : m_htim(htim)
{
    // ここで初期化はCubeMX側の MX_TIMx_Init() がやるケースが多いです
}

void TimerSTM32F4::start() {
    HAL_TIM_Base_Start_IT(m_htim); // 割り込み有効でスタート
}

void TimerSTM32F4::stop() {
    HAL_TIM_Base_Stop_IT(m_htim);
}

void TimerSTM32F4::setCallback(void (*callback)()) {
    m_callback = callback;
}

// 割り込みハンドラ (HAL_TIM_PeriodElapsedCallback) から呼ばれる想定
void TimerSTM32F4::onInterrupt() {
    if (m_callback) {
        m_callback();
    }
}
