#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Channel
{
public:
    virtual ~Channel() = default;
    // std::string_view(C++17) 대신 const std::string&로 받는다.
    virtual void send(const std::string& message) const = 0;
};

class PushChannel : public Channel
{
public:
    void send(const std::string& message) const override
    {
        std::cout << "[앱 알림] " << message << '\n';
    }
};

class Notifier
{
public:
    void add(std::unique_ptr<Channel> channel)
    {
        m_channels.push_back(std::move(channel));
    }

    void notify(const std::string& message) const
    {
        for (const auto& channel : m_channels) {
            channel->send(message);
        }
    }

private:
    std::vector<std::unique_ptr<Channel>> m_channels;
};

int main()
{
    Notifier notifier;
    // std::make_unique(C++14) 대신 new로 만든 포인터를 넘긴다.
    notifier.add(std::unique_ptr<Channel>(new PushChannel()));
    notifier.notify("주문이 발송되었습니다");
}
