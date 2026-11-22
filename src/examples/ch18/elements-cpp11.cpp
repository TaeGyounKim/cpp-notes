#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// 값 의미론, reference_wrapper, 이동만 되는 타입, noexcept 이동은
// 모두 C++11부터 쓸 수 있다. make_unique(C++14) 대신 new를 감싼다.
class Reading
{
public:
    explicit Reading(int v) : m_value(v) {}
    Reading(const Reading& other) : m_value(other.m_value)
    {
        std::cout << "복사 ";
    }
    Reading(Reading&& other) noexcept : m_value(other.m_value)
    {
        std::cout << "이동 ";
    }

private:
    int m_value;
};

int main()
{
    std::string a = "침실";
    std::vector<std::reference_wrapper<std::string>> refs = { std::ref(a) };
    a = "서재";
    std::cout << refs[0].get() << '\n';

    std::vector<std::unique_ptr<int>> owners;
    owners.push_back(std::unique_ptr<int>(new int(42)));
    std::cout << *owners[0] << '\n';

    std::vector<Reading> v;
    v.reserve(1);
    v.emplace_back(1);
    v.emplace_back(2);                 // 재할당: 기존 원소를 이동
    std::cout << '\n';
}
