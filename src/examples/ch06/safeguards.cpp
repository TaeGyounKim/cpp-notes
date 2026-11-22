#include <cstddef>
#include <print>
#include <stdexcept>
#include <vector>

class Playlist
{
public:
    void add(int songId) { m_songs.push_back(songId); }
    std::size_t size() const { return m_songs.size(); }

    // 계약에 의한 설계: 검사하지 않는다.
    // 사전 조건: index < size(). 지키는 것은 부르는 쪽의 책임이다.
    int operator[](std::size_t index) const { return m_songs[index]; }

    // 안전한 설계: 검사하고, 어기면 예외를 던진다.
    int at(std::size_t index) const
    {
        if (index >= m_songs.size()) {
            throw std::out_of_range{ "no such song" };
        }
        return m_songs[index];
    }

    // 값이 이치에 맞는지 확인하고 받는다.
    void setVolume(int volume)
    {
        if (volume < 0 || volume > 100) {
            throw std::invalid_argument{ "volume must be 0..100" };
        }
        m_volume = volume;
    }

private:
    std::vector<int> m_songs;
    int m_volume{ 50 };
};

int main()
{
    Playlist playlist;
    playlist.add(101);
    playlist.add(205);

    // 번호가 범위 안이라는 것을 반복문이 보장한다. 검사 없는 쪽이 알맞다.
    for (std::size_t i{ 0 }; i < playlist.size(); ++i) {
        std::println("{}번 곡: {}", i, playlist[i]);
    }

    // 사용자가 입력한 번호처럼 믿을 수 없는 값에는 검사하는 쪽을 쓴다.
    try {
        std::println("{}", playlist.at(7));
    } catch (const std::out_of_range& error) {
        std::println("오류: {}", error.what());
    }

    try {
        playlist.setVolume(150);
    } catch (const std::invalid_argument& error) {
        std::println("오류: {}", error.what());
    }
}
