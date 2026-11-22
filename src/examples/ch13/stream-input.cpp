#include <cctype>
#include <iostream>
#include <print>
#include <string>

int main()
{
    // >>는 공백에서 끊어 읽는다.
    std::string room;
    int people{ 0 };
    std::cin >> room >> people;
    std::println("방 '{}', 인원 {}", room, people);

    // 숫자들을 읽어 더하다가 숫자가 아닌 것은 건너뛴다.
    int sum{ 0 };
    for (int i{ 0 }; i < 4; ++i) {
        int number{ 0 };
        std::cin >> number;
        if (std::cin) {
            sum += number;
        } else if (std::cin.eof()) {
            break;
        } else {                       // fail(): 숫자가 아님
            std::cin.clear();          // 실패 상태를 지우고
            std::string bad;
            std::cin >> bad;           // 문제의 토큰을 버린다.
            std::println("숫자가 아님: {}", bad);
        }
    }
    std::println("합 {}", sum);

    // peek()로 미리 보고, 숫자가 나올 때까지 공백 포함해 읽는다.
    std::cin >> std::ws;               // 앞의 공백을 건너뜀
    std::string label;
    while (std::cin && !std::isdigit(std::cin.peek())) {
        label += static_cast<char>(std::cin.get());
    }
    int floor{ 0 };
    std::cin >> floor;
    std::println("이름 '{}', 층 {}", label, floor);

    // 줄 단위로 읽기. 앞 줄의 남은 줄바꿈을 먼저 버린다.
    std::cin.ignore();
    std::string line;
    std::getline(std::cin, line);
    std::println("줄: '{}'", line);

    // 구분 문자를 바꿔 '@'까지 읽기(여러 줄 가능)
    std::string memo;
    std::getline(std::cin, memo, '@');
    std::println("메모: '{}'", memo);
}
