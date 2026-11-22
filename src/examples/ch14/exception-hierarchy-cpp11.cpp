#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

// 예외 계층과 사용자 정의 예외는 C++98부터 있다.
// 중첩 예외(throw_with_nested, rethrow_if_nested)는 C++11부터 있다.
class FileError : public std::runtime_error
{
public:
    explicit FileError(const std::string& file)
        : std::runtime_error(file + "을(를) 열 수 없음"), m_file(file) {}
    const std::string& file() const noexcept { return m_file; }

private:
    std::string m_file;
};

void loadConfig()
{
    try {
        throw FileError("config.txt");
    } catch (const FileError&) {
        std::throw_with_nested(std::runtime_error("설정을 불러오지 못함"));
    }
}

int main()
{
    try {
        loadConfig();
    } catch (const std::exception& e) {
        std::cout << "바깥: " << e.what() << '\n';
        try {
            std::rethrow_if_nested(e);
        } catch (const FileError& inner) {
            std::cout << "  안쪽: " << inner.what() << '\n';
        }
    }
}
