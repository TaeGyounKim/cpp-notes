#include <cassert>
#include <cstddef>
#include <format>
#include <iostream>
#include <print>
#include <source_location>
#include <stdexcept>
#include <string>
#include <vector>

// ---- 최근 추적 메시지만 고정 개수로 기억하는 링 버퍼 ----
class TraceRing {
public:
    explicit TraceRing(std::size_t capacity) : m_items(capacity) {}

    void add(std::string message)
    {
        m_items[m_next] = std::format("#{} {}", m_count, std::move(message));
        m_next = (m_next + 1) % m_items.size();   // 끝에 닿으면 처음으로
        ++m_count;
    }

    void dump() const   // 가장 오래된 것부터
    {
        std::size_t n{ m_count < m_items.size() ? m_count : m_items.size() };
        std::size_t start{ m_count < m_items.size() ? 0 : m_next };
        std::println("--- 최근 추적 {}개 (전체 {}개 중) ---", n, m_count);
        for (std::size_t i{ 0 }; i < n; ++i) {
            std::println("  {}", m_items[(start + i) % m_items.size()]);
        }
    }

private:
    std::vector<std::string> m_items;
    std::size_t m_next{ 0 };
    std::size_t m_count{ 0 };
};

TraceRing g_ring{ 5 };
bool g_debug_mode{ false };   // 시작할 때 정하는 디버그 모드

// "int f(const std::string&)"에서 "f"만 남긴다.
std::string short_name(std::string full)
{
    full = full.substr(0, full.find('('));
    return full.substr(full.rfind(' ') + 1);
}

// 매크로 없이 호출한 함수 이름을 얻는다(C++20 source_location).
void trace(const std::string& message,
           std::source_location where = std::source_location::current())
{
    std::string line{ std::format("{}:{} {}", short_name(where.function_name()),
                                  where.line(), message) };
    if (g_debug_mode) { std::println("[trace] {}", line); }   // 바로 출력
    g_ring.add(std::move(line));                               // 늘 기억
}

enum class Level { Info, Warning, Error };

void log(Level level, const std::string& message)   // 사용자에게도 보이는 로그
{
    constexpr const char* names[]{ "INFO", "WARN", "ERROR" };
    std::println("[{}] {}", names[static_cast<int>(level)], message);
}

// ---- 시험용 작업 ----
int parse_quantity(const std::string& text)
{
    trace(std::format("parse '{}'", text));
    int value{ std::stoi(text) };            // 숫자가 아니면 던짐
    assert(value >= 0 && "수량은 음수가 될 수 없다");   // 가정 확인
    return value;
}

int total_quantity(const std::vector<std::string>& lines)
{
    int total{ 0 };
    for (const auto& line : lines) {
        total += parse_quantity(line);
        trace(std::format("total = {}", total));
    }
    return total;
}

int main()
{
    std::string mode;
    std::getline(std::cin, mode);
    g_debug_mode = (mode == "-d");
    log(Level::Info, std::format("시작 (디버그 모드 {})", g_debug_mode));

    try {
        std::println("합계: {}", total_quantity({ "3", "4", "10" }));
        std::println("합계: {}", total_quantity({ "2", "5", "x7", "1" }));
    } catch (const std::exception& e) {
        log(Level::Error, std::format("수량을 읽지 못함: {}", e.what()));
        g_ring.dump();   // 치명적 오류: 기억해 둔 추적을 내보냄
    }
}
