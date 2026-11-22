#include <array>
#include <print>
#include <string_view>

// constexpr 함수: 컴파일 중에도 계산될 수 있다.
constexpr int slotsPerDay(int minutesPerSlot)
{
    return 24 * 60 / minutesPerSlot;
}

void log(std::string_view message)   // constexpr가 아닌 보통 함수
{
    std::println("  [로그] {}", message);
}

constexpr int threshold(bool verbose)
{
    if (verbose) {
        log("자세한 모드");   // 실행 중에 계산될 때만 거치는 길
        return 30;
    }
    return 35;
}

int main()
{
    // std::array의 크기는 상수 식이어야 한다.
    std::array<double, slotsPerDay(30)> readings{};   // 48칸
    std::println("측정 칸 수: {}", readings.size());

    constexpr int quiet{ threshold(false) };   // 컴파일 중에 계산
    // constexpr int loud{ threshold(true) };  // 컴파일 오류: log()를 거침
    const int loud{ threshold(true) };         // 실행 중에 계산: 됨
    std::println("기준: {} / {}", quiet, loud);
}
