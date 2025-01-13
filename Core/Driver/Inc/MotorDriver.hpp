#pragma once

#include <stdint.h>          // uint8_t, etc.
#include "../../HALinterface/Inc/PwmSTM32F4.hpp"    // PWM抽象クラス(実装済み)
#include "../../HALinterface/Inc/GpioSTM32F4.hpp"   // GPIO抽象クラス(実装済み)

/**
 * @brief  単一モータ(左 or 右)を制御するクラス
 *         - PWM出力 (duty)
 *         - IN1,IN2ピン (GPIO)
 *         - 正転, 逆転, ブレーキ
 */
class MotorDriver {
public:
    /**
     * @param pwm       このモータに割り当てる PwmSTM32F4 インスタンスへのポインタ
     * @param channel   pwm->setDutyCycle(channel, duty) を呼ぶときのチャネル指定 (例: 0)
     * @param in1       回転方向制御ピン1
     * @param in2       回転方向制御ピン2
     * @param counterMax PWM CCR値を計算するときに使う最大値(Period)。例: 999等
     */
    MotorDriver(
        PwmSTM32F4* pwm,
        GpioSTM32F4* in1,
        GpioSTM32F4* in2,
        float counterMax = 999.0f
    );

    /**
     * @brief 時計回り (IN1=Low, IN2=Highなど)  
     * @param duty [0.0 ~ 1.0]
     */
    void clockwise(float duty);

    /**
     * @brief 反時計回り (IN1=High, IN2=Lowなど)
     * @param duty [0.0 ~ 1.0]
     */
    void counterClockwise(float duty);

    /**
     * @brief ブレーキ (IN1=High, IN2=High など)
     */
    void brake();

    /**
     * @brief -1.0~1.0 のdutyで回転
     *        負値 → 正転 (clockwise)
     *        正値 → 逆転 (counterClockwise)
     *        0    → ブレーキ
     */
    void setDuty(float duty);

private:
    PwmSTM32F4*   m_pwm;
    uint8_t       m_channel;
    GpioSTM32F4*  m_in1;
    GpioSTM32F4*  m_in2;
    float         m_counterMax;  // CCR計算用
};
