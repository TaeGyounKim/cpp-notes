#include <iostream>

int main()
{
    // C++11에는 2진수 리터럴이 없다. 16진수로 쓴다.
    std::cout << 123 << ' ' << 0173 << ' ' << 0x7B << std::endl;

    // C++11에는 자릿수 구분자가 없다. 붙여 쓴다.
    std::cout << 1000000 << std::endl;
}
