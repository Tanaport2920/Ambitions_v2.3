#include "../Inc/LEDController.hpp"

// コンストラクタ
LEDController::LEDController(
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
)
: m_sensorLED_FL(sensorLED_FL)
, m_sensorLED_FR(sensorLED_FR)
, m_sensorLED_R(sensorLED_R)
, m_sensorLED_L(sensorLED_L)
, m_led_FL(led_FL)
, m_led_FR(led_FR)
, m_led_R(led_R)
, m_led_L(led_L)
, m_modeLED1(modeLED1)
, m_modeLED2(modeLED2)
, m_modeLED3(modeLED3)
{
}

// センサLEDの制御
void LEDController::setSensorLED(bool fl, bool fr, bool r, bool l) {
    if (fl) m_sensorLED_FL->setHigh(); 
    else m_sensorLED_FL->setLow();
    if (fr) m_sensorLED_FR->setHigh(); 
    else m_sensorLED_FR->setLow();
    if (r)  m_sensorLED_R->setHigh();  
    else m_sensorLED_R->setLow();
    if (l)  m_sensorLED_L->setHigh();  
    else m_sensorLED_L->setLow();
}

void LEDController::sensorLEDOn() {
    setSensorLED(true, true, true, true);
}

void LEDController::sensorLEDOff() {
    setSensorLED(false, false, false, false);
}

// 通常LEDの制御
void LEDController::setLED(bool fl, bool fr, bool r, bool l) {
    if (fl) m_led_FL->setHigh(); 
    else m_led_FL->setLow();
    if (fr) m_led_FR->setHigh(); 
    else m_led_FR->setLow();
    if (r)  m_led_R->setHigh();  
    else m_led_R->setLow();
    if (l)  m_led_L->setHigh();  
    else m_led_L->setLow();
}

void LEDController::turnAllLEDOn() {
    setLED(true, true, true, true);
}

void LEDController::turnAllLEDOff() {
    setLED(false, false, false, false);
}

// モードLEDの制御
void LEDController::setModeLED(uint8_t mode) {
    n = mode;
    for(uint8_t i=0; n>0; i++){
        bit[i]= n%2;
        n /= 2;
    }
    // まず全消灯
    m_modeLED1->setLow();
    m_modeLED2->setLow();
    m_modeLED3->setLow();

    if(bit[0]) m_modeLED1->setHigh();
    else m_modeLED1->setLow();
    if(bit[1]) m_modeLED2->setHigh();
    else m_modeLED2->setLow();
    if(bit[2])m_modeLED3->setHigh();
    else m_modeLED3->setLow();
}