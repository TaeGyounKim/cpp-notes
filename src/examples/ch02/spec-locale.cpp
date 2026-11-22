#include <exception>
#include <format>
#include <iostream>
#include <locale>

int main()
{
    int population{ 1234567 };
    double price{ 1234.5 };

    try {
        // L을 쓸 때는 std::format의 첫 인수로 로케일을 넘긴다.
        std::locale us{ "en_US.UTF-8" };   // 미국식
        std::locale de{ "de_DE.UTF-8" };   // 독일식

        std::cout << std::format("{}", population) << '\n';
        std::cout << std::format(us, "{:L}", population) << '\n';
        std::cout << std::format(de, "{:L}", population) << '\n';

        std::cout << std::format(us, "{:L}", price) << '\n';
        std::cout << std::format(de, "{:L}", price) << '\n';
    } catch (const std::exception& exception) {
        // 실행 환경에 그 로케일이 설치되어 있지 않으면 여기로 온다.
        std::cout << "로케일을 쓸 수 없음: " << exception.what() << '\n';
    }
}
