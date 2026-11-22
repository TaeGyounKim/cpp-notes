#include <print>
#include <utility>

struct Tracer
{
    Tracer() = default;
    Tracer(const Tracer&) { std::println("    복사 생성자"); }
    Tracer(Tracer&&) noexcept { std::println("    이동 생성자"); }
    Tracer& operator=(const Tracer&)
    {
        std::println("    복사 대입");
        return *this;
    }
    Tracer& operator=(Tracer&&) noexcept
    {
        std::println("    이동 대입");
        return *this;
    }
};

class Holder
{
public:
    // 어차피 복사해 둘 매개변수: 값으로 받고 멤버로 옮긴다.
    void set(Tracer value) { m_value = std::move(value); }

private:
    Tracer m_value;
};

int main()
{
    Holder holder;
    Tracer named;

    std::println("좌측값을 넘김");
    holder.set(named);      // 매개변수로 복사 1번, 멤버로 이동 1번

    std::println("우측값을 넘김");
    holder.set(Tracer{});   // 복사 없음: 매개변수 생성은 생략, 멤버로 이동 1번
}
