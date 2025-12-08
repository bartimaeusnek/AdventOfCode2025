// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#include <future>

#include "Cell.hpp"
#include "Board.hpp"

Cell::Cell()
: m_position({}), m_board({}), m_type(None), m_count(0) {}

Cell::Cell(const Position position, const CellType type, const std::weak_ptr<Board> &board)
: m_position(position), m_board(board), m_type(type), m_count(0) {}

int32_t Cell::get_index() const {
    return m_board.lock()->get_index(m_position);
}

void Cell::backtrack() const {
    const auto sp = m_board.lock();

    auto left = m_position;
    --left.x;
    if (auto* leftCell = sp->get_cell(left);
        leftCell && leftCell->get_type() == Splitter) {
        leftCell->m_count += m_count;
    }

    auto right = m_position;
    ++right.x;
    if (auto* rightCell = sp->get_cell(right);
        rightCell && rightCell->get_type() == Splitter) {
        rightCell->m_count += m_count;
    }

    auto above = m_position;
    --above.y;
    if (auto* aboveCell = sp->get_cell(above);
        aboveCell && (aboveCell->get_type() == Beam || aboveCell->get_type() == Start)) {
        aboveCell->m_count += m_count;
        aboveCell->backtrack();
    }
}

static void fire_beam_at(const std::shared_ptr<Board>& board, const Position position, int64_t &split_times) {
    if (auto* other_cell = board->get_cell(position)) {
        other_cell->fire_beam_counting(split_times);
    }
}

void Cell::fire_beam_counting(int64_t &split_times) {
    auto posCpy = m_position;
    switch (this->get_type()) {
        case Beam:
            //early exit so we dont have to process 2^1500 branches
            return;
        case Start:
            ++posCpy.y;
            fire_beam_at(m_board.lock(), posCpy, split_times);
            return;
        case None:
            ++posCpy.y;
            //naive implementation of part 2 DOES NOT set type to Beam
            set_type(Beam);
            fire_beam_at(m_board.lock(), posCpy, split_times);
            return;
        case Splitter: {
            const auto sp = m_board.lock();

            ++split_times;

            ++posCpy.x;
            fire_beam_at(sp, posCpy, split_times);

            posCpy.x -= 2;
            fire_beam_at(sp, posCpy, split_times);
            return;
        }
        default:
            throw std::invalid_argument("Invalid cell type");
    }
}