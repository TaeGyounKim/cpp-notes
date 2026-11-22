#include <algorithm>
#include <cstddef>
#include <print>
#include <string>
#include <utility>
#include <vector>

// 직접 만든 정렬. 동작은 하지만 느리고(O(n²)),
// 시험과 유지 보수가 모두 내 몫이다.
void mySort(std::vector<std::string>& values)
{
    for (std::size_t i{ 0 }; i < values.size(); ++i) {
        for (std::size_t j{ 0 }; j + 1 < values.size() - i; ++j) {
            if (values[j] > values[j + 1]) {
                std::swap(values[j], values[j + 1]);
            }
        }
    }
}

int main()
{
    std::vector<std::string> names{ "Park", "Kim", "Lee", "Choi" };

    std::vector<std::string> first{ names };
    mySort(first);
    std::println("{}", first);

    // 표준 라이브러리를 재사용: 한 줄. 이미 수많은 사람이 써서 검증했다.
    std::vector<std::string> second{ names };
    std::ranges::sort(second);
    std::println("{}", second);

    // 있는 기능을 조합해 새 요구도 바로 해결한다: 길이 순으로 정렬
    std::ranges::sort(second, {}, &std::string::size);
    std::println("{}", second);
}
