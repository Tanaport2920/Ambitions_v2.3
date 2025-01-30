#include "../Inc/Path.hpp"

void Path::addStraight(float distance) {
    // もし連続で Straight を追加するなら、後ろのステップとマージしてもよい
    // ただし、圧縮は別メソッド compressPath() にまとめてもOK
    if (!m_steps.empty()) {
        PathStep& last = m_steps.back();
        if (last.stepType == StepType::Straight) {
            // 後ろが Straight なら距離を加算
            last.distance += distance;
            return;
        }
    }
    // 新しく追加
    PathStep step;
    step.stepType = StepType::Straight;
    step.distance = distance;
    m_steps.push_back(step);
}

void Path::addTurn(StepType turnType) {
    // ここでは distance=0 として格納
    PathStep step;
    step.stepType = turnType;
    step.distance = 0;
    m_steps.push_back(step);
}

void Path::compressPath() {
    // 1. 連続直進をマージ (例: forward 1, forward 2 → forward 3)
    mergeStraightSegments();

    // 2. ターンの最適化 (連続ターンのまとめ、スラローム化など)
    optimizeTurns();
}

void Path::mergeStraightSegments() {
    if (m_steps.size() < 2) return;

    std::vector<PathStep> merged;
    merged.reserve(m_steps.size());

    for (auto & step : m_steps) {
        if (!merged.empty() &&
            merged.back().stepType == StepType::Straight &&
            step.stepType == StepType::Straight)
        {
            // 連続するStraightをまとめる
            merged.back().distance += step.distance;
        }
        else {
            // それ以外はそのまま追加
            merged.push_back(step);
        }
    }

    m_steps = merged;
}

void Path::optimizeTurns() {
    // 例: (TurnLeft90, TurnRight90) → Turn180 のようにまとめる、など
    // スラローム化する場合は、連続する "Straight + 90° Turn + Straight" の組を一つのStepに変形する、
    // といった高度な処理を書く。
    // ここではサンプルとして空実装。
}
