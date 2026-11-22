#include <iostream>
#include <memory>

class Sensor
{
public:
    virtual ~Sensor() = default;   // = default는 C++11부터
};

class Logger : public Sensor
{
public:
    // make_unique(C++14) 대신 new를 unique_ptr에 넘긴다.
    Logger() : m_buffer(new char[1024]) {}
    ~Logger() override { std::cout << "~Logger: 버퍼 반납\n"; }

private:
    std::unique_ptr<char[]> m_buffer;
};

int main()
{
    std::unique_ptr<Sensor> p(new Logger());
}   // p가 사라지며 delete -> 가상 소멸자 덕분에 ~Logger가 불림
