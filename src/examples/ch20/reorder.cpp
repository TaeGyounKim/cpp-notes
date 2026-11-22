#include <algorithm>
#include <map>
#include <print>
#include <random>
#include <string>
#include <vector>

// for_each는 콜백의 복사본을 돌려준다. 상태는 돌려받은 값에서 읽는다.
class Stats
{
public:
    void operator()(int v)
    {
        m_sum += v;
        m_max = std::max(m_max, v);
    }
    int sum() const { return m_sum; }
    int max() const { return m_max; }

private:
    int m_sum{ 0 };
    int m_max{ 0 };
};

int main()
{
    // unique: 이웃한 중복을 앞으로 모으고 끝을 돌려준다(지우기는 erase로).
    std::vector log{ 1, 1, 2, 2, 2, 3, 1, 1 };
    log.erase(std::unique(log.begin(), log.end()), log.end());
    std::println("unique {}", log);              // 이웃한 것만 합쳐짐

    // shuffle과 sample: 난수 엔진이 필요하다(23장). 씨앗을 고정해 결과를 재현
    std::vector deck{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::mt19937 engine{ 42 };
    std::shuffle(deck.begin(), deck.end(), engine);
    std::vector<int> picked(3);
    std::sample(deck.cbegin(), deck.cend(), picked.begin(), 3, engine);
    std::println("shuffle {} / sample {}", deck, picked);

    // reverse, reverse_copy
    std::vector steps{ 1, 2, 3, 4 };
    std::reverse(steps.begin(), steps.end());
    std::vector<int> back(steps.size());
    std::reverse_copy(steps.cbegin(), steps.cend(), back.begin());
    std::println("reverse {} / reverse_copy {}", steps, back);

    // shift_left, shift_right(C++20): 밀어낸 뒤 남는 쪽을 erase
    std::vector queue{ 11, 22, 33, 44, 55 };
    queue.erase(std::shift_left(queue.begin(), queue.end(), 2), queue.end());
    std::println("shift_left 2 {}", queue);
    queue.erase(queue.begin(), std::shift_right(queue.begin(), queue.end(), 1));
    std::println("shift_right 1 {}", queue);

    // for_each와 for_each_n
    std::map<std::string, int> stock{ { "감", 4 }, { "배", 7 }, { "사과", 2 } };
    std::for_each_n(stock.cbegin(), 2, [](const auto& p) {
        std::print("{}:{} ", p.first, p.second);
    });
    std::println("");
    std::vector values{ 3, 9, 4 };
    Stats st{ std::for_each(values.cbegin(), values.cend(), Stats{}) };
    std::println("합 {} 최대 {}", st.sum(), st.max());
    std::for_each(values.begin(), values.end(), [](int& v) { v *= 2; });
    std::println("두 배 {}", values);
}
