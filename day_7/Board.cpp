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

void Board::add_cell_to_board(const Position position, const CellType type, const std::shared_ptr<Board>& board) {
    auto cell = Cell(position, type, board);
    const auto cellIndex = cell.get_index();
    m_board[cellIndex] = std::move(cell);
}

Cell* Board::get_cell(const Position position) {
    if (position.x < 0 || position.y < 0 || position.x >= m_width || position.y >= m_height)
        return nullptr;

    if (const auto index = get_index(position); index >= 0 && index < m_board.size())
        return &m_board[index];

    return nullptr;
}

void Board::print_board() const {
    for (int y = 0; y < m_height; ++y)  {
        for (int x = 0; x < m_width; ++x) {
            auto* cell = &m_board[get_index(x, y)];
            std::cout << get_char_for_type(cell->get_type()) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

Cell* Board::get_starting_cell() {
    for (int y = 0; y < m_height; ++y)
        for (int x = 0; x < m_width; ++x)
            if (auto* cell = &m_board[get_index(x, y)];
                cell->get_type() == Start)
                return cell;

    return nullptr;
}

void Board::reset_field() {
    for (int y = 0; y < m_height; ++y)
        for (int x = 0; x < m_width; ++x)
            if (auto* cell = &m_board[get_index(x, y)];
                cell->get_type() == Beam)
                cell->set_type(None);
}

int64_t Board::analyse_field() {
    for (int x = 0; x < m_width; ++x)
        if (auto* cell = &m_board[get_index(x, m_height - 1)])
            cell->set_count(1);

    for (int y = m_height - 1; y >= 0; --y)
        for (int x = 0; x < m_width; ++x)
            if (const auto* cell = &m_board[get_index(x, y)];
                cell->get_type() == Splitter || y == m_height - 1)
                cell->backtrack();

    return get_starting_cell()->get_count();
}