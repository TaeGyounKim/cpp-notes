#include <memory>
#include <print>
#include <string>
#include <utility>

class Song
{
public:
    explicit Song(std::string title) : m_title{ std::move(title) }
    {
        std::println("  [+] {}", m_title);
    }
    ~Song() { std::println("  [-] {}", m_title); }

private:
    std::string m_title;
};

int main()
{
    auto a{ std::make_shared<Song>("Intro") };
    std::println("a만 있을 때: {}", a.use_count());

    {
        auto b{ a };   // 복사: 주인이 하나 늘어난다.
        std::println("b를 복사한 뒤: {}", a.use_count());
    }   // b가 사라진다. 객체는 아직 a가 가지고 있다.
    std::println("b가 사라진 뒤: {}", a.use_count());

    auto c{ a };
    std::println("c를 복사한 뒤: {}", a.use_count());
    a.reset();     // a는 손을 뗀다. 남은 주인 c
    std::println("a.reset() 뒤 c의 횟수: {}", c.use_count());
    std::println("c.reset() 하기 직전");
    c.reset();     // 마지막 주인이 손을 떼는 순간 지워진다.
    std::println("끝");
}
