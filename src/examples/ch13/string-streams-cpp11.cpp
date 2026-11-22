#include <iostream>
#include <sstream>
#include <string>

// 문자열 스트림과 사용자 정의 조작자는 C++98부터 있다.
std::ostream& bullet(std::ostream& out) { return out << " - "; }

int main()
{
    std::ostringstream out;
    out << "온도=" << 23.5 << ", 습도=" << 41;
    std::string text = out.str();
    std::cout << "목록" << bullet << text << '\n';

    // quoted(C++14) 없이: 따옴표 없는 형식으로 읽는다.
    std::istringstream in("부엌 21 false");
    std::string place;
    double value = 0;
    bool alarm = true;
    in >> place >> value >> std::boolalpha >> alarm;
    std::cout << place << ' ' << value << ' ' << std::boolalpha << alarm
              << '\n';
}
