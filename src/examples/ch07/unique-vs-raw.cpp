#include <memory>
#include <print>
#include <stdexcept>

class Photo
{
public:
    Photo() { ++s_alive; }
    ~Photo() { --s_alive; }
    void upload(bool fail)
    {
        if (fail) {
            throw std::runtime_error{ "network down" };
        }
    }
    static int alive() { return s_alive; }

private:
    static inline int s_alive{ 0 };
};

void withRawPointer(bool fail)
{
    Photo* photo{ new Photo{} };
    photo->upload(fail);   // 예외가 나면 아래 delete까지 가지 못한다.
    delete photo;
}

void withUniquePtr(bool fail)
{
    auto photo{ std::make_unique<Photo>() };
    photo->upload(fail);   // 예외가 나도 photo가 범위를 벗어나며 지운다.
}

int main()
{
    for (bool fail : { false, true }) {
        try {
            withRawPointer(fail);
        } catch (const std::exception&) {
        }
    }
    std::println("맨 포인터: 남은 Photo {}개", Photo::alive());

    for (bool fail : { false, true }) {
        try {
            withUniquePtr(fail);
        } catch (const std::exception&) {
        }
    }
    std::println("unique_ptr 뒤에도 늘지 않음: {}개", Photo::alive());
}
