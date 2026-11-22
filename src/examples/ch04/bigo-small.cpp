#include <cstddef>
#include <print>
#include <random>
#include <vector>

long long g_steps{ 0 };

// 삽입 정렬: O(n²). 하지만 하는 일이 단순하다.
void insertionSort(std::vector<int>& values)
{
    for (std::size_t i{ 1 }; i < values.size(); ++i) {
        const int element{ values[i] };
        std::size_t j{ i };
        while (j > 0 && (++g_steps, values[j - 1] > element)) {
            values[j] = values[j - 1];
            ++g_steps;
            --j;
        }
        values[j] = element;
        ++g_steps;
    }
}

// 병합 정렬: O(n log n). 하지만 임시 공간에 옮겼다가 되돌리는 일이 더 든다.
void mergeSort(std::vector<int>& values, std::size_t begin, std::size_t end)
{
    if (end - begin < 2) {
        return;
    }
    const std::size_t middle{ begin + (end - begin) / 2 };
    mergeSort(values, begin, middle);
    mergeSort(values, middle, end);

    std::vector<int> merged;
    std::size_t left{ begin };
    std::size_t right{ middle };
    while (left < middle && right < end) {
        ++g_steps;   // 비교
        merged.push_back(values[left] <= values[right] ? values[left++]
                                                       : values[right++]);
        ++g_steps;   // 임시 공간으로 옮기기
    }
    while (left < middle) { merged.push_back(values[left++]); ++g_steps; }
    while (right < end) { merged.push_back(values[right++]); ++g_steps; }
    for (std::size_t i{ 0 }; i < merged.size(); ++i) {
        values[begin + i] = merged[i];
        ++g_steps;   // 되돌려 놓기
    }
}

int main()
{
    // 첫째 열: 삽입 정렬의 걸음 수, 둘째 열: 병합 정렬의 걸음 수
    std::println("{:>6} {:>13} {:>14}", "n", "insertion", "merge");

    for (std::size_t n : { 8, 32, 128, 2048 }) {
        std::mt19937 generator{ 42 };   // 같은 씨앗: 실행할 때마다 같은 데이터
        std::vector<int> data;
        for (std::size_t i{ 0 }; i < n; ++i) {
            data.push_back(static_cast<int>(generator() % 10'000));
        }

        std::vector<int> first{ data };
        g_steps = 0;
        insertionSort(first);
        const long long insertionSteps{ g_steps };

        std::vector<int> second{ data };
        g_steps = 0;
        mergeSort(second, 0, second.size());
        const long long mergeSteps{ g_steps };

        std::println("{:>6} {:>13} {:>14}", n, insertionSteps, mergeSteps);
    }
}
