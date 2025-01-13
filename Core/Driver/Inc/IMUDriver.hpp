#pragma once

#include <stdint.h>
#include "../../HALinterface/Inc/ISpi.hpp"   // インターフェースを使う

/**
 * @brief LSM6DSR等のIMUを操作するクラス
 *
 * SPI通信はISpiインターフェースを通じて行う
 */
class Imu {
public:
    /**
     * @param spi  このIMUが使うSPIインターフェース(実体は SPISTM32F4 など)
     */
    Imu(ISpi* spi);

    void Lsm6dsrPowerOn();
    float Lsm6dsrReadGyroZ();
    void gyro_get_ref();

private:
    // レジスタ読出し/書き込み
    uint8_t SpiReadBytes(uint8_t reg);
    void SpiWriteBytes(uint8_t reg, uint8_t data);
    void Lsm6dsrError(uint8_t whoami);

    ISpi* m_spi;       // SPIインターフェース
    float gyro_reference;
};
