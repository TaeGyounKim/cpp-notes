#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>

int sum(std::initializer_list<int> values)
{
    int total{ 0 };
    for (int value : values) {
        total += value;
    }
    return total;
}

int main()
{
    // 범위 기반 for 문과 std::initializer_list는 C++11에서도 그대로 쓴다.
    std::vector<int> scores{ 90, 75, 60 };
    for (int score : scores) {
        std::cout << score << ' ';
    }
    std::cout << '\n';

    // for 문의 초기화 구문 대신: 변수를 앞에 선언하고 블록으로 감싼다.
    {
        std::vector<char> codes{ 'A', 'B', 'C' };
        for (char code : codes) {
            std::cout << code << ' ';
        }
        std::cout << '\n';
    }

    std::cout << sum({ 1, 2, 3 }) << '\n';

    std::string greeting{ "Hello" };
    std::cout << greeting << ' ' << greeting[1] << '\n';
}
