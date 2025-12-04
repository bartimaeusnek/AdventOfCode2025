// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#include "Cell.hpp"
#include "Board.hpp"

#include <iostream>

Board::Board(const int32_t width, const int32_t height) {
    m_width = width;
    m_height = height;
    m_board.resize(width * height);
}
void Board::add_cell_to_board(const Position position, const bool hasPaper, const std::shared_ptr<Board>& board) {
    auto cell = Cell(position, hasPaper, board);
    const auto cellIndex = cell.get_index();
    m_board[cellIndex] = std::move(cell);
}
int32_t Board::get_width() const {return m_width;}
Cell* Board::get_cell(const Position position) {
    if (position.x < 0 || position.y < 0 || position.x >= m_width || position.y >= m_height)
        return nullptr;

    if (const auto index = position.x * get_width() + position.y; index >= 0 && index < m_board.size())
        return &m_board[index];

    return nullptr;
}

uint64_t Board::get_moveable_scroll_count() const {
    int64_t count = 0;
    for (const auto &cell : m_board) {
        if (cell.can_be_moved_by_forklift()) {
            ++count;
        }
    }
    return count;
}

uint64_t Board::compute_total_removed_scrolls() {
    while (get_moveable_scroll_count() > 0) {
        m_total_removed += remove_moveable_scrolls();
    }
    return m_total_removed;
}

uint64_t Board::remove_moveable_scrolls() {
    uint64_t removed = 0;
    for (auto &cell : m_board) {
        if (cell.can_be_moved_by_forklift()) {
            cell.set_paper(false);
            ++removed;
        }
    }
    return removed;
}

void Board::print_board() const {
    for (int y = 0; y < m_height; ++y)  {
        for (int x = 0; x < m_width; ++x) {
            auto* cell = &m_board[x * m_width + y];
            std::cout << (cell->has_paper() ? '@' : '.') << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
     for (int y = 0; y < m_height; ++y) {
            for (int x = 0; x < m_width; ++x){
            auto* cell = &m_board[x * m_width + y];
            std::cout << (cell->can_be_moved_by_forklift() ? 'x' : '.') << " ";
        }
        std::cout << std::endl;
    }
}