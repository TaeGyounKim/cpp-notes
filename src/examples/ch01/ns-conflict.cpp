#include <print>

// ---- 외부 라이브러리에서 온 코드라고 가정 ----
void play()
{
    std::println("영상을 재생합니다.");
}

// ---- 내가 쓴 코드 ----
void play()
{
    std::println("소리를 재생합니다.");
}

int main()
{
    play();
}
