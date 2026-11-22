#include <memory>
#include <print>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

// 확장을 위한 설계: 새 채널을 더해도 Notifier는 고치지 않는다.
class Channel
{
public:
    virtual ~Channel() = default;
    virtual void send(std::string_view message) const = 0;
};

class EmailChannel : public Channel
{
public:
    explicit EmailChannel(std::string address) : m_address{ address } {}
    void send(std::string_view message) const override
    {
        std::println("[메일 → {}] {}", m_address, message);
    }

private:
    std::string m_address;
};

class SmsChannel : public Channel
{
public:
    explicit SmsChannel(std::string phone) : m_phone{ phone } {}
    void send(std::string_view message) const override
    {
        std::println("[문자 → {}] {}", m_phone, message);
    }

private:
    std::string m_phone;
};

// 나중에 추가한 채널. 아래 Notifier는 한 글자도 바뀌지 않았다.
class PushChannel : public Channel
{
public:
    void send(std::string_view message) const override
    {
        std::println("[앱 알림] {}", message);
    }
};

class Notifier
{
public:
    void add(std::unique_ptr<Channel> channel)
    {
        m_channels.push_back(std::move(channel));
    }

    void notify(std::string_view message) const
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
    notifier.add(std::make_unique<EmailChannel>("kim@example.com"));
    notifier.add(std::make_unique<SmsChannel>("010-0000-0000"));
    notifier.add(std::make_unique<PushChannel>());
    notifier.notify("주문이 발송되었습니다");
}
