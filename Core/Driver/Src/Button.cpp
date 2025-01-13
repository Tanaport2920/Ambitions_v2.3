#include "../Inc/button.hpp"

Button::Button(IGpio* gpio, uint32_t longPressThresholdMs)
    : m_gpio(gpio)
    , m_longPressThreshold(longPressThresholdMs)
{
    // 必要ならコンストラクタで初期化処理
}

uint8_t Button::checkState()
{
    // ボタンが押されている(LOW)か確認
    if (!m_gpio->read()) { // 例: false == 押下
        // 押下開始時刻を記録
        uint32_t btnStartTime = HAL_GetTick();

        // ボタンが離される(=HIGH)まで待つ (ブロッキング)
        while (!m_gpio->read()) {
            // 必要ならここで小さなウェイトや
            // ウォッチドッグのリフレッシュなどを挟む
        }
        
        // 離されたタイミングの時刻
        uint32_t btnEndTime = HAL_GetTick();
        // 押下時間を計算
        uint32_t elapsed = btnEndTime - btnStartTime;

        // 閾値より短ければ On、長ければ LongOn
        if (elapsed < m_longPressThreshold) {
            return On;
        } else {
            return LongOn;
        }
    }
    // 押されていなければ Off
    return Off;
}
