#pragma once

#include <cstdint>
// GPIO制御用インターフェース (LED, Buttonにも使える)
class IGpio {
public:
    virtual ~IGpio() = default;
    virtual void setHigh() = 0;
    virtual void setLow() = 0;
    virtual bool read() = 0;
};