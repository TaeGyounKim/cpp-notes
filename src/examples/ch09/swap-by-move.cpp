#include <print>
#include <utility>

struct Heavy
{
    Heavy() = default;
    Heavy(const Heavy&) { std::println("    복사"); }
    Heavy(Heavy&&) noexcept { std::println("    이동"); }
    Heavy& operator=(const Heavy&)
    {
        std::println("    복사 대입");
        return *this;
    }
    Heavy& operator=(Heavy&&) noexcept
    {
        std::println("    이동 대입");
        return *this;
    }
};

void swapCopy(Heavy& a, Heavy& b)
{
    Heavy temp{ a };
    a = b;
    b = temp;
}

void swapMove(Heavy& a, Heavy& b)
{
    Heavy temp{ std::move(a) };
    a = std::move(b);
    b = std::move(temp);
}

int main()
{
    Heavy x;
    Heavy y;
    std::println("swapCopy");
    swapCopy(x, y);
    std::println("swapMove");
    swapMove(x, y);
    std::println("std::swap");
    std::swap(x, y);   // 표준 swap도 이동으로 구현되어 있다.
}
