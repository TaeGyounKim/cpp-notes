#include <print>

class Reading;
void log(const Reading& reading);

class Reading
{
public:
    // 버그: 매개변수와 데이터 멤버의 이름이 같다.
    // celsius = celsius;는 매개변수에 자기 자신을 대입할 뿐이다.
    void setWrong(double celsius) { celsius = celsius; }

    // this->celsius는 "이 객체의 celsius" 멤버다.
    void setRight(double celsius)
    {
        this->celsius = celsius;
        log(*this);   // 이 객체 자체를 다른 함수에 넘긴다.
    }

    double get() const { return celsius; }

private:
    double celsius{ 0.0 };
};

void log(const Reading& reading)
{
    std::println("  기록: {}", reading.get());
}

int main()
{
    Reading reading;
    reading.setWrong(25.0);
    std::println("setWrong 뒤: {}", reading.get());

    reading.setRight(25.0);
    std::println("setRight 뒤: {}", reading.get());
}
