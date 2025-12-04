// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Cell.hpp"
#include "Board.hpp"

int main() {
    std::ifstream file("../input");
    if (!file) {
        std::cerr << "Failed to open file\n";
        return 1;
    }
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    if (line.empty()) {
        line = lines[0];
    }

    const auto board = std::make_shared<Board>(line.size(), lines.size());

    for (int y = 0; y < lines.size(); ++y) {
        line = lines[y];
        for (int x = 0; x < line.size(); ++x) {
            const auto cellContent = line[x];
            const auto cellPosition = Position(x, y);
            board->add_cell_to_board(cellPosition, cellContent == '@', board);
        }
    }

    std::cout << "Part 1: " << board->get_moveable_scroll_count() << std::endl;
    std::cout << "Part 2: " << board->compute_total_removed_scrolls() << std::endl;
    return 0;
}
