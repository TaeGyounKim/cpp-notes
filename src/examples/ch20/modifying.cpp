#include <algorithm>
#include <iterator>
#include <print>
#include <string>
#include <utility>
#include <vector>

int main()
{
    // generate: 콜백이 만든 값으로 채운다.
    std::vector<int> doubling(6);
    int seed{ 1 };
    std::generate(doubling.begin(), doubling.end(),
                  [&seed] { return seed *= 2; });
    std::println("generate {}", doubling);

    // transform: 제자리에서, 또는 두 범위를 짝지어
    std::vector celsius{ 20, 25, 30 };
    std::vector<double> fahrenheit(celsius.size());
    std::transform(celsius.cbegin(), celsius.cend(), fahrenheit.begin(),
                   [](int c) { return c * 1.8 + 32; });
    std::vector offset{ 1, -1, 0 };
    std::transform(celsius.cbegin(), celsius.cend(), offset.cbegin(),
                   celsius.begin(), [](int c, int d) { return c + d; });
    std::println("transform {} / 보정 {}", fahrenheit, celsius);

    // copy 계열: 대상은 미리 충분히 커야 한다(넣지 않고 덮어쓴다).
    std::vector readings{ 5, 12, 7, 18, 3 };
    std::vector<int> high(readings.size());
    auto copiedEnd{ std::copy_if(readings.cbegin(), readings.cend(),
                                 high.begin(), [](int r) { return r >= 7; }) };
    high.erase(copiedEnd, high.end());           // 남는 자리를 지운다.
    std::vector<int> firstTwo(2);
    std::copy_n(readings.cbegin(), 2, firstTwo.begin());
    std::vector<int> appended;
    std::copy(readings.cbegin(), readings.cend(),
              std::back_inserter(appended));      // 17장: 삽입 반복자
    std::println("copy_if {} copy_n {} back_inserter {}", high, firstTwo,
                 appended.size());

    // move 알고리즘: 원소를 이동 대입으로 옮긴다.
    std::vector<std::string> src{ "alpha", "beta" };
    std::vector<std::string> dst(src.size());
    std::move(src.begin(), src.end(), dst.begin());
    std::println("move {} / 옮겨진 원본은 쓰지 않음", dst);

    // replace_if: 조건에 맞는 값을 바꾼다.
    std::replace_if(readings.begin(), readings.end(),
                    [](int r) { return r > 15; }, 15);   // 상한 15
    std::println("replace_if {}", readings);

    // 지우기: C++20 std::erase_if가 가장 간단하다.
    std::vector<std::string> notes{ "", "점검", "", "교체", "청소" };
    std::erase_if(notes, [](const std::string& s) { return s.empty(); });
    std::println("erase_if {}", notes);

    // 그 이전: 지우기-제거 관용구
    std::vector v{ 3, 0, 5, 0, 0, 7 };
    auto it{ std::remove(v.begin(), v.end(), 0) };   // 남길 원소를 앞으로
    std::println("remove 직후 크기 {} 앞쪽 {}", v.size(),
                 std::vector(v.begin(), it));
    v.erase(it, v.end());                             // 실제로 지운다.
    std::println("erase 뒤 {}", v);
}
