#include <print>
#include <stdexcept>

// 측정값 하나. 숫자처럼 더하고 나눌 수 있게 만든다.
class Reading
{
public:
    Reading() = default;
    Reading(double value) : m_value{ value } {}   // 변환 생성자(explicit 아님)

    double value() const { return m_value; }

    // 복합 대입 연산자: 왼쪽 객체를 바꾸고 그 참조를 돌려준다. 멤버로 둔다.
    Reading& operator+=(const Reading& rhs)
    {
        m_value += rhs.m_value;
        return *this;
    }
    Reading& operator/=(const Reading& rhs)
    {
        if (rhs.m_value == 0.0) {
            throw std::invalid_argument{ "0으로 나눔" };
        }
        m_value /= rhs.m_value;
        return *this;
    }

private:
    double m_value{ 0.0 };
};

// 이항 산술 연산자: 전역 함수로. 복합 대입 연산자에 맡긴다.
Reading operator+(const Reading& lhs, const Reading& rhs)
{
    Reading result{ lhs };   // 사본을 만들고
    result += rhs;           // +=에 맡긴다.
    return result;
}

Reading operator/(const Reading& lhs, const Reading& rhs)
{
    Reading result{ lhs };
    result /= rhs;
    return result;
}

int main()
{
    Reading morning{ 18.5 };
    Reading noon{ 24.0 };

    Reading sum{ morning + noon };     // operator+(morning, noon)
    std::println("합: {}", sum.value());

    // 변환 생성자 덕분에 double이 Reading으로 바뀐다. 양쪽 다 된다.
    std::println("{} {}", (morning + 1.5).value(), (1.5 + morning).value());

    Reading total;
    total += morning;
    total += noon;
    total += 21.5;                     // double -> Reading
    std::println("평균: {}", (total / 3).value());

    try {
        std::println("{}", (total / 0).value());
    } catch (const std::invalid_argument& e) {
        std::println("오류: {}", e.what());
    }
}
