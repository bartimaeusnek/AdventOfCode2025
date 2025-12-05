// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

template<typename T>
constexpr T min(T a, T b) {
    return a < b ? a : b;
}

template<typename T>
constexpr T max(T a, T b) {
    return a > b ? a : b;
}

template<typename T>
constexpr bool within_range(T x, T a, T b) {
    return min(a, b) <= x && max(a, b) >= x;
}

std::pair<uint64_t, uint64_t> merge_range(std::vector<std::pair<uint64_t, uint64_t>> &rangeLinesUint, std::pair<uint64_t, uint64_t> rangeToMerge, bool *modified) {
    for (auto [first, second] : rangeLinesUint) {
        if (first == rangeToMerge.first && second == rangeToMerge.second) {
            continue;
        }
        if (within_range(rangeToMerge.first, first, second)) {
            rangeToMerge.first = first;
            *modified = true;
        }
        if (within_range(rangeToMerge.second, first, second)) {
            rangeToMerge.second = second;
            *modified = true;
        }
    }
    return rangeToMerge;
}

std::vector<std::pair<uint64_t, uint64_t>> merge_ranges(std::vector<std::pair<uint64_t, uint64_t>> rangeLinesUint) {
    bool modified;
    std::vector<std::pair<uint64_t, uint64_t>> vec;
    do {
        modified = false;
        //clear intermediate results
        vec.clear();
        for (const auto originalRange : rangeLinesUint) {
            auto mergedRange = merge_range(rangeLinesUint, originalRange, &modified);
            vec.emplace_back(mergedRange);
        }
        //remove duplicates from the vector
        std::ranges::sort(vec);
        vec.erase(std::ranges::unique(vec).begin(), vec.end());
        //make sure to iterate over the new vector instead of the old
        rangeLinesUint = vec;
    } while (modified);

    return vec;
}

int main() {
    std::ifstream file("../input");
    if (!file) {
        std::cerr << "Failed to open file\n";
        return 1;
    }
    std::string line;
    std::vector<std::pair<uint64_t, uint64_t>> rangeLinesUint;
    std::vector<uint64_t> nonRangeLinesUint;
    while (std::getline(file, line)) {
        if (line.find('-') != std::string::npos) {
            uint64_t rangeStart = std::stoll(line.substr(0, line.find('-')));
            uint64_t rangeEnd = std::stoll(line.substr(line.find('-') + 1));
            rangeLinesUint.emplace_back(rangeStart, rangeEnd);
        }
        else if (!line.empty()) nonRangeLinesUint.push_back(std::stoll(line));
    }

    size_t size = 0;
    for (const uint64_t nonRangeUnit : nonRangeLinesUint) {
        for (auto [first, second] : rangeLinesUint) {
            if (within_range(nonRangeUnit, first, second)) {
                ++size;
                break;
            }
        }
    }

    std::cout << "Part 1: " << size << "\n";

    const auto ranges = merge_ranges(rangeLinesUint);

    uint64_t nonRange = 0;
    for (const auto [first, second] : ranges) {
        nonRange += second - first + 1;
    }
    std::cout << "Part 2: " << nonRange << "\n";

    return 0;
}