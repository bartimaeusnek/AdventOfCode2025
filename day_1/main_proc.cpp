// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <iostream>
#include <fstream>
#include <string>

//https://stackoverflow.com/a/2581867
template<typename T>
T mod(const T& a, const T& b)
{
    return (a % b + b) % b;
}

int main() {
    std::ifstream file("../input.txt");
    if (!file) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    int32_t current = 50;
#if Debug
    int32_t current_cpy;
#endif
    std::string line;
    int32_t total = 0;
    int32_t clicks = 0;
    while (std::getline(file, line)) {
#if Debug
        current_cpy = current;
        std::cout << line << std::endl;
#endif
        auto direction = line[0];
        int32_t moveBy = std::stoi(line.substr(1));
        switch (direction) {
            case 'L': {
                int32_t rest = current % 100;
                if (rest == 0)
                    rest = 100;
                if (moveBy >= rest) {
                    clicks += 1 + (moveBy - rest) / 100;
                }
                current = mod(current - moveBy, 100);
                break;
            }
            case 'R': {
                int32_t rest = (100 - current) % 100;
                if (rest == 0) rest = 100;
                if (moveBy >= rest) {
                    clicks += 1 + (moveBy - rest) / 100;
                }
                current = mod(current + moveBy, 100);
                break;
            }
            default: std::cerr << "Invalid direction!\n"; return -1;
        }
#if Debug
       std::cout << "at " << current_cpy << " direction: " << direction << " move by: " << moveBy << " result: " << current << std::endl;
#endif
        if (!current) ++total;
    }
    std::cout << "Password: " << total << std::endl;
    std::cout << "Password method 0x434C49434B: " << clicks << std::endl;
    return 0;
}
