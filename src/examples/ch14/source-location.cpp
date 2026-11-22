#include <exception>
#include <print>
#include <source_location>
#include <stacktrace>
#include <string>
#include <string_view>
#include <utility>

// 기본 인수 current()는 이 함수를 부른 곳에서 계산된다.
void logMessage(std::string_view message,
                std::source_location where = std::source_location::current())
{
    std::println("{}({}): {}: {}", where.file_name(), where.line(),
                 where.function_name(), message);
}

class TracedError : public std::exception
{
public:
    explicit TracedError(std::string message,
                         std::source_location where =
                             std::source_location::current())
        : m_message{ std::move(message) }, m_where{ where },
          m_trace{ std::stacktrace::current(1) }   // 생성자 프레임은 건너뜀
    {}
    const char* what() const noexcept override { return m_message.c_str(); }
    const std::source_location& where() const noexcept { return m_where; }
    const std::stacktrace& trace() const noexcept { return m_trace; }

private:
    std::string m_message;
    std::source_location m_where;
    std::stacktrace m_trace;
};

void readSensor()
{
    logMessage("측정 시작");
    throw TracedError{ "센서 응답 없음" };
}

void poll() { readSensor(); }

int main()
{
    try {
        poll();
    } catch (const TracedError& e) {
        std::println("잡음: '{}' {}번째 줄, {}", e.what(), e.where().line(),
                     e.where().function_name());
        std::println("스택 프레임 {}개. 위의 셋:", e.trace().size());
        for (unsigned i{ 0 }; const auto& frame : e.trace()) {
            if (i == 3) { break; }
            std::println("  {}> {} ({}번째 줄)", i++, frame.description(),
                         frame.source_line());
        }
    }
}
