#include <cctype>
#include <cstdint>
#include <format>
#include <iostream>
#include <locale>
#include <print>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>

// 로캘 이름은 구현마다 다르다. 없으면 예외가 나므로 여러 이름을 시도한다.
std::locale tryLocale(std::initializer_list<const char*> names)
{
    for (const char* n : names) {
        try { return std::locale{ n }; } catch (const std::runtime_error&) {}
    }
    return std::locale::classic();               // 없으면 "C" 로캘
}

int main()
{
    // 문자 타입과 리터럴 접두사
    wchar_t wide{ L'가' };
    char16_t utf16{ u'가' };
    char32_t utf32{ U'가' };
    std::u8string u8{ u8"가나" };
    std::println("크기(바이트) wchar_t {} char16_t {} char32_t {}",
                 sizeof(wide), sizeof(utf16), sizeof(utf32));
    std::println("u8\"가나\"는 {}바이트(한 글자 3바이트)", u8.size());
    std::println("코드 포인트 U+{:04X}", static_cast<std::uint32_t>(utf32));

    // 같은 문자를 이스케이프로(C++23 \u{...}, \N{...})
    const char pi[]{ "\u03C0 \u{3C0} \N{GREEK SMALL LETTER PI}" };   // C++23
    std::println("{}", pi);

    // 와이드 문자열과 와이드 스트림
    std::wstring wname{ L"temperature" };
    std::wcout << L"wide: " << wname << L'\n';
    std::wcout << std::format(L"{} readings", 3) << L'\n';

    // 로캘: 숫자 서식이 달라진다.
    std::locale us{ tryLocale({ "en_US.UTF-8", "en_US", "en-US" }) };
    std::locale de{ tryLocale({ "de_DE.UTF-8", "de_DE", "de-DE" }) };
    std::println("로캘 이름: {} / {}", us.name(), de.name());

    std::ostringstream out;
    out.imbue(us);
    out << 1234567;
    std::println("en_US 스트림 {}", out.str());
    std::println("C 로캘 println {}", 1234567);
    std::println("{}", std::format(us, "en_US format {:L}", 1234567));
    std::println("{}", std::format(de, "de_DE format {:L}", 1234567.5));

    // 문자 분류와 변환(로캘을 받는 판)
    std::println("isupper('Q') {} toupper('q') {}", std::isupper('Q', us),
                 std::toupper('q', us));

    // 패싯: 로캘의 한 구성 요소
    auto& punct{ std::use_facet<std::numpunct<char>>(de) };
    std::println("de 소수점 '{}' 천 단위 '{}'", punct.decimal_point(),
                 punct.thousands_sep());
}
