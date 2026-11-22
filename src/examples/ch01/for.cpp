#include <cstddef>
#include <print>
#include <vector>

int main()
{
    // for (시작; 조건; 한 바퀴가 끝날 때마다 할 일)
    int total{ 0 };
    for (int i{ 1 }; i <= 5; ++i) {
        total += i;
    }
    std::println("1부터 5까지의 합: {}", total);

    // 번호로 컨테이너의 원소를 차례로 방문한다.
    std::vector<int> scores{ 90, 75, 60 };
    for (std::size_t i{ 0 }; i < scores.size(); ++i) {
        std::println("{}번: {}", i, scores[i]);
    }
}
