#include "RobotController.hpp"
#include <stdio.h>

RobotController::RobotController(
    Button* modeButton,
    LEDController* ledController,
    Imu* imu,
    PhotoSensor* photoSensor,
    MotorDriver* rightMotor,
    MotorDriver* leftMotor,
    MazeSolver* mazeSolver
)
: m_modeButton(modeButton)
, m_ledController(ledController)
, m_imu(imu)
, m_photoSensor(photoSensor)
, m_rightMotor(rightMotor)
, m_leftMotor(leftMotor)
, m_mazeSolver(mazeSolver)
, m_isShortestMode(false)
{
}

void RobotController::init() {
    // 例: ジャイロの初期オフセット取得
    m_imu->gyro_get_ref();

    // 例: フォトセンサーの初期読み取り or キャリブレーション
    // ...

    // LED初期状態
    m_ledController->turnAllLEDOff();
    m_ledController->sensorLEDOff();

    // 迷路データ初期化
    m_maze.init();  // 迷路サイズ16x16など

    printf("[RobotController] init done.\n");
}

void RobotController::updateSensors() {
    // フォトセンサーから値を読み取る (DMAで読み込み済みならバッファ参照だけかも)
    uint16_t fl = m_photoSensor->getValue(0);
    uint16_t fr = m_photoSensor->getValue(1);
    uint16_t sr = m_photoSensor->getValue(2);
    uint16_t sl = m_photoSensor->getValue(3);

    // IMU (ジャイロZ, etc.)
    float gz = m_imu->Lsm6dsrReadGyroZ();

    // 必要に応じて内部変数に保存
    // ...
}

void RobotController::updateMaze() {
    // 例: PhotoSensor 値から左右・前方に壁があるかを推定
    //     m_maze.setWall(x, y, direction, true/false); 
    //     などで書き込み

    // 走行中のロボット位置・向きが分かるなら、そこから「どの壁があるか？」を判定
    // ...
}

void RobotController::controlMotors() {
    // 例: センサ情報を参考にモータ出力を決定
    //     自己位置推定して、目標速度を算出し MotorDriver で出力
    float rightDuty = 0.3f;
    float leftDuty = 0.3f;

    m_rightMotor->setDuty(rightDuty);
    m_leftMotor->setDuty(leftDuty);
}

void RobotController::checkModeButton() {
    ButtonState state = m_modeButton->checkState();
    if (state == ButtonState::On) {
        // モード切り替え
        m_isShortestMode = !m_isShortestMode;
        printf("Mode toggled! ShortestMode = %d\n", m_isShortestMode);
    }
    else if (state == ButtonState::LongOn) {
        // 別の機能 (例: reset, etc.)
        printf("Long press detected!\n");
    }
}

void RobotController::exploreMaze() {
    // 例: 足立法ベースの探索走行を実装し、m_mazeを壁情報で埋める
    //     走行中に updateSensors(), updateMaze() を繰り返す
    // ...
}

void RobotController::runShortestPath() {
    // 1. すでに m_maze が埋まっている前提 (もしくは途中でもOK)
    // 2. MazeSolver を使って最短経路を計算
    Path path = m_mazeSolver->solveMaze(m_maze, /* start, goal */);

    // 3. 返ってきた Path(セル列やコマンド列) をモータで走行
    //    例: pathに「(0,0)->(1,0)->(2,0) ...」が入っていれば、順に走る
    //    走行中はセンサを見て壁があれば再計算、など高度な処理も
    for (auto& step : path.steps) {
        // stepに応じてモータ出力
        // ...
    }
    printf("Shortest run complete!\n");
}
