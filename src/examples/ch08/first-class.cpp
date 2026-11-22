#include <print>

// 클래스 정의: 멤버의 선언만 모은다. 세미콜론으로 끝난다.
class Temperature
{
public:
    void setCelsius(double celsius);
    double getCelsius() const;   // 객체를 바꾸지 않으므로 const

private:
    double m_celsius{ 0.0 };     // 클래스 안 멤버 초기화
};

// 멤버 함수 정의: 클래스 이름과 ::를 붙인다. 접근 지정자는 다시 적지 않는다.
void Temperature::setCelsius(double celsius)
{
    m_celsius = celsius;   // 이 함수를 부른 바로 그 객체의 m_celsius
}

double Temperature::getCelsius() const
{
    return m_celsius;
}

int main()
{
    Temperature morning;
    Temperature noon;

    // 같은 멤버 함수, 다른 객체: 각자 자기 m_celsius를 바꾼다.
    morning.setCelsius(12.5);
    noon.setCelsius(24.0);

    std::println("아침 {}도, 낮 {}도", morning.getCelsius(), noon.getCelsius());

    Temperature unset;   // 아무것도 정하지 않아도 0으로 시작
    std::println("정하지 않은 값: {}", unset.getCelsius());
}
