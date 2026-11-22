#include <format>
#include <print>
#include <string>

struct Version
{
    int major;
    int minor;
};

// 가장 쉬운 방법: 이미 있는 std::string용 formatter를 물려받는다.
// parse는 물려받은 것을 그대로 쓰므로, 너비·정렬 같은 문자열용
// 형식 지정자를 Version에도 그대로 쓸 수 있다.
template <>
class std::formatter<Version> : public std::formatter<std::string>
{
public:
    auto format(const Version& version, auto& context) const
    {
        std::string text{ std::format("v{}.{}", version.major,
                                      version.minor) };
        return std::formatter<std::string>::format(text, context);
    }
};

int main()
{
    Version version{ 2, 15 };

    std::println("{}", version);
    std::println("[{:>10}]", version);
    std::println("[{:*^10}]", version);
}
