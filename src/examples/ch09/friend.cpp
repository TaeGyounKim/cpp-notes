#include <print>

class Thermometer;

class Inspector
{
public:
    void check(const Thermometer& t);   // 이 멤버 함수 하나만 friend
};

class Thermometer
{
    friend class Technician;                          // 클래스 전체
    friend void Inspector::check(const Thermometer&); // 멤버 함수 하나
    friend void printReport(const Thermometer& t);    // 독립 함수

public:
    explicit Thermometer(double raw) : m_raw{ raw } {}
    double celsius() const { return m_raw + m_offset; }

private:
    double m_raw;            // 센서가 읽은 값
    double m_offset{ 0.0 };  // 보정값: 밖에서 함부로 바꾸면 안 된다.
};

class Technician
{
public:
    void calibrate(Thermometer& t, double offset)
    {
        t.m_offset = offset;   // friend라서 private 멤버에 접근
    }
};

void Inspector::check(const Thermometer& t)
{
    std::println("점검: 보정값 {}", t.m_offset);
}

// friend 선언이 이 함수의 원형 역할도 한다. 정의에는 friend를 쓰지 않는다.
void printReport(const Thermometer& t)
{
    std::println("원래 값 {} + 보정 {} = {}", t.m_raw, t.m_offset,
                 t.celsius());
}

int main()
{
    Thermometer t{ 21.3 };
    Technician{}.calibrate(t, -0.8);
    Inspector{}.check(t);
    printReport(t);
    // t.m_offset = 5.0;   // 컴파일 오류: main은 friend가 아니다.
}
