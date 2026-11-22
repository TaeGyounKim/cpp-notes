#include <cstddef>
#include <exception>
#include <format>
#include <fstream>
#include <print>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// 직접 만든 예외 계층. 표준 std::exception에서 파생한다.
class FileError : public std::exception
{
public:
    explicit FileError(std::string file) : m_file{ std::move(file) } {}
    const char* what() const noexcept override { return m_message.c_str(); }
    const std::string& file() const noexcept { return m_file; }

protected:
    void setMessage(std::string message) { m_message = std::move(message); }

private:
    std::string m_file;
    std::string m_message;
};

class FileOpenError : public FileError
{
public:
    explicit FileOpenError(std::string file) : FileError{ std::move(file) }
    {
        // file은 이미 이동했으므로 file()로 읽는다.
        setMessage(std::format("{}을(를) 열 수 없음", this->file()));
    }
};

class FileReadError : public FileError
{
public:
    FileReadError(std::string file, std::size_t line)
        : FileError{ std::move(file) }, m_line{ line }
    {
        setMessage(std::format("{} {}번째 줄을 읽을 수 없음",
                               this->file(), line));
    }
    std::size_t line() const noexcept { return m_line; }

private:
    std::size_t m_line{ 0 };
};

std::vector<int> readNumbers(const std::string& file)
{
    std::ifstream in{ file };
    if (in.fail()) { throw FileOpenError{ file }; }
    std::vector<int> numbers;
    std::size_t lineNo{ 0 };
    std::string line;
    while (std::getline(in, line)) {
        ++lineNo;
        std::istringstream lineIn{ line };
        int value{ 0 };
        while (lineIn >> value) { numbers.push_back(value); }
        if (!lineIn.eof()) { throw FileReadError{ file, lineNo }; }
    }
    return numbers;
}

// 다른 예외를 품은 채 새 예외를 던진다(중첩 예외).
void loadConfig()
{
    try {
        readNumbers("config.txt");
    } catch (const FileError&) {
        std::throw_with_nested(std::runtime_error{ "설정을 불러오지 못함" });
    }
}

int main()
{
    std::ofstream{ "data.txt" } << "1 2 3\n4 x 6\n";

    for (const char* file : { "data.txt", "missing.txt" }) {
        try {
            readNumbers(file);
        } catch (const FileReadError& e) {         // 구체적인 것부터
            std::println("읽기 오류({}번째 줄): {}", e.line(), e.what());
        } catch (const FileError& e) {             // 그다음 기반 클래스
            std::println("파일 오류: {}", e.what());
        }
    }

    try {
        loadConfig();
    } catch (const std::exception& e) {
        std::println("바깥: {}", e.what());
        try {
            std::rethrow_if_nested(e);             // 품은 예외를 다시 던짐
        } catch (const FileError& inner) {
            std::println("  안쪽: {}", inner.what());
        }
    }
}
