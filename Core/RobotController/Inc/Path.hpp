#pragma once

#include <vector>
#include <cstdint>

enum class StepType {
    Straight,      // 直進
    TurnLeft90,    // 左 90°ターン
    TurnRight90,   // 右 90°ターン
    Turn180,       // 180°その場回転
    // 以下は高度なターン（スラロームや大回り等）を追加してもOK
    // SlalomLeft90,
    // SlalomRight90,
    // ...
};

/**
 * @brief ロボットが1ステップで行う動作(直進 or ターン)を表すデータ
 */
struct PathStep {
    StepType stepType;    ///< 動作の種類

    float distance;  // このステップで進む距離
    float angle;  // ターン時の回転角度

    // このステップを行う際の想定速度(通過速度など)
    float speed;
    float speedSaturation;  // 速度の最大値(飽和値)
    float angularVelocity;  // 角速度(旋回時のみ)
    float angularSaturation;  // 角速度の最大値(飽和値)

    // ターン用の追加パラメータ(旋回半径, 回転中心, 進入/退出速度など)
    // 必要に応じて拡張
    float turnRadius;     ///< スラロームターンを行う場合の旋回半径(大回り/小回り)
    float inVelocity;   ///< 進入速度(例)
    float outVelocity;  ///< 退出速度(例)
    float inDistance;   ///< 進入距離(例)  
    float outDistance;  ///< 退出距離(例)

    // コンストラクタ (デフォルト)
    PathStep()
        : stepType(StepType::Straight)
        , distance(0)
        , angle(0)
        , speed(0.0f)
        , speedSaturation(0.0f)
        , angularVelocity(0.0f)
        , angularSaturation(0.0f)
        , turnRadius(0.0f)
        , inVelocity(0.0f)
        , outVelocity(0.0f)
        , inDistance(0.0f)
        , outDistance(0.0f)

    {}
};

/**
 * @brief マウス走行用のコマンド列(直進/ターン等)を保持・管理するクラス
 */
class Path {
public:

    Path() : m_currentIndex(0) {}
    ~Path() = default;

    // 走行コマンドを追加
    void addStraight(float distance);
    void addTurn(StepType turnType);

    // 経路を圧縮(連続した直進まとめ, ターン短縮など)
    void compressPath();

    // パス情報を取得
    const std::vector<PathStep>& getSteps() const { return m_steps; }

    // パスをクリア
    void clear() { 
        m_steps.clear();
        m_currentIndex = 0;
    }

    /**
     * @brief 現在のステップ(PathStep)を参照する (書き換えたい場合は非const版も)
     * @return 現在のステップへの参照
     */
    const PathStep& getCurrentStep() const;

    /**
     * @brief 次のステップに進む
     *        (走行中に「ステップが完了した」と判断したら呼ぶ)
     */
    void nextStep();

    /**
     * @brief 現在のステップインデックスが範囲外かどうか (パス終了判定)
     */
    bool isFinished() const;

    std::vector<PathStep> m_steps;

private:

    // 現在のステップ番号
    std::size_t m_currentIndex;

    // 内部的に呼ぶヘルパー関数例
    void mergeStraightSegments();
    void optimizeTurns();
};
