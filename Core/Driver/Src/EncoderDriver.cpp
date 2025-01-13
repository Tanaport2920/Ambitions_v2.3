#include <math.h>
#include "../Inc/EncoderDriver.hpp"
#include "stm32f4xx_hal.h"
#include "../../params.h"  // MPP, dt, ReductionRation, ENC_RES_HALF, ENC_RES_MAX が定義されている前提

// コンストラクタ
EncoderDriver::EncoderDriver(EncoderSTM32F4* encoder, bool inverted)
    : m_encoder(encoder)
    , m_inverted(inverted)
{
    // 初回のカウンタ値を取得しておく
    m_prevCount = m_encoder->getCount();
}

float EncoderDriver::readVelocity() {
    // 現在のカウンタ値を取得
    int32_t currentCount = m_encoder->getCount();
    int32_t diff = 0;

    // 右側エンコーダの場合： diff = current - previous
    // 左側の場合は反転： diff = previous - current
    if (m_inverted) {
        diff = m_prevCount - currentCount;
    } else {
        diff = currentCount - m_prevCount;
    }

    // ラップアラウンド（カウンタのオーバーフローまたはアンダーフロー）の補正
    // ※ ENC_RES_HALF, ENC_RES_MAX は params.h に定義されているとする
    if ((diff > ENC_RES_HALF || diff < -ENC_RES_HALF) && m_prevCount > ENC_RES_HALF) {
        diff = ((ENC_RES_MAX - 1) - m_prevCount) + currentCount;
    }
    else if ((diff > ENC_RES_HALF || diff < -ENC_RES_HALF) && m_prevCount <= ENC_RES_HALF) {
        diff = m_prevCount + ((ENC_RES_MAX - 1) - currentCount);
    }
    
    // 更新：次回計算用に現在値を保存
    m_prevCount = currentCount;
    
    // 速度換算： (diff * MPP) / (dt * ReductionRation)
    float velocity = ((float)diff * MPP) / (dt * ReductionRation);
    return velocity;
}
