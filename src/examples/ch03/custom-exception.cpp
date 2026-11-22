#include <print>
#include <stdexcept>
#include <string>

// 방법 1: 특별한 값으로 오류를 알린다. 부르는 쪽이 검사를 잊기 쉽다.
// [[nodiscard]]를 붙이면 반환값을 버릴 때 컴파일러가 경고한다.
[[nodiscard]] int findPort(const std::string& service)
{
    if (service == "http") { return 80; }
    if (service == "https") { return 443; }
    return -1;   // 찾지 못함
}

// 방법 2: 직접 만든 예외. 오류에 관한 정보를 함께 실어 보낸다.
class UnknownServiceError : public std::runtime_error
{
public:
    explicit UnknownServiceError(const std::string& service)
        : std::runtime_error{ "unknown service: " + service }
        , m_service{ service }
    {
    }

    const std::string& getService() const { return m_service; }

private:
    std::string m_service;
};

int getPort(const std::string& service)
{
    const int port{ findPort(service) };
    if (port == -1) {
        throw UnknownServiceError{ service };
    }
    return port;
}

int main()
{
    std::println("{}", getPort("https"));

    try {
        std::println("{}", getPort("gopher"));
    } catch (const UnknownServiceError& error) {
        std::println("오류: {}", error.what());
        std::println("문제가 된 서비스: {}", error.getService());
    }
}
