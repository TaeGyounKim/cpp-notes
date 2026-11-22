#include <functional>
#include <iostream>
#include <string>

class Uploader
{
public:
    // std::function과 람다는 C++11부터 쓸 수 있다.
    // std::string_view(C++17) 대신 const std::string&를 받는다.
    using ErrorHandler = std::function<void(const std::string&)>;

    void setErrorHandler(ErrorHandler handler) { m_onError = handler; }

    bool upload(const std::string& file, int sizeMb)
    {
        if (sizeMb > 100) {
            if (m_onError) {
                m_onError("too large: " + file);
            }
            return false;
        }
        std::cout << "업로드: " << file << '\n';
        return true;
    }

private:
    ErrorHandler m_onError;
};

int main()
{
    Uploader uploader;
    uploader.setErrorHandler([](const std::string& message) {
        std::cout << "[오류] " << message << '\n';
    });
    uploader.upload("a.png", 3);
    uploader.upload("movie.mp4", 700);
}
