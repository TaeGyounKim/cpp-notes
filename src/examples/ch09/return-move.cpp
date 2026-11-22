#include <print>
#include <utility>

struct Tracer
{
    Tracer() = default;
    Tracer(const Tracer&) { std::println("    복사 생성자"); }
    Tracer(Tracer&&) noexcept { std::println("    이동 생성자"); }
};

Tracer plain()
{
    Tracer local;
    return local;              // 권장: 복사 생략(NRVO) 또는 이동
}

Tracer withMove()
{
    Tracer local;
    return std::move(local);   // 복사 생략을 막는다. 이동이 일어남
}

Tracer pick(bool first)
{
    Tracer a;
    Tracer b;
    return first ? a : b;      // 좌측값 식: 복사가 일어남
}

Tracer pickBetter(bool first)
{
    Tracer a;
    Tracer b;
    if (first) {
        return a;              // 각각 return 지역변수; 꼴이라 이동이 됨
    }
    return b;
}

int main()
{
    std::println("return local;");
    Tracer t1{ plain() };
    std::println("return std::move(local);");
    Tracer t2{ withMove() };
    std::println("return cond ? a : b;");
    Tracer t3{ pick(true) };
    std::println("if로 나눠 return");
    Tracer t4{ pickBetter(true) };
}
