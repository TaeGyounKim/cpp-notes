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
    const std::string& getTitle() const { return m_title; }

private:
    std::string m_title;
};

// 소유하지 않고 잠깐 쓰기만 하는 함수는 맨 포인터나 참조로 받는다.
void show(const Song* song)
{
    std::println("  재생 중: {}", song->getTitle());
}

// 소유권을 넘겨받아 보관하는 클래스
class Playlist
{
public:
    void add(std::unique_ptr<Song> song) { m_last = std::move(song); }

private:
    std::unique_ptr<Song> m_last;
};

int main()
{
    std::println("만들기");
    auto song{ std::make_unique<Song>("Intro") };   // 생성자 인수를 넘긴다.
    std::println("  {}, {}", song->getTitle(), (*song).getTitle());

    std::println("get(): 소유는 그대로, 주소만 빌려준다");
    show(song.get());

    std::println("reset(새 객체): 옛 객체를 지우고 새것을 가진다");
    song.reset(new Song{ "Verse" });

    std::println("move: 소유권을 넘긴다");
    Playlist playlist;
    playlist.add(std::move(song));
    std::println("  song은 이제 비었는가: {}", song == nullptr);

    std::println("release(): 소유를 포기한다. 지우는 것은 이제 내 몫");
    auto other{ std::make_unique<Song>("Outro") };
    Song* raw{ other.release() };
    delete raw;
    raw = nullptr;

    std::println("main 끝");
}   // playlist가 사라지며 Verse를 지운다.
