#include <cstddef>
#include <cstring>
#include <iostream>

// std::optional(C++17)이 없으므로 못 찾으면 -1을 돌려준다.
template <typename T>
long indexOf(const T& value, const T* arr, std::size_t size)
{
    for (std::size_t i = 0; i < size; ++i) {
        if (arr[i] == value) { return static_cast<long>(i); }
    }
    return -1;
}

template <typename T, std::size_t N>
long indexOf(const T& value, const T (&arr)[N])
{
    return indexOf(value, arr, N);
}

long indexOf(const char* value, const char** arr, std::size_t size)
{
    for (std::size_t i = 0; i < size; ++i) {
        if (std::strcmp(arr[i], value) == 0) { return static_cast<long>(i); }
    }
    return -1;
}

int main()
{
    int ids[] = { 10, 20, 30, 40 };
    const char word[] = "습도";
    const char* names[] = { "온도", "습도", "기압" };
    std::cout << indexOf(30, ids) << ' ' << indexOf(word, names, 3) << ' '
              << indexOf<const char*>(word, names, 3) << '\n';
}
