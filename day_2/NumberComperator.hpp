// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once
#include <string>
#include <unordered_set>
#include <vector>

class NumberComperator {
public:
    bool fromString(const std::string& min, const std::string& max);
    [[nodiscard]] std::vector<int64_t> compare() const;

    [[nodiscard]] std::unordered_set<int64_t> compare_part_two() const;

    [[nodiscard]] int64_t getMinNumber() const;
    [[nodiscard]] int64_t getMaxNumber() const;
private:
    int64_t m_min_number = 0;
    int64_t m_max_number = 0;
    [[nodiscard]] static std::vector<int64_t> compare_part_one(int64_t, int64_t);
    [[nodiscard]] static std::unordered_set<int64_t> compare_part_two(int64_t, int64_t);
};