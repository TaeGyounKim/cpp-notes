#include <chrono>
#include <cmath>
#include <ctime>
#include <print>

int main()
{
    using namespace std::chrono;

    // system_clock: 벽시계 시각(UTC). steady_clock: 거꾸로 가지 않는 시계
    std::println("system steady? {} / steady steady? {}",
                 system_clock::is_steady, steady_clock::is_steady);
    auto now{ system_clock::now() };
    std::println("지금(UTC) {}", floor<seconds>(now));
    std::println("지금(UTC) {:%Y년 %m월 %d일 %H시 %M분}", now);

    // C 스타일 time_t와 오가기
    std::time_t t{ system_clock::to_time_t(now) };
    std::println("time_t {} -> 다시 {}", t,
                 floor<seconds>(system_clock::from_time_t(t)));

    // 실행 시간 재기: steady_clock
    auto start{ steady_clock::now() };
    double acc{ 0 };
    const int n{ 2'000'000 };
    for (int i{ 0 }; i < n; ++i) { acc += std::sqrt(i) * std::sin(i); }
    auto elapsed{ steady_clock::now() - start };     // duration
    // 계산 결과를 쓰지 않으면 최적화로 반복문이 사라질 수 있다.
    std::println("acc = {:.3f}", acc);
    duration<double, std::milli> ms{ elapsed };      // 실수 밀리초
    // elapsed / n은 정수 나눗셈이므로 실수 duration으로 바꾼 뒤 나눈다.
    auto each{ duration<double, std::nano>{ elapsed } / n };
    std::println("걸린 시간 {:.2f}ms, 반복 한 번 {:.2f}ns", ms.count(),
                 each.count());
    std::println("밀리초로 버림 {}", duration_cast<milliseconds>(elapsed));

    // time_point: 시계의 기점(epoch)으로부터의 duration
    time_point<steady_clock, seconds> origin;        // 기점(초 단위)
    auto later{ origin + 90s };                      // tp + d = tp
    std::println("later - origin = {}", later - origin);   // tp - tp = d
    std::println("since epoch {}", later.time_since_epoch());

    // 변환: 세밀하게는 암시적, 거칠게는 time_point_cast
    time_point<steady_clock, milliseconds> fine{ later };
    time_point<steady_clock, milliseconds> odd{ 95'000ms };
    auto coarse{ time_point_cast<minutes>(odd) };
    std::println("{} / {} -> {} (round {})", fine.time_since_epoch(),
                 odd.time_since_epoch(), coarse.time_since_epoch(),
                 round<minutes>(odd).time_since_epoch());
}
