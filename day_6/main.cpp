// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <iostream>
#include <fstream>
#include <span>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split_string(const std::string& s, const char delim = ' ')
{
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim)) {
        if (!item.empty()) {
            result.push_back(item);
        }
    }
    return result;
}

void trim_in_place(std::string& s)
{
    s.erase(0, s.find_first_not_of(" \t\n\r\f\v"));
    s.erase(s.find_last_not_of(" \t\n\r\f\v") + 1);
}

int part_one(const std::string &s) {
    std::string content = s;
    const auto rows = split_string(content, '\n');
    const auto oneLineSplit = split_string(rows[0]);
    const auto elementsPerRow = oneLineSplit.size();
    for (char & _char: content) {
        if (_char == '\n') {
            _char = ' ';
        }
    }
    const auto split = split_string(content);
    const auto arithmeticSymbols = std::span(split).last(elementsPerRow);
    const auto numericSymbols = std::span(split).first(split.size() - elementsPerRow);
    for (auto basic_string : arithmeticSymbols) {
        trim_in_place(basic_string);
    }
    for (auto string : split) {
        trim_in_place(string);
    }

    std::vector<uint64_t> arr(elementsPerRow);
    for (int i = 0; i < elementsPerRow; ++i) {
        if (arithmeticSymbols[i] == "+" || arithmeticSymbols[i] == "-")
            arr[i] = 0;
        else
            arr[i] = 1;
    }

    for (size_t row = 0; row < numericSymbols.size() / elementsPerRow; ++row) {
        for (int i = 0; i < elementsPerRow; ++i) {
            auto index = row * elementsPerRow + i;
            auto element = std::stoll(numericSymbols[index]);
            auto symbol = arithmeticSymbols[i][0];
            switch (symbol) {
                case '+':
                    arr[i] += element;
                    break;
                case '-':
                    arr[i] -= element;
                    break;
                case '*':
                    arr[i] *= element;
                    break;
                case '/':
                    arr[i] /= element;
                    break;
                default:
                    return 2;
            }
        }
    }

    uint64_t total = 0;
    for (uint64_t value : arr)
        total += value;
    std::cout << total << std::endl;
    return 0;
}

void numeric_calc(const std::span<std::string> &numericPart, const int col, std::vector<uint64_t> &currentBlock ) {
    std::string numberRaw;
    for (const auto & row : numericPart) {
        const char c = row.size() < col ? ' ' : row[col];
        if (c >= '0' && c <= '9') {
            numberRaw += c;
        }
    }
    if (!numberRaw.empty()) currentBlock.emplace_back(std::stoll(numberRaw));
}

std::vector<std::vector<uint64_t>> calculate_total_numeric_blocks(std::vector<std::string> &rows) {
    int offset = 1;
    if (rows[rows.size() -1].empty()) {
        offset++;
    }
    const std::span<std::string> numericPart = std::span(rows).first(rows.size() - offset);
    const auto rowLength = numericPart[numericPart.size() -1].length();

    std::vector<std::vector<uint64_t>> blocks;
    std::vector<uint64_t> currentBlock;
    for (int col = 0; col < rowLength; ++col) {
        const char basecharacter = numericPart[0].size() < col ? ' ' : numericPart[0][col];
        if (basecharacter == ' ') {
            for (const auto & row : numericPart) {
                const char c = row.size() < col ? ' ' : row[col];
                if (c != ' ') {
                    if (c >= '0' && c <= '9') {
                        numeric_calc(numericPart, col, currentBlock);
                    }
                    goto next;
                }
            }
            blocks.emplace_back(currentBlock);
            currentBlock = std::vector<uint64_t>();
        }
        else {
            numeric_calc(numericPart, col, currentBlock);
        }
        next:;
    }
    blocks.emplace_back(currentBlock);
    return blocks;
}

int part_two(const std::string &s) {
    std::string content = s;
    auto rows = split_string(content, '\n');
    auto slots = calculate_total_numeric_blocks(rows);
    for (char & _char: content) {
        if (_char == '\n') {
            _char = ' ';
        }
    }
    const auto elementsPerRow = slots.size();
    const auto split = split_string(content);
    const auto arithmeticSymbols = std::span(split).last(elementsPerRow);
    std::vector<uint64_t> arr(slots.size());
    for (int i = 0; i < slots.size(); ++i) {
        if (arithmeticSymbols[i] == "+" || arithmeticSymbols[i] == "-")
            arr[i] = 0;
        else
            arr[i] = 1;
    }
    for (int i = 0; i < slots.size(); ++i) {
        auto symbol = arithmeticSymbols[i][0];
        for (auto element: slots[i]) {
            switch (symbol) {
                case '+':
                    arr[i] += element;
                    break;
                case '-':
                    arr[i] -= element;
                    break;
                case '*':
                    arr[i] *= element;
                    break;
                case '/':
                    arr[i] /= element;
                    break;
                default:
                    return 2;
            }
        }
    }
    uint64_t total = 0;
    for (uint64_t value : arr)
        total += value;
    std::cout << total << std::endl;
    return 0;
}

int main() {
    std::ifstream file("../input");
    if (!file) {
        std::cerr << "Failed to open file\n";
        return 1;
    }
    const std::string content{std::istreambuf_iterator(file),{}};
    file.close();
    if (const int err = part_one(content)) {
        std::cerr << "Part 1 failed\n";
        return err;
    }
    if (const int err = part_two(content)) {
        std::cerr << "Part 2 failed\n";
        return err;
    }
    return 0;
}