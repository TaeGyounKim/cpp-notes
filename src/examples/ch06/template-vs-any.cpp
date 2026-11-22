#include <any>
#include <print>
#include <string>
#include <vector>

// 템플릿: 담을 타입이 정해진 상자. 다른 타입은 컴파일 단계에서 거부된다.
template <typename T>
class Shelf
{
public:
    void put(const T& item) { m_items.push_back(item); }
    const T& get(std::size_t index) const { return m_items.at(index); }

private:
    std::vector<T> m_items;
};

int main()
{
    Shelf<std::string> titles;
    titles.put("C++ Basics");
    // titles.put(42);   // 컴파일 오류: int는 std::string이 아니다.
    std::println("템플릿: {}", titles.get(0));

    // std::any: 무엇이든 담는다. 대신 꺼낼 때 타입을 직접 말해야 한다.
    std::vector<std::any> anything;
    anything.push_back(std::string{ "C++ Basics" });
    anything.push_back(42);

    // 맞는 타입으로 꺼내면 된다.
    std::println("any: {}", std::any_cast<std::string>(anything[0]));

    // 틀린 타입으로 꺼내면 실행 중에야 알게 된다.
    try {
        std::println("{}", std::any_cast<std::string>(anything[1]));
    } catch (const std::bad_any_cast& error) {
        std::println("실행 중 오류: {}", error.what());
    }
}
