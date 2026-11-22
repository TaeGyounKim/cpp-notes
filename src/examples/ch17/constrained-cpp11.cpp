#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Sensor
{
    std::string room;
    double celsius;
};

// 범위 판 알고리즘과 프로젝션(C++20)이 없으므로 반복자 쌍과
// 두 원소를 비교하는 람다(비교자)를 넘긴다.
int main()
{
    std::vector<Sensor> sensors = { { "침실", 19.5 }, { "거실", 22.0 },
                                    { "부엌", 24.5 } };
    std::sort(sensors.begin(), sensors.end(),
              [](const Sensor& a, const Sensor& b) { return a.room < b.room; });
    std::cout << sensors.front().room << '\n';

    std::vector<Sensor>::iterator it = std::find_if(
        sensors.begin(), sensors.end(),
        [](const Sensor& s) { return s.room == "거실"; });
    if (it != sensors.end()) { std::cout << it->celsius << '\n'; }
}
