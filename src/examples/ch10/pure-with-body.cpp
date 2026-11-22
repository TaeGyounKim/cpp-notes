#include <print>

class Field
{
public:
    virtual ~Field() = default;
    virtual void reset() = 0;   // 순수 가상 함수
};

// 순수 가상 함수에도 클래스 밖에서 구현을 줄 수 있다. 그래도 Field는 추상
void Field::reset() { std::println("  Field::reset: 공통 정리"); }

class TextField : public Field
{
public:
    void reset() override
    {
        Field::reset();   // 기반 클래스의 구현을 부른다.
        std::println("  TextField::reset: 글자 지움");
    }
};

int main()
{
    TextField name;
    Field& field{ name };
    field.reset();
}
