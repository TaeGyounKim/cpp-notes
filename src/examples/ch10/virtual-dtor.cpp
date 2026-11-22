#include <memory>
#include <print>

class Sensor
{
public:
    ~Sensor() { std::println("  ~Sensor"); }   // virtual이 아님: 문제
};

class Logger : public Sensor
{
public:
    Logger() : m_buffer{ std::make_unique<char[]>(1024) }
    {
        std::println("  Logger: 버퍼 1024바이트 확보");
    }
    ~Logger() { std::println("  ~Logger: 버퍼 반납"); }

private:
    std::unique_ptr<char[]> m_buffer;
};

class SafeSensor
{
public:
    virtual ~SafeSensor() { std::println("  ~SafeSensor"); }   // virtual
};

class SafeLogger : public SafeSensor
{
public:
    SafeLogger() : m_buffer{ std::make_unique<char[]>(1024) } {}
    ~SafeLogger() override { std::println("  ~SafeLogger: 버퍼 반납"); }

private:
    std::unique_ptr<char[]> m_buffer;
};

int main()
{
    std::println("비가상 소멸자");
    Sensor* p{ new Logger{} };
    delete p;   // 정의되지 않은 동작. 보통 ~Sensor만 불리고 ~Logger는 건너뜀

    std::println("가상 소멸자");
    SafeSensor* q{ new SafeLogger{} };
    delete q;   // ~SafeLogger가 먼저, 그다음 ~SafeSensor
}
