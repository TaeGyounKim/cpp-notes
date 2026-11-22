#include <iostream>
#include <string>

// source_location(C++20) 이전에는 매크로로 위치를 모았다.
// __FILE__, __LINE__은 C부터, __func__는 C++11부터 있다.
#define LOG(message) \
    logMessage((message), __FILE__, __LINE__, __func__)

void logMessage(const std::string& message, const char* file, int line,
                const char* function)
{
    std::cout << file << '(' << line << "): " << function << ": " << message
              << '\n';
}

void readSensor()
{
    LOG("측정 시작");
}

int main()
{
    readSensor();
}
