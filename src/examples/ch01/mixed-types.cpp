#include <print>

int main()
{
    int total{ 7 };
    int count{ 2 };

    // int / int: 둘 다 정수라 변환이 일어나지 않는다. 결과도 정수.
    std::println("{}", total / count);

    // int / double: int 쪽이 double로 바뀐 뒤 나눈다.
    std::println("{}", total / 2.0);

    // 한쪽을 직접 double로 바꾸면 나머지 한쪽도 따라서 바뀐다.
    std::println("{}", static_cast<double>(total) / count);

    // int와 unsigned int: int 쪽이 unsigned int로 바뀐다.
    int minus{ -1 };
    unsigned int one{ 1 };
    std::println("{}", minus * one);
}
