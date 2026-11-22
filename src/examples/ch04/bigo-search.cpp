#include <algorithm>
#include <print>
#include <vector>

// 비교가 일어난 횟수를 세는 전역 카운터
long long g_comparisons{ 0 };

// 값을 감싸서, 비교할 때마다 횟수를 올린다.
struct Counted
{
    int value;
};

bool operator==(const Counted& a, const Counted& b)
{
    ++g_comparisons;
    return a.value == b.value;
}

bool operator<(const Counted& a, const Counted& b)
{
    ++g_comparisons;
    return a.value < b.value;
}

int main()
{
    std::println("{:>9} {:>12} {:>16}", "n", "find", "binary_search");

    for (int n : { 1'000, 100'000, 1'000'000 }) {
        // 0, 1, 2, ... 로 채운다. 이미 정렬된 상태다.
        std::vector<Counted> values;
        for (int i{ 0 }; i < n; ++i) {
            values.push_back(Counted{ i });
        }
        const Counted target{ n - 1 };   // 맨 끝의 값: find에게 가장 나쁜 경우

        // std::find: 앞에서부터 하나씩. 문서에 적힌 복잡도는 O(n)
        g_comparisons = 0;
        const bool foundByFind{ std::find(values.begin(), values.end(), target)
                                != values.end() };
        const long long findCount{ g_comparisons };

        // std::binary_search: 절반씩 좁힌다. 문서에 적힌 복잡도는 O(log n)
        g_comparisons = 0;
        const bool foundByBinary{ std::binary_search(
            values.begin(), values.end(), target) };
        const long long binaryCount{ g_comparisons };

        if (foundByFind && foundByBinary) {
            std::println("{:>9} {:>12} {:>16}", n, findCount, binaryCount);
        }
    }
}
