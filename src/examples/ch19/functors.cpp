#include <cmath>
#include <concepts>
#include <functional>
#include <iterator>
#include <print>
#include <queue>
#include <set>
#include <string>
#include <string_view>
#include <vector>

using namespace std::string_view_literals;

// 상태를 가진 함수 객체: 기준 온도를 기억한다.
class Above
{
public:
    explicit Above(int limit) : m_limit{ limit } {}
    bool operator()(int value) const { return value > m_limit; }   // const

private:
    int m_limit;
};

// 연산을 콜백으로 받아 누적한다.
template <std::input_iterator Iter, typename Start,
          std::invocable<const Start&, const Start&> Op>
auto accumulateWith(Iter first, Iter last, const Start& start, Op op)
{
    auto result{ start };
    for (auto it{ first }; it != last; ++it) { result = op(result, *it); }
    return result;
}

void announce(int floor, std::string_view room)
{
    std::println("  {}층 {}", floor, room);
}

void increment(int& n) { ++n; }

int main()
{
    std::vector temps{ 18, 26, 31, 22 };
    Above hot{ 25 };
    std::print("25도 초과:");
    for (int t : temps) { if (hot(t)) { std::print(" {}", t); } }
    std::println("");

    // 산술 함수 객체를 콜백으로
    std::vector growth{ 2, 3, 4 };
    auto product{ accumulateWith(growth.begin(), growth.end(), 1,
                                 std::multiplies<>{}) };      // 투명 연산자
    std::println("곱 {}, 기하 평균 {:.3f}", product,
                 std::pow(product, 1.0 / growth.size()));
    // 투명 연산자는 타입이 섞여도 된다: double 1.5 * int
    std::println("1.5에서 시작 {}", accumulateWith(growth.begin(), growth.end(),
                                                   1.5, std::multiplies<>{}));

    // 비교 함수 객체로 순서 바꾸기
    std::priority_queue<int, std::vector<int>, std::greater<>> lowFirst;
    for (int t : temps) { lowFirst.push(t); }
    std::println("가장 낮은 온도 {}", lowFirst.top());

    // 투명 비교자: 문자열 리터럴로 찾을 때 std::string을 만들지 않는다.
    std::set<std::string, std::less<>> rooms{ "거실", "부엌" };
    std::println("부엌 있나? {}", rooms.contains("부엌"sv));

    // 바인더
    auto onThird{ std::bind(announce, 3, std::placeholders::_1) };
    onThird("회의실");
    auto swapped{ std::bind(announce, std::placeholders::_2,
                            std::placeholders::_1) };
    swapped("창고", 1);
    std::bind_front(announce, 5)("옥상");      // C++20
    std::bind_back(announce, "로비")(1);       // C++23

    int count{ 0 };
    std::bind(increment, count)();                    // 복사본이 늘어남
    std::bind(increment, std::ref(count))();          // 원본이 늘어남
    std::println("count {}", count);

    // 부정자와 멤버 함수 호출
    std::vector<std::string> notes{ "점검", "", "교체", "" };
    auto notEmpty{ std::not_fn(std::mem_fn(&std::string::empty)) };
    std::print("비지 않은 메모:");
    for (const auto& n : notes) { if (notEmpty(n)) { std::print(" {}", n); } }
    std::println("");
}
