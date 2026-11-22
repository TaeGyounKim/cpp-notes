#include <print>

class Sensor
{
public:
    Sensor() { m_reading = new int{}; }    // 생성자에서 잡고
    ~Sensor() { delete m_reading; }       // 소멸자에서 돌려준다. 제대로 짰다.
    void set(int value) { *m_reading = value; }

private:
    int* m_reading;
};

// 매개변수가 "포인터의 참조"다. 부르는 쪽의 포인터를 바꿔 버린다.
// 버그: 원래 가리키던 객체를 지우지 않았다.
void replace(Sensor*& sensor)
{
    sensor = new Sensor{};
}

int main()
{
    Sensor* sensor{ new Sensor{} };   // 첫째 Sensor
    replace(sensor);                  // 이제 둘째 Sensor를 가리킨다.
    sensor->set(42);
    delete sensor;                    // 둘째만 지워진다.
    std::println("끝");
}
