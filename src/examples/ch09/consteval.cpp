#include <print>

constexpr double toFahrenheit(double c) { return c * 9.0 / 5.0 + 32.0; }

// consteval: 반드시 컴파일 중에 계산된다(즉시 함수).
consteval double toKelvin(double c) { return c + 273.15; }

constexpr double describe(double c)
{
    if consteval {          // C++23: 상수 평가 중인가?
        return toKelvin(c); // 즉시 함수는 여기서만 부를 수 있다.
    } else {
        return -1.0;        // 실행 중에는 다른 길
    }
}

int main()
{
    constexpr double boiling{ 100.0 };
    constexpr double f1{ toFahrenheit(boiling) };   // 컴파일 중
    double measured{ 36.5 };
    double f2{ toFahrenheit(measured) };            // 실행 중(constexpr라도)

    constexpr double k1{ toKelvin(boiling) };       // 컴파일 중
    // double k2{ toKelvin(measured) };  // 컴파일 오류: 실행 중 값

    constexpr double d1{ describe(0.0) };   // 상수 평가: 273.15
    double d2{ describe(measured) };        // 실행 중: -1
    std::println("{} {} {} {} {}", f1, f2, k1, d1, d2);
}
