#include <cstdint>
#include <cstdio>
#include <cstring>

// std::endian(C++20), std::bit_cast(C++20), std::byteswap(C++23) 없이:
// memcpy로 바이트를 들여다보고, 시프트로 직접 뒤집는다.
bool is_little_endian()
{
    std::uint16_t probe = 1;
    unsigned char first = 0;
    std::memcpy(&first, &probe, 1);   // 낮은 주소의 바이트
    return first == 1;
}

std::uint32_t swap32(std::uint32_t v)
{
    return ((v & 0x000000FFu) << 24) | ((v & 0x0000FF00u) << 8) |
           ((v & 0x00FF0000u) >> 8) | ((v & 0xFF000000u) >> 24);
}

int main()
{
    std::printf("int %u, long %u, pointer %u\n",
                static_cast<unsigned>(sizeof(int)),
                static_cast<unsigned>(sizeof(long)),
                static_cast<unsigned>(sizeof(void*)));
    std::printf("%s\n", is_little_endian() ? "little-endian" : "big-endian");

    std::uint32_t id = 0x12345678;
    unsigned char wire[4] = {
        static_cast<unsigned char>(id >> 24),
        static_cast<unsigned char>(id >> 16),
        static_cast<unsigned char>(id >> 8),
        static_cast<unsigned char>(id) };
    std::printf("%02x %02x %02x %02x\n", wire[0], wire[1], wire[2], wire[3]);
    std::printf("swapped 0x%x\n", static_cast<unsigned>(swap32(id)));
}
