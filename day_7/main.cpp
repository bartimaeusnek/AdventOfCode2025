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
    while (std::getline(file, line)) lines.push_back(line);

    if (line.empty()) line = lines[0];

    const auto board = std::make_shared<Board>(line.size(), lines.size());

    for (int y = 0; y < lines.size(); ++y) {
        line = lines[y];
        for (int x = 0; x < line.size(); ++x) {
            const auto cellContent = try_get_cell_type_from_char(line[x]);
            if (!cellContent.has_value()) continue;
            const auto cellPosition = Position(x, y);
            board->add_cell_to_board(cellPosition, cellContent.value(), board);
        }
    }
    int64_t split_times = 0;
    auto* startingCell = board->get_starting_cell();
    if (startingCell == nullptr) {
        std::cerr << "Failed to get starting cell\n";
        return 1;
    }
    startingCell->fire_beam_counting(split_times);
    std::cout << split_times << std::endl;
    std::cout << board->analyse_field() << std::endl;

    return 0;
}