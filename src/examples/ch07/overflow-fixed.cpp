#include <print>
#include <string>
#include <vector>

// 네트워크에서 조금씩 받는다고 치자. 몇 번, 얼마나 올지 모른다.
std::vector<std::string> receiveChunks()
{
    return { "C++ ", "strings ", "grow ", "as ", "needed" };
}

int main()
{
    // std::string은 이어 붙일 때 필요한 만큼 스스로 메모리를 늘린다.
    std::string message;
    for (const auto& chunk : receiveChunks()) {
        message += chunk;
    }
    std::println("{} ({}글자)", message, message.size());
}
