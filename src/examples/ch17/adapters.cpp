#include <algorithm>
#include <iterator>
#include <print>
#include <string>
#include <vector>

// 복사인지 이동인지 보여 주는 클래스
class Sample
{
public:
    explicit Sample(std::string name) : m_name{ std::move(name) } {}
    Sample(const Sample& other) : m_name{ other.m_name }
    {
        std::println("  복사: {}", m_name);
    }
    Sample(Sample&& other) noexcept : m_name{ std::move(other.m_name) }
    {
        std::println("  이동: {}", m_name);
    }
    const std::string& name() const { return m_name; }

private:
    std::string m_name;
};

int main()
{
    // 역방향 반복자: 마지막으로 나오는 22를 찾는다.
    std::vector<int> v{ 11, 22, 33, 22, 11 };
    auto fwd{ std::find(v.begin(), v.end(), 22) };
    auto rev{ std::find(v.rbegin(), v.rend(), 22) };
    std::println("앞에서 찾은 위치 {}", std::distance(v.begin(), fwd));
    // base()는 한 칸 뒤를 가리키므로 하나 뺀다.
    std::println("뒤에서 찾은 위치 {}",
                 std::distance(v.begin(), rev.base()) - 1);

    std::vector<Sample> source;
    source.reserve(2);                 // 재할당으로 인한 이동을 막는다.
    source.emplace_back("A");
    source.emplace_back("B");

    std::println("보통 반복자로 만들기");
    std::vector<Sample> copied(source.begin(), source.end());

    std::println("이동 반복자로 만들기");
    std::vector<Sample> moved(std::make_move_iterator(source.begin()),
                              std::make_move_iterator(source.end()));
    std::println("옮긴 뒤 원본 이름 길이 {}, {}", source[0].name().size(),
                 source[1].name().size());
}
