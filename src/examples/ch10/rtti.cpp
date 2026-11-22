#include <print>
#include <string>
#include <typeinfo>

class Loggable
{
public:
    virtual ~Loggable() = default;   // typeid가 실제 타입을 보려면 필요
    virtual std::string logMessage() const = 0;
};

class Thermometer : public Loggable
{
public:
    std::string logMessage() const override { return "21.5도"; }
};

class Camera : public Loggable
{
public:
    std::string logMessage() const override { return "사진 3장"; }
};

void logObject(const Loggable& object)
{
    // name()이 돌려주는 이름은 컴파일러마다 다르다.
    std::println("{}: {}", typeid(object).name(), object.logMessage());
}

int main()
{
    Thermometer t;
    Camera c;
    logObject(t);
    logObject(c);

    const Loggable& ref{ t };
    std::println("ref는 Thermometer인가? {}",
                 typeid(ref) == typeid(Thermometer));
    std::println("typeid는 const와 참조를 떼어 낸다: {}",
                 typeid(const Thermometer&) == typeid(Thermometer));
}
