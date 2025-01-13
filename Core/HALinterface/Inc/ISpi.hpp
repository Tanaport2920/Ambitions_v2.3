#pragma once
#include <stdint.h>

/**
 * @brief SPI通信の抽象インターフェース
 *
 * どのMCU実装でも差し替えられるように定義。
 */
class ISpi {
public:
    virtual ~ISpi() = default;

    /**
     * @brief チップセレクトをアクティブ(Low)にする
     */
    virtual void resetChipSelect() = 0;

    /**
     * @brief チップセレクトを非アクティブ(High)にする
     */
    virtual void setChipSelect() = 0;

    /**
     * @brief 送受信 (TxRx)
     * @param tx_data 送信バッファ
     * @param rx_data 受信バッファ
     * @param size    バイト数
     * @param timeout タイムアウト(msなど)
     */
    virtual void transmitReceive(uint8_t* tx_data, uint8_t* rx_data, uint16_t size, uint32_t timeout) = 0;
};
