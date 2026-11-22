// C++20 이전: <iomanip>의 조작자를 스트림에 흘려보내 형식을 지정한다.
#include <iomanip>
#include <iostream>

int main()
{
    std::cout << std::left << std::setw(8) << "item"
              << std::right << std::setw(5) << "qty"
              << std::setw(9) << "price" << '\n';

    // 소수점 아래 두 자리로 고정한다. 한번 설정하면 계속 유지된다.
    std::cout << std::fixed << std::setprecision(2);

    std::cout << std::left << std::setw(8) << "apple"
              << std::right << std::setw(5) << 3
              << std::setw(9) << 1.5 << '\n';

    std::cout << std::left << std::setw(8) << "melon"
              << std::right << std::setw(5) << 12
              << std::setw(9) << 23.456 << '\n';

    std::cout << "order no. " << std::setfill('0') << std::setw(5) << 42
              << '\n';
}
