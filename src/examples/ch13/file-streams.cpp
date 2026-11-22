#include <fstream>
#include <iostream>
#include <print>
#include <string>
#include <string_view>

// 고정 폭 레코드의 값을 제자리에서 바꾼다(양방향 스트림).
bool changeValue(const std::string& file, int id, std::string_view value)
{
    std::fstream io{ file };                 // 읽기와 쓰기 모두
    if (!io) { return false; }
    int idRead{ 0 };
    std::string old;
    while (io >> idRead) {
        if (idRead == id) {
            io.seekp(io.tellg());            // 쓰기 위치를 읽기 위치로
            io << ' ' << value;              // 같은 폭으로 덮어씀
            return true;
        }
        io >> old;                           // 이 레코드의 값을 건너뜀
    }
    return false;
}

int main()
{
    {
        std::ofstream out{ "digits.txt" };   // 기본 모드: 처음부터 덮어씀
        if (!out) { std::println(std::cerr, "열 수 없음"); return 1; }
        out << "54321";
        std::println("쓰기 위치 {}", static_cast<long long>(out.tellp()));
        out.seekp(2, std::ios_base::beg);    // 앞에서 2바이트 뒤로 이동
        out << 0;                            // 세 번째 글자를 0으로
    }                                        // 소멸자가 파일을 닫는다.

    std::ifstream in{ "digits.txt" };
    int value{ 0 };
    in >> value;
    std::println("읽은 값 {}", value);       // 54021

    {
        std::ofstream log{ "log.txt" };                    // 새로 만듦
        log << "첫 줄\n";
    }
    {
        std::ofstream log{ "log.txt", std::ios_base::app }; // 끝에 덧붙임
        log << "둘째 줄\n";
    }
    std::ifstream logIn{ "log.txt" };
    std::string all;
    std::getline(logIn, all, '\0');          // 파일 전체 읽기
    std::print("{}", all);

    {
        std::ofstream table{ "table.txt" };
        table << "101 23.5\n102 19.0\n103 30.1\n";
    }
    changeValue("table.txt", 102, "21.7");
    std::ifstream tableIn{ "table.txt" };
    std::getline(tableIn, all, '\0');
    std::print("{}", all);
}
