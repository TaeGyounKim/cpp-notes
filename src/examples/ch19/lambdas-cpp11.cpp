#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

// 람다와 std::function은 C++11부터 있다. move_only_function(C++23),
// 캡처 표현식(C++14), 클래스 템플릿 인수 추론(C++17)은 쓰지 않는다.
class Thermostat
{
public:
    typedef std::function<void(int)> Alarm;
    void onOverheat(Alarm alarm) { m_alarm = alarm; }
    void report(int celsius) const
    {
        if (celsius > 28 && m_alarm) { m_alarm(celsius); }
    }

private:
    Alarm m_alarm;
};

int main()
{
    int limit = 25;
    int alarms = 0;
    auto isHot = [limit](int t) { return t > limit; };
    auto ring = [&alarms](int t) {
        ++alarms;
        std::cout << "경보: " << t << '\n';
    };
    limit = 30;

    Thermostat t;
    t.onOverheat(ring);
    t.report(31);

    int (*twice)(int) = [](int x) { return x * 2; };
    std::vector<int> temps = { 22, 31, 19, 29 };
    std::cout << isHot(28) << ' ' << alarms << ' ' << twice(21) << ' '
              << std::count_if(temps.begin(), temps.end(), isHot) << '\n';
}
