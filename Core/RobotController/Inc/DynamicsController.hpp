#pragma once

#include "Path.hpp"      // 物理パラメータを参照するため
#include "../../Driver/Inc/EncoderDriver.hpp" // エンコーダ情報取得のため(必要なら)
#include "../../Driver/Inc/ImuDriver.hpp"

class DynamicsController {
public:
    /**
     * @brief コンストラクタ
     * @param wheelBase       車体のトレッド幅[mm]など
     * @param wheelDiameter   ホイール直径[mm]
     *        などのパラメータを受け取る想定
     */
    DynamicsController(float wheelBase, float wheelDiameter);

    /**
     * @brief メイン制御関数
     *        現在のPathStepとセンサ情報を参照し、モータ出力を計算
     * @param step       今の走行ステップ(速度, 角速度などの目標値)
     * @param dt         制御周期[秒]
     * @param encLeft    左エンコーダカウント(または速度)
     * @param encRight   右エンコーダカウント(または速度)
     * @param gyroZ      ジャイロで測った角速度[rad/s] (必要に応じて)
     * @return (leftPWM, rightPWM) モータ出力(例えば -1.0 ~ +1.0)
     */
    std::pair<float, float> update(
        const PathStep& step,
        float encLeft,
        float encRight,
        float gyroZ
    );

private:
    float m_wheelBase;
    float m_wheelDiameter;

    // 必要に応じて内部にPIDゲインや制御状態を保持する
    float m_leftErrorInt;   // 左車輪速度PID用の積分項など
    float m_rightErrorInt;
    float m_yawErrorInt;    // 角度制御用積分項 ... etc

    // 内部メソッド (例: 速度制御, 角速度制御, フィードフォワード…)
    float computePWMForSpeed(float targetSpeed, float currentSpeed);
    float computePWMForAngle(float targetAngVel, float currentAngVel);
};
