// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#pragma once
#include <cstdint>
#include <memory>

class Board;
#include "Position.h"

class Cell {
public:
    Cell() = default;
    Cell(Position position, bool hasPaper, const std::weak_ptr<Board> &board);
    [[nodiscard]] int32_t get_index() const;
    [[nodiscard]] bool can_be_moved_by_forklift() const;
    [[nodiscard]] bool has_paper() const {
        return m_hasPaper;
    }
    [[nodiscard]] Position get_position() const {
        return m_position;
    }
    void set_paper(const bool cond) {
        m_hasPaper = cond;
    };

private:
    Position m_position;
    std::weak_ptr<Board> m_board;
    bool m_hasPaper;
};