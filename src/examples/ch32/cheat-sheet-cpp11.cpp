#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

// 개념(C++20) 대신 static_assert로 템플릿 인수를 제한하고,
// make_unique(C++14) 대신 unique_ptr에 new를 넘긴다.
template <typename T>
class MaxTracker {
    static_assert(std::is_arithmetic<T>::value, "T는 산술 타입이어야 함");

public:
    MaxTracker() : m_max() {}
    void add(const T& v)
    {
        if (m_items.empty() || v > m_max) { m_max = v; }
        m_items.push_back(v);
    }
    const T& max() const
    {
        if (m_items.empty()) { throw std::logic_error("empty"); }
        return m_max;
    }

private:
    std::vector<T> m_items;
    T m_max;
};

class Shape {
public:
    virtual ~Shape() {}
    virtual double area() const = 0;
};

class Rect final : public Shape {
public:
    Rect(double w, double h) : m_w(w), m_h(h) {}
    double area() const override { return m_w * m_h; }

private:
    double m_w, m_h;
};

int main()
{
    std::unique_ptr<Shape> shape(new Rect(2.0, 3.5));
    std::cout << "area " << shape->area() << '\n';

    MaxTracker<int> tracker;
    try {
        tracker.max();
    } catch (const std::logic_error& e) {
        std::cout << "caught " << e.what() << '\n';
    }
    int values[] = { 5, 1, 4, 2, 6 };
    for (int x : values) { tracker.add(x); }
    std::cout << "max " << tracker.max() << '\n';

    {
        std::ofstream out("notes.txt");
        out << "first line\n" << 42 << '\n';
    }
    std::ifstream in("notes.txt");
    std::string line;
    int number = 0;
    std::getline(in, line);
    in >> number;
    std::cout << line << ", " << number << '\n';
}
