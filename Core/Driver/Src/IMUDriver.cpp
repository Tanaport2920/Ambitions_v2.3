#include "../Inc/IMUDriver.hpp"
#include "stm32f4xx_hal.h"  // printf, HAL_Delay
#include <cmath>            // M_PI
#include <cstdio>

Imu::Imu(SPISTM32F4* spi)
    : m_spi(spi)
    , gyro_reference(0.0f)
{
}

uint8_t Imu::SpiReadBytes(uint8_t reg) {
    uint8_t tx_data[2] = { static_cast<uint8_t>(reg | 0x80), 0x00 };
    uint8_t rx_data[2] = {0, 0};

    m_spi->resetChipSelect();
    m_spi->transmitReceive(tx_data, rx_data, 2, HAL_MAX_DELAY);
    m_spi->setChipSelect();

    return rx_data[1];
}

void Imu::SpiWriteBytes(uint8_t reg, uint8_t data) {
    uint8_t tx_data[2] = { static_cast<uint8_t>(reg & 0x7F), data };
    uint8_t rx_data[2] = {0, 0};

    m_spi->resetChipSelect();
    m_spi->transmitReceive(tx_data, rx_data, 2, HAL_MAX_DELAY);
    m_spi->setChipSelect();
}

void Imu::Lsm6dsrError(uint8_t whoami) {
    printf("Failed WHO_AM_I. 0x%02X != 0x6B\n", whoami);
}

void Imu::Lsm6dsrPowerOn() {
    HAL_Delay(100);

    uint8_t who_am_i = SpiReadBytes(0x0F);
    printf("WHO_AM_I: 0x%02X\n", who_am_i);

    if (who_am_i == 0x6B) {
        // CTRL1_XL(0x10)=0x84 → 1.66kHz, ±16g
        HAL_Delay(10);
        SpiWriteBytes(0x10, 0x84);

        // CTRL2_G(0x11)=0x81 → 1.66kHz, 4000dps
        HAL_Delay(10);
        SpiWriteBytes(0x11, 0x81);
        HAL_Delay(10);
    } else {
        Lsm6dsrError(who_am_i);
    }
}

float Imu::Lsm6dsrReadGyroZ() {
    uint8_t low  = SpiReadBytes(0x26);
    uint8_t high = SpiReadBytes(0x27);

    int16_t gyro_data = (int16_t)((high << 8) | low);
    float gyro_fix_data = (float)gyro_data - gyro_reference;

    // ±4000 dps → ~0.14 dps/LSB
    return (gyro_fix_data * 0.14f) * (M_PI / 180.0f);
}

void Imu::gyro_get_ref() {
    float accum = 0.0f;
    gyro_reference = 0.0f;

    for(int i=0; i<500; i++) {
        uint8_t low  = SpiReadBytes(0x26);
        uint8_t high = SpiReadBytes(0x27);
        int16_t gyro_z = (int16_t)((high << 8) | low);
        accum += (float)gyro_z;
        HAL_Delay(10);
    }

    gyro_reference = accum / 500.0f;
    printf("Gyro reference: %f\n", gyro_reference);
    HAL_Delay(10);
}