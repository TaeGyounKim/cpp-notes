#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <print>

// 어떤 기계에서든 같은 바이트열이 나오도록 직접 큰 쪽부터 쓴다.
std::array<std::uint8_t, 4> to_big_endian(std::uint32_t v)
{
    return { static_cast<std::uint8_t>(v >> 24),
             static_cast<std::uint8_t>(v >> 16),
             static_cast<std::uint8_t>(v >> 8),
             static_cast<std::uint8_t>(v) };
}

std::uint32_t from_big_endian(const std::array<std::uint8_t, 4>& b)
{
    return (std::uint32_t{ b[0] } << 24) | (std::uint32_t{ b[1] } << 16) |
           (std::uint32_t{ b[2] } << 8) | std::uint32_t{ b[3] };
}

int main()
{
    std::println("기본 정수 타입의 크기(이 환경):");
    std::println("  short {} / int {} / long {} / long long {}", sizeof(short),
                 sizeof(int), sizeof(long), sizeof(long long));
    std::println("  포인터 {} / std::uintptr_t {}", sizeof(void*),
                 sizeof(std::uintptr_t));
    std::println("  int_least16_t {} / int_fast16_t {}",
                 sizeof(std::int_least16_t), sizeof(std::int_fast16_t));

    std::println("이 기계의 바이트 순서: {}",
                 std::endian::native == std::endian::little ? "리틀 엔디언"
                 : std::endian::native == std::endian::big  ? "빅 엔디언"
                                                            : "혼합");

    std::uint16_t value{ 513 };                 // 0x0201
    auto raw{ std::bit_cast<std::array<std::uint8_t, 2>>(value) };
    std::println("513을 메모리에 둔 그대로: {:02x} {:02x}", raw[0], raw[1]);

    std::uint32_t id{ 0x12345678 };
    auto wire{ to_big_endian(id) };             // 네트워크 바이트 순서
    std::println("네트워크로 보낼 바이트: {:02x} {:02x} {:02x} {:02x}",
                 wire[0], wire[1], wire[2], wire[3]);
    std::println("받아서 되돌림: {:#x}", from_big_endian(wire));
    std::println("byteswap: {:#x}", std::byteswap(id));   // C++23
}
