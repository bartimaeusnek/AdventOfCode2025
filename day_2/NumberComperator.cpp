// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "NumberComperator.hpp"

#include <iostream>
#include <memory>
#include <unordered_set>
#include <vector>

bool NumberComperator::fromString(const std::string& min_str, const std::string& max_str) {
    try {
        const int64_t min = std::stoll(min_str); //strip leadin nulls
        const int64_t max = std::stoll(max_str); //strip leadin nulls
        m_min_number = min;
        m_max_number = max;
        return true;
    } catch (...) {
        return false;
    }
}

int64_t NumberComperator::getMinNumber() const {
    return m_min_number;
}

int64_t NumberComperator::getMaxNumber() const {
    return m_max_number;
}

std::vector<int64_t> NumberComperator::compare_part_one(const int64_t a, const int64_t b) {
    std::vector<int64_t> invalidNumbers;
    for (int64_t i = a; i <= b; i++) {
        auto input = std::to_string(i);
        std::string pattern;

        for (int j = 0; j < input.length(); ++j) {
            pattern += input[j];
            auto substr = input.substr(j + 1);
            if (pattern == substr) {
                invalidNumbers.push_back(std::stoll(input));
                break;
            }
        }
    }
   return invalidNumbers;
}

static void find_recursive(const std::string& pattern, const std::string& input, const size_t search_from, size_t& hits, const size_t recursion_guard) {
    if (search_from >= input.size() || recursion_guard >= 128) return;

    if (const size_t hit = input.find(pattern, search_from); hit != std::string::npos)
        find_recursive(pattern, input, hit + 1, ++hits, recursion_guard + 1);
}

static bool isOnlyPattern(const std::string& input, const std::string& pattern) {
    if (input.size() % pattern.size() != 0) return false;

    for (size_t i = 0; i < input.size(); i += pattern.size())
        if (input.compare(i, pattern.size(), pattern) != 0)
            return false;

    return true;
}

std::unordered_set<int64_t> NumberComperator::compare_part_two(const int64_t a, const int64_t b) {
    std::unordered_set<int64_t> invalidNumbers;
    for (int64_t i = a; i <= b; i++) {
        auto input = std::to_string(i);
        std::string pattern;

        for (int j = 0; j < input.length(); ++j) {
            pattern += input[j];
            if (!isOnlyPattern(input, pattern)) continue;

            size_t hits = 0;
            find_recursive(pattern, input, 0, hits, 0);
            if (hits > 1) invalidNumbers.emplace(i);

        }
    }
    return invalidNumbers;
}

std::vector<int64_t> NumberComperator::compare() const {
    return compare_part_one(getMinNumber(), getMaxNumber());
}
std::unordered_set<int64_t> NumberComperator::compare_part_two() const {
    return compare_part_two(getMinNumber(), getMaxNumber());
}