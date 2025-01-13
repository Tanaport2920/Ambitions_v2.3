#pragma once

#include <stdint.h>
#include "stm32f4xx_hal.h"

/**
 * @brief PhotoSensor クラス
 *
 * ADC1に4チャネル分の変換結果をDMAで取得し、
 * 各チャネルの最新の変換結果を返すクラスです。
 */
class PhotoSensor {
public:
    /**
     * @brief コンストラクタ
     * @param hadc         ADCハンドル（例：&hadc1）
     * @param dmaBuffer    DMAでADC変換結果を格納するバッファへのポインタ
     * @param bufferSize   dmaBufferのサイズ（この例では4）
     */
    PhotoSensor(ADC_HandleTypeDef* hadc, uint16_t* dmaBuffer, uint32_t bufferSize);

    /**
     * @brief ADCのDMA変換を開始する
     */
    void start();

    /**
     * @brief 指定したチャネル(index: 0～bufferSize-1)の最新のADC変換結果を返す
     * @param index チャネルのインデックス（0～3）
     * @return ADC変換値（uint16_t） 
     */
    uint16_t getValue(uint32_t index) const;

    /**
     * @brief DMA変換結果の全チャネルの値が入ったバッファを取得する（必要に応じて）
     * @return dmaBuffer ポインタ
     */
    const uint16_t* getAllValues() const { return m_dmaBuffer; }

private:
    ADC_HandleTypeDef* m_hadc;      ///< ADCハンドル
    uint16_t*          m_dmaBuffer; ///< DMA変換結果バッファ
    uint32_t           m_bufferSize;  ///< バッファのサイズ（チャネル数、例：4）
};
