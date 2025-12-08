# --- Day 4: Printing Department ---  
This day was the easiest conceptually for me by far. Cpp gave me a bit of trouble tho. The line:
```cpp
const auto nuPosition = Position(lx + m_position.x, ly + m_position.y);
```
used to be 
```cpp
const auto nuPosition = {x = x + m_position.x, y = y + m_position.y};
```
which modified the variables x & y, instead of setting them on the struct... oh well...  
That's something I've learned today.