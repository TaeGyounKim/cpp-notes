#include <cmath>
#include <iostream>
#include <limits>
#include <type_traits>

// 콘셉트(C++20) 대신 std::enable_if로 템플릿을 고르는 SFINAE(26장)
template <typename T,
          typename std::enable_if<std::is_integral<T>::value
                                  && sizeof(T) != 4, int>::type = 0>
void kind(const T&) { std::cout << "정수\n"; }

// C++11에는 포섭이 없으므로 두 조건이 겹치지 않게 직접 나눈다.
template <typename T,
          typename std::enable_if<std::is_integral<T>::value
                                  && sizeof(T) == 4, int>::type = 0>
void kind(const T&) { std::cout << "4바이트 정수\n"; }

template <typename T,
          typename std::enable_if<std::is_floating_point<T>::value,
                                  int>::type = 0>
bool nearlyEqual(T x, T y, int ulps = 2)
{
    return std::fabs(x - y)
               <= std::numeric_limits<T>::epsilon() * std::fabs(x + y) * ulps
        || std::fabs(x - y) < std::numeric_limits<T>::min();
}

struct Device { virtual ~Device() {} };
struct Sensor : Device { int id = 7; };

template <typename T>
class Slot
{
    // 클래스 템플릿 제약은 static_assert로 흉내 낸다.
    static_assert(std::is_base_of<Device, T>::value, "T는 Device여야 함");

public:
    void put(const T& item) { m_item = item; }
    const T& get() const { return m_item; }

private:
    T m_item;
};

int main()
{
    kind(1);
    kind(static_cast<short>(2));
    std::cout << nearlyEqual(0.1 + 0.2, 0.3) << '\n';
    Slot<Sensor> slot;
    slot.put(Sensor());
    std::cout << slot.get().id << '\n';
}
