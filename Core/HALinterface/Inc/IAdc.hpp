#pragma once

#include <cstdint>
// ADC用インターフェース
class IAdc {
public:
    virtual ~IAdc() = default;
    virtual uint16_t read(uint8_t channel) = 0;
};