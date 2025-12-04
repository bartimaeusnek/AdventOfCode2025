// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#include "Cell.hpp"
#include "Board.hpp"


int32_t Cell::get_index() const {return m_position.x * m_board.lock()->get_width() + m_position.y;}

bool Cell::can_be_moved_by_forklift() const {
    if (!m_hasPaper) return false;
    const auto board = m_board.lock();
    int8_t rolls = 0;
    for (int lx = -1; lx <= 1; ++lx) {
        for (int ly = -1; ly <= 1; ++ly) {
            if (lx == 0 && ly == 0) {
                continue;
            }
            const auto nuPosition = Position(lx + m_position.x, ly + m_position.y);
            const auto* cellOrNull = board->get_cell(nuPosition);
            if (cellOrNull == nullptr) {
                continue;
            }
            if (cellOrNull->m_hasPaper) {
                ++rolls;
                if (rolls >= 4) {
                    return false;
                }
            }
        }
    }

    return true;
}

Cell::Cell(const Position position, const bool hasPaper, const std::weak_ptr<Board> &board) : m_position(position), m_board(board), m_hasPaper(hasPaper) {}
