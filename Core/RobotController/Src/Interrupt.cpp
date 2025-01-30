#include "stm32f4xx_hal.h"
#include "../Inc/Path.hpp"
#include "../Inc/DynamicsController.hpp"
#include "../Inc/RobotController.hpp"

extern RobotController* robotController; // 別ファイルで宣言したポインタ

extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM5) {
        robotController->update(); // ロボット制御の更新
    }
}