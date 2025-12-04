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
    void add_cell_to_board(Position position, bool hasPaper, const std::shared_ptr<Board>& board);
    [[nodiscard]] int32_t get_width() const;
    [[nodiscard]] Cell* get_cell(Position position);
    [[nodiscard]] uint64_t get_moveable_scroll_count() const;
    uint64_t compute_total_removed_scrolls();
    void print_board() const;
private:
    uint64_t remove_moveable_scrolls();
    std::vector<Cell> m_board;
    int32_t m_width;
    int32_t m_height;
    uint64_t m_total_removed = 0LL;
};