#include "../Inc/SPISTM32F4.hpp"

SPISTM32F4::SPISTM32F4(SPI_HandleTypeDef* hspi, GPIO_TypeDef* csPort, uint16_t csPin)
    : m_hspi(hspi)
    , m_csPort(csPort)
    , m_csPin(csPin)
{
    // CubeMX側で既にHAL_SPI_Init()済みを想定
}

void SPISTM32F4::resetChipSelect() {
    HAL_GPIO_WritePin(m_csPort, m_csPin, GPIO_PIN_RESET); // CS Low
}

void SPISTM32F4::setChipSelect() {
    HAL_GPIO_WritePin(m_csPort, m_csPin, GPIO_PIN_SET);   // CS High
}

void SPISTM32F4::transmitReceive(uint8_t* tx_data, uint8_t* rx_data, uint16_t size, uint32_t timeout) {
    HAL_SPI_TransmitReceive(m_hspi, tx_data, rx_data, size, timeout);
}