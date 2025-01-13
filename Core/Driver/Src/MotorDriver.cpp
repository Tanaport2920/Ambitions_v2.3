#include "../Inc/MotorDriver.hpp"
#include <algorithm>  // std::clamp (C++17以降)

// コンストラクタ
MotorDriver::MotorDriver(
    PwmSTM32F4* pwm,
    GpioSTM32F4* in1,
    GpioSTM32F4* in2,
    float counterMax
)
: m_pwm(pwm)
, m_in1(in1)
, m_in2(in2)
, m_counterMax(counterMax)
{
}

// 時計回り
void MotorDriver::clockwise(float duty) {
    if (duty < 0.0f)  duty = 0.0f;
    if (duty > 1.0f)  duty = 1.0f;

    // 例: IN1 = Low, IN2 = High
    m_in1->setLow();
    m_in2->setHigh();

    float ccrVal = duty * m_counterMax;
    m_pwm->setDutyCycle(ccrVal);
}

// 反時計回り
void MotorDriver::counterClockwise(float duty) {
    if (duty < 0.0f)  duty = 0.0f;
    if (duty > 1.0f)  duty = 1.0f;

    // 例: IN1 = High, IN2 = Low
    m_in1->setHigh();
    m_in2->setLow();

    float ccrVal = duty * m_counterMax;
    m_pwm->setDutyCycle(ccrVal);
}

// ブレーキ
void MotorDriver::brake() {
    // 例: IN1=High, IN2=High
    m_in1->setHigh();
    m_in2->setHigh();
    // 必要なら PWMを0%にするか停止する
    m_pwm->setDutyCycle(0.0f);
    // m_pwm->stop(); // stop()を定義しているなら
}

// setDuty : -1.0 ~ +1.0
void MotorDriver::setDuty(float duty) {
    // 小数点取り扱いに注意
    // 例: duty < 0 → 時計回り, duty > 0 → 反時計回り, 0 → ブレーキ
    if (duty > 0.0f) {
        counterClockwise(duty);  // 正→反時計
    }
    else if (duty < 0.0f) {
        clockwise(-duty);        // 負→時計回り
    }
    else {
        brake();
    }
}
