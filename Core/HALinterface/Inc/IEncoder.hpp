#pragma once

#include <cstdint>
// エンコーダ用インターフェース
class IEncoder {
public:
    virtual ~IEncoder() = default;
    virtual int32_t getCount() const = 0;
    virtual void resetCount() = 0;
};