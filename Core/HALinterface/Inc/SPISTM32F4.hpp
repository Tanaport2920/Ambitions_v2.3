#pragma once

#include "ISpi.hpp"
#include "stm32f4xx_hal.h"

/**
 * @brief STM32F4 HALを使ってSPI通信を行うクラス
 *        ISpiインターフェースを実装する
 */
class SPISTM32F4 : public ISpi {
public:
    /**
     * @param hspi   CubeMX等で生成された SPI_HandleTypeDef (例: &hspi3)
     * @param csPort GPIOポート (例: GPIOA)
     * @param csPin  GPIOピン   (例: GPIO_PIN_4)
     */
    SPISTM32F4(SPI_HandleTypeDef* hspi, GPIO_TypeDef* csPort, uint16_t csPin);
    virtual ~SPISTM32F4() = default;

    // ISpiインターフェース実装
    virtual void resetChipSelect() override;
    virtual void setChipSelect() override;
    virtual void transmitReceive(uint8_t* tx_data, uint8_t* rx_data, uint16_t size, uint32_t timeout) override;

private:
    SPI_HandleTypeDef* m_hspi;
    GPIO_TypeDef*      m_csPort;
    uint16_t           m_csPin;
};
