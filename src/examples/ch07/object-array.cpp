#include <cstddef>
#include <print>

class Seat
{
public:
    Seat() : m_number{ ++s_next }
    {
        std::println("  생성: {}번 좌석", m_number);
    }
    ~Seat() { std::println("  소멸: {}번 좌석", m_number); }

private:
    int m_number;
    static inline int s_next{ 0 };
};

int main()
{
    std::println("객체의 배열");
    Seat* row{ new Seat[3] };   // 기본 생성자가 원소마다 불린다.
    delete[] row;               // 소멸자가 원소마다 불린다.
    row = nullptr;

    std::println("포인터의 배열");
    const std::size_t size{ 2 };
    Seat** seats{ new Seat*[size] };   // 포인터만 잡는다. Seat는 아직 없다.
    for (std::size_t i{ 0 }; i < size; ++i) {
        seats[i] = new Seat{};         // 객체는 하나씩 따로 만든다.
    }
    for (std::size_t i{ 0 }; i < size; ++i) {
        delete seats[i];               // 하나씩 따로 지운다.
        seats[i] = nullptr;
    }
    delete[] seats;                    // 마지막으로 포인터 배열을 지운다.
    seats = nullptr;
}
