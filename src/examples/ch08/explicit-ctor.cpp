#include <print>

class Loose
{
public:
    Loose(double celsius) : m_celsius{ celsius } {}       // 변환 생성자
    Loose(double low, double high) : m_celsius{ (low + high) / 2 } {}
    double get() const { return m_celsius; }

private:
    double m_celsius;
};

class Strict
{
public:
    explicit Strict(double celsius) : m_celsius{ celsius } {}
    double get() const { return m_celsius; }

private:
    double m_celsius;
};

void showLoose(const Loose& t) { std::println("Loose: {}", t.get()); }
void showStrict(const Strict& t) { std::println("Strict: {}", t.get()); }

int main()
{
    showLoose(30.0);            // double -> Loose로 몰래 변환
    showLoose({ 18.0, 24.0 });  // 인수 둘도 중괄호로 변환(C++11부터)
    Loose t{ 1.0 };
    t = 99.0;                   // 대입에서도 변환이 일어난다.
    std::println("t: {}", t.get());

    // showStrict(30.0);        // 컴파일 오류: 몰래 변환하지 않는다.
    showStrict(Strict{ 30.0 }); // 변환을 드러내 적어야 한다.
}
