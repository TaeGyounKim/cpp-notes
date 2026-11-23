#include <cstddef>
#include <cstdio>
#include <functional>
#include <map>
#include <string>

// 구조적 바인딩(C++17), std::exchange(C++14) 없이 쓴 관찰자.
// 함수 안 static 지역 변수의 스레드 안전한 초기화는 C++11부터 보장된다.
class Inventory {
public:
    typedef std::function<void(const std::string&, int)> Observer;

    Inventory() : m_last(0) {}
    std::size_t subscribe(Observer o)
    {
        m_observers[++m_last] = o;
        return m_last;
    }
    void unsubscribe(std::size_t id) { m_observers.erase(id); }
    void set(const std::string& item, int qty)
    {
        std::map<std::size_t, Observer>::const_iterator it;
        for (it = m_observers.begin(); it != m_observers.end(); ++it) {
            it->second(item, qty);
        }
    }

private:
    std::map<std::size_t, Observer> m_observers;
    std::size_t m_last;
};

void print_stock(const std::string& item, int qty)
{
    std::printf("%s -> %d\n", item.c_str(), qty);
}

class AppConfig final {
public:
    static AppConfig& instance()
    {
        static AppConfig config;
        return config;
    }
    AppConfig(const AppConfig&) = delete;
    AppConfig& operator=(const AppConfig&) = delete;
    std::string language;

private:
    AppConfig() : language("ko") { std::printf("(config created)\n"); }
};

int main()
{
    Inventory inv;
    std::size_t id = inv.subscribe(print_stock);
    inv.set("milk", 3);
    inv.unsubscribe(id);
    inv.set("bread", 5);   // 아무도 받지 않음

    AppConfig::instance().language = "en";
    std::printf("%s\n", AppConfig::instance().language.c_str());
}
