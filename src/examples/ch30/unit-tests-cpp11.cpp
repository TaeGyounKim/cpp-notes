#include <cstdio>
#include <functional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// source_location(C++20) 대신 __LINE__ 매크로,
// inline 정적 멤버(C++17) 대신 클래스 밖 정의를 쓴다.
struct TestCase {
    std::string name;
    std::function<void()> body;
};
std::vector<TestCase>& registry()
{
    static std::vector<TestCase> tests;
    return tests;
}
struct Register {
    Register(const char* name, std::function<void()> body)
    {
        TestCase t = { name, std::move(body) };
        registry().push_back(t);
    }
};
struct CheckFailed : std::runtime_error {
    explicit CheckFailed(const std::string& s) : std::runtime_error(s) {}
};

void check(bool ok, const char* expr, int line)
{
    if (!ok) {
        throw CheckFailed(std::string(expr) + " (line " +
                          std::to_string(line) + ")");
    }
}
#define CHECK(expr) check(static_cast<bool>(expr), #expr, __LINE__)

#define TEST(name)                          \
    void name();                            \
    Register reg_##name(#name, name);       \
    void name()

struct Counter {
    static int alive;
    Counter() { ++alive; }
    ~Counter() { --alive; }
};
int Counter::alive = 0;

TEST(alive_count)
{
    {
        Counter a, b;
        CHECK(Counter::alive == 2);
    }
    CHECK(Counter::alive == 0);
}

TEST(stoi_rejects_letters)   // 부정 테스트
{
    bool thrown = false;
    try { std::stoi("abc"); }
    catch (const std::invalid_argument&) { thrown = true; }
    CHECK(thrown);
}

int main()
{
    int failed = 0;
    for (std::size_t i = 0; i < registry().size(); ++i) {
        try {
            registry()[i].body();
            std::printf("[pass] %s\n", registry()[i].name.c_str());
        } catch (const std::exception& e) {
            ++failed;
            std::printf("[fail] %s: %s\n", registry()[i].name.c_str(),
                        e.what());
        }
    }
    std::printf("%d failed\n", failed);
    return failed == 0 ? 0 : 1;
}
