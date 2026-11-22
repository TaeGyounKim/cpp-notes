#include <print>
#include <string>

int main()
{
    double value{ 3.1415 / 2.3 };

    // 부동소수점의 타입과 정밀도
    // 기본: 값을 되살릴 수 있는 가장 짧은 표현
    std::println("|{}|", value);
    std::println("|{:f}|", value);      // 고정 소수점. 정밀도 기본 6
    std::println("|{:.2f}|", value);    // 소수점 아래 2자리
    std::println("|{:e}|", value);      // 지수 표기
    std::println("|{:.3}|", value);     // 유효 숫자 3자리
    std::println("|{:10.2f}|", value);  // 너비 10, 소수점 아래 2자리

    // 문자열의 정밀도: 앞에서부터 몇 글자만
    std::string title{ "Professional" };
    std::println("|{:.3}|", title);

    // 정밀도를 인수로 받기 (동적 정밀도)
    std::println("|{:{}.{}f}|", value, 10, 3);

    // 0: 숫자 앞을 0으로 채운다. 부호와 접두어 뒤에 들어간다.
    int number{ 42 };
    std::println("|{:06d}|", number);
    std::println("|{:+06d}|", number);
    std::println("|{:#06x}|", number);
}
