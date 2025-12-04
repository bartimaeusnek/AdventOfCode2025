#include <cstdint>
#include <fstream>
#include <future>
#include <iostream>
#include <span>
#include <string>
#include <vector>

static bool contains(std::vector<int32_t> &vec, const int32_t value) {
    return std::ranges::find(vec, value) != vec.end();
}

int partOne() {
    std::ifstream file("../input");
    if (!file) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    std::string line;
    uint32_t totalJoltage = 0;
    while (std::getline(file, line)) {
        int32_t secondMax = -1;
        uint32_t max = 0;
        std::vector<int32_t> excluded;
        while (secondMax == -1) {
            secondMax = -1;
            max = 0;
            uint32_t maxIndex = 0;
            for (uint32_t i = 0; i < line.size() -1; ++i) {
                char c = line[i] - '0';
                if (c > max && !contains(excluded, c)) {
                    max = c;
                    maxIndex = i;
                }
            }

            for (uint32_t i = maxIndex + 1; i < line.size(); ++i) {
                char c = line[i] - '0';
                if (c > secondMax) {
                    secondMax = c;
                }
            }
            if (secondMax == -1) {
                excluded.push_back(max);
            }
        }

        uint32_t joltage = max * 10 + secondMax;
        // std::cout << "joltage: " << joltage << std::endl;

        totalJoltage += joltage;
    }

    std::cout << "Part 1 Total joltage: " << totalJoltage << std::endl;
    return 0;
}

typedef struct {
    uint8_t index;
    uint8_t value;
} JoltageCell;

int partTwo() {
    std::ifstream file("../input");
    if (!file) {
        std::cerr << "Failed to open file\n";
        return 1;
    }
    std::string line;
    uint64_t totalJoltage = 0;
    while (std::getline(file, line)) {
        std::vector<JoltageCell> cells;
        for (uint8_t i = 0; i < line.length(); ++i ) {
            const char c = line[i] - '0';
            cells.push_back({.index = i, .value = static_cast<uint8_t>(c)});
        }

        uint64_t joltage = 0;
        auto startingIter = cells.begin();
        for (int i = 0; i < 12; ++i) {
            auto endIter = cells.end() - (12 - i - 1);
            if (startingIter > endIter) {
                std::cerr << "Invalid range!\n";
                return 1;
            }

            const auto current_max_element = std::max_element(
                startingIter,
                endIter,
                [](const JoltageCell& a, const JoltageCell& b) { return a.value < b.value; }
            );

            joltage = joltage * 10 + current_max_element->value;
            startingIter = cells.begin() + current_max_element->index + 1;
        }
        std::cout << "Joltage: " << joltage << std::endl;
        totalJoltage += joltage;
    }


    std::cout << "Part 2 Total joltage: " << totalJoltage << std::endl;
    return 0;
}


int main() {
   partOne();
   partTwo();
}