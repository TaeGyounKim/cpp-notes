#include <iostream>
#include <locale>
#include <sstream>
#include <stdexcept>
#include <string>

// char16_t·char32_t와 u·U 접두사는 C++11부터, u8 문자열 리터럴은 C++11부터
// (char8_t 타입은 C++20), std::format의 {:L}(C++20)이 없으므로 스트림에
// 로캘을 imbue한다.
int main()
{
    char32_t ga = U'가';                 // U+AC00
    std::u16string s16 = u"가나";
    std::cout << sizeof(char16_t) << ' ' << s16.size() << ' '
              << static_cast<unsigned long>(ga) << '\n';

    std::ostringstream out;
    try {
        out.imbue(std::locale("en_US.UTF-8"));
    } catch (const std::runtime_error&) {
        out.imbue(std::locale::classic());
    }
    out << 1234567;
    std::cout << out.str() << '\n';
}
