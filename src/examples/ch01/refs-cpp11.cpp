#include <iostream>
#include <string>
#include <utility>

void addOne(int& n)
{
    n++;
}

void printTitle(const std::string& title)
{
    std::cout << title << '\n';
}

int main()
{
    // 참조, const 참조, 참조 매개변수는 C++11에서도 그대로 쓴다.
    int count{ 7 };
    addOne(count);
    std::cout << count << '\n';

    printTitle("Hello");

    // 구조적 바인딩의 auto& 대신: first, second에 직접 참조를 붙인다.
    std::pair<int, char> item{ 4500, 'A' };
    int& price{ item.first };
    price = 5000;
    std::cout << item.first << '\n';

    // std::as_const 대신: const 참조 변수를 직접 만든다.
    std::string name{ "C++" };
    const std::string& view{ name };
    std::cout << view << '\n';
}
