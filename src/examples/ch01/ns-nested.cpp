#include <print>

// C++17: 중첩 네임스페이스를 한 줄로 쓴다.
namespace studio::audio::effects {
    void echo()
    {
        std::println("메아리 효과");
    }
}

// 네임스페이스 별칭: 긴 이름에 짧은 이름을 붙인다.
namespace fx = studio::audio::effects;

int main()
{
    studio::audio::effects::echo();
    fx::echo();
}
