#include <cstdio>
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

// std::unreachable(C++23) 대신 컴파일러 확장을 쓴다.
// GCC, Clang: __builtin_unreachable(), MSVC: __assume(false)
#if defined(_MSC_VER)
#define UNREACHABLE() __assume(false)
#else
#define UNREACHABLE() __builtin_unreachable()
#endif

struct Counter {
    int made, copied, moved, destroyed;
    void reset() { made = copied = moved = destroyed = 0; }
    void show(const char* label) const
    {
        std::printf("%-12s made %d copied %d moved %d destroyed %d\n",
                    label, made, copied, moved, destroyed);
    }
};
Counter counter = {};

class Book {
public:
    Book(double price) : m_price(price) { ++counter.made; }
    Book(const Book& other)
        : m_title(other.m_title), m_price(other.m_price) { ++counter.copied; }
    Book(Book&& other) noexcept
        : m_title(std::move(other.m_title)), m_price(other.m_price)
    { ++counter.moved; }
    ~Book() { ++counter.destroyed; }
    double price() const { return m_price; }

private:
    std::string m_title;
    double m_price;
};

double by_value(Book b) { return b.price(); }
double by_cref(const Book& b) { return b.price(); }

int code_to_points(int code)
{
    switch (code) {
    case 0: return 10;
    case 1: return 20;
    case 2: return 30;
    case 3: return 40;
    default: UNREACHABLE();
    }
}

int main()
{
    Book book(32.5);

    counter.reset();
    by_value(book);
    counter.show("by value");

    counter.reset();
    by_cref(book);
    counter.show("by cref");

    counter.reset();
    by_cref(19.9);
    counter.show("temporary");

    for (int r = 0; r < 2; ++r) {
        std::vector<Book> shelf;
        if (r == 1) { shelf.reserve(1000); }
        counter.reset();
        for (int i = 0; i < 1000; ++i) { shelf.emplace_back(i * 1.0); }
        std::printf("reserve %d: moved %d\n", r, counter.moved);
    }

    int codes[] = { 0, 1, 2, 3, 2 };
    int total = 0;
    for (int c : codes) { total += code_to_points(c); }
    std::printf("total %d\n", total);
}
