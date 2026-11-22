#include <cmath>
#include <concepts>
#include <cstddef>
#include <limits>
#include <optional>
#include <print>

template <typename T>
concept Incrementable = requires(T x) { x++; ++x; };

// 여러 가지 문법으로 같은 제약을 건다.
template <typename T> requires Incrementable<T>
void bumpA(T& t) { ++t; }

template <typename T>
void bumpB(T& t) requires Incrementable<T> { ++t; }   // 뒤에 오는 requires 절

template <Incrementable T>
void bumpC(T& t) { ++t; }

void bumpD(Incrementable auto& t) { ++t; }             // 축약 + 타입 제약

// 제약 포섭: 더 구체적인 제약을 가진 쪽이 골라진다.
template <typename T> requires std::integral<T>
void kind(const T&) { std::println("정수"); }

template <typename T> requires (std::integral<T> && sizeof(T) == 4)
void kind(const T&) { std::println("4바이트 정수"); }

// 부동소수점에는 == 대신 오차를 허용하는 비교
template <std::floating_point T>
bool nearlyEqual(T x, T y, int ulps = 2)
{
    return std::fabs(x - y)
               <= std::numeric_limits<T>::epsilon() * std::fabs(x + y) * ulps
        || std::fabs(x - y) < std::numeric_limits<T>::min();
}

template <typename T>
std::optional<std::size_t> indexOf(const T& v, const T* arr, std::size_t n)
{
    for (std::size_t i{ 0 }; i < n; ++i) { if (arr[i] == v) { return i; } }
    return {};
}

template <std::floating_point T>   // 제약 기반 오버로드
std::optional<std::size_t> indexOf(const T& v, const T* arr, std::size_t n)
{
    for (std::size_t i{ 0 }; i < n; ++i) {
        if (nearlyEqual(arr[i], v)) { return i; }
    }
    return {};
}

// 클래스 템플릿과 멤버 함수의 제약
struct Device { virtual ~Device() = default; };
struct Sensor : Device { int id{ 7 }; };

template <std::derived_from<Device> T>
class Slot
{
public:
    void put(T item) requires std::copyable<T> { m_item = item; }
    const T& get() const { return m_item; }

private:
    T m_item{};
};

int main()
{
    int n{ 1 };
    bumpA(n); bumpB(n); bumpC(n); bumpD(n);
    std::println("n = {}", n);

    Incrementable auto counter{ 10 };      // 제약을 건 auto
    std::println("counter = {}", ++counter);

    kind(1);                // int: 두 판이 모두 맞지만 더 구체적인 쪽
    kind(short{ 2 });

    double values[]{ 0.1, 0.2, 0.30000000000000004 };
    std::println("== : {}", 0.1 + 0.2 == 0.3);
    std::println("indexOf 0.3: {}", indexOf(0.3, values, 3).value_or(99));

    Slot<Sensor> slot;
    slot.put(Sensor{});
    std::println("id {}", slot.get().id);
    // Slot<std::string> bad;   // 오류: std::string은 Device에서 파생하지 않음
}
