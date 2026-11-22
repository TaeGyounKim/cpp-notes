#include <chrono>
#include <print>

int main()
{
    using namespace std::chrono;

    // 날짜 만들기: / 연산자로 연/월/일, 월/일/연, 일/월/연
    year_month_day release{ 2026y / March / 14d };
    auto same{ 14d / March / 2026y };
    std::println("{} {} ok={}", release, release == same, release.ok());
    auto bad{ 2026y / February / 30d };
    std::println("{} ok={}", bad, bad.ok());

    // 몇째 요일, 마지막 날
    auto thanks{ 2026y / November / Thursday[4] };     // 넷째 목요일
    auto lastFeb{ 2028y / February / last };           // 윤년 2월 말
    std::println("{} -> {}", thanks, year_month_day{ sys_days{ thanks } });
    std::println("{} -> {}", lastFeb, year_month_day{ lastFeb });
    std::println("2028 윤년? {} / 요일 {}", year{ 2028 }.is_leap(),
                 weekday{ sys_days{ release } });

    // 직렬 타입 sys_days로 날짜 계산
    sys_days start{ 2026y / December / 20d };
    sys_days due{ start + days{ 45 } };
    std::println("45일 뒤 {}, 사이 {}", year_month_day{ due },
                 (due - start).count());

    // years를 time_point에 더하면 "평균 1년"이 더해진다.
    auto t{ sys_days{ 2026y / June / 1d } + 9h + 30min };
    std::println("+years{{1}} (직렬) {}", t + years{ 1 });
    // 필드 타입으로 바꿔 연만 더하면 시각이 그대로다.
    sys_days d{ floor<days>(t) };
    auto timeOfDay{ t - d };
    year_month_day ymd{ d };
    std::println("+years{{1}} (필드) {}",
                 sys_days{ ymd + years{ 1 } } + timeOfDay);

    // 시간대: UTC 시각을 지역 시각으로
    const time_zone* seoul{ locate_zone("Asia/Seoul") };
    const time_zone* ny{ locate_zone("America/New_York") };
    std::println("서울 {}", seoul->to_local(t));
    std::println("뉴욕 {}", ny->to_local(t));

    // zoned_time: 시간대와 시각을 함께
    zoned_time meet{ seoul, local_days{ 2026y / June / 1d } + 22h };
    zoned_time there{ ny, meet };
    std::println("{} = {}", meet, there);
}
