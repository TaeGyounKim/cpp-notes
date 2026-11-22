#include <print>

namespace audio {
    void play()
    {
        std::println("audio의 play");
    }
}

// 전역 네임스페이스에도 play가 있다.
void play()
{
    std::println("전역의 play");
}

// using 지시문: 이름을 들여오지 않으므로 여기서는 충돌하지 않는다.
using namespace audio;

int main()
{
    audio::play();
    ::play();   // 맨 앞의 :: 는 "전역 네임스페이스의"라는 뜻
}
