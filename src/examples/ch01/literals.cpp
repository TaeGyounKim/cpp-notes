#include <print>

int main()
{
    // 같은 수 123을 네 가지 진법으로 쓴 것
    std::println("{} {} {} {}", 123, 0173, 0x7B, 0b1111011);

    // 자릿수 구분자
    std::println("{}", 1'000'000);

    // 접미사: f가 붙으면 float, 없으면 double
    std::println("{} {}", 1.0f / 3, 1.0 / 3);

    // 나란히 쓴 문자열 리터럴은 하나로 합쳐진다.
    std::println("나눠 쓴 "
                 "문자열");
}
