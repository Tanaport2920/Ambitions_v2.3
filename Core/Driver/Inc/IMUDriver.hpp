#pragma once

#include <stdint.h>
#include "../../HALinterface/Inc/SPISTM32F4.hpp"  // SPI通信用インターフェース

/**
 * @brief LSM6DSRなどのIMUを扱うクラス (抽象インターフェース ISpi は使わない)
 */
class Imu {
public:
    /**
     * @param spi  STM32F4用 SPIクラスへのポインタ
     */
    Imu(SPISTM32F4* spi);

    void Lsm6dsrPowerOn();
    float Lsm6dsrReadGyroZ();
    void gyro_get_ref();

private:
    // レジスタ読書き/書き
    uint8_t SpiReadBytes(uint8_t reg);
    void SpiWriteBytes(uint8_t reg, uint8_t data);
    void Lsm6dsrError(uint8_t whoami);

    SPISTM32F4* m_spi;  // ISpi ではなく SPISTM32F4 を直接持つ
    float gyro_reference;
};
