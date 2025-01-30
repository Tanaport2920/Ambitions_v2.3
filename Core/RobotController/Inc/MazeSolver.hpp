#pragma once
#include "Maze.hpp"
#include "Path.hpp"  // 経路情報を格納するクラス、プロジェクトの仕様に合わせて設計

// 迷路解法の抽象クラス
class MazeSolver {
public:
    virtual ~MazeSolver() = default;
    virtual Path solveMaze(const Maze& maze, const uint16_t start, const uint16_t goal) = 0;
};

// 足立法の実装例
class AdachiSolver : public MazeSolver {
public:
    virtual Path solveMaze(const Maze& maze, const uint16_t start, const uint16_t goal) override {
        // 足立法の実装
        Path path;
        // … 実装コード …
        return path;
    }
};

// ダイクストラ法の実装例
class DijkstraSolver : public MazeSolver {
public:
    virtual Path solveMaze(const Maze& maze, const uint16_t start, const uint16_t goal) override {
        // ダイクストラ法の実装
        Path path;
        // … 実装コード …
        return path;
    }
};
