#include "../Inc/DynamicsController.hpp"
#include <cmath>

DynamicsController::DynamicsController(float wheelBase, float wheelDiameter)
    : m_wheelBase(wheelBase)
    , m_wheelDiameter(wheelDiameter)
    , m_leftErrorInt(0.0f)
    , m_rightErrorInt(0.0f)
    , m_yawErrorInt(0.0f)
{
    // 必要なら初期化
}

std::pair<float, float> DynamicsController::update(
    const PathStep& step,
    float encLeft,
    float encRight,
    float gyroZ
) {
    // 1. 実速度を算出(エンコーダから)
    // 例: encLeft, encRight をdtで割って 左右車輪速度[currentSpeedL, currentSpeedR]を計算
    //     ここでは仮の値
    float currentSpeedL = 0.0f;
    float currentSpeedR = 0.0f;

    float currentLinVel = (currentSpeedL + currentSpeedR) * 0.5f; // 左右平均
    float currentAngVel = gyroZ; // ジャイロZを角速度と仮定 (rad/s)

    // 2. 目標速度 & 角速度
    float targetLinVel = step.speed;             // 直進用速度(またはその場旋回でも可)
    float targetAngVel = step.angularVelocity;   // ターン時の角速度

    // 3. 速度制御 (直進方向)
    float linControl = computePWMForSpeed(targetLinVel, currentLinVel);
    // 4. 角速度制御 (旋回方向)
    float angControl = computePWMForAngle(targetAngVel, currentAngVel);

    // 5. モータ指令 (左右車輪速度差により旋回を生む)
    //    例えば leftMotor = linControl - angControl / 2
    //             rightMotor= linControl + angControl / 2
    //    ここはプロジェクトの車体モデル次第で書き方が変わる
    float leftPWM  = linControl - angControl * 0.5f;
    float rightPWM = linControl + angControl * 0.5f;

    // 6. 飽和処理 ( step.speedSaturation なども参考にするならここ )
    if (leftPWM  > 1.0f) leftPWM  = 1.0f;
    if (leftPWM  < -1.0f) leftPWM  = -1.0f;
    if (rightPWM > 1.0f) rightPWM = 1.0f;
    if (rightPWM < -1.0f) rightPWM = -1.0f;

    return { leftPWM, rightPWM };
}

float DynamicsController::computePWMForSpeed(float targetSpeed, float currentSpeed) {
    // 簡易PID例 (Pのみ)
    float Kp = 0.01f;
    float Ki = 0.0f;
    float Kd = 0.0f;
    float error = targetSpeed - currentSpeed;
    float pwm = Kp * error;
    return pwm;
}

float DynamicsController::computePWMForAngle(float targetAngVel, float currentAngVel) {
    // 簡易PID例 (Pのみ)
    float Kp_yaw = 0.01f;
    float error = targetAngVel - currentAngVel;
    float pwm = Kp_yaw * error;
    return pwm;
}
