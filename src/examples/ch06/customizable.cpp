#include <functional>
#include <print>
#include <string>
#include <string_view>
#include <utility>

class Uploader
{
public:
    using ErrorHandler = std::function<void(std::string_view)>;

    // 맞춤 설정: 오류가 났을 때 할 일을 클라이언트가 정할 수 있다.
    // 정하지 않으면 아무것도 하지 않는다(기본 동작).
    void setErrorHandler(ErrorHandler handler)
    {
        m_onError = std::move(handler);
    }

    bool upload(std::string_view file, int sizeMb)
    {
        if (sizeMb > 100) {
            if (m_onError) {
                m_onError("too large: " + std::string{ file });
            }
            return false;
        }
        std::println("업로드: {} ({}MB)", file, sizeMb);
        return true;
    }

private:
    ErrorHandler m_onError;
};

int main()
{
    Uploader quiet;
    quiet.upload("a.png", 3);
    quiet.upload("movie.mp4", 700);   // 아무 말 없이 실패만 알린다.

    Uploader verbose;
    int errorCount{ 0 };
    // 람다를 넘겨 오류를 세고 출력하게 맞춘다.
    verbose.setErrorHandler([&errorCount](std::string_view message) {
        ++errorCount;
        std::println("[오류 {}] {}", errorCount, message);
    });
    verbose.upload("movie.mp4", 700);
    verbose.upload("backup.zip", 300);
}
