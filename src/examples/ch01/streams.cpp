#include <format>
#include <iostream>
#include <print>

int main()
{
    // << 로 여러 값을 차례로 흘려보낸다.
    std::cout << "사과 " << 3 << "개" << std::endl;

    // format으로 문자열을 먼저 만든 뒤 흘려보낸다.
    std::cout << std::format("사과 {}개", 3) << '\n';

    // 이스케이프 시퀀스: \t 는 탭, \" 는 큰따옴표
    std::cout << "이름\t점수\n";
    std::cout << "\"민수\"\t90\n";

    // 오류 출력으로 보낸다.
    std::println(std::cerr, "파일을 열 수 없습니다: {}", "data.txt");
}
