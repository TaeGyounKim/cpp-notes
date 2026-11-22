#include <iostream>
#include <string>

const int versionMajor{ 2 };

class Counter
{
public:
    int getCount() const { return m_count; }
    void increase() { ++m_count; }

private:
    int m_count{ 0 };
};

void printTitle(const std::string* title)
{
    std::cout << *title << '\n';
}

int main()
{
    // const의 쓰임은 C++11에서도 모두 같다.
    std::string title{ "note" };
    printTitle(&title);

    int value{ 10 };
    const int* a{ &value };
    int* const b{ &value };
    *b = 11;
    std::cout << *a << ' ' << versionMajor << '\n';

    Counter counter;
    counter.increase();
    std::cout << counter.getCount() << '\n';
}
