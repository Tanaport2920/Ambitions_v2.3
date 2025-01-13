#pragma once

#include <cstdint>
// タイマ用インターフェース
class ITimer {
public:
    virtual ~ITimer() = default;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void setCallback(void (*callback)()) = 0; 
    // 1kHz割り込みを発生させるなど
};