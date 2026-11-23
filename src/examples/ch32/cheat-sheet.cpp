#include <algorithm>
#include <concepts>
#include <cstddef>
#include <fstream>
#include <memory>
#include <print>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// 1) 클래스 하나: 특수 멤버 함수를 명시
class Shape {
public:
    explicit Shape(std::string name) : m_name{ std::move(name) } {}
    virtual ~Shape() = default;                  // 기반 클래스면 가상 소멸자
    Shape(const Shape&) = delete;                // 복사 금지
    Shape& operator=(const Shape&) = delete;
    Shape(Shape&&) = default;                    // 이동은 허용
    Shape& operator=(Shape&&) = default;

    virtual double area() const = 0;             // 순수 가상 함수
    const std::string& name() const { return m_name; }

private:
    std::string m_name;
};

// 2) 파생 클래스: override, final
class Rect final : public Shape {
public:
    Rect(double w, double h) : Shape{ "rect" }, m_w{ w }, m_h{ h } {}
    double area() const override { return m_w * m_h; }

private:
    double m_w, m_h;
};

// 3) 복사 후 맞바꾸기(copy-and-swap)
class Buffer {
public:
    explicit Buffer(std::size_t n) : m_size{ n }, m_data{ new int[n]{} } {}
    ~Buffer() { delete[] m_data; }
    Buffer(const Buffer& src) : Buffer{ src.m_size }
    {
        std::copy(src.m_data, src.m_data + m_size, m_data);
    }
    Buffer& operator=(const Buffer& rhs)
    {
        Buffer temp{ rhs };   // 복사가 실패해도 *this는 그대로
        swap(temp);           // noexcept 맞바꾸기
        return *this;
    }
    void swap(Buffer& other) noexcept
    {
        std::swap(m_size, other.m_size);
        std::swap(m_data, other.m_data);
    }
    std::size_t size() const { return m_size; }

private:
    std::size_t m_size;
    int* m_data;
};

// 4) 개념으로 제약한 클래스 템플릿
template <std::totally_ordered T>
class MaxTracker {
public:
    void add(const T& v)
    {
        if (m_items.empty() || v > m_max) { m_max = v; }
        m_items.push_back(v);
    }
    const T& max() const
    {
        if (m_items.empty()) { throw std::logic_error{ "비어 있음" }; }
        return m_max;
    }

private:
    std::vector<T> m_items;
    T m_max{};
};

int main()
{
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Rect>(2.0, 3.5));
    for (const auto& s : shapes) {
        std::println("{}: {}", s->name(), s->area());
    }

    // 5) 람다: 캡처, 매개변수, 반환
    int threshold{ 3 };
    std::vector<int> v{ 5, 1, 4, 2, 6 };
    auto big{ std::count_if(v.begin(), v.end(),
                            [threshold](int x) { return x > threshold; }) };
    std::println("{}보다 큰 원소: {}개", threshold, big);

    Buffer a{ 4 }, b{ 10 };
    a = b;
    std::println("대입 후 크기: {}", a.size());

    // 6) 예외 던지고 잡기
    MaxTracker<int> tracker;
    try {
        std::println("최댓값: {}", tracker.max());
    } catch (const std::logic_error& e) {
        std::println("잡은 예외: {}", e.what());
    }
    for (int x : v) { tracker.add(x); }
    std::println("최댓값: {}", tracker.max());

    // 7) 파일 쓰기와 읽기
    {
        std::ofstream out{ "notes.txt" };
        if (!out) { std::println("파일을 열 수 없음"); return 1; }
        out << "first line\n" << 42 << '\n';
    }   // 여기서 닫힘
    std::ifstream in{ "notes.txt" };
    std::string line;
    int number{ 0 };
    std::getline(in, line);
    in >> number;
    std::println("읽음: '{}', {}", line, number);
}
