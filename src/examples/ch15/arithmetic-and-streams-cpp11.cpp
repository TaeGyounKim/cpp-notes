// 단항·증감·스트림 연산자 오버로딩은 C++98부터 같다. println만 cout으로 바꿨다.
#include <iostream>
#include <sstream>

class Celsius
{
public:
    explicit Celsius(double value = 0) : m_value(value) {}
    double value() const { return m_value; }
    void set(double value) { m_value = value; }

    // 단항 -: 새 객체를 만들어 값으로 돌려준다.
    Celsius operator-() const { return Celsius{ -m_value }; }

    // 전위 ++: 바뀐 자신을 참조로
    Celsius& operator++()
    {
        ++m_value;
        return *this;
    }

    // 후위 ++: int는 구별용. 바뀌기 전 값을 복사해 값으로
    Celsius operator++(int)
    {
        Celsius old{ *this };
        ++(*this);           // 전위 판으로 구현한다.
        return old;
    }

private:
    double m_value{ 0 };
};

// 스트림 연산자: 왼쪽이 스트림이므로 전역. 스트림 참조를 돌려줘 이어 쓰게 한다.
std::ostream& operator<<(std::ostream& out, const Celsius& c)
{
    out << c.value() << "도";
    return out;
}

std::istream& operator>>(std::istream& in, Celsius& c)
{
    double value{ 0 };
    if (in >> value) { c.set(value); }   // 읽기에 실패하면 c를 바꾸지 않는다.
    return in;
}

int main()
{
    Celsius a{ 21.5 };
    Celsius b{ -a };
    std::cout << "a = " << a << ", -a = " << b << '\n';

    Celsius before{ a++ };   // 후위: 이전 값
    Celsius after{ ++a };    // 전위: 바뀐 값
    std::cout << before << ' ' << after << ' ' << a << '\n';

    // 어떤 입력 스트림이든 된다. 여기서는 문자열 스트림
    std::istringstream in{ "18.5 30 x" };
    Celsius x, y, z{ 99 };
    in >> x >> y >> z;       // operator>>(operator>>(operator>>(in, x), y), z)
    std::cout << x << ' ' << y << ' ' << z << " (실패: " << in.fail()
              << ")\n";

    std::ostringstream out;
    out << x << '/' << y;    // 어떤 출력 스트림이든 된다.
    std::cout << "문자열: " << out.str() << '\n';
}
