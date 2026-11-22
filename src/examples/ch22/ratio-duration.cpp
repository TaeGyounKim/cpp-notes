#include <chrono>
#include <print>
#include <ratio>

int main()
{
    // ratio: 컴파일 시간 유리수. 객체가 아니라 타입이다.
    using third = std::ratio<2, 6>;              // 약분되어 1/3
    using sixth = std::ratio<1, 6>;
    using sum = std::ratio_add<third, sixth>;    // 1/3 + 1/6 = 1/2
    std::println("third = {}/{}", third::num, third::den);
    std::println("sum = {}/{}", sum::num, sum::den);
    std::println("sixth < third: {}", std::ratio_less<sixth, third>::value);

    using namespace std::chrono;
    // duration<틱 타입, 틱 주기(초)>
    duration<int, std::ratio<60>> lap{ 3 };      // 3분
    duration<int> rest{ 45 };                    // 45초
    std::println("lap {} (count {}), rest {}", lap, lap.count(), rest);

    // 단위가 달라도 계산·비교가 된다. 결과는 더 세밀한 단위(초)
    auto total{ lap * 4 + rest * 3 };
    std::println("total {} / lap > rest: {}", total, lap > rest);

    // 세밀한 단위로: 암시적 변환 / 거친 단위로: 실수 타입이나 duration_cast
    seconds s{ lap };
    duration<double, std::ratio<60>> m{ total };
    minutes cut{ duration_cast<minutes>(total) };
    std::println("{} = {} / {} -> {} (버림)", lap, s, total, cut);
    std::println("floor {}, ceil {}, round {}", floor<minutes>(total),
                 ceil<minutes>(total), round<minutes>(total));
    std::println("{}", m);

    // 미리 정의된 duration과 리터럴
    auto meeting{ 1h + 25min + 30s };
    std::println("meeting {} = {}", meeting, duration_cast<minutes>(meeting));
    auto frame{ 1000ms / 60 };                   // 정수 나눗셈
    std::println("frame {}", frame);

    // hh_mm_ss: 시, 분, 초로 나눈다.
    hh_mm_ss parts{ meeting + 250ms };
    std::println("{}시간 {}분 {}초 {}", parts.hours().count(),
                 parts.minutes().count(), parts.seconds().count(),
                 parts.subseconds());
}
