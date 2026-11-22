#include <print>
#include <string>
#include <type_traits>
#include <utility>

// 추론할 수 없는 RetType은 앞에 두고 직접 지정한다.
template <typename RetType, typename T1, typename T2>
RetType addAs(const T1& a, const T2& b) { return a + b; }

// 반환 타입의 기본값
template <typename RetType = long long, typename T1, typename T2>
RetType addWide(const T1& a, const T2& b) { return a + b; }

// C++14: 반환 타입 추론
template <typename T1, typename T2>
auto add(const T1& a, const T2& b) { return a + b; }

const std::string g_unit{ "kPa" };
const std::string& unit() { return g_unit; }

// decltype(auto)는 참조와 const를 그대로 둔다.
template <typename F>
decltype(auto) callKeep(F f) { return f(); }

template <typename F>
auto callCopy(F f) { return f(); }

int main()
{
    auto x{ addAs<long long, int, int>(1, 2) };   // 모두 지정
    auto y{ addAs<long long>(1, 2) };             // T1, T2는 추론
    auto z{ addWide(1, 2) };                      // 기본값 long long
    std::println("{} {} {}", std::is_same_v<decltype(x), long long>,
                 std::is_same_v<decltype(y), long long>,
                 std::is_same_v<decltype(z), long long>);

    auto d{ add(1, 2.5) };                        // int + double -> double
    std::println("{} {}", d, std::is_same_v<decltype(d), double>);

    auto s1{ unit() };                 // auto: 참조와 const가 벗겨져 복사
    decltype(auto) s2{ unit() };       // const std::string&
    std::println("{} {}", std::is_same_v<decltype(s1), std::string>,
                 std::is_same_v<decltype(s2), const std::string&>);

    std::println("{} {}",
        std::is_same_v<decltype(callKeep(unit)), const std::string&>,
        std::is_same_v<decltype(callCopy(unit)), std::string>);
}
