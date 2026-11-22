#include <initializer_list>
#include <print>
#include <stdexcept>
#include <vector>

class TemperatureLog
{
public:
    // 초기화 목록 생성자: 중괄호 안의 값들을 한꺼번에 받는다.
    TemperatureLog(std::initializer_list<double> values)
    {
        for (double value : values) {   // 범위 기반 for로 하나씩 읽음
            if (value < -273.15) {
                throw std::invalid_argument{ "절대 영도보다 낮은 값" };
            }
        }
        m_values.assign(values);   // vector에 통째로 복사
    }

    void print() const
    {
        std::println("기록 {}개: {}", m_values.size(), m_values);
    }

private:
    std::vector<double> m_values;
};

int main()
{
    try {
        TemperatureLog morning{ 12.5, 14.0, 17.5 };
        morning.print();

        TemperatureLog broken{ 20.0, -300.0 };   // 예외가 던져진다.
        broken.print();
    } catch (const std::invalid_argument& e) {
        std::println("오류: {}", e.what());
    }

    // 표준 라이브러리도 초기화 목록 생성자를 쓴다. {}와 ()의 차이에 주의
    std::vector<int> a{ 6 };   // 원소 하나: 6
    std::vector<int> b(6);     // 원소 여섯 개: 모두 0
    std::println("a: {}  b: {}", a, b);
}
