#pragma once

#include <stdint.h>
#include "../../Driver/Inc/Button.hpp"
#include "../../Driver/Inc/EncoderDriver.hpp"
#include "../../Driver/Inc/LEDController.hpp"
#include "../../Driver/Inc/ImuDriver.hpp"
#include "../../Driver/Inc/PhotoSensor.hpp"
#include "../../Driver/Inc/MotorDriver.hpp"
#include "MazeSolver.hpp"
#include "Maze.hpp"
#include "Path.hpp"
#include "DynamicsController.hpp"

/**
 * @brief ロボット全体を統括するクラス
 * 
 * センサー読み取り、モータ制御、迷路情報の更新、最短走行などを一元管理する。
 */
class RobotController {
public:
    /**
     * @brief コンストラクタ
     * @param modeButton     モード変更ボタン
     * @param ledController  LED制御
     * @param imu            IMU(ジャイロ・加速度)
     * @param photoSensor    フォトセンサー(ADC読み取り)
     * @param rightEncoder   右エンコーダ制御ドライバ
     * @param leftEncoder    左エンコーダ制御ドライバ
     * @param rightMotor     右モータ制御ドライバ
     * @param leftMotor      左モータ制御ドライバ
     * @param mazeSolver     迷路解法クラス
     */
    RobotController(
        Button* modeButton,
        LEDController* ledController,
        Imu* imu,
        PhotoSensor* photoSensor,
        EncoderDriver* rightEncoder,
        EncoderDriver* leftEncoder,
        MotorDriver* rightMotor,
        MotorDriver* leftMotor,
        MazeSolver* mazeSolver
    );

    /**
     * @brief ロボット全体の初期化処理
     *        (センサキャリブレーション等も含むイメージ)
     */
    void init();

    /**
     * @brief 制御値更新
     */
    void update();

    /**
     * @brief センサ値更新 (PhotoSensor, IMU, など)
     */
    void updateSensors();

    /**
     * @brief 迷路情報の更新 (壁検出など)
     *        PhotoSensor値から壁有無を推定して Maze に反映
     */
    void updateMaze();

    /**
     * @brief モータ制御 (例: 壁情報などから適切に出力を計算)
     */
    void controlMotors(float, float);

    /**
     * @brief ボタン状態確認 (モード変更, etc.)
     */
    void checkModeButton();

    /**
     * @brief 最短走行: 迷路情報を用いて MazeSolver で経路を計算し、実際に走行
     */
    void runShortestPath();

    void exploreMaze();

    // MazeSolver の切り替え用セッター
    void setMazeSolver(MazeSolver* newSolver);

private:
    // --- デバイス / クラス参照 ---
    Button*         m_modeButton;
    LEDController*  m_ledController;
    Imu*            m_imu;
    PhotoSensor*    m_photoSensor;
    EncoderDriver*  m_rightEncoder;
    EncoderDriver*  m_leftEncoder;
    MotorDriver*    m_rightMotor;
    MotorDriver*    m_leftMotor;
    MazeSolver*     m_mazeSolver;

    // --- 内部で保持する迷路情報とパス情報 ---
    Maze            m_maze; // 迷路情報(壁の有無、到達フラグなど)
    Path            m_path; // 現在の走行経路

    // --- 内部状態 ---
    bool            m_isShortestMode;  // 「最短走行モード」等のフラグ
    // 他にもロボットの位置・方位など

    // --- 制御 ---
    DynamicsController m_dynamicsController;  // モータ制御クラス
};
