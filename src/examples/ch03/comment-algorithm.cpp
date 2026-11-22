#include <cstddef>
#include <optional>
#include <print>
#include <vector>

// 이진 탐색으로 target의 위치를 찾는다.
// values는 오름차순으로 정렬되어 있어야 한다.
// 찾으면 그 번호를, 없으면 std::nullopt를 돌려준다.
std::optional<std::size_t> find(const std::vector<int>& values, int target)
{
    // 찾는 값이 있을 수 있는 구간을 [low, high)로 두고,
    // 한 번 비교할 때마다 구간을 절반으로 줄여 나간다.
    std::size_t low{ 0 };
    std::size_t high{ values.size() };

    // 반복 불변식: target이 있다면 반드시 [low, high) 안에 있다.
    while (low < high) {
        // (low + high) / 2 는 두 수의 합이 넘칠 수 있어 이렇게 적는다.
        std::size_t middle{ low + (high - low) / 2 };

        if (values[middle] == target) {
            return middle;
        }
        if (values[middle] < target) {
            // middle과 그 왼쪽은 모두 target보다 작다. 오른쪽 절반만 남긴다.
            low = middle + 1;
        } else {
            // middle과 그 오른쪽은 모두 target보다 크다. 왼쪽 절반만 남긴다.
            high = middle;
        }
    }
    // 구간이 비었다. target은 없다.
    return std::nullopt;
}

int main()
{
    std::vector<int> values{ 3, 8, 15, 21, 42, 57 };

    if (auto position{ find(values, 21) }; position) {
        std::println("21은 {}번에 있다", *position);
    }
    if (!find(values, 20)) {
        std::println("20은 없다");
    }
}
