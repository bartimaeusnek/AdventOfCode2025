// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#pragma once

#include <cstdint>
#include <memory>

#include "CellType.hpp"
#include "Position.h"

class Board;

class Cell {
public:
    Cell();
    Cell(Position position, CellType type, const std::weak_ptr<Board> &board);

    void fire_beam_counting(int64_t &split_times);
    void backtrack() const;
    [[nodiscard]] int32_t get_index() const;

    [[nodiscard]] CellType get_type() const {
        return m_type;
    }

    [[nodiscard]] Position get_position() const {
        return m_position;
    }
    void set_type(const CellType type) {
        m_type = type;
    }

    [[nodiscard]] int64_t get_count() const {
        return m_count;
    }
    void set_count(const int64_t count) {
        m_count = count;
    }

private:
    Position m_position;
    std::weak_ptr<Board> m_board;
    CellType m_type;
    int64_t m_count;
};