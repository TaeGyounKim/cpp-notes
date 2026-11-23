#include <print>
#include <string>
#include <type_traits>
#include <utility>

// 1) 태그 디스패치: true_type / false_type으로 오버로드를 고른다.
template <typename T>
void describe_impl(const T& v, std::true_type)
{
    std::println("{}: 정수 계열", v);
}
template <typename T>
void describe_impl(const T& v, std::false_type)
{
    std::println("{}: 정수 계열 아님", v);
}
template <typename T>
void describe(const T& v)
{
    describe_impl(v, std::is_integral<T>{});   // 둘 중 하나를 상속한 객체
}

// 2) 관계: 같은 타입인가
template <typename A, typename B>
void same_type(const A& a, const B& b)
{
    std::println("{} / {}: {}", a, b,
                 std::is_same_v<A, B> ? "같은 타입" : "다른 타입");
}

// 3) conditional: 조건에 따라 타입을 고른다.
//    이동 대입이 예외를 던지지 않을 때만 우측값 참조로 넘긴다.
template <typename T>
constexpr std::conditional_t<std::is_nothrow_move_assignable_v<T>, T&&,
                             const T&>
move_assign_if_noexcept(T& t) noexcept
{
    return std::move(t);
}

void say(const char* what) { std::println("  {}", what); }
struct Risky {   // 이동 대입이 noexcept가 아님
    Risky& operator=(const Risky&) { say("복사 대입"); return *this; }
    Risky& operator=(Risky&&) { say("이동 대입"); return *this; }
};
struct Safe {    // 이동 대입이 noexcept
    Safe& operator=(const Safe&) { say("복사 대입"); return *this; }
    Safe& operator=(Safe&&) noexcept { say("이동 대입"); return *this; }
};

// 4) 직접 만든 타입 변경 트레이트
template <typename T> struct strip_ptr { using type = T; };
template <typename T> struct strip_ptr<T*> { using type = T; };
template <typename T> using strip_ptr_t = typename strip_ptr<T>::type;

int main()
{
    describe(42);
    describe(2.5);
    describe(std::string{ "text" });

    same_type(1, 32);
    same_type(1, 3.5);

    Risky r1, r2;
    Safe s1, s2;
    std::println("Risky:");
    r1 = move_assign_if_noexcept(r2);
    std::println("Safe:");
    s1 = move_assign_if_noexcept(s2);

    // 범주와 속성은 _v로 바로 값을 얻는다.
    std::println("{} {} {} {}", std::is_pointer_v<int*>,
                 std::is_floating_point_v<float>, std::is_const_v<const int>,
                 std::is_class_v<std::string>);
    // 타입 변경 트레이트는 _t로 새 타입을 얻는다.
    std::println("{} {} {}",
                 std::is_same_v<std::remove_pointer_t<int*>, int>,
                 std::is_same_v<std::add_const_t<int>, const int>,
                 std::is_same_v<strip_ptr_t<double*>, double>);
}
