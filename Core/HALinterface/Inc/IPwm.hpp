#pragma once

#include <cstdint>
// PWM用インターフェース
class IPwm {
public:
    virtual ~IPwm() = default;
    virtual void setDutyCycle(float duty) = 0;
};