#include <bit>
#include <cmath>
#include <cstdint>
#include <numbers>
#include <numeric>
#include <print>
#include <utility>
#include <version>   // 표준 라이브러리 기능 검사 매크로

int main()
{
    // 부호 있는 수와 없는 수의 안전한 비교
    // -1이 부호 없는 수로 바뀌어 아주 큰 수가 된다(-Wsign-compare 경고).
    std::println("-1 > 0u: {}", -1 > 0u);
    std::println("cmp_greater(-1, 0u): {}", std::cmp_greater(-1, 0u));

    // 수학 함수와 상수
    std::println("gcd {} lcm {} midpoint {}", std::gcd(12, 18), std::lcm(4, 6),
                 std::midpoint(10, 20));
    std::println("lerp(20, 30, 0.25) = {}", std::lerp(20.0, 30.0, 0.25));
    std::println("pi {:.5f} sqrt2 {:.5f}", std::numbers::pi,
                 std::numbers::sqrt2);

    // 비트 다루기(부호 없는 타입)
    std::uint8_t bits{ 0b1110'1011u };
    std::println("popcount {} countl_one {} countr_one {}", std::popcount(bits),
                 std::countl_one(bits), std::countr_one(bits));
    std::uint8_t r{ 0b1000'1000u };
    std::println("rotl {:08b}", std::rotl(r, 2));
    std::uint8_t v{ 0b0000'1011u };
    std::println("bit_ceil {} bit_floor {} bit_width {}", std::bit_ceil(v),
                 std::bit_floor(v), std::bit_width(v));
    std::uint32_t word{ 0x12345678u };
    std::println("byteswap {:x}", std::byteswap(word));         // C++23

#ifdef __cpp_lib_constexpr_vector
    std::println("__cpp_lib_constexpr_vector = {}", __cpp_lib_constexpr_vector);
#endif
    std::println("__cpp_lib_filesystem = {}", __cpp_lib_filesystem);
}
