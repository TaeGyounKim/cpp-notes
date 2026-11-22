#include <memory>
#include <print>
#include <string>
#include <utility>
#include <vector>

class Track : public std::enable_shared_from_this<Track>
{
public:
    explicit Track(std::string title) : m_title{ std::move(title) } {}
    const std::string& getTitle() const { return m_title; }

    // 자기 자신을 가리키는 shared_ptr를 안전하게 돌려준다.
    std::shared_ptr<Track> getShared() { return shared_from_this(); }

private:
    std::string m_title;
};

// 1. 소유와 상관없이 쓰기만: 참조로 받는다.
void play(const Track& track)
{
    std::println("재생: {}", track.getTitle());
}

// 2. 소유를 나눠 갖는다: shared_ptr를 값으로 받는다.
class Queue
{
public:
    void add(std::shared_ptr<Track> track)
    {
        m_tracks.push_back(std::move(track));
    }

private:
    std::vector<std::shared_ptr<Track>> m_tracks;
};

// 3. 소유를 넘겨받는다: unique_ptr를 값으로 받는다.
void archive(std::unique_ptr<Track> track)
{
    std::println("보관: {}", track->getTitle());
}   // 여기서 지워진다.

// 만들어서 돌려주기: 값으로 돌려주면 된다. 복사가 아니라 이동된다.
std::unique_ptr<Track> load(std::string title)
{
    auto track{ std::make_unique<Track>(std::move(title)) };
    return track;
}

int main()
{
    auto song{ std::make_shared<Track>("Intro") };
    play(*song);

    Queue queue;
    queue.add(song);
    std::println("큐에 넣은 뒤 횟수: {}", song.use_count());

    auto again{ song->getShared() };
    std::println("getShared 뒤 횟수: {}", song.use_count());

    archive(load("Demo"));
}
