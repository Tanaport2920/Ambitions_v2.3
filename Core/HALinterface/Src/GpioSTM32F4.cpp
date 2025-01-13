#include "../Inc/GpioSTM32F4.hpp"
#include "stm32f4xx_hal.h"

GpioSTM32F4::GpioSTM32F4(GPIO_TypeDef* port, uint16_t pin)
    : m_port(port), m_pin(pin)
{
    // GPIO初期化はCubeMXが行う想定
}

void GpioSTM32F4::setHigh() {
    HAL_GPIO_WritePin(m_port, m_pin, GPIO_PIN_SET);
}

void GpioSTM32F4::setLow() {
    HAL_GPIO_WritePin(m_port, m_pin, GPIO_PIN_RESET);
}

bool GpioSTM32F4::read() {
    GPIO_PinState state = HAL_GPIO_ReadPin(m_port, m_pin);
    return (state == GPIO_PIN_SET);
}
