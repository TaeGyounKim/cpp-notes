#include <print>

int main()
{
    // 보통의 리터럴: 큰따옴표와 역슬래시 앞에 역슬래시를 붙여야 한다.
    std::println("Hello \"World\"!");
    std::println("C:\\temp\\notes.txt");

    // 로 문자열 리터럴: 적은 그대로 들어간다.
    std::println(R"(Hello "World"!)");
    std::println(R"(C:\temp\notes.txt)");

    // 이스케이프 시퀀스도 그냥 글자로 취급된다.
    std::println(R"(탭 문자가 될까? \t)");

    // 여러 줄도 그대로 적는다.
    std::println(R"(첫째 줄
둘째 줄)");

    // 안에 )" 가 들어가야 하면 구분자를 정해서 쓴다. 여기서는 -
    std::println(R"-(안에 )" 가 들어 있다)-");
}
