#include <print>
#include <string>
#include <string_view>
#include <vector>

// 1. 서비스의 인터페이스: "로그를 남길 수 있다"만 약속한다.
class Logger
{
public:
    virtual ~Logger() = default;
    virtual void log(std::string_view message) = 0;
};

// 2. 인터페이스의 구현 하나: 콘솔에 출력한다.
class ConsoleLogger : public Logger
{
public:
    void log(std::string_view message) override
    {
        std::println("[log] {}", message);
    }
};

// 구현 둘: 메모리에 모아 둔다. 테스트할 때 쓰기 좋다.
class MemoryLogger : public Logger
{
public:
    void log(std::string_view message) override
    {
        m_messages.emplace_back(message);
    }

    std::size_t getCount() const { return m_messages.size(); }

private:
    std::vector<std::string> m_messages;
};

// 3. 로거를 쓰는 부품. 어떤 로거인지는 모른다.
// 필요한 서비스를 밖에서 넣어 준다(의존성 주입).
class Downloader
{
public:
    explicit Downloader(Logger& logger) : m_logger{ logger } {}

    void download(std::string_view address)
    {
        m_logger.log("start: " + std::string{ address });
        m_logger.log("done");
    }

private:
    Logger& m_logger;
};

int main()
{
    ConsoleLogger consoleLogger;
    Downloader downloader{ consoleLogger };
    downloader.download("example.com/a.zip");

    // Downloader를 고치지 않고 로거만 바꿔 끼운다.
    MemoryLogger memoryLogger;
    Downloader quietDownloader{ memoryLogger };
    quietDownloader.download("example.com/b.zip");
    std::println("모아 둔 로그: {}개", memoryLogger.getCount());
}
