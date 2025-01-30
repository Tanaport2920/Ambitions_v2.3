#ifndef MAZE_HPP
#define MAZE_HPP

#include <cstddef>

// 迷路の方向を表す列挙型
enum class MazeDirection {
    North,  // 上
    East,   // 右
    South,  // 下
    West    // 左
};

/**
 * @brief Mazeクラス
 *
 * 各セルごとの壁情報（North, East, South, West）を管理する。
 */
class Maze {
public:
    /**
     * @brief コンストラクタ
     * @param width  迷路の幅（セル数）
     * @param height 迷路の高さ（セル数）
     */
    Maze(std::size_t width, std::size_t height);

    /**
     * @brief デストラクタ
     */
    ~Maze();

    /**
     * @brief 指定セルの指定方向の壁の状態を設定する
     * @param x セルの X 座標 (0～width-1)
     * @param y セルの Y 座標 (0～height-1)
     * @param direction 壁の方向 (MazeDirection::North など)
     * @param isWall true: 壁がある, false: 壁がない
     */
    void setWall(std::size_t x, std::size_t y, MazeDirection direction, bool isWall);

    /**
     * @brief 指定セルの指定方向に壁があるかを取得する
     * @param x セルの X 座標
     * @param y セルの Y 座標
     * @param direction 調べる方向
     * @return true なら壁がある, false なら壁がない
     */
    bool hasWall(std::size_t x, std::size_t y, MazeDirection direction) const;


private:
    // 各セルの壁情報を保持する構造体
    struct Cell {
        bool north;
        bool east;
        bool south;
        bool west;
        bool visited;
    };

    std::size_t m_width;
    std::size_t m_height;
    Cell* m_cells;  // 幅×高さのセルの配列

    // (x, y) 座標を 1次元のインデックスに変換
    inline std::size_t index(std::size_t x, std::size_t y) const {
        return y * m_width + x;
    }
};

#endif // MAZE_HPP
