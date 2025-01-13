#pragma once

#include "../../HALinterface/Inc/GpioSTM32F4.hpp"

class LEDController {
public:
    /**
     * @brief コンストラクタ
     * @param sensorLED_FL センサLED Front-Left の GPIO ポインタ
     * @param sensorLED_FR センサLED Front-Right の GPIO ポインタ
     * @param sensorLED_R  センサLED Right の GPIO ポインタ
     * @param sensorLED_L  センサLED Left の GPIO ポインタ
     * @param led_FL       通常LED Front-Left の GPIO ポインタ
     * @param led_FR       通常LED Front-Right の GPIO ポインタ
     * @param led_R        通常LED Right の GPIO ポインタ
     * @param led_L        通常LED Left の GPIO ポインタ
     * @param modeLED1     モードLED1 の GPIO ポインタ
     * @param modeLED2     モードLED2 の GPIO ポインタ
     * @param modeLED3     モードLED3 の GPIO ポインタ
     */
    LEDController(
        GpioSTM32F4* sensorLED_FL,
        GpioSTM32F4* sensorLED_FR,
        GpioSTM32F4* sensorLED_R,
        GpioSTM32F4* sensorLED_L,
        GpioSTM32F4* led_FL,
        GpioSTM32F4* led_FR,
        GpioSTM32F4* led_R,
        GpioSTM32F4* led_L,
        GpioSTM32F4* modeLED1,
        GpioSTM32F4* modeLED2,
        GpioSTM32F4* modeLED3
    );

    // センサLEDグループ制御
    void setSensorLED(bool fl, bool fr, bool r, bool l);
    void sensorLEDOn();
    void sensorLEDOff();

    // 通常LEDグループ制御
    void setLED(bool fl, bool fr, bool r, bool l);
    void turnAllLEDOn();
    void turnAllLEDOff();

    // モードLEDグループ制御
    void setModeLED(uint8_t mode);

private:
    // センサLED群
    GpioSTM32F4* m_sensorLED_FL;
    GpioSTM32F4* m_sensorLED_FR;
    GpioSTM32F4* m_sensorLED_R;
    GpioSTM32F4* m_sensorLED_L;

    // 通常LED群
    GpioSTM32F4* m_led_FL;
    GpioSTM32F4* m_led_FR;
    GpioSTM32F4* m_led_R;
    GpioSTM32F4* m_led_L;

    // モードLED群
    GpioSTM32F4* m_modeLED1;
    GpioSTM32F4* m_modeLED2;
    GpioSTM32F4* m_modeLED3;

    uint8_t bit[3];
    uint8_t n;
};
