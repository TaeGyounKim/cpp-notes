#include <fstream>
#include <iostream>
#include <string>

// 파일 스트림은 C++98부터 있다. C++11부터 생성자가 std::string 이름도 받는다.
int main()
{
    std::string name = "c11.txt";
    {
        std::ofstream out(name);
        out << "54321";
        out.seekp(2, std::ios_base::beg);
        out << 0;
    }
    std::ifstream in(name);
    int value = 0;
    in >> value;
    std::cout << value << '\n';
}
