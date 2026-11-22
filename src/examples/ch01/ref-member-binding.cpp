#include <print>
#include <utility>

// 참조 데이터 멤버는 생성자 초기화 리스트에서 초기화해야 한다.
class Doubler
{
public:
    Doubler(int& target)
        : m_target{ target }
    {
    }

    void run() { m_target *= 2; }

private:
    int& m_target;
};

int main()
{
    int value{ 21 };
    Doubler doubler{ value };
    doubler.run();
    std::println("{}", value);

    // 구조적 바인딩과 참조
    std::pair item{ 4500, 'A' };

    auto [priceCopy, gradeCopy]{ item };   // 복사본
    priceCopy = 0;
    std::println("{}", item.first);        // 그대로 4500

    auto& [price, grade]{ item };          // 원본의 다른 이름
    price = 5000;
    std::println("{}", item.first);        // 5000

    const auto& [p, g]{ item };            // 읽기 전용
    std::println("{} {}", p, g);
}
