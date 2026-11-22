#include <array>
#include <print>
#include <vector>

int main()
{
    std::array scores{ 90, 75, 60 };

    // scores의 원소를 하나씩 score에 복사해 가며 반복한다.
    for (int score : scores) {
        std::println("{}", score);
    }

    // vector와 C 스타일 배열에도 똑같이 쓴다.
    std::vector<double> prices{ 4500.0, 3000.5 };
    for (double price : prices) {
        std::println("{}", price);
    }

    // 초기화 구문: codes는 이 for 문 안에서만 쓴다. (C++20)
    for (std::array codes{ 'A', 'B', 'C' }; char code : codes) {
        std::println("{}", code);
    }
}
