#include <iostream>
#include <stdexcept>
#include <vector>

// 예외, 타입 별칭(using), auto, decltype 모두 C++11에서 쓸 수 있다.
using ScoreList = std::vector<int>;

int average(int total, int count)
{
    if (count == 0) {
        throw std::invalid_argument{ "count is zero" };
    }
    return total / count;
}

int main()
{
    ScoreList scores{ 90, 75, 60 };
    auto first = scores[0];
    decltype(first) second{ scores[1] };
    std::cout << first << ' ' << second << '\n';

    try {
        std::cout << average(100, 0) << '\n';
    } catch (const std::invalid_argument& exception) {
        std::cout << "caught: " << exception.what() << '\n';
    }
}
