#include <cstdlib>
#include <iostream>

// auto 반환 타입 추론 대신: 반환 타입을 직접 적는다.
int calculateTotal(int price, int count)
{
    return price * count;
}

// [[maybe_unused]] 대신: 쓰지 않는 매개변수의 이름을 지운다.
int area(int width, int /* height */)
{
    return width * 10;
}

// [[noreturn]]은 C++11에서도 쓸 수 있다.
[[noreturn]] void stopProgram()
{
    std::exit(1);
}

int main()
{
    std::cout << calculateTotal(4500, 3) << '\n';
    std::cout << area(3, 4) << '\n';
    std::cout << __func__ << '\n';
    if (calculateTotal(1, 1) != 1) { stopProgram(); }
}
