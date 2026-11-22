#include <iostream>

extern int g_readings;

namespace {   // 이름 없는 네임스페이스는 C++98부터
double calibrate(double raw) { return raw - 0.4; }
}

int g_readings = 0;

int main()
{
    ++g_readings;
    std::cout << g_readings << ' ' << calibrate(22.0) << '\n';
}
