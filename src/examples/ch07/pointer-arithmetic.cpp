#include <cstddef>
#include <print>

int sum(const int* values, std::size_t count)
{
    int total{ 0 };
    for (std::size_t i{ 0 }; i < count; ++i) {
        total += values[i];
    }
    return total;
}

int main()
{
    int values[]{ 10, 20, 30, 40, 50 };
    int* p{ values };

    // p + 2는 "int 두 개만큼 뒤". 2바이트 뒤가 아니다.
    std::println("*(p + 2) = {}, p[2] = {}", *(p + 2), p[2]);

    // 포인터끼리 빼면 바이트 수가 아니라 원소 수가 나온다.
    int* last{ &values[4] };
    std::println("last - p = {}원소", last - p);
    std::println("바이트로는 {}",
                 reinterpret_cast<const char*>(last)
                     - reinterpret_cast<const char*>(p));

    // p + 2도 int를 가리키는 포인터. 배열의 뒷부분을 작은 배열처럼 넘긴다.
    std::println("전체의 합: {}", sum(p, 5));
    std::println("뒤 세 개의 합: {}", sum(p + 2, 3));

    // 원소 크기와 상관없이 "7칸 뒤". wchar_t는 1바이트가 아니다.
    const wchar_t* wide{ L"Hello, World" };
    std::println("wchar_t 크기: {}바이트", sizeof(wchar_t));
    std::println("7칸 뒤 글자: {}", static_cast<char>(*(wide + 7)));
}
