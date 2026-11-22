#include <print>

namespace audio {
    void play()
    {
        std::println("소리를 재생합니다.");
    }

    void stop()
    {
        std::println("소리를 멈춥니다.");
    }
}

namespace video {
    void play()
    {
        std::println("영상을 재생합니다.");
    }
}

// using 지시문: audio의 모든 이름을 접두어 없이 쓴다.
using namespace audio;

// using 선언: std 중에서 println 하나만 접두어 없이 쓴다.
using std::println;

int main()
{
    play();          // audio::play
    stop();          // audio::stop
    video::play();   // video의 것은 여전히 접두어가 필요하다.
    println("끝");   // std::println
}
