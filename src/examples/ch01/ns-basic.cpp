#include <print>

namespace audio {
    void play()
    {
        std::println("소리를 재생합니다.");
    }
}

namespace video {
    void play()
    {
        std::println("영상을 재생합니다.");
    }
}

int main()
{
    audio::play();
    video::play();
}
