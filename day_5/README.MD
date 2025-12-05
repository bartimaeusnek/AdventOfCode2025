# --- Day 5: Cafeteria ---

Part 1 gave me no trouble at all. it was rather simple. For part 2 i first tried this naive implementation:  
```c++
//naive implementation, works for the example but not for the input:
std::unordered_set<uint64_t> _allranges;
for (auto [first, second] : rangeLinesUint) {
    for (uint64_t i = first; i <= second; ++i) {
        _allranges.insert(i);
    }
}
std::cout << "Part 2: " << _allranges.size() << "\n";
```
which did work fine for the example, but the actual input is just too big. So i had to redo it, which wasn't hard either.