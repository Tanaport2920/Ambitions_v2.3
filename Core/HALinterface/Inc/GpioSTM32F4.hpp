#pragma once

#include "IGpio.hpp"
#include "stm32f4xx_hal.h"

class GpioSTM32F4 : public IGpio {
public:
    // コンストラクタでどのポート・ピンを使うかを受け取る
    GpioSTM32F4(GPIO_TypeDef* port, uint16_t pin);

    virtual void setHigh() override;
    virtual void setLow() override;
    virtual bool read() override;

private:
    GPIO_TypeDef* m_port;
    uint16_t      m_pin;
};
