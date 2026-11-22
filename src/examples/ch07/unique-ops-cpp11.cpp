#include <iostream>
#include <memory>
#include <string>
#include <utility>

class Song
{
public:
    explicit Song(std::string title) : m_title{ title } {}
    ~Song() { std::cout << "  [-] " << m_title << '\n'; }
    const std::string& getTitle() const { return m_title; }

private:
    std::string m_title;
};

// std::make_unique는 C++14부터. C++11에서는 이렇게 직접 만들어 쓴다.
template <typename T, typename... Args>
std::unique_ptr<T> makeUnique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

int main()
{
    std::unique_ptr<Song> song{ makeUnique<Song>("Intro") };
    std::unique_ptr<Song> moved{ std::move(song) };   // move는 C++11부터
    std::cout << moved->getTitle() << ", song 비었음: "
              << (song == nullptr) << '\n';
}
