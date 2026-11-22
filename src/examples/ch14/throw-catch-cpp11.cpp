#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// try/catch, throw, 표준 예외 클래스는 C++98부터 같다.
std::vector<int> readNumbers(const std::string& file)
{
    std::ifstream in(file);
    if (in.fail()) { throw std::invalid_argument("열 수 없음: " + file); }
    std::vector<int> numbers;
    int value = 0;
    while (in >> value) { numbers.push_back(value); }
    if (!in.eof()) { throw std::runtime_error("읽기 오류: " + file); }
    return numbers;
}

int main()
{
    { std::ofstream out("bad.txt"); out << "3 1 x 5"; }
    const char* files[] = { "bad.txt", "missing.txt" };
    for (const char* f : files) {
        try {
            readNumbers(f);
        } catch (const std::invalid_argument& e) {
            std::cout << "열기 실패 -> " << e.what() << '\n';
        } catch (const std::runtime_error& e) {
            std::cout << "형식 오류 -> " << e.what() << '\n';
        }
    }
}
