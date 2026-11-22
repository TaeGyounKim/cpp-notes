#include <algorithm>
#include <cstddef>
#include <print>
#include <string>
#include <utility>
#include <vector>

class Station   // 격자들이 속한 관측소. 내용은 단순하게
{
public:
    explicit Station(std::string name) : m_name{ std::move(name) } {}
    const std::string& name() const { return m_name; }

private:
    std::string m_name;
};

class Grid
{
public:
    // 클래스 상수: 모든 객체가 함께 쓰는 값
    static constexpr std::size_t MaxWidth{ 100 };
    static constexpr std::size_t MaxHeight{ 100 };

    Grid(const Station& station, std::size_t width = MaxWidth,
         std::size_t height = MaxHeight)
        : m_id{ ms_counter++ },                       // static 멤버 사용
          m_width{ std::min(width, MaxWidth) },       // 최댓값으로 자름
          m_height{ std::min(height, MaxHeight) },
          m_station{ station },                       // 참조 멤버
          m_cells(m_width * m_height)
    {
    }

    void print() const
    {
        std::println("격자 #{} {}x{} ({})", m_id, m_width, m_height,
                     m_station.name());
    }

    static std::size_t created() { return ms_counter; }   // static 게터

private:
    static inline std::size_t ms_counter{ 0 };   // 클래스 전체의 카운터
    const std::size_t m_id;                      // 한번 정하면 바뀌지 않음
    std::size_t m_width;
    std::size_t m_height;
    const Station& m_station;                    // const 참조 멤버
    std::vector<double> m_cells;
};

int main()
{
    Station seoul{ "서울 관측소" };
    Grid a{ seoul, 3, 2 };
    Grid b{ seoul, 500, 4 };   // 너비가 100으로 잘림
    Grid c{ seoul };           // 기본 인수: 100x100
    a.print();
    b.print();
    c.print();
    std::println("만든 격자 수: {}, 최대 너비: {}", Grid::created(),
                 Grid::MaxWidth);
    // a = b;   // 컴파일 오류: const 멤버와 참조 멤버 때문에 대입 불가
}
