#include <print>

// 한 파일 안에서 보는 링크. 여러 파일에서의 동작은 본문을 보라.

extern int g_readings;   // 선언: 어딘가에 정의된 int가 있다(공간을 잡지 않음).

namespace {              // 이름 없는 네임스페이스: 이 파일 안에서만 보인다.
    double calibrate(double raw) { return raw - 0.4; }
}

int g_readings{ 0 };     // 정의: 여기서 공간을 잡는다(외부 링크).

void record(double raw)
{
    ++g_readings;
    std::println("기록 #{}: {}", g_readings, calibrate(raw));
}

int main()
{
    int local{ 5 };      // 링크 없음: 이 블록 안에서만 쓰는 이름
    record(22.0);
    record(21.4);
    std::println("총 {}회, 지역 변수 {}", g_readings, local);
}
