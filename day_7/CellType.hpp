// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#pragma once

#include <optional>
#include <stdexcept>

enum CellType {
    None = 0,
    Start = 0b1,
    Splitter = 0b10,
    Beam = 0b100,
};

inline char get_char_for_type(const CellType type) {
    switch (type) {
        case None: return '.';
        case Start : return 'S';
        case Splitter: return '^';
        case Beam: return '|';
        default: throw std::invalid_argument("Invalid Cell Type");
    }
}
inline std::optional<CellType> try_get_cell_type_from_char(const char c) {
    switch (c) {
        case '.': return None;
        case 'S': return Start;
        case '^': return Splitter;
        case '|': return Beam;
        default: return std::nullopt;
    }
}