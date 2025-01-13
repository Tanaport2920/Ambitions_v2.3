#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#include "stm32f4xx_hal.h"
#ifdef __cplusplus
}
#endif

class Gpio
{
public:
    Gpio(GPIO_TypeDef* port, uint16_t pin)
        : m_port(port), m_pin(pin)
    {
    }

    void set()
    {
        HAL_GPIO_WritePin(m_port, m_pin, GPIO_PIN_SET);
    }

    void reset()
    {
        HAL_GPIO_WritePin(m_port, m_pin, GPIO_PIN_RESET);
    }

private:
    GPIO_TypeDef* m_port;
    uint16_t m_pin;
};