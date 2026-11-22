#include <print>

#define SENSOR_COUNT 3          // 값을 가진 식별자
#define USE_FAHRENHEIT          // 값 없이 정의만

int main()
{
#if SENSOR_COUNT > 2
    std::println("센서가 많은 구성: {}개", SENSOR_COUNT);
#else
    std::println("센서가 적은 구성");
#endif

#ifdef USE_FAHRENHEIT           // #if defined(USE_FAHRENHEIT)와 같다.
    std::println("단위: 화씨");
#elifdef USE_KELVIN             // C++23: #elif defined(USE_KELVIN)의 줄임
    std::println("단위: 켈빈");
#else
    std::println("단위: 섭씨");
#endif

#undef SENSOR_COUNT             // 정의를 없앤다.
#ifndef SENSOR_COUNT
    std::println("SENSOR_COUNT는 이제 정의되어 있지 않다.");
#endif

#if __cplusplus >= 202302L      // 표준 버전 검사
    std::println("C++23 이상으로 컴파일 중");
#endif
}
