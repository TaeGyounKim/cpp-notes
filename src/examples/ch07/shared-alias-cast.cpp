#include <memory>
#include <print>
#include <string>

struct Profile
{
    std::string name;
    int age{ 0 };
    ~Profile() { std::println("  Profile 소멸"); }
};

class Shape
{
public:
    virtual ~Shape() = default;
};

class Circle : public Shape
{
public:
    double radius{ 2.0 };
};

int main()
{
    std::println("별칭(aliasing)");
    std::shared_ptr<int> age;
    {
        auto profile{ std::make_shared<Profile>() };
        profile->age = 30;
        // profile 객체를 소유하면서, 그 안의 age 멤버를 가리킨다.
        age = std::shared_ptr<int>{ profile, &profile->age };
        std::println("  횟수: {}", profile.use_count());
    }   // profile 변수는 사라졌지만 객체는 age가 붙잡고 있다.
    std::println("  나이: {}", *age);
    age.reset();   // 마지막 주인이 놓을 때 Profile 전체가 지워진다.

    std::println("형변환");
    std::shared_ptr<Shape> shape{ std::make_shared<Circle>() };
    // dynamic_pointer_cast: 실제로 Circle이면 Circle을, 아니면 빈 포인터
    if (auto circle{ std::dynamic_pointer_cast<Circle>(shape) }) {
        std::println("  반지름: {}, 횟수: {}", circle->radius,
                     shape.use_count());
    }
}
