#include "../Inc/PhotoSensor.hpp"

PhotoSensor::PhotoSensor(ADC_HandleTypeDef* hadc, uint16_t* dmaBuffer, uint32_t bufferSize)
    : m_hadc(hadc)
    , m_dmaBuffer(dmaBuffer)
    , m_bufferSize(bufferSize)
{
}

void PhotoSensor::start() {
    // ADC1をDMAモードでスタートする
    // 第3引数にバッファのサイズ（チャネル数）を渡す
    if (HAL_ADC_Start_DMA(m_hadc, (uint32_t*)m_dmaBuffer, m_bufferSize) != HAL_OK) {
        // エラー処理（必要なら）
    }
}

uint16_t PhotoSensor::getValue(uint32_t index) const {
    if (index < m_bufferSize) {
        return m_dmaBuffer[index];
    } else {
        // indexエラーの場合は0を返すか、別のエラー処理を行う
        return 0;
    }
}
