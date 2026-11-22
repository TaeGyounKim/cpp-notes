#include <print>
#include <string>
#include <string_view>
#include <utility>

// 낯선 방식: 쓰는 사람이 open()과 close()를 직접 불러야 한다.
class UnusualRecorder
{
public:
    void open(std::string name)
    {
        m_name = std::move(name);
        std::println("[{}] 열림", m_name);
    }
    void write(std::string_view text) { std::println("[{}] {}", m_name, text); }
    void close() { std::println("[{}] 닫힘", m_name); }

private:
    std::string m_name;
};

// 익숙한 방식: 생성자가 준비하고 소멸자가 정리한다.
class Recorder
{
public:
    explicit Recorder(std::string name) : m_name{ std::move(name) }
    {
        std::println("[{}] 열림", m_name);
    }
    ~Recorder() { std::println("[{}] 닫힘", m_name); }

    void write(std::string_view text) { std::println("[{}] {}", m_name, text); }

private:
    std::string m_name;
};

int main()
{
    {
        UnusualRecorder recorder;
        recorder.open("a.log");
        recorder.write("시작");
        // close()를 잊었다. "닫힘"이 출력되지 않는다.
    }

    {
        Recorder recorder{ "b.log" };
        recorder.write("시작");
    }   // 블록이 끝나면 저절로 닫힌다. 잊을 수가 없다.
}
