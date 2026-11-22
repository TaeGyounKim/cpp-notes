#include <memory>
#include <print>
#include <string>
#include <utility>

struct Session
{
    explicit Session(std::string name) : user{ std::move(name) } {}
    ~Session() { std::println("  세션 종료: {}", user); }
    std::string user;
};

void check(const std::weak_ptr<Session>& weak)
{
    // lock(): 아직 살아 있으면 shared_ptr를, 아니면 빈 shared_ptr를 준다.
    if (auto session{ weak.lock() }) {
        std::println("  살아 있음: {}", session->user);
    } else {
        std::println("  이미 사라짐");
    }
}

int main()
{
    auto session{ std::make_shared<Session>("kim") };
    std::weak_ptr<Session> watcher{ session };   // 소유하지 않고 지켜본다.

    std::println("참조 횟수: {}", session.use_count());   // weak는 세지 않는다.
    check(watcher);

    session.reset();   // 유일한 주인이 손을 뗀다. weak_ptr가 있어도 지워진다.
    std::println("expired: {}", watcher.expired());
    check(watcher);
}
