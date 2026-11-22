#include <cstddef>
#include <iostream>
#include <vector>

// span(C++20)과 콘셉트(C++20)가 없으므로 vector 참조와
// 제약 없는 템플릿을 쓴다. using 별칭은 C++11부터, 그 전에는 typedef.
typedef bool (*Matcher)(int, int);

template <typename Handler>
void compareReadings(const std::vector<int>& a, const std::vector<int>& b,
                     Matcher matcher, Handler handler)
{
    for (std::size_t i = 0; i < a.size() && i < b.size(); ++i) {
        if (matcher(a[i], b[i])) { handler(i, a[i], b[i]); }
    }
}

bool same(int x, int y) { return x == y; }
void report(std::size_t pos, int x, int y)
{
    std::cout << '[' << pos << ": " << x << ", " << y << "] ";
}

struct Sensor
{
    int reading() const { return 7; }
};

int main()
{
    std::vector<int> inside = { 21, 30, 25, 33, 18 };
    std::vector<int> outside = { 19, 30, 26, 35, 18 };
    compareReadings(inside, outside, same, report);

    int (Sensor::*getter)() const = &Sensor::reading;
    Sensor s;
    std::cout << (s.*getter)() << '\n';
}
