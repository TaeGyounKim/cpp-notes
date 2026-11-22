#include <print>
#include <string>
#include <utility>
#include <vector>

using namespace std::string_literals;

int main()
{
    std::vector values{ 11, 22, 33 };

    std::println("{}", values);          // 기본: 대괄호와 쉼표
    std::println("{:n}", values);        // n: 대괄호를 뺀다.
    std::println("{{{:n}}}", values);    // 다른 괄호로 감싸기

    // 첫 번째 콜론 뒤: 범위 전체의 모양
    std::println("{:*^20}", values);

    // 두 번째 콜론 뒤: 원소 하나하나의 모양
    std::println("{::04}", values);
    std::println("{:n:#x}", values);

    // 문자열의 범위: 원소가 기본으로 이스케이프되어 나온다.
    std::vector words{ "Hello"s, "Tab\there"s };
    std::println("{}", words);
    // 원소 형식을 비워 두면 이스케이프하지 않는다.
    std::println("{::}", words);

    // 문자의 범위: s를 붙이면 문자열 하나처럼 출력한다.
    std::vector letters{ 'C', '+', '+' };
    std::println("{}", letters);
    std::println("{:s}", letters);

    // pair: 기본은 소괄호. m을 붙이면 "키: 값" 모양
    std::pair entry{ "width", 80 };
    std::println("{}", entry);
    std::println("{:n}", entry);
    std::println("{:m}", entry);

    // 범위 안의 범위: 콜론을 이어 가며 안쪽의 모양을 정한다.
    std::vector<std::vector<int>> grid{ { 1, 2 }, { 3, 4, 5 } };
    std::println("{}", grid);
    std::println("{:n}", grid);
    std::println("{:n:n}", grid);
    std::println("{:n:n:02}", grid);
}
