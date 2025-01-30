#include "../Inc/Maze.hpp"
#include <cstring>  // memset を使う場合など

Maze::Maze(std::size_t width, std::size_t height)
    : m_width(width)
    , m_height(height)
{
    m_cells = new Cell[m_width * m_height];

    // 全セルの壁情報を初期化（すべての壁を false とする）
    for (std::size_t i = 0; i < m_width * m_height; ++i) {
        m_cells[i].north = false;
        m_cells[i].east  = false;
        m_cells[i].south = false;
        m_cells[i].west  = false;
        m_cells[i].visited = false;
    }
}

Maze::~Maze() {
    delete[] m_cells;
}

void Maze::setWall(std::size_t x, std::size_t y, MazeDirection direction, bool isWall) {
    if (x >= m_width || y >= m_height) {
        return; // 範囲外の場合は何もしない（必要に応じ例外処理）
    }
    std::size_t idx = index(x, y);
    switch (direction) {
        case MazeDirection::North:
            m_cells[idx].north = isWall;
            break;
        case MazeDirection::East:
            m_cells[idx].east = isWall;
            break;
        case MazeDirection::South:
            m_cells[idx].south = isWall;
            break;
        case MazeDirection::West:
            m_cells[idx].west = isWall;
            break;
    }
    m_cells[idx].visited = true;
}

bool Maze::hasWall(std::size_t x, std::size_t y, MazeDirection direction) const {
    if (x >= m_width || y >= m_height) {
        return false; // 範囲外なら false とするか、エラー扱い
    }
    std::size_t idx = index(x, y);
    switch (direction) {
        case MazeDirection::North:
            return m_cells[idx].north;
        case MazeDirection::East:
            return m_cells[idx].east;
        case MazeDirection::South:
            return m_cells[idx].south;
        case MazeDirection::West:
            return m_cells[idx].west;
        default:
            return false;
    }
}
