#include <format>
#include <print>

struct Color
{
    int red;
    int green;
    int blue;
};

// Color를 형식화하는 방법을 표준 라이브러리에 알려 준다.
//   {}   또는 {:d}  ->  rgb(255, 128, 0)
//   {:h}            ->  #ff8000
template <>
class std::formatter<Color>
{
public:
    // 1. 형식 지정자를 해석한다. 콜론 뒤부터 '}' 앞까지가 넘어온다.
    constexpr auto parse(auto& context)
    {
        auto iter{ context.begin() };
        if (iter != context.end() && *iter != '}') {
            if (*iter == 'h') {
                m_hex = true;
            } else if (*iter == 'd') {
                m_hex = false;
            } else {
                throw std::format_error{ "Invalid Color format." };
            }
            ++iter;
        }
        if (iter != context.end() && *iter != '}') {
            throw std::format_error{ "Invalid Color format." };
        }
        return iter;   // 해석이 끝난 위치를 돌려준다.
    }

    // 2. 해석한 내용에 따라 값을 출력한다.
    auto format(const Color& color, auto& context) const
    {
        if (m_hex) {
            return std::format_to(context.out(), "#{:02x}{:02x}{:02x}",
                                  color.red, color.green, color.blue);
        }
        return std::format_to(context.out(), "rgb({}, {}, {})", color.red,
                              color.green, color.blue);
    }

private:
    bool m_hex{ false };
};

int main()
{
    Color orange{ 255, 128, 0 };

    std::println("{}", orange);
    std::println("{:d}", orange);
    std::println("{:h}", orange);
    std::println("색: {0:h} = {0}", orange);

    // 잘못된 형식 지정자: 실행 중 검사에서는 예외가 던져진다.
    try {
        auto text{ std::vformat("{:z}", std::make_format_args(orange)) };
        std::println("{}", text);
    } catch (const std::format_error& exception) {
        std::println("format_error: {}", exception.what());
    }
}
