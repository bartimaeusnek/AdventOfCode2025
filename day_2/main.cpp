// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <filesystem>
#include <iostream>
#include <fstream>
#include <ranges>
#include <sstream>

#include "NumberComperator.hpp"

int main() {
    constexpr auto filename = "../input";
    auto size = std::filesystem::file_size(filename);
    std::string content(size, '\0');
    std::ifstream in(filename);
    in.read(&content[0], static_cast<std::streamsize>(size));
    in.close();

    std::string range;
    std::stringstream ss(content);
    constexpr char comma_delimiter = ',';
    std::stringstream ss2;
    int64_t number = 0;
    int64_t number_part_two = 0;
    while (getline(ss, range, comma_delimiter)) {
        constexpr char minus_delimiter = '-';
        ss2 = std::stringstream(range);

        std::string min_str;
        std::string max_str;
        getline(ss2, min_str, minus_delimiter);
        getline(ss2, max_str, minus_delimiter);

        NumberComperator comperator;
        comperator.fromString(min_str, max_str);
        for (auto str: comperator.compare_part_two()) {
            number_part_two += str;
        }
        for (auto str: comperator.compare()) {
            number += str;
        }
    }
    std::cout << "Part 1: " << number << std::endl;
    std::cout << "Part 2: " << number_part_two << std::endl;
    return 0;
}