#include <cstring>
#include <iomanip>
#include <iostream>
#include <print>
#include <string>

int main()
{
    // <<는 스트림 참조를 돌려주므로 이어 쓸 수 있다.
    int sensor{ 7 };
    std::string unit{ "kPa" };
    std::cout << "센서 " << sensor << ", 단위 " << unit << '\n';

    // 서식 없이 그대로: put()은 문자 하나, write()는 문자 배열
    const char* raw{ "raw" };
    std::cout.write(raw, std::strlen(raw));
    std::cout.put('!');
    std::cout.put('\n');

    // 상태 확인: 스트림은 bool로 바뀐다(!fail()과 같음).
    std::cout.flush();
    if (std::cout) { std::cout << "good: " << std::cout.good() << '\n'; }

    // 조작자
    bool ok{ true };
    std::cout << ok << ' ' << std::boolalpha << ok << std::noboolalpha << '\n';
    std::cout << std::hex << 255 << ' ' << std::oct << 8 << std::dec << '\n';

    int code{ 42 };
    std::cout << '[' << std::setw(6) << code << "]\n";      // 폭은 한 번만
    std::cout << '[' << std::setfill('0') << std::setw(6) << code << "]\n";
    std::cout << std::setfill(' ');
    std::println("[{:6}] [{:0>6}]", code, code);              // 같은 결과

    double ratio{ 1.23456789 };
    std::cout << std::setprecision(3) << ratio << ' '   // 유효 숫자 3
              << std::fixed << ratio << ' '             // 소수점 아래 3
              << std::scientific << ratio << '\n';
    std::cout << std::defaultfloat << std::setprecision(6);

    std::cout << 5.0 << ' ' << std::showpoint << 5.0 << '\n';
    std::cout << std::noshowpoint;
    std::cout << std::quoted("이름은 \"거실\"") << '\n';

    // 조작자 대신 멤버 함수: 이전 값을 돌려주므로 되돌리기 쉽다.
    auto old{ std::cout.precision(4) };
    std::cout << ratio << '\n';
    std::cout.precision(old);
    std::cout << ratio << '\n';
}
