// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "Position.h"

class Cell;

class Board {
public:
    explicit Board(int32_t width, int32_t height);
    void add_cell_to_board(Position position, CellType type, const std::shared_ptr<Board>& board);
    [[nodiscard]] Cell* get_cell(Position position);
    void print_board() const;
    [[nodiscard]] Cell* get_starting_cell();
    void reset_field();
    int64_t analyse_field();

    [[nodiscard]] int32_t get_index(const int32_t x, const int32_t y) const {
        return x * get_height() + y;
    }
    [[nodiscard]] int32_t get_index(const Position position) const {
        return position.x * get_height() + position.y;
    }
    [[nodiscard]] int32_t get_height() const {
        return m_height;
    }
    [[nodiscard]] int32_t get_width() const {
        return m_width;
    }
private:

    std::vector<Cell> m_board;
    int32_t m_width;
    int32_t m_height;
};