#include <print>

class Battery   // 데이터 멤버로 쓰일 클래스
{
public:
    Battery() { std::println("  2. Battery 생성"); }
    ~Battery() { std::println("  5. Battery 소멸"); }
};

class Device   // 기반 클래스
{
public:
    explicit Device(int id)
    {
        std::println("  1. Device({}) 생성", id);
        describe();   // 생성자 안의 가상 함수 호출
    }
    virtual ~Device() { std::println("  6. Device 소멸"); }
    virtual void describe() const { std::println("     (Device판 describe)"); }
};

class Station : public Device
{
public:
    // 기반 클래스에 기본 생성자가 없으니 초기화 목록에서 직접 부른다.
    explicit Station(int id) : Device{ id }
    {
        std::println("  3. Station 생성자 본문");
    }
    ~Station() override { std::println("  4. Station 소멸자 본문"); }
    void describe() const override { std::println("     (Station판)"); }

private:
    Battery m_battery;
};

int main()
{
    std::println("만들기");
    {
        Station s{ 7 };
    }
    std::println("기반 포인터로 지우기");
    Device* p{ new Station{ 8 } };
    delete p;   // 가상 소멸자 덕분에 4, 5, 6이 모두 불린다.
}
