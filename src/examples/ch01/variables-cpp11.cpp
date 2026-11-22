#include <iostream>
#include <limits>

int main()
{
    // 중괄호 초기화와 빈 중괄호 초기화는 C++11부터 쓸 수 있다.
    int total{ 7 };
    int count{};
    long long big{ 14LL };

    std::cout << total << ' ' << count << ' ' << big << std::endl;
    std::cout << "int max: " << std::numeric_limits<int>::max() << std::endl;
}
