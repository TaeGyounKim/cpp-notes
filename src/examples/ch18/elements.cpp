#include <functional>
#include <memory>
#include <print>
#include <string>
#include <vector>

// 이동 생성자에 noexcept가 있으면 vector가 커질 때 이동, 없으면 복사한다.
template <bool NoThrow>
class Reading
{
public:
    explicit Reading(int v) : m_value{ v } {}
    Reading(const Reading& other) : m_value{ other.m_value }
    {
        std::print("복사 ");
    }
    Reading(Reading&& other) noexcept(NoThrow) : m_value{ other.m_value }
    {
        std::print("이동 ");
    }

private:
    int m_value;
};

template <bool NoThrow>
void grow()
{
    std::vector<Reading<NoThrow>> v;
    v.reserve(2);
    v.emplace_back(1);
    v.emplace_back(2);
    std::print("커질 때 기존 원소: ");
    v.emplace_back(3);                 // 용량을 넘어 재할당
    std::println("");
}

int main()
{
    // 값 의미론: 컨테이너는 복사본을 저장한다.
    std::string name{ "거실" };
    std::vector<std::string> rooms{ name };
    name = "부엌";
    std::println("원본 {} / 컨테이너 안 {}", name, rooms[0]);

    // 참조 의미론이 필요하면 reference_wrapper(std::ref)를 담는다.
    std::string a{ "침실" };
    std::vector<std::reference_wrapper<std::string>> refs{ std::ref(a) };
    a = "서재";
    std::println("참조로 본 값 {}", refs[0].get());

    // 이동만 되는 타입(unique_ptr)도 담을 수 있다.
    std::vector<std::unique_ptr<int>> owners;
    owners.push_back(std::make_unique<int>(42));
    // auto copy{ owners };     // 오류: unique_ptr는 복사할 수 없다.
    auto moved{ std::move(owners) };
    std::println("옮긴 벡터의 첫 값 {}", *moved[0]);

    grow<true>();                      // noexcept 이동 생성자
    grow<false>();                     // noexcept가 아님
}
