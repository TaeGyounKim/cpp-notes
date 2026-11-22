#include <print>
#include <string>
#include <vector>

const std::string message{ "Test" };

const std::string& getMessage()
{
    return message;
}

int main()
{
    auto count{ 123 };      // int
    auto ratio{ 1.5 };      // double
    auto letter{ 'A' };     // char
    std::println("{} {} {}", count, ratio, letter);

    std::vector<int> scores{ 90, 75, 60 };
    auto size{ scores.size() };   // 반환 타입을 몰라도 받을 수 있다.
    std::println("{}", size);

    // auto는 참조와 const를 떼어 낸다. copy는 std::string, 즉 복사본
    auto copy{ getMessage() };
    copy += "!";            // const가 떨어져 나갔으므로 바꿀 수 있다.
    std::println("{} / {}", copy, message);

    // 복사하지 않으려면 직접 적는다.
    const auto& view{ getMessage() };
    std::println("같은 객체인가: {}", &view == &message);
    std::println("같은 객체인가: {}", &copy == &message);
}
