#include <print>
#include <string>
#include <utility>
#include <vector>

struct City
{
    std::string name;
    std::string language;
};

class CityMap
{
public:
    // 흔한 경우: 이름만 넘기면 된다. 언어는 기본값 "ko"
    // 드문 경우: 언어를 직접 정할 수도 있다.
    void addCity(std::string name, std::string language = "ko")
    {
        m_cities.push_back({ std::move(name), std::move(language) });
    }

    void print() const
    {
        for (const auto& city : m_cities) {
            std::println("{} ({})", city.name, city.language);
        }
    }

private:
    std::vector<City> m_cities;
};

int main()
{
    CityMap map;
    map.addCity("서울");
    map.addCity("부산");
    map.addCity("Tokyo", "en");
    map.print();
}
