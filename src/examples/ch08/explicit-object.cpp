#include <print>

class Temperature
{
public:
    // 명시적 객체 매개변수: this를 붙인 첫 매개변수가 "이 객체"다.
    void setCelsius(this Temperature& self, double celsius)
    {
        self.m_celsius = celsius;   // 숨은 this가 없으므로 self로 접근
    }

    double getCelsius(this const Temperature& self)
    {
        return self.m_celsius;
    }

private:
    double m_celsius{ 0.0 };
};

int main()
{
    Temperature room;
    room.setCelsius(21.5);   // 부르는 모습은 그대로. 인수는 하나만
    std::println("{}", room.getCelsius());
}
