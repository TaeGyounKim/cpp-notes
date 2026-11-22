#include <print>

namespace audio {
    void beep()
    {
        std::println("삑");
    }

    void alarm()
    {
        // 같은 네임스페이스 안에서는 접두어 없이 부를 수 있다.
        beep();
        beep();
    }
}

int main()
{
    audio::alarm();
}
