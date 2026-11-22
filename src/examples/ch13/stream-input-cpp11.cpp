#include <iostream>
#include <string>

// 입력 스트림의 멤버와 조작자는 C++98부터 같다(std::ws, getline 등).
int main()
{
    std::string room;
    int people = 0;
    std::cin >> room >> people;

    char ch = 0;
    std::cin >> ch;            // 다음 문자 하나
    std::cin.putback('#');     // 다른 문자를 되돌려 놓기
    char again = 0;
    std::cin >> again;

    std::cin >> std::ws;
    std::string rest;
    std::getline(std::cin, rest);
    std::cout << room << ' ' << people << ' ' << ch << ' ' << again
              << " [" << rest << "]\n";
}
