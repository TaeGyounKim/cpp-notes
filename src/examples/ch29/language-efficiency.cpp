#include <print>
#include <string>
#include <utility>
#include <vector>

// 생성, 복사, 이동, 소멸을 셉니다.
struct Counter {
    int made{ 0 }, copied{ 0 }, moved{ 0 }, destroyed{ 0 };
    void reset() { *this = Counter{}; }
    void show(const char* label) const
    {
        std::println("{:<22} 생성 {} 복사 {} 이동 {} 소멸 {}",
                     label, made, copied, moved, destroyed);
    }
};
Counter counter;

class Book {
public:
    Book(double price) : m_price{ price } { ++counter.made; }   // explicit 아님
    Book(std::string title, double price)
        : m_title{ std::move(title) }, m_price{ price } { ++counter.made; }
    Book(const Book& other)
        : m_title{ other.m_title }, m_price{ other.m_price }
    { ++counter.copied; }
    Book(Book&& other) noexcept
        : m_title{ std::move(other.m_title) }, m_price{ other.m_price }
    { ++counter.moved; }
    ~Book() { ++counter.destroyed; }
    double price() const { return m_price; }

private:
    std::string m_title;
    double m_price{ 0 };
};

double by_value(Book b) { return b.price(); }
double by_cref(const Book& b) { return b.price(); }

int code_to_points(int code)   // code는 0~3만 들어온다고 약속된 값
{
    switch (code) {
    case 0: return 10;
    case 1: return 20;
    case 2: return 30;
    case 3: return 40;
    default: std::unreachable();   // C++23
    }
}

int main()
{
    Book book{ "Efficient Code", 32.5 };

    counter.reset();
    by_value(book);
    counter.show("값으로 전달");

    counter.reset();
    by_cref(book);
    counter.show("const 참조로 전달");

    counter.reset();
    by_cref(19.9);   // double에서 임시 Book이 만들어짐
    counter.show("변환으로 임시 객체");

    counter.reset();
    try {
        throw Book{ 1.0 };
    } catch (const Book&) {
        counter.show("참조로 catch");
    }

    // 미리 할당하지 않으면 자랄 때마다 옮겨 담는다.
    for (bool reserve : { false, true }) {
        std::vector<Book> shelf;
        if (reserve) { shelf.reserve(1000); }
        counter.reset();
        std::size_t grows{ 0 };
        std::size_t cap{ shelf.capacity() };
        for (int i{ 0 }; i < 1000; ++i) {
            shelf.emplace_back(i * 1.0);
            if (shelf.capacity() != cap) { ++grows; cap = shelf.capacity(); }
        }
        std::println("reserve {:5}: 재할당 {:2}회, 옮긴 원소 {}",
                     reserve, grows, counter.moved);
    }

    int total{ 0 };
    for (int c : { 0, 1, 2, 3, 2 }) { total += code_to_points(c); }
    std::println("점수 합: {}", total);
}
