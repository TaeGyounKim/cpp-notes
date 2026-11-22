#include <cstddef>
#include <iostream>
#include <new>

// 클래스별 operator new/delete는 C++98부터, = delete는 C++11부터 있다.
// 크기를 받는 delete는 클래스 멤버로는 C++98부터 쓸 수 있다.
class Tracked
{
public:
    void* operator new(std::size_t size)
    {
        std::cout << "operator new(" << size << ")\n";
        return ::operator new(size);
    }
    void operator delete(void* ptr, std::size_t size) noexcept
    {
        std::cout << "operator delete(" << size << ")\n";
        ::operator delete(ptr);
    }

private:
    int m_value = 0;
};

class StackOnly
{
public:
    void* operator new(std::size_t) = delete;
};

int main()
{
    Tracked* t = new Tracked;
    delete t;
    StackOnly ok;
    (void)ok;
}
