#pragma once

#include <stdint.h>
#include "../../HALinterface/Inc/EncoderSTM32F4.hpp"  // EncoderSTM32F4 の定義があるとする

/**
 * @brief EncoderDriver は、EncoderSTM32F4 のラッパーとしてエンコーダから
 *        取得したカウンタ値の差分を用いて速度を計算する。
 * 
 * コンストラクタの inverted フラグで、差分計算の符号を反転させることができる（左／右で異なる向きの場合）。
 */
class EncoderDriver {
public:
    /**
     * @brief コンストラクタ
     * @param encoder    使用する EncoderSTM32F4 インスタンスへのポインタ
     * @param inverted   差分計算の符号を反転させる場合は true （例: 左側エンコーダ）
     */
    EncoderDriver(EncoderSTM32F4* encoder, bool inverted = false);

    /**
     * @brief エンコーダから計算した速度を返す
     * @return float 型の速度（単位は MPP, dt, ReductionRation の設定に依存）
     */
    float readVelocity();

private:
    EncoderSTM32F4* m_encoder;  // 対象のエンコーダインスタンス
    bool            m_inverted; // 差分計算で反転するかどうか
    int32_t         m_prevCount; // 前回のカウンタ値（初回はコンストラクタで取得）
};
