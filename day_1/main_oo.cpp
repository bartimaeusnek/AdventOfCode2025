// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <iostream>
#include <fstream>
#include <string>

#include "Dial.hpp"

int main() {
    std::ifstream file("../input.txt");
    if (!file) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    auto dial = Dial(100, 50);
    std::string line;
    uint32_t total = 0;
    while (std::getline(file, line)) {
#if Debug
        std::cout << line << std::endl;
#endif
        auto direction = line[0];
        uint32_t moveBy = std::stoi(line.substr(1));
        int32_t value;
#if Debug
        int32_t current = dial->Current();
#endif
        switch (direction) {
            case 'L': value = dial.MoveLeft(moveBy); break;
            case 'R': value = dial.MoveRight(moveBy); break;
            default: std::cerr << "Invalid direction!\n"; return -1;
        }
#if Debug
        std::cout << "at " << current << " direction: " << direction << " move by: " << moveBy << " result: " << value << std::endl;
#endif
        if (!value) ++total;
    }

    std::cout << "Password: " << total << std::endl;
    std::cout << "Password method 0x434C49434B: " << dial.get_clicks() << std::endl;
    return 0;
}
