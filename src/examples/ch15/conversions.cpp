#include <format>
#include <print>
#include <string>

class Celsius
{
public:
    Celsius(double value) : m_value{ value } {}   // double -> Celsius (암시적)

    // Celsius -> double. explicit이라 static_cast 등으로만 바뀐다.
    explicit operator double() const { return m_value; }

    // Celsius -> std::string. 반환 타입은 이름에 들어 있다.
    operator std::string() const { return std::format("{}도", m_value); }

private:
    double m_value{ 0 };
};

Celsius operator+(const Celsius& a, const Celsius& b)
{
    return Celsius{ static_cast<double>(a) + static_cast<double>(b) };
}

template <typename T>
class Owner
{
public:
    explicit Owner(T* ptr = nullptr) : m_ptr{ ptr } {}
    ~Owner() { delete m_ptr; }
    Owner(const Owner&) = delete;
    Owner& operator=(const Owner&) = delete;

    // if (p), !p 에서만 쓰인다. int로 몰래 바뀌지 않는다.
    explicit operator bool() const { return m_ptr != nullptr; }

private:
    T* m_ptr;
};

int main()
{
    Celsius c{ 6.6 };
    Celsius sum{ c + 3.4 };   // 3.4가 Celsius로 바뀐다. 모호하지 않다.
    double d{ static_cast<double>(sum) };
    std::string text = sum;   // 문자열로 변환
    std::println("{} / {}", d, text);

    Owner<int> empty;
    Owner<int> full{ new int{ 7 } };
    for (const Owner<int>* p : { &empty, &full }) {
        if (*p) { std::println("가리키는 것이 있음"); }
        if (!*p) { std::println("비어 있음"); }
    }
    // int i{ full };          // explicit operator bool: 컴파일 오류
}
