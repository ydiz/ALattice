For std::array, the second template argument is of type std::size_t, not int
```
template<typename T, std::size_t N>   // don't use int
std::ostream& operator<<(std::ostream& out, const std::array<T, N> &a)
```
