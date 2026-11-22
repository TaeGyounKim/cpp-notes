#include <cstddef>
#include <new>
#include <print>
#include <stdexcept>

class Tracked
{
public:
    explicit Tracked(bool fail = false)
    {
        if (fail) { throw std::runtime_error{ "생성자 실패" }; }
    }
    virtual ~Tracked() = default;

    // 이 클래스의 객체에만 쓰이는 할당·해제 함수. 전역 판에 넘긴다.
    void* operator new(std::size_t size)
    {
        std::println("  operator new({})", size);
        return ::operator new(size);
    }
    void operator delete(void* ptr, std::size_t size) noexcept  // 크기도 받음
    {
        std::println("  operator delete(크기 {})", size);
        ::operator delete(ptr);
    }
    void* operator new[](std::size_t size)
    {
        std::println("  operator new[]({})", size);
        return ::operator new[](size);
    }
    void operator delete[](void* ptr) noexcept
    {
        std::println("  operator delete[]");
        ::operator delete[](ptr);
    }

    // 추가 매개변수가 있는 판. new (태그) Tracked{} 모양으로 부른다.
    void* operator new(std::size_t size, int tag)
    {
        std::println("  operator new({}, 태그 {})", size, tag);
        return ::operator new(size);
    }
    // 위 new 뒤 생성자가 던질 때만 불린다.
    void operator delete(void* ptr, int tag) noexcept
    {
        std::println("  operator delete(태그 {})", tag);
        ::operator delete(ptr);
    }
};

class StackOnly
{
public:
    void* operator new(std::size_t) = delete;     // new로 만들 수 없다.
    void* operator new[](std::size_t) = delete;
};

int main()
{
    std::println("new / delete:");
    Tracked* t{ new Tracked{} };
    delete t;

    std::println("new[] / delete[]:");
    Tracked* many{ new Tracked[3] };
    delete[] many;

    std::println("태그를 넘기는 new:");
    Tracked* tagged{ new (7) Tracked{} };
    delete tagged;          // 보통 delete가 불린다.

    std::println("생성자가 던지면 짝이 맞는 delete가 불린다:");
    try {
        Tracked* bad{ new (9) Tracked{ true } };
        delete bad;
    } catch (const std::exception& e) {
        std::println("  잡음: {}", e.what());
    }

    // 배치 new: 이미 있는 메모리 위에 생성자만 부른다.
    alignas(Tracked) std::byte buffer[sizeof(Tracked)];
    Tracked* placed{ ::new (buffer) Tracked{} };
    placed->~Tracked();     // 소멸자는 직접 부르고, 메모리는 해제하지 않는다.
    std::println("배치 new 끝");

    StackOnly ok;           // 스택에는 만들 수 있다.
    (void)ok;
    // StackOnly* p{ new StackOnly };   // 컴파일 오류
}
